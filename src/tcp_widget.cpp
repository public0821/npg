#include "tcp_widget.h"
#include <qsettings.h>
#include <string>
#include "public.h"
#include "socket/tcp.h"

TcpWidget::TcpWidget(QWidget *parent) :
		TabSheet(parent), m_name("TCP")
{
	ui.setupUi(this);
	setupUi(ui.sendLayout);

	ui.portEdit->setValidator(new QIntValidator(1, 65535, this));
	ui.timeoutEdit->setValidator(new QIntValidator(1, 15, this));
}

TcpWidget::~TcpWidget()
{

}

void TcpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(m_name);
	settings.setValue("ip", ui.ipEdit->text());
	settings.setValue("port", ui.portEdit->text());
	settings.setValue("timeout", ui.timeoutEdit->text());
	settings.setValue("data", ui.dataEdit->toPlainText());
	settings.endGroup();
}

void TcpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(m_name);
	ui.ipEdit->setText(settings.value("ip").toString());
	ui.portEdit->setText(settings.value("port").toString());
	ui.timeoutEdit->setText(settings.value("timeout").toString());
	ui.dataEdit->setText(settings.value("data").toString());
	settings.endGroup();
}

QString TcpWidget::sendData()
{
//	showTip("");
	std::string ip = ui.ipEdit->text().toStdString();
	int port = ui.portEdit->text().toInt();
	int timeout = ui.timeoutEdit->text().toInt();
	std::string data = ui.dataEdit->toPlainText().toStdString();
	if (ip.empty() || port <= 0 || data.empty())
	{
		return QString("ip and port and data must set");
	}

	if(timeout == 0)//set default timeout
	{
		timeout = 10;
	}

	Tcp tcp;
	bool ret = tcp.connect(ip.c_str(), port, timeout);
	if (!ret)
	{
		return QString(tcp.errorStr());
	}

	int len = tcp.send(data.c_str(), data.length());
	if (len == K_SOCKET_ERROR)
	{
		return QString(tcp.errorStr());
	}

	return QString();
}

//QString TcpWidget::beforeSendData()
//{
//	return "";
//}
