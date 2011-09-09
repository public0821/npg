#ifndef TCP_WIDGET_H
#define TCP_WIDGET_H

#include <QtGui/QWidget>
#include "ui_tcp_widget.h"
#include "tab_sheet.h"

class TcpWidget : public TabSheet
{
    Q_OBJECT

public:
    TcpWidget(QWidget *parent = 0);
    ~TcpWidget();
public:
    QString sendData();
 //   QString beforeSendData();
private:
	void saveSettings();
	void restoreSettings();
private:
    Ui::TcpWidgetClass ui;
	const  QString m_name;
};

#endif // TCP_WIDGET_H
