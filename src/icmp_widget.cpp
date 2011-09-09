#include "icmp_widget.h"
#include "socket/icmp.h"
#include    <netinet/in_systm.h>
#include <qsettings.h>
#include "public.h"
#include    <netinet/ip_icmp.h>

IcmpWidget::IcmpWidget(QWidget *parent) :
		TabSheet(parent), m_seq(0)
{
	ui.setupUi(this);
	setupUi(ui.sendLayout);

	initProtocol();

	connect(ui.typeBox, SIGNAL(currentIndexChanged(const QString &)), this,
			SLOT( onTypeIndexChanged(const QString &)));
	connect(ui.codeBox, SIGNAL(currentIndexChanged(const QString &)), this,
			SLOT( onCodeIndexChanged(const QString &)));
	connect(ui.checkBox, SIGNAL(clicked ( bool)), ui.checkNumEdit,
			SLOT( setDisabled(bool)));
	connect(ui.idCheckBox, SIGNAL(clicked ( bool)), ui.idEdit,
			SLOT( setDisabled(bool)));
	connect(ui.seqCheckBox, SIGNAL(clicked ( bool)), ui.seqEdit,
			SLOT( setDisabled(bool)));
	connect(ui.moreCheckBox1, SIGNAL(clicked ( bool)), ui.moreEdit1,
			SLOT( setDisabled(bool)));
	connect(ui.moreCheckBox2, SIGNAL(clicked ( bool)), ui.moreEdit2,
			SLOT( setDisabled(bool)));
	connect(ui.moreCheckBox3, SIGNAL(clicked ( bool)), ui.moreEdit3,
			SLOT( setDisabled(bool)));

	ui.checkBox->setChecked(true);
	ui.checkNumEdit->setDisabled(true);

	hideExendedWidget();

	QList<int> keys = m_protocol.keys();
	QList<int>::iterator it;
	for (it = keys.begin(); it != keys.end(); ++it)
	{
		ui.typeBox->addItem(QString::number(*it));
	}

	ui.typeBox->setValidator(new QIntValidator(this));
	ui.codeBox->setValidator(new QIntValidator(this));
	ui.checkNumEdit->setValidator(new QIntValidator(this));
	ui.idEdit->setValidator(new QIntValidator(this));
	ui.seqEdit->setValidator(new QIntValidator(this));
}

void IcmpWidget::initProtocol()
{
	QMap<int, QString> temp;
	temp.insert(0, tr("ping response"));
	m_protocol.insert(0, temp);

	temp.clear();
	temp.insert(0, tr("network unreachable"));
	temp.insert(1, tr("host unreachable"));
	temp.insert(2, tr("protocol unreachable"));
	temp.insert(3, tr("port unreachable"));
	temp.insert(4, tr("需要分片但设置了不分片比特"));
	temp.insert(5, tr("源站选路失败"));
	temp.insert(6, tr("目的网络不认识"));
	temp.insert(7, tr("目的主机不认识"));
	temp.insert(9, tr("目的网络被强制禁止"));
	temp.insert(10, tr("目的主机被强制禁止"));
	temp.insert(11, tr("由于服务类型TOS，网络不可达"));
	temp.insert(12, tr("由于服务类型TOS，主机不可达"));
	temp.insert(13, tr("由于过滤，通讯被强制禁止"));
	temp.insert(14, tr("主机越权"));
	temp.insert(15, tr("优先权终止生效"));
	m_protocol.insert(3, temp);

	temp.clear();
	temp.insert(0, tr("源端被关闭"));
	m_protocol.insert(4, temp);

	temp.clear();
	temp.insert(0, tr("对网络重定向"));
	temp.insert(1, tr("对主机重定向"));
	temp.insert(2, tr("对服务类型和网络重定向"));
	temp.insert(3, tr("对服务类型和主机重定向"));
	m_protocol.insert(5, temp);

	temp.clear();
	temp.insert(0, tr("ping request"));
	m_protocol.insert(8, temp);

	temp.clear();
	temp.insert(0, tr("路由器通告"));
	m_protocol.insert(9, temp);

	temp.clear();
	temp.insert(0, tr("路由器请求"));
	m_protocol.insert(10, temp);

	temp.clear();
	temp.insert(0, tr("传输期间生存时间为0"));
	temp.insert(1, tr("在数据报组装期间生存时间为0"));
	m_protocol.insert(11, temp);

	temp.clear();
	temp.insert(0, tr("怀的IP首部"));
	temp.insert(1, tr("缺少必须的选项"));
	m_protocol.insert(12, temp);

	temp.clear();
	temp.insert(0, tr("时间戳请求"));
	m_protocol.insert(13, temp);

	temp.clear();
	temp.insert(0, tr("时间戳应答"));
	m_protocol.insert(14, temp);

	temp.clear();
	temp.insert(0, tr("地址掩码请求"));
	m_protocol.insert(17, temp);

	temp.clear();
	temp.insert(0, tr("地址掩码应答"));
	m_protocol.insert(18, temp);
}

