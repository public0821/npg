#ifndef IP_WIDGET_H
#define IP_WIDGET_H

#include <QWidget>
#include "ui_ip_widget.h"
#include <map>
#include "base_protocol_widget.h"

class IpWidget : public BaseProtocolWidget
{
	Q_OBJECT

public:
	IpWidget(const QString& protocol_name, const QString& ip_protocol_name, QWidget *parent);
	~IpWidget();
public:
	QString sendData(const char* data, u_int16_t length);
public:
	void saveSettings();
	void restoreSettings();
private:
	Ui::IpWidget ui;
	std::map<sstring, int>  m_built_in_protocol;
};

#endif // IP_WIDGET_H
