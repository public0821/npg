#include "udp_widget.h"
#include <qmessagebox.h>
#include <qsettings.h>
#include <string>
#include "public.h"
#include "socket/udp.h"

UdpWidget::UdpWidget(QWidget *parent) :
		TabSheet(parent), m_name("UDP")
{
	ui.setupUi(this);
//	ui.labelTip->setTextFormat(Qt::RichText);
//	QSize size = parent->size();
//	setGeometry(0, 0, size.width(), size.height());
//	ui.gridLayoutWidget->setGeometry(0, 0, size.width(), size.height());
	setupUi(ui.sendLayout);

	ui.portEdit->setValidator(new QIntValidator(1, 65535, this));
}

UdpWidget::~UdpWidget()
{
}

QString UdpWidget::sendData()
{
//	showTip("");
	std::string ip = ui.ipEdit->text().toStdString();
	int port = ui.portEdit->text().toInt();
	std::string data = ui.dataEdit->toPlainText().toStdString();
	if(ip.empty() || port <= 0 || data.empty())
	{
		return QString("ip and port and data must set");
	}

	Udp udp;
	bool ret = udp.sendto(ip.c_str(), port, data.c_str(), data.length());
	if (!ret)
	{
		return QString(udp.errorStr());
	}

	return QString();
}

void UdpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(m_name);
	settings.setValue("ip", ui.ipEdit->text());
	settings.setValue("port", ui.portEdit->text());
	settings.setValue("data", ui.dataEdit->toPlainText());
	settings.endGroup();
}

void UdpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(m_name);
	ui.ipEdit->setText(settings.value("ip").toString());
	ui.portEdit->setText(settings.value("port").toString());
	ui.dataEdit->setText(settings.value("data").toString());
	settings.endGroup();
}
