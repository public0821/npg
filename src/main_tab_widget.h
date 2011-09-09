/*
 * main_tab_widget.h
 *
 *  Created on: 2011-8-19
 *      Author: wuyangchun
 */

#ifndef MAIN_TAB_WIDGET_H_
#define MAIN_TAB_WIDGET_H_
#include <qtabwidget.h>
#include <qvector.h>
#include "tab_sheet.h"
class MainTabWidget: public QTabWidget
{
	Q_OBJECT
public:
	MainTabWidget();
	virtual ~MainTabWidget();
public:
	int addTab(const QString &type);
private slots:
	void onCloseTab(int index);
private:
	QVector<TabSheet*>	m_tabs;
};

#endif /* MAIN_TAB_WIDGET_H_ */
