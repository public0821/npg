/*
 * tab_sheet.h
 *
 *  Created on: 2011-8-22
 *      Author: wuyangchun
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
#include <qthread.h>

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
		return m_bAdvanced;
	}
	;
private:
	void run();
	void stop();
private:
	virtual void saveSettings()=0;
	virtual void restoreSettings()=0;
	virtual QString sendData()=0;
	virtual QString beforeSendData(){return "";};

protected slots:
		void onAdvanced();
		void onSend();
		void onSendFinish();
		void counter(int count, int seconds);
private:
	QPushButton *m_sendButton;
	QPushButton *m_advancedButton;
	QLabel *m_tipLabel;
	QLabel *m_statusLabel1;
	QLabel *m_statusLabel2;

	QComboBox *m_sendTypeBox;
	QLineEdit* m_countEdit;

	QGroupBox * m_advancedGroup;

	bool m_bAdvanced;

	SendThread* m_sendThread;

	friend class SendThread;
};


#endif /* TAB_SHEET_H_ */
