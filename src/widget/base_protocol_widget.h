#ifndef BASE_PROTOCOL_WIDGET_H
#define BASE_PROTOCOL_WIDGET_H

#include <QWidget>
#include "system/types.h"
#include <QPushButton>
#include <QHBoxLayout>

class BaseProtocolWidget : public QWidget
{
	Q_OBJECT

public:
	BaseProtocolWidget(const QString& name,QWidget *parent);
	virtual ~BaseProtocolWidget();
public:
	virtual QString sendData(const char* data, u_int16_t length) = 0;
	virtual void saveSettings() = 0;
	virtual void restoreSettings() = 0;
protected:
	QString protocolName()const{return m_name;};
	void setupUi(QHBoxLayout* layout, QWidget* show_widget);
protected slots:
	void onShowButton();
private:
	QString m_name;
	QPushButton* m_show_button;
	QWidget* m_show_widget;
	bool m_show;
};

#endif // BASE_PROTOCOL_WIDGET_H
