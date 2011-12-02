/*
 * main_list_widget.h
 *
 *  Created on: 2011-8-19
 *      Author: Young <public0821@gmail.com>
 */

#ifndef TYPELISTWIDGET_H_
#define TYPELISTWIDGET_H_

#include <qlistwidget.h>

class MainListWidget: public QListWidget
{
	Q_OBJECT

public:
	MainListWidget();
	~MainListWidget();
};

#endif /* TYPELISTWIDGET_H_ */
