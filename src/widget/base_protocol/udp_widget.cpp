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
#include "config.h"
#include "lib/socket/udp.h"
#include "lib/socket/raw_udp.h"
#include "../logger.h"

UdpWidget::UdpWidget(const QString& protocol_name, QWidget *parent) :
		BaseProtocolWidget(protocol_name, parent), m_udp(NULL)
{
	ui.setupUi(this);

	ui.src_port_edit->setValidator(new QIntValidator(1, 65535, this));
	ui.dst_port_edit->setValidator(new QIntValidator(1, 65535, this));

	connect(ui.src_ip_checkbox, SIGNAL(clicked ( bool)), ui.src_ip_combobox,
			SLOT( setDisabled(bool)));
	connect(ui.src_ip_checkbox, SIGNAL(clicked ( bool)), ui.src_port_edit,
			SLOT( setDisabled(bool)));

//	ui.dst_ip_edit->setWhatsThis(tr("Multiple IP separated by commas"));
//	ui.dst_ip_edit->setStatusTip(tr("Multiple IP separated by commas"));
	ui.dst_ip_edit->setToolTip(tr("Multiple IP separated by commas"));
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

	if (ui.src_ip_checkbox->checkState() == Qt::Checked) {
		m_udp = new Udp();
	} else {
		IpAddress src_addr = ui.src_ip_combobox->getIpAddress();
		uint16_t srcport = ui.src_port_edit->text().toUShort();
		m_udp = new Udp(src_addr, srcport);
	}
	return true;
}

bool UdpWidget::postSendData() {
	if (m_udp != NULL) {
		delete m_udp;
		m_udp = NULL;
	}

	return true;
}

bool UdpWidget::sendData(const char* data, uint16_t length) {
	if (m_udp == NULL) {
		LOG_ERROR(tr("should call 'preSendData' function first"));
		return false;
	}

	return m_udp->sendto(m_dstip, m_dstport, data, length);
}

void UdpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(fullProtocolName());
	settings.setValue("src_ip_combobox", ui.src_ip_combobox->currentIndex());
	settings.setValue("dstip", ui.dst_ip_edit->text());
	settings.setValue("srcport", ui.src_port_edit->text());
	settings.setValue("dstport", ui.dst_port_edit->text());
	settings.setValue("src_ip_checkbox", ui.src_ip_checkbox->checkState());
	settings.endGroup();
}

void UdpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(fullProtocolName());
	ui.src_ip_combobox->setCurrentIndex(settings.value("src_ip_combobox").toInt());
	ui.dst_ip_edit->setText(settings.value("dstip").toString());
	ui.src_port_edit->setText(settings.value("srcport").toString());
	ui.dst_port_edit->setText(settings.value("dstport").toString());
	Qt::CheckState state = (Qt::CheckState) settings.value("src_ip_box").toInt();
	if (state == Qt::Checked) {
		ui.src_ip_checkbox->click();
	}
	settings.endGroup();
}
