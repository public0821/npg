/*
 * number_edit.cpp
 *
 *  Created on: 2012-12-24
 *      Author: Young <public0821@gmail.com>
 */

#include "number_edit.h"
#include <qvalidator.h>
#include "logger.h"
#include "number_validator.h"

NumberEdit::NumberEdit(const Field& field, QWidget* parent) :
		QLineEdit(parent), m_field(field) {
	//}
	//	edit->setValidator(new QIntValidator(this));
	//			break;
	//		case E_FIELD_TYPE_INT:
	this->setValidator(new NumberValidator(this));
}

NumberEdit::~NumberEdit() {
}

QString NumberEdit::getIntValue() {
	return "";
}
