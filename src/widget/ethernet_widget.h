/*
 * ethernet_widget.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef ETHERNET_WIDGET_H
#define ETHERNET_WIDGET_H

#include <QWidget>
#include "ui_ethernet_widget.h"
#include "base_protocol_widget.h"

class EthernetWidget  : public BaseProtocolWidget
{
	Q_OBJECT

public:
	EthernetWidget(const QString& protocol_name, const QString& ether_protocol_name, QWidget *parent);
	~EthernetWidget();
public:
	virtual QString sendData(const char* data, u_int16_t length);
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
};

#endif // ETHERNET_WIDGET_H
