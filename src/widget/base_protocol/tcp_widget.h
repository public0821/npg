/*
 * tcp_widget.h
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */

#ifndef TCP_WIDGET_H
#define TCP_WIDGET_H

#include "ui_tcp_widget.h"
#include "base_protocol_widget.h"
#include "lib/types.h"

class Tcp;
class TcpWidget : public BaseProtocolWidget
{
    Q_OBJECT

public:
    TcpWidget(const QString& protocol_name, QWidget *parent = 0);
    ~TcpWidget();
public:
	bool preSendData();
	bool postSendData();
	bool sendData(const char* data, uint16_t length);
private:
	void saveSettings();
	void restoreSettings();
private:
    Ui::TcpWidgetClass ui;

	time_t m_timeout;
	Tcp* m_tcp;
	bool m_wait_for_response;
};

#endif // TCP_WIDGET_H
