/*
 * tcp_widget.h
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */

#ifndef TCP_WIDGET_H
#define TCP_WIDGET_H

#include "ui_tcp_widget.h"
#include "tab_sheet.h"

class TcpWidget : public TabSheet
{
    Q_OBJECT

public:
    TcpWidget(const QString& name, QWidget *parent = 0);
    ~TcpWidget();
public:
    QString sendData();
 //   QString beforeSendData();
private:
	void saveSettings();
	void restoreSettings();
private:
    Ui::TcpWidgetClass ui;
};

#endif // TCP_WIDGET_H
