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
private:
	const  QString m_name;
};

#endif // UDPWIDGET_H
