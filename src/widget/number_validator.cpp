/*
 * number_validator.cpp
 *
 *  Created on: 2012-12-24
 *      Author: Young <public0821@gmail.com>
 */

#include "number_validator.h"
#include "logger.h"
#include "lib/types.h"

NumberValidator::NumberValidator(QObject * parent) :
		QValidator(parent), m_bottom(INT64_MIN), m_top(INT64_MAX) {
}

NumberValidator::NumberValidator(int64_t bottom, int64_t top, QObject * parent) :
		QValidator(parent), m_bottom(bottom), m_top(top) {

}

NumberValidator::~NumberValidator()
{
	// TODO Auto-generated destructor stub
}

QValidator::State NumberValidator::validate(QString & input, int & pos) const {
	int base = 10;
	if (input.length() >= 2 && input[0] == '0') {
		base = 8;
		if(input[1] == 'x' || input[1] == 'X' ){
			base = 16;
			if(input.length() == 2){
				return Acceptable;
			}
		}
	}

	bool ok;
	int64_t value = input.toLongLong(&ok, base);
	if (!ok) {
		return Invalid;
	}

//	LOG_ERROR(tr("%1").arg(value));
	if (value >= m_bottom && value <= m_top) {
		return Acceptable;
	}

	return Invalid;
}
