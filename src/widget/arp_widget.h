/*
 * arp_widget.h
 *
 *  Created on: 2011-10-11
 *      Author: Young <public0821@gmail.com>
 */

#ifndef ARP_WIDGET_H
#define ARP_WIDGET_H

#include "ui_arp_widget.h"
#include "tab_sheet.h"

class ArpWidget: public TabSheet
{
    Q_OBJECT

public:
    ArpWidget(QWidget *parent = 0);
    ~ArpWidget();
private:
	void saveSettings();
	void restoreSettings();
	QString sendData();
private:
    Ui::ArpWidgetClass ui;
};

#endif // ARP_WIDGET_H
