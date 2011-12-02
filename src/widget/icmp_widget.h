/*
 * icmp_widget.h
 *
 *  Created on: 2011-10-11
 *      Author: Young <public0821@gmail.com>
 */
#ifndef ICMP_WIDGET_H
#define ICMP_WIDGET_H

#include <QtGui/QWidget>
#include "ui_icmp_widget.h"
#include "tab_sheet.h"
#include <qmap.h>
#include <qlist.h>
#include <qpair.h>

class IcmpWidget: public TabSheet
{
Q_OBJECT

public:
	IcmpWidget(QWidget *parent = 0);
	~IcmpWidget();
private:
	void saveSettings();
	void restoreSettings();
	QString sendData();
private slots:
	void onTypeIndexChanged(const QString &text);
	void onCodeIndexChanged(const QString &text);
private:
	void initProtocol();
	void hideExendedWidget();
	void showIdWidget();
	void showMoreWidget(int index, const QString& label,
			const QString& tip = "");

	void showMoreWidgetPing();
private:
	Ui::IcmpWidgetClass ui;
	QMap<int, QMap<int, QString> > m_protocol;
	int m_seq;
};

#endif // ICMP_WIDGET_H