IcmpWidget::~IcmpWidget()
{

}

QString IcmpWidget::sendData()
{
	QString typeStr = ui.typeBox->currentText();
	bool ok;
	int type = typeStr.toInt(&ok);
	if (!ok)
	{
		return tr("unknown type");
	}

	QString codeStr = ui.codeBox->currentText();
	int code = codeStr.toInt(&ok);
	if (!ok)
	{
		return tr("unknown code");
	}

	struct icmp icmp;
	int len = ICMP_MINLEN;
	bzero(&icmp, sizeof(icmp));

	icmp.icmp_type = type;
	icmp.icmp_code = code;

	//ID
	if (ui.idCheckBox->checkState() == Qt::Checked)
	{
		icmp.icmp_id = getpid();
	}
	else
	{
		icmp.icmp_id = ui.idEdit->text().toInt();
	}
	//seq
	if (ui.seqCheckBox->checkState() == Qt::Checked)
	{
		icmp.icmp_seq = m_seq++;
	}
	else
	{
		icmp.icmp_seq = ui.seqEdit->text().toInt();
	}

	if (type == 8 && code == 0) //ping
	{
		struct timeval start;
		gettimeofday(&start, NULL);
		icmp.icmp_otime = start.tv_sec;
		icmp.icmp_rtime = start.tv_usec;
		if (ui.moreCheckBox1->checkState() == Qt::Checked)
		{
			icmp.icmp_otime = start.tv_sec;
		}
		else
		{
			icmp.icmp_otime = ui.moreEdit1->text().toInt();
		}
		if (ui.moreCheckBox2->checkState() == Qt::Checked)
		{
			icmp.icmp_rtime = start.tv_sec;
		}
		else
		{
			icmp.icmp_rtime = ui.moreEdit2->text().toInt();
		}

		len = ICMP_MINLEN + 8;
	}

	Icmp npg_icmp;
	QByteArray ip = ui.ipEdit->text().toLatin1();
	if (ui.checkBox->checkState() == Qt::Checked)
	{
		npg_icmp.sendto(ip.data(), (void*)&icmp, len, true);
	}
	else
	{
		icmp.icmp_cksum = ui.checkNumEdit->text().toInt();
		npg_icmp.sendto(ip.data(),(void*) &icmp, len, false);
	}

	return npg_icmp.errorStr();
}

void IcmpWidget::onTypeIndexChanged(const QString &text)
{
	ui.codeBox->clear();

	bool ok;
	int type = text.toInt(&ok);
	if (!ok)
	{
		return;
	}

	QMap<int, QString> values = m_protocol.value(type);
	QList<int> subKeys = values.keys();
	QList<int>::iterator it;
	for (it = subKeys.begin(); it != subKeys.end(); ++it)
	{
		ui.codeBox->addItem(QString::number(*it));
	}

}

