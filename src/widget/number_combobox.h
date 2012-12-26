/*
 * number_combobox.h
 *
 *  Created on: 2012-12-24
 *      Author: Young <public0821@gmail.com>
 */

#ifndef NUMBER_COMBOBOX_H_
#define NUMBER_COMBOBOX_H_

#include <qcombobox.h>
#include "protocol/field.h"
#include "number_validator.h"

class NumberComboBox: public QComboBox {
public:
	NumberComboBox(QWidget* parent = NULL);
	NumberComboBox(const std::vector<FieldItem>& field_items, QWidget* parent = NULL);
	virtual ~NumberComboBox();
	QString getIntStrValue();
    void addItems(const std::vector<FieldItem>& field_items);
    void addItem(int value, QString text="", int base=10);
    void addItem(QString value, QString text="" );

private:
//	NumberValidator m_validator;
};

#endif /* NUMBER_COMBOBOX_H_ */
