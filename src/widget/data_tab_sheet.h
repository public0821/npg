/*
 * data_table_sheet.h
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */

#ifndef UDP_TAB_SHEET_H
#define UDP_TAB_SHEET_H

#include "tab_sheet.h"
#include <QTextEdit>

class DataTabSheet: public TabSheet
{
Q_OBJECT

public:
	DataTabSheet(const QString& name, QWidget *parent);
	~DataTabSheet();
	public:
	bool sendData();
	bool preSendData();
	bool postSendData();
	private:
	void saveSettings();
	void restoreSettings();
	void setupUi();
	void onSaveSettings() {
	}
	void onRestoreSettings() {
	}
private:
	QTextEdit* m_data_edit;
	QByteArray m_data;
};

#endif // UDPWIDGET_H
