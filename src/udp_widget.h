/*
 * udp_widget.h
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */

#ifndef UDPWIDGET_H
#define UDPWIDGET_H

#include "tab_sheet.h"
#include "ui_udp_widget.h"

class UdpWidget : public TabSheet
{
    Q_OBJECT

public:
    UdpWidget(QWidget *parent);
    ~UdpWidget();
public:
    QString sendData();
private:
	void saveSettings();
	void restoreSettings();
private:
    Ui::UdpWidgetClass ui;
};

#endif // UDPWIDGET_H
