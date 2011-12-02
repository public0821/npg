/*
 * dns_widget.h
 *
 *  Created on: 2011-10-11
 *      Author: Young <public0821@gmail.com>
 */

#ifndef DNS_WIDGET_H
#define DNS_WIDGET_H

#include "ui_dns_widget.h"
#include "tab_sheet.h"

class DnsWidget : public TabSheet
{
    Q_OBJECT

public:
    DnsWidget(QWidget *parent = 0);
    ~DnsWidget();
private:
	void saveSettings();
	void restoreSettings();
	QString sendData();
private:
    Ui::DnsWidgetClass ui;
};

#endif // DNS_WIDGET_H
