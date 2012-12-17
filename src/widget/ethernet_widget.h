/*
 * ethernet_widget.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef ETHERNET_WIDGET_H
#define ETHERNET_WIDGET_H

#include <QWidget>
#include "ui/ui_ethernet_widget.h"
#include "base_protocol_widget.h"
#include "lib/socket/ethernet.h"

class EthernetWidget  : public BaseProtocolWidget
{
	Q_OBJECT

public:
	EthernetWidget(const QString& protocol_name, const QString& ether_protocol_name, QWidget *parent);
	~EthernetWidget();
public:
	QString preSendData();
	QString postSendData();
	virtual QString sendData(const char* data, uint16_t length);
public:
	void saveSettings();
	void restoreSettings();
private:
	void setupEtherProtocol(const QString& ether_protocol_name);
	void setupInterface(QWidget *parent);
private slots:
	void onInterfaceChanged(int index);
private:
	Ui::EthernetWidget ui;
	int m_protocol;
	std::string m_dstmac;
	std::string m_srcmac;
	ifi_info m_dev;

	Ethernet* m_ethernet;
};

#endif // ETHERNET_WIDGET_H
