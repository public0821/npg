/*
 * tcp_widget.cpp
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */
#include "tcp_widget.h"
#include <qsettings.h>
#include <string>
#include "npg_define.h"
#include "socket/tcp.h"

TcpWidget::TcpWidget(QWidget *parent) :
		TabSheet(parent)
{
	ui.setupUi(this);
	setupUi(ui.send_layout);

	ui.port_edit->setValidator(new QIntValidator(1, 65535, this));
	ui.timeout_edit->setValidator(new QIntValidator(1, 15, this));
}

TcpWidget::~TcpWidget()
{

}

void TcpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(K_TCP);
	settings.setValue("ip", ui.ip_edit->text());
	settings.setValue("port", ui.port_edit->text());
	settings.setValue("timeout", ui.timeout_edit->text());
	settings.setValue("data", ui.data_edit->toPlainText());
	settings.endGroup();
}

void TcpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(K_TCP);
	ui.ip_edit->setText(settings.value("ip").toString());
	ui.port_edit->setText(settings.value("port").toString());
	ui.timeout_edit->setText(settings.value("timeout").toString());
	ui.data_edit->setText(settings.value("data").toString());
	settings.endGroup();
}

QString TcpWidget::sendData()
{
//	showTip("");
	sstring ip = ui.ip_edit->text().toStdString();
	u_int16_t port = ui.port_edit->text().toUShort();
	time_t timeout = ui.timeout_edit->text().toInt();
	sstring data = ui.data_edit->toPlainText().toStdString();
	if (ip.empty() || port <= 0 || data.empty())
	{
		return tr("ip and port and data must set");
	}

	if(timeout == 0)//set default timeout
	{
		timeout = 10;
	}

	Tcp tcp;
	bool ret = tcp.connect(ip.c_str(), port, timeout);
	if (!ret)
	{
		return QString(tr(tcp.errorStr()));
	}

	ret = tcp.send(data.c_str(), data.length());
	if (!ret)
	{
		return QString(tr(tcp.errorStr()));
	}

	return QString();
}

//QString TcpWidget::beforeSendData()
//{
//	return "";
//}
