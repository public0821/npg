/*
 * icmp_widget.cpp
 *
 *  Created on: 2011-10-11
 *      Author: Young <public0821@gmail.com>
 */


#include "icmp_widget.h"
#include "socket/icmp.h"
#include <qsettings.h>
#include "npg_define.h"
#include "system/os.h"
#include "socket/socket_public.h"

IcmpWidget::IcmpWidget(const QString& name, QWidget *parent) :
		TabSheet(name,parent), m_seq(0)
{
	ui.setupUi(this);
	setupUi(ui.send_layout);

	initProtocol();

	connect(ui.type_box, SIGNAL(currentIndexChanged(const QString &)), this,
			SLOT( onTypeIndexChanged(const QString &)));
	connect(ui.code_box, SIGNAL(currentIndexChanged(const QString &)), this,
			SLOT( onCodeIndexChanged(const QString &)));
	connect(ui.checkbox, SIGNAL(clicked ( bool)), ui.checknum_edit,
			SLOT( setDisabled(bool)));
	connect(ui.id_checkbox, SIGNAL(clicked ( bool)), ui.id_edit,
			SLOT( setDisabled(bool)));
	connect(ui.seq_checkbox, SIGNAL(clicked ( bool)), ui.seq_edit,
			SLOT( setDisabled(bool)));
	connect(ui.more_checkbox1, SIGNAL(clicked ( bool)), ui.more_edit1,
			SLOT( setDisabled(bool)));
	connect(ui.more_checkbox2, SIGNAL(clicked ( bool)), ui.more_edit2,
			SLOT( setDisabled(bool)));
	connect(ui.more_checkbox3, SIGNAL(clicked ( bool)), ui.more_edit3,
			SLOT( setDisabled(bool)));

	ui.checkbox->setChecked(true);
	ui.checknum_edit->setDisabled(true);

	hideExendedWidget();

	QList<int> keys = m_protocol.keys();
	QList<int>::iterator it;
	for (it = keys.begin(); it != keys.end(); ++it)
	{
		ui.type_box->addItem(QString::number(*it));
	}

	ui.type_box->setValidator(new QIntValidator(this));
	ui.code_box->setValidator(new QIntValidator(this));
	ui.checknum_edit->setValidator(new QIntValidator(this));
	ui.id_edit->setValidator(new QIntValidator(this));
	ui.seq_edit->setValidator(new QIntValidator(this));

	ui.tip_lable1->setText("");
	ui.tip_lable2->setText("");
	ui.tip_lable3->setText("");
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
	temp.insert(4, tr("Fragmentation Required but not fragment bit set"));
	temp.insert(5, tr("Source Routing failure"));
	temp.insert(6, tr("Do not know the destination network"));
	temp.insert(7, tr("Do not know the destination host"));
	temp.insert(9, tr("The destination network administratively prohibited"));
	temp.insert(10, tr("The destination host administratively prohibited"));
	temp.insert(11, tr("As the type of service TOS, the network is not up to"));
	temp.insert(12, tr("As the type of service TOS, the host is not up to"));
	temp.insert(13, tr("As the filter, communication administratively prohibited"));
	temp.insert(14, tr("Host ultra vires"));
	temp.insert(15, tr("Priority cease to have effect"));
	m_protocol.insert(3, temp);

	temp.clear();
	temp.insert(0, tr("Source is shutdown"));
	m_protocol.insert(4, temp);

	temp.clear();
	temp.insert(0, tr("Redirect for network"));
	temp.insert(1, tr("Redirect for host"));
	temp.insert(2, tr("Redirect for network and type of service"));
	temp.insert(3, tr("Redirect for host and type of service"));
	m_protocol.insert(5, temp);

	temp.clear();
	temp.insert(0, tr("ping request"));
	m_protocol.insert(8, temp);

	temp.clear();
	temp.insert(0, tr("Router advertisement"));
	m_protocol.insert(9, temp);

	temp.clear();
	temp.insert(0, tr("Router request"));
	m_protocol.insert(10, temp);

	temp.clear();
	temp.insert(0, tr("the survival time is zero during transmission"));
	temp.insert(1, tr("the survival time is zero during packet assembly"));
	m_protocol.insert(11, temp);

	temp.clear();
	temp.insert(0, tr("Pregnant for the IP header"));
	temp.insert(1, tr("The lack of the necessary options"));
	m_protocol.insert(12, temp);

	temp.clear();
	temp.insert(0, tr("Timestamp request"));
	m_protocol.insert(13, temp);

	temp.clear();
	temp.insert(0, tr("Timestamp response"));
	m_protocol.insert(14, temp);

	temp.clear();
	temp.insert(0, tr("Netmask request"));
	m_protocol.insert(17, temp);

	temp.clear();
	temp.insert(0, tr("Netmask reply"));
	m_protocol.insert(18, temp);
}

IcmpWidget::~IcmpWidget()
{

}

