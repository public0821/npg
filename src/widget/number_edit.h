/*
 * number_edit.h
 *
 *  Created on: 2012-12-24
 *      Author: Young <public0821@gmail.com>
 */

#ifndef NUMBER_EDIT_H_
#define NUMBER_EDIT_H_

#include <qlineedit.h>
#include "protocol/field.h"
#include "number_validator.h"

class NumberEdit: public QLineEdit {
public:
	NumberEdit(QWidget* parent=NULL);
	NumberEdit(int64_t bottom, int64_t top, QWidget* parent=NULL);
	virtual ~NumberEdit();
public:
	QString getIntValue();
//	int8_t getInt8Number();
//	int16_t getInt16Number();
//	int32_t getInt32Number();
//	int64_t getInt64Number();
private:
	NumberValidator m_validator;
};

#endif /* NUMBER_EDIT_H_ */
