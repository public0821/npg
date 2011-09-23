#ifndef ARP_WIDGET_H
#define ARP_WIDGET_H

#include <QtGui/QWidget>
#include "ui_arp_widget.h"
#include "tab_sheet.h"

class ArpWidget: public TabSheet
{
    Q_OBJECT

public:
    ArpWidget(QWidget *parent = 0);
    ~ArpWidget();
private:
	virtual void saveSettings();
	virtual void restoreSettings();
	QString sendData();
private:
    Ui::ArpWidgetClass ui;
};

#endif // ARP_WIDGET_H
