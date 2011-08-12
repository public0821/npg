#ifndef UDPWIDGET_H
#define UDPWIDGET_H

#include <QtGui/QWidget>
#include "ui_udp_widget.h"

class UdpWidget : public QWidget
{
    Q_OBJECT

public:
    UdpWidget(QWidget *parent);
    ~UdpWidget();
private slots:
	void onSend();
private:
    Ui::UdpWidgetClass ui;
};

#endif // UDPWIDGET_H