QString IcmpWidget::sendData()
{
	QString type_str = ui.type_box->currentText();
	bool ok;
	int type = type_str.toInt(&ok);
	if (!ok)
	{
		return tr("unknown type");
	}

	QString code_str = ui.code_box->currentText();
	int code = code_str.toInt(&ok);
	if (!ok)
	{
		return tr("unknown code");
	}

	struct icmp icmp;
	size_t len = ICMP_MINLEN;
	bzero(&icmp, sizeof(icmp));

	icmp.icmp_type = type;
	icmp.icmp_code = code;

	//ID
	if (ui.id_checkbox->checkState() == Qt::Checked)
	{
		icmp.icmp_id = getpid();
	}
	else
	{
		icmp.icmp_id = ui.id_edit->text().toInt();
	}
	//seq
	if (ui.seq_checkbox->checkState() == Qt::Checked)
	{
		icmp.icmp_seq = m_seq++;
	}
	else
	{
		icmp.icmp_seq = ui.seq_edit->text().toInt();
	}

	if (type == 8 && code == 0) //ping
	{
		struct timeval start;
		gettimeofday(&start, NULL);
		icmp.icmp_otime = start.tv_sec;
		icmp.icmp_rtime = start.tv_usec;
		if (ui.more_checkbox1->checkState() == Qt::Checked)
		{
			icmp.icmp_otime = start.tv_sec;
		}
		else
		{
			icmp.icmp_otime = ui.more_edit1->text().toInt();
		}
		if (ui.more_checkbox2->checkState() == Qt::Checked)
		{
			icmp.icmp_rtime = start.tv_sec;
		}
		else
		{
			icmp.icmp_rtime = ui.more_edit2->text().toInt();
		}

		len = ICMP_MINLEN + 8;
	}

	Icmp npg_icmp;
	sstring ip = ui.ip_edit->text().toStdString();
	if (ui.checkbox->checkState() == Qt::Checked)
	{
		npg_icmp.sendto(ip.c_str(), (void*)&icmp, len, true);
	}
	else
	{
		icmp.icmp_cksum = ui.checknum_edit->text().toInt();
		npg_icmp.sendto(ip.c_str(),(void*) &icmp, len, false);
	}

	return npg_icmp.errorStr();
}

void IcmpWidget::onTypeIndexChanged(const QString &text)
{
	ui.code_box->clear();

	bool ok;
	int type = text.toInt(&ok);
	if (!ok)
	{
		return;
	}

	QMap<int, QString> values = m_protocol.value(type);
	QList<int> sub_keys = values.keys();
	QList<int>::iterator it;
	for (it = sub_keys.begin(); it != sub_keys.end(); ++it)
	{
		ui.code_box->addItem(QString::number(*it));
	}

}

void IcmpWidget::onCodeIndexChanged(const QString &text)
{
	QString type_str = ui.type_box->currentText();
	bool ok;
	int type = type_str.toInt(&ok);
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
	ui.id_label->setVisible(false);
	ui.id_edit->setVisible(false);
	ui.id_checkbox->setVisible(false);

	ui.seq_lable->setVisible(false);
	ui.seq_checkbox->setVisible(false);
	ui.seq_edit->setVisible(false);

	ui.more_label1->setVisible(false);
	ui.more_edit1->setVisible(false);
	ui.more_checkbox1->setVisible(false);
	ui.tip_lable1->setVisible(false);
	ui.more_edit1->setValidator(NULL);

	ui.more_label2->setVisible(false);
	ui.more_edit2->setVisible(false);
	ui.more_checkbox2->setVisible(false);
	ui.tip_lable2->setVisible(false);
	ui.more_edit2->setValidator(NULL);

	ui.more_label3->setVisible(false);
	ui.more_edit3->setVisible(false);
	ui.more_checkbox3->setVisible(false);
	ui.tip_lable3->setVisible(false);
	ui.more_edit3->setValidator(NULL);
}

void IcmpWidget::showIdWidget()
{
	ui.id_label->setVisible(true);
	ui.id_edit->setVisible(true);
	ui.id_checkbox->setVisible(true);

	ui.seq_lable->setVisible(true);
	ui.seq_checkbox->setVisible(true);
	ui.seq_edit->setVisible(true);

	ui.id_checkbox->setChecked(true);
	ui.seq_checkbox->setChecked(true);
	ui.id_edit->setDisabled(true);
	ui.seq_edit->setDisabled(true);
}

void IcmpWidget::showMoreWidgetPing()
{
	showMoreWidget(1, tr("Seconds"));
	showMoreWidget(2, tr("MicroSeconds"));

	ui.more_edit1->setValidator(new QIntValidator(this));
	ui.more_edit2->setValidator(new QIntValidator(this));
}

void IcmpWidget::showMoreWidget(int index, const QString& label,
		const QString& tip)
{
	switch (index)
	{
	case 1:
		ui.more_label1->setVisible(true);
		ui.more_label1->setText(label);
		ui.more_checkbox1->setVisible(true);
		ui.more_checkbox1->setChecked(true);
		ui.more_edit1->setVisible(true);
		ui.more_edit1->setDisabled(true);
		ui.tip_lable1->setVisible(true);
		ui.tip_lable1->setText(tip);
		break;
	case 2:
		ui.more_label2->setVisible(true);
		ui.more_label2->setText(label);
		ui.more_checkbox2->setVisible(true);
		ui.more_checkbox2->setChecked(true);
		ui.more_edit2->setVisible(true);
		ui.more_edit2->setDisabled(true);
		ui.tip_lable2->setVisible(true);
		ui.tip_lable2->setText(tip);
		break;
	case 3:
		ui.more_label3->setVisible(true);
		ui.more_label3->setText(label);
		ui.more_checkbox3->setVisible(true);
		ui.more_checkbox3->setChecked(true);
		ui.more_edit3->setVisible(true);
		ui.more_edit3->setDisabled(true);
		ui.tip_lable3->setVisible(true);
		ui.tip_lable3->setText(tip);
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
	settings.beginGroup(protocolName());
	settings.setValue("ip", ui.ip_edit->text());
	settings.endGroup();
}

void IcmpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	ui.ip_edit->setText(settings.value("ip").toString());
	settings.endGroup();
}
