/*
 * npg.h
 *
 *  Created on: 2011-8-19
 *      Author: Young <public0821@gmail.com>
 */
#ifndef NPG_H
#define NPG_H

#include <QtGui/QMainWindow>
#include "ui/ui_npg.h"
#include <QSplitter>
#include "widget/main_list_widget.h"
#include "widget/main_tab_widget.h"
#include <qtextbrowser.h>

class Npg: public QMainWindow
{
Q_OBJECT

public:
	Npg(QWidget *parent = 0);
	~Npg();
private slots:
	void onItemDoubleClicked(QListWidgetItem * item);
	void onConverterClicked();
	void onAbout();
private:
	void saveSettings();
	void restoreSettings();
	void closeEvent(QCloseEvent *event);
private:
	Ui::npgClass ui;
	MainListWidget* m_type_list;
	MainTabWidget* m_tab_widget;
	QSplitter* m_main_splitter;
	QSplitter* m_log_splitter;
	QTextBrowser* m_logger;
//	QStringList m_data_types;
};

#endif // NPG_H
