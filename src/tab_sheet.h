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

class SendThread;
class TabSheet: public QWidget
{
Q_OBJECT

public:
	TabSheet(QWidget *parent);
	virtual ~TabSheet();
protected:
	void setupUi(QHBoxLayout* layout);
	void showTip(const QString& tip);
	void showSuccessfulTip(const QString& tip);
	void showFailedTip(const QString& tip);
	bool isAdvance() const
	{
		return m_is_advanced;
	}
	;
private:
	void run();
	void stop();
private:
	virtual void saveSettings()=0;
	virtual void restoreSettings()=0;
	virtual QString sendData()=0;
	virtual QString beforeSendData(){return tr("");};

protected slots:
		void onAdvanced();
		void onSend();
		void onSendFinish();
		void counter(int count, int seconds);
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

	friend class SendThread;
};


#endif /* TAB_SHEET_H_ */
