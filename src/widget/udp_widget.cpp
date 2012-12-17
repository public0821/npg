/*
 * udp_widget.cpp
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */
#include "udp_widget.h"
#include <qmessagebox.h>
#include <qsettings.h>
#include <string>
#include "npg_define.h"
#include "lib/socket/udp.h"
#include "lib/socket/raw_udp.h"
#include "../logger.h"

UdpWidget::UdpWidget(const QString& protocol_name, QWidget *parent) :
		BaseProtocolWidget(protocol_name, parent), m_udp(NULL)
{
	ui.setupUi(this);

	ui.src_port_edit->setValidator(new QIntValidator(1, 65535, this));
	ui.dst_port_edit->setValidator(new QIntValidator(1, 65535, this));

	connect(ui.src_ip_box, SIGNAL(clicked ( bool)), ui.src_ip_edit,
			SLOT( setDisabled(bool)));
	connect(ui.src_ip_box, SIGNAL(clicked ( bool)), ui.src_port_edit,
			SLOT( setDisabled(bool)));

	ui.src_ip_box->setChecked(true);
	ui.src_ip_edit->setDisabled(true);
	ui.src_port_edit->setDisabled(true);

//	setupUi(ui.base_layout, ui.groupBox);
}

UdpWidget::~UdpWidget()
{
}

bool UdpWidget::preSendData() {
	if (m_udp != NULL) {
		LOG_ERROR(tr("'preSendData' function has been called"));
		return false;
	}

	std::string dstip = ui.dst_ip_edit->text().toLocal8Bit().constData();
	m_dstport = ui.dst_port_edit->text().toUShort();
	if (dstip.empty() || m_dstport <= 0) {
		LOG_ERROR(tr("ip and port and data must set"));
		return false;
	}
	bool ret = m_dstip.from_string(dstip);
	if (!ret) {
		LOG_ERROR(tr("invaild dst ip: %1").arg(dstip.c_str()));
		return false;
	}

	m_is_raw_socket = !(ui.src_ip_box->checkState() == Qt::Checked);
	if (m_is_raw_socket)
	{
		std::string srcip = ui.src_ip_edit->text().toLocal8Bit().constData();
		ret = m_srcip.from_string(srcip);
		if (!ret) {
			LOG_ERROR(tr("invaild src ip: %1").arg(srcip.c_str()));
			return false;
		}
		m_srcport = ui.src_port_edit->text().toUShort();
		m_udp = new RawUdp();
	} else {
		m_udp = new Udp();
	}
	return true;
}

bool UdpWidget::postSendData() {
	if (m_udp != NULL) {
		if (m_is_raw_socket) {
			RawUdp* raw_udp = (RawUdp*) m_udp;
			delete raw_udp;
		} else {
			Udp *udp = (Udp*) m_udp;
			delete udp;
		}
		m_udp = NULL;
	}

	return true;
}

bool UdpWidget::sendData(const char* data, uint16_t length) {
	if (m_udp == NULL) {
		LOG_ERROR(tr("should call 'preSendData' function first"));
		return false;
	}

	if (m_is_raw_socket) {
		RawUdp* raw_udp = (RawUdp*) m_udp;
//		return raw_udp->sendto(m_srcip.c_str(), m_dstip.c_str(), m_srcport, m_dstport,
//				data, length);
		LOG_ERROR(tr("unimplemented"));
		return false;
	} else {
		Udp *udp = (Udp*) m_udp;
		return udp->sendto(m_dstip, m_dstport, data, length);
	}
}

void UdpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	settings.setValue("srcip", ui.src_ip_edit->text());
	settings.setValue("dstip", ui.dst_ip_edit->text());
	settings.setValue("srcport", ui.src_port_edit->text());
	settings.setValue("dstport", ui.dst_port_edit->text());
	settings.endGroup();
}

void UdpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	ui.src_ip_edit->setText(settings.value("srcip").toString());
	ui.dst_ip_edit->setText(settings.value("dstip").toString());
	ui.src_port_edit->setText(settings.value("srcport").toString());
	ui.dst_port_edit->setText(settings.value("dstport").toString());
	settings.endGroup();
}
