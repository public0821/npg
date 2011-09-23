#include "udp_widget.h"
#include <qmessagebox.h>
#include <qsettings.h>
#include <string>
#include "public.h"
#include "socket/udp.h"
#include "socket/raw_udp.h"

UdpWidget::UdpWidget(QWidget *parent) :
		TabSheet(parent), m_name("UDP")
{
	ui.setupUi(this);
//	ui.labelTip->setTextFormat(Qt::RichText);
//	QSize size = parent->size();
//	setGeometry(0, 0, size.width(), size.height());
//	ui.gridLayoutWidget->setGeometry(0, 0, size.width(), size.height());
	setupUi(ui.sendLayout);

	ui.srcPortEdit->setValidator(new QIntValidator(1, 65535, this));
	ui.dstPortEdit->setValidator(new QIntValidator(1, 65535, this));

	connect(ui.srcIpBox, SIGNAL(clicked ( bool)), ui.srcIpEdit,
			SLOT( setDisabled(bool)));
	connect(ui.srcIpBox, SIGNAL(clicked ( bool)), ui.srcPortEdit,
				SLOT( setDisabled(bool)));

	ui.srcIpBox->setChecked(true);
	ui.srcIpEdit->setDisabled(true);
	ui.srcPortEdit->setDisabled(true);
}

UdpWidget::~UdpWidget()
{
}

QString UdpWidget::sendData()
{

	std::string dstip = ui.dstIpEdit->text().toStdString();
	int dstport = ui.dstPortEdit->text().toInt();
	std::string data = ui.dataEdit->toPlainText().toStdString();
	if (dstip.empty() || dstport <= 0 || data.empty())
	{
		return QString("ip and port and data must set");
	}

	bool bRawSocket = !(ui.srcIpBox->checkState() == Qt::Checked);
	if (bRawSocket)
	{
		std::string srcip = ui.srcIpEdit->text().toStdString();
		int srcport = ui.srcPortEdit->text().toInt();
		RawUdp rawUdp;
		bool ret = rawUdp.sendto(srcip.c_str(), dstip.c_str(), srcport, dstport,
				data.c_str(), data.length());
		if (!ret)
		{
			return QString(rawUdp.errorStr());
		}
	}
	else
	{

		Udp udp;
		bool ret = udp.sendto(dstip.c_str(), dstport, data.c_str(),
				data.length());
		if (!ret)
		{
			return QString(udp.errorStr());
		}
	}
	return QString();
}

void UdpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(m_name);
	settings.setValue("srcip", ui.srcIpEdit->text());
	settings.setValue("dstip", ui.dstIpEdit->text());
	settings.setValue("srcport", ui.srcPortEdit->text());
	settings.setValue("dstport", ui.dstPortEdit->text());
	settings.setValue("data", ui.dataEdit->toPlainText());
	settings.endGroup();
}

void UdpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(m_name);
	ui.srcIpEdit->setText(settings.value("srcip").toString());
	ui.dstIpEdit->setText(settings.value("dstip").toString());
	ui.srcPortEdit->setText(settings.value("srcport").toString());
	ui.dstPortEdit->setText(settings.value("dstport").toString());
	ui.dataEdit->setText(settings.value("data").toString());
	settings.endGroup();
}
