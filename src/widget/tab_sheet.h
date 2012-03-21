/*
 * tab_sheet.h
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */

#ifndef TAB_SHEET_H_
#define TAB_SHEET_H_

#include <qwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <QHBoxLayout>
#include <QGroupBox>
#include "base_protocol_widget.h"

class SendThread;
class TabSheet: public QWidget
{
Q_OBJECT

public:
	TabSheet(const QString& protocol_name, QWidget *parent = NULL, QString depend_protocol_name="", QString depend_protocol_param="");
	virtual ~TabSheet();
public:
	void showTip(const QString& tip);
	void showSuccessfulTip(const QString& tip);
	void showFailedTip(const QString& tip);
protected:
	void setupUi(QHBoxLayout* layout);
	bool isAdvance() const
	{
		return m_is_advanced;
	}
	;
	QString protocolName()const{return m_protocol_name;};
	BaseProtocolWidget* dependProtocolWidget()const{return m_base_protocol_widget;};
private:
	void run();
	void stop();
protected:
	virtual void saveSettings()
	{ 
		if (m_base_protocol_widget != NULL)
		{
			m_base_protocol_widget->saveSettings();
		}
	};
	virtual void restoreSettings()
	{
		if (m_base_protocol_widget != NULL)
		{
			m_base_protocol_widget->restoreSettings();
		}	
	};

	virtual QString preSendData()=0;
	virtual QString sendData()=0;
	virtual QString postSendData()=0;
	

protected slots:
		void onAdvanced();
		void onSend();
		void onSendFinish();
		void onCounter(int count, time_t seconds);
private:
	QPushButton *m_send_button;
	QPushButton *m_advanced_button;
	QLabel *m_tip_label;
	QLabel *m_status_label1;
	QLabel *m_status_label2;

	QComboBox *m_send_typeBox;
	QLineEdit* m_count_edit;

	QGroupBox * m_advanced_group;

	bool m_is_advanced;

	SendThread* m_send_thread;

	QString m_protocol_name;
//	QString m_depend_protocol_name;

	BaseProtocolWidget* m_base_protocol_widget;

	friend class SendThread;
};


#endif /* TAB_SHEET_H_ */
