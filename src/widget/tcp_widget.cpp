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
#include "tcp_response_dialog.h"

TcpWidget::TcpWidget(const QString& protocol_name, QWidget *parent) :
BaseProtocolWidget(protocol_name, parent)
{
	ui.setupUi(this);

	ui.port_edit->setValidator(new QIntValidator(1, 65535, this));
	ui.timeout_edit->setValidator(new QIntValidator(1, 15, this));
}

TcpWidget::~TcpWidget()
{

}

void TcpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	settings.setValue("tcp_ip", ui.ip_edit->text());
	settings.setValue("tcp_port", ui.port_edit->text());
	settings.setValue("tcp_timeout", ui.timeout_edit->text());
	settings.setValue("tcp_wait_for_response", ui.wait_for_response_box->checkState());
	settings.endGroup();
}

void TcpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	ui.ip_edit->setText(settings.value("tcp_ip").toString());
	ui.port_edit->setText(settings.value("tcp_port").toString());
	ui.timeout_edit->setText(settings.value("tcp_timeout").toString());
	ui.wait_for_response_box->setCheckState((Qt::CheckState)settings.value("tcp_wait_for_response").toInt());
	settings.endGroup();
}

QString TcpWidget::sendData(const char* data, u_int16_t length)
{
//	showTip("");
	sstring ip = ui.ip_edit->text().toStdString();
	u_int16_t port = ui.port_edit->text().toUShort();
	time_t timeout = ui.timeout_edit->text().toInt();
	if (ip.empty() || port <= 0)
	{
		return tr("ip and port and data must set");
	}

	if(timeout == 0)//set default timeout
	{
		timeout = 10;
	}

	Tcp tcp;
	bool ret = tcp.setBlocking(false);
	if (!ret)
	{
		return QString(tr(tcp.errorString()));
	}
	ret = tcp.connect(ip.c_str(), port, timeout);
	if (!ret)
	{
		return QString(tr(tcp.errorString()));
	}
	ret = tcp.setBlocking(true);
	if (!ret)
	{
		return QString(tr(tcp.errorString()));
	}
	ret = tcp.send(data, length);
	if (!ret)
	{
		return QString(tr(tcp.errorString()));
	}

	if (ui.wait_for_response_box->checkState() == Qt::Checked)
	{
		TcpResponseDialog dialog(tcp, this);
		dialog.exec();
	}
	
	return QString();
}

//QString TcpWidget::beforeSendData()
//{
//	return "";
//}
