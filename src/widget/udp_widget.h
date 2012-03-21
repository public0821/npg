/*
 * udp_widget.h
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */

#ifndef UDPWIDGET_H
#define UDPWIDGET_H

#include "base_protocol_widget.h"
#include "ui_udp_widget.h"
#include "system/types.h"

class UdpWidget : public BaseProtocolWidget
{
    Q_OBJECT

public:
    UdpWidget(const QString& protocol_name, QWidget *parent);
    ~UdpWidget();
public:
	QString preSendData();
	QString postSendData();
    QString sendData(const char* data, u_int16_t length);
public:
	void saveSettings();
	void restoreSettings();
private:
    Ui::UdpWidgetClass ui;

	sstring m_srcip; 
	u_int16_t m_srcport;
	sstring m_dstip; 
	u_int16_t m_dstport;
	bool m_is_raw_socket;
	void* m_udp;
};

#endif // UDPWIDGET_H
