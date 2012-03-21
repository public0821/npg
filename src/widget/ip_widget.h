/*
 * ip_widget.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef IP_WIDGET_H
#define IP_WIDGET_H

#include <QWidget>
#include "ui_ip_widget.h"
#include <map>
#include "base_protocol_widget.h"

class Ip;
class IpWidget : public BaseProtocolWidget
{
	Q_OBJECT

public:
	IpWidget(const QString& protocol_name, const QString& ip_protocol_name, QWidget *parent);
	~IpWidget();
public:
	QString preSendData();
	QString postSendData();
	virtual QString sendData(const char* data, u_int16_t length);
public:
	void saveSettings();
	void restoreSettings();
private:
	Ui::IpWidget ui;
	std::map<QString, int>  m_built_in_protocol;

	sstring m_dstip;
	Ip* m_ip;
};

#endif // IP_WIDGET_H
