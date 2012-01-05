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

class DataTabSheet : public TabSheet
{
    Q_OBJECT

public:
    DataTabSheet(const QString& name, QWidget *parent);
    ~DataTabSheet();
public:
    QString sendData();
private:
	void saveSettings();
	void restoreSettings();
	void setupUi();
private:
	QTextEdit* m_data_edit;
};

#endif // UDPWIDGET_H
