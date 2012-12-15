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
BaseProtocolWidget(protocol_name, parent), m_tcp(NULL)
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

QString TcpWidget::preSendData()
{
	if (m_tcp != NULL)
	{
		return tr("'preSendData' function has been called");//this message just for developer, End-user will not see it
	}

	m_ip = ui.ip_edit->text().toLocal8Bit().constData();
	m_port = ui.port_edit->text().toUShort();
	m_timeout = ui.timeout_edit->text().toInt();
	if (m_ip.empty() || m_port <= 0)
	{
		return tr("ip and port and data must set");
	}

	if(m_timeout == 0)//set default timeout
	{
		m_timeout = 10;
	}

	if (ui.wait_for_response_box->checkState() == Qt::Checked)
	{
		m_wait_for_response = true;
	}
	else
	{
		m_wait_for_response = false;
	}


	m_tcp = new Tcp();
	bool ret = m_tcp->connect(m_ip.c_str(), m_port, m_timeout);
	if (!ret)
	{
		QString  temp_error(tr(m_tcp->errorString()));
		delete m_tcp;
		m_tcp = NULL;
		return temp_error;
	}

	return QString();
}

QString TcpWidget::postSendData()
{
	if (m_tcp != NULL)
	{
		delete m_tcp;
		m_tcp = NULL;
	}

	return QString();
}
QString TcpWidget::sendData(const char* data, uint16_t length)
{
//	showTip("");

	if (m_tcp == NULL)
	{
		return tr("should call 'preSendData' function first");
	}

	bool ret = m_tcp->send(data, length);
	if (!ret)
	{
		return QString(tr(m_tcp->errorString()));
	}

	if (m_wait_for_response)
	{
		TcpResponseDialog dialog(*m_tcp, this);
		dialog.exec();
	}
	
	return QString();
}

//QString TcpWidget::beforeSendData()
//{
//	return "";
//}
