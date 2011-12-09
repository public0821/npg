/*
 * main_tab_widget.h
 *
 *  Created on: 2011-8-19
 *      Author: Young <public0821@gmail.com>
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
	MainTabWidget(const QMap<QString, QString>& name_icons,  QWidget* parent = NULL);
	~MainTabWidget();
public:
	int addTab(const QString &type);
private slots:
	void onCloseTab(int index);
private:
	QVector<TabSheet*>	m_tabs;
	QMap<QString, QString> m_name_icons;
};

#endif /* MAIN_TAB_WIDGET_H_ */
