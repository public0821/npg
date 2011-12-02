/*
 * dns_widget.h
 *
 *  Created on: 2011-10-11
 *      Author: Young <public0821@gmail.com>
 */

#ifndef PROTOCOL_WIDGET_H
#define PROTOCOL_WIDGET_H

#include "ui_protocol_widget.h"
#include "tab_sheet.h"
#include "protocol/protocol.h"

class ProtocolWidget : public TabSheet
{
    Q_OBJECT

public:
    ProtocolWidget(Protocol protocol, QWidget *parent = 0);
    ~ProtocolWidget();
private:
	void saveSettings();
	void restoreSettings();
	QString sendData();
private:
//	Ui::
    Ui::ProtocolWidgetClass ui;
	Protocol m_protocol;
};

#endif // DNS_WIDGET_H
