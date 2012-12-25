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

class NumberComboBox: public QComboBox {
public:
	NumberComboBox(const Field& field, QWidget* parent=NULL);
	virtual ~NumberComboBox();
	QString getIntValue();
private:
	const Field& m_field;
};

#endif /* NUMBER_COMBOBOX_H_ */
