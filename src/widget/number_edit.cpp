/*
 * number_edit.cpp
 *
 *  Created on: 2012-12-24
 *      Author: Young <public0821@gmail.com>
 */

#include "number_edit.h"
#include <qvalidator.h>
#include "logger.h"

NumberEdit::NumberEdit(int64_t bottom, int64_t top, QWidget* parent) :
		QLineEdit(parent), m_validator(bottom, top, this) {
	this->setValidator(&m_validator);
}
NumberEdit::NumberEdit(QWidget* parent) :
		QLineEdit(parent), m_validator(this) {
	this->setValidator(&m_validator);
}

NumberEdit::~NumberEdit() {
}

QString NumberEdit::getIntValue() {
	return QString("%1").arg(m_validator.value(text()));
}