void IcmpWidget::onCodeIndexChanged(const QString &text)
{
	QString typeStr = ui.typeBox->currentText();
	bool ok;
	int type = typeStr.toInt(&ok);
	if (!ok)
	{
		return;
	}

	int code = text.toInt(&ok);
	if (!ok)
	{
		return;
	}

	QMap<int, QString> values = m_protocol.value(type);
	QString tip = values.value(code);
	showTip(tip);

	if (type == 8 && code == 0)
	{
		showIdWidget();
		showMoreWidgetPing();
	}
	else
	{
		hideExendedWidget();
	}
}

void IcmpWidget::hideExendedWidget()
{
	ui.idLabel->setVisible(false);
	ui.idEdit->setVisible(false);
	ui.idCheckBox->setVisible(false);

	ui.seqLable->setVisible(false);
	ui.seqCheckBox->setVisible(false);
	ui.seqEdit->setVisible(false);

	ui.moreLabel1->setVisible(false);
	ui.moreEdit1->setVisible(false);
	ui.moreCheckBox1->setVisible(false);
	ui.tipLable1->setVisible(false);
	ui.moreEdit1->setValidator(NULL);

	ui.moreLabel2->setVisible(false);
	ui.moreEdit2->setVisible(false);
	ui.moreCheckBox2->setVisible(false);
	ui.tipLable2->setVisible(false);
	ui.moreEdit2->setValidator(NULL);

	ui.moreLabel3->setVisible(false);
	ui.moreEdit3->setVisible(false);
	ui.moreCheckBox3->setVisible(false);
	ui.tipLable3->setVisible(false);
	ui.moreEdit3->setValidator(NULL);
}

void IcmpWidget::showIdWidget()
{
	ui.idLabel->setVisible(true);
	ui.idEdit->setVisible(true);
	ui.idCheckBox->setVisible(true);

	ui.seqLable->setVisible(true);
	ui.seqCheckBox->setVisible(true);
	ui.seqEdit->setVisible(true);

	ui.idCheckBox->setChecked(true);
	ui.seqCheckBox->setChecked(true);
	ui.idEdit->setDisabled(true);
	ui.seqEdit->setDisabled(true);
}

void IcmpWidget::showMoreWidgetPing()
{
	showMoreWidget(1, tr("Seconds"));
	showMoreWidget(2, tr("MicroSeconds"));

	ui.moreEdit1->setValidator(new QIntValidator(this));
	ui.moreEdit2->setValidator(new QIntValidator(this));
}

void IcmpWidget::showMoreWidget(int index, const QString& label,
		const QString& tip)
{
	switch (index)
	{
	case 1:
		ui.moreLabel1->setVisible(true);
		ui.moreLabel1->setText(label);
		ui.moreCheckBox1->setVisible(true);
		ui.moreCheckBox1->setChecked(true);
		ui.moreEdit1->setVisible(true);
		ui.moreEdit1->setDisabled(true);
		ui.tipLable1->setVisible(true);
		ui.tipLable1->setText(tip);
		break;
	case 2:
		ui.moreLabel2->setVisible(true);
		ui.moreLabel2->setText(label);
		ui.moreCheckBox2->setVisible(true);
		ui.moreCheckBox2->setChecked(true);
		ui.moreEdit2->setVisible(true);
		ui.moreEdit2->setDisabled(true);
		ui.tipLable2->setVisible(true);
		ui.tipLable2->setText(tip);
		break;
	case 3:
		ui.moreLabel3->setVisible(true);
		ui.moreLabel3->setText(label);
		ui.moreCheckBox3->setVisible(true);
		ui.moreCheckBox3->setChecked(true);
		ui.moreEdit3->setVisible(true);
		ui.moreEdit3->setDisabled(true);
		ui.tipLable3->setVisible(true);
		ui.tipLable3->setText(tip);
		break;
	default:
		break;
	}

}

//void IcmpWidget::showMoreWidgetPing()
//{
//
//}
//
//void IcmpWidget::showMoreWidgetPing()
//{
//
//}

void IcmpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(K_ICMP);
	settings.setValue("ip", ui.ipEdit->text());
	settings.endGroup();
}

void IcmpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(K_ICMP);
	ui.ipEdit->setText(settings.value("ip").toString());
	settings.endGroup();
}
