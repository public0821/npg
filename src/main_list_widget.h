/*
 * TypeListWidget.h
 *
 *  Created on: 2011-8-19
 *      Author: wuyangchun
 */

#ifndef TYPELISTWIDGET_H_
#define TYPELISTWIDGET_H_

#include <qlistwidget.h>

class MainListWidget: public QListWidget
{
	Q_OBJECT

public:
	MainListWidget();
	virtual ~MainListWidget();
};

#endif /* TYPELISTWIDGET_H_ */
