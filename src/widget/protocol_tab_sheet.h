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
#include "base_protocol/base_protocol_widget.h"

class ProtocolTabSheet : public TabSheet
{
    Q_OBJECT

public:
    ProtocolTabSheet(const Protocol& protocol, QWidget *parent = 0);
    ~ProtocolTabSheet();
private:
	void saveSettings();
	void restoreSettings();
	bool sendData();
	bool preSendData();
	bool postSendData();
private:
//	Ui::
    Ui::ProtocolWidgetClass ui;
	Protocol m_protocol;
	uint32_t m_seq;

	std::string m_data;
};

#endif // DNS_WIDGET_H
