/*
 * tcp_widget.cpp
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */
#include "tcp_widget.h"
#include <qsettings.h>
#include <string>
#include "config.h"
#include "lib/socket/tcp.h"
#include "tcp_response_dialog.h"
#include "../logger.h"

TcpWidget::TcpWidget(const QString& protocol_name, QWidget *parent) :
		BaseProtocolWidget(protocol_name, parent), m_tcp(NULL)
{
	ui.setupUi(this);
	ui.sport_edit->setValidator(new QIntValidator(1, 65535, this));
	ui.dport_edit->setValidator(new QIntValidator(1, 65535, this));
	ui.timeout_edit->setValidator(new QIntValidator(1, 15, this));

	connect(ui.src_ip_box, SIGNAL(clicked ( bool)), ui.sip_box,
			SLOT( setDisabled(bool)));
	connect(ui.src_ip_box, SIGNAL(clicked ( bool)), ui.sport_edit,
			SLOT( setDisabled(bool)));
}

TcpWidget::~TcpWidget()
{

}

void TcpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(fullProtocolName());
	settings.setValue("tcp_dip", ui.dip_edit->text());
	settings.setValue("tcp_dport", ui.dport_edit->text());
	settings.setValue("tcp_sport", ui.sport_edit->text());
	settings.setValue("tcp_sip", ui.sip_box->currentIndex());
	settings.setValue("tcp_timeout", ui.timeout_edit->text());
	settings.setValue("tcp_wait_for_response", ui.wait_for_response_box->checkState());
	settings.setValue("src_ip_box", ui.src_ip_box->checkState());
	settings.endGroup();
}

void TcpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(fullProtocolName());
	ui.dip_edit->setText(settings.value("tcp_dip").toString());
	ui.dport_edit->setText(settings.value("tcp_dport").toString());
	ui.sport_edit->setText(settings.value("tcp_sport").toString());
	ui.sip_box->setCurrentIndex(settings.value("tcp_sip").toInt());
	ui.timeout_edit->setText(settings.value("tcp_timeout").toString());
	ui.wait_for_response_box->setCheckState((Qt::CheckState) settings.value("tcp_wait_for_response").toInt());
	Qt::CheckState state = (Qt::CheckState) settings.value("src_ip_box").toInt();
	if(state == Qt::Checked){
		ui.src_ip_box->click();
	}
	settings.endGroup();
}

bool TcpWidget::preSendData() {
	if (m_tcp != NULL) {
		LOG_ERROR(tr("'preSendData' function has been called"));
		return false;
	}

	std::string dst_ip = ui.dip_edit->text().toLocal8Bit().constData();
	uint16_t dst_port = ui.dport_edit->text().toUShort();
	m_timeout = ui.timeout_edit->text().toInt();
	if (dst_ip.empty() || dst_port <= 0) {
		LOG_ERROR(tr("ip and port and data must set"));
		return false;
	}

	if (m_timeout == 0) { //set default timeout
		m_timeout = 10;
	}

	if (ui.wait_for_response_box->checkState() == Qt::Checked) {
		m_wait_for_response = true;
	} else {
		m_wait_for_response = false;
	}

	IpAddress dst_addr;
	if (!dst_addr.from_string(dst_ip)) {
		LOG_ERROR(tr("invaild dst ip address: %1").arg(dst_ip.c_str()));
		return false;
	}
	if (ui.src_ip_box->checkState() == Qt::Checked) {
		m_tcp = new Tcp();
	} else {
		uint16_t src_port = ui.sport_edit->text().toUShort();
		IpAddress src_addr = ui.sip_box->getIpAddress();
		m_tcp = new Tcp(src_addr, src_port);
	}
	bool ret = m_tcp->connect(dst_addr, dst_port, m_timeout);
	if (!ret) {
		delete m_tcp;
		m_tcp = NULL;
		return false;
	}

	return true;
}

bool TcpWidget::postSendData() {
	if (m_tcp != NULL) {
		delete m_tcp;
		m_tcp = NULL;
	}

	return true;
}

bool TcpWidget::sendData(const char* data, uint16_t length) {
//	showTip("");

	if (m_tcp == NULL) {
		LOG_ERROR(tr("should call 'preSendData' function first"));
		return false;
	}

	bool ret = m_tcp->send(data, length);
	if (!ret) {
		return false;
	}

	if (m_wait_for_response) {
		TcpResponseDialog dialog(*m_tcp, this);
		dialog.exec();
	}

	return true;
}

//QString TcpWidget::beforeSendData()
//{
//	return "";
//}
