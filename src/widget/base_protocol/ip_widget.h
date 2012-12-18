/*
 * ip_widget.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef IP_WIDGET_H
#define IP_WIDGET_H

#include <QWidget>
#include "ui/ui_ip_widget.h"
#include <map>
#include "base_protocol_widget.h"
#include "lib/socket/ip_address.h"

class Ip;
class IpWidget : public BaseProtocolWidget
{
	Q_OBJECT

public:
	IpWidget(const QString& protocol_name, const QString& ip_protocol_name, QWidget *parent);
	~IpWidget();
public:
	bool preSendData();
	bool postSendData();
	virtual bool sendData(const char* data, uint16_t length);
public:
	void saveSettings();
	void restoreSettings();
private:
	Ui::IpWidget ui;
	std::map<QString, int>  m_built_in_protocol;

	IpAddress m_dstip;
	Ip* m_ip;
};

#endif // IP_WIDGET_H
