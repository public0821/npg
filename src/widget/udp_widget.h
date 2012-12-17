/*
 * udp_widget.h
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */

#ifndef UDPWIDGET_H
#define UDPWIDGET_H

#include "base_protocol_widget.h"
#include "ui/ui_udp_widget.h"
#include "lib/types.h"
#include "../lib/socket/ip_address.h"

class UdpWidget : public BaseProtocolWidget
{
    Q_OBJECT

public:
    UdpWidget(const QString& protocol_name, QWidget *parent);
    ~UdpWidget();
public:
	bool preSendData();
	bool postSendData();
	bool sendData(const char* data, uint16_t length);
public:
	void saveSettings();
	void restoreSettings();
private:
    Ui::UdpWidgetClass ui;

    IpAddress m_srcip;
	uint16_t m_srcport;
	IpAddress m_dstip;
	uint16_t m_dstport;
	bool m_is_raw_socket;
	void* m_udp;
};

#endif // UDPWIDGET_H
