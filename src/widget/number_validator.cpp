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
	bool ok;
	int64_t result = this->value(input, &ok);
	if (!ok) {
		return Invalid;
	}

//	LOG_ERROR(tr("%1").arg(value));
	if (INT64_MAX == m_top && input[0] != '-') {
		uint64_t temp_result = (uint64_t)result;
		if (temp_result <= UINT64_MAX) {
			return Acceptable;
		}
	} else {
		if (result >= m_bottom && result <= m_top) {
			return Acceptable;
		}
	}

	return Invalid;
}

int64_t NumberValidator::value(const QString & input, bool *ok) const {
	if (input.length() == 0) {
		if (ok != NULL) {
			*ok = true;
		}
		return 0;
	}

	if (input.length() == 1 && input[0] == '-') {
		if (ok != NULL) {
			*ok = true;
		}
		return 0;
	}

	int base = 10;
	if (input.length() >= 2 && input[0] == '0') {
		base = 8;
		if (input[1] == 'x' || input[1] == 'X') {
			base = 16;
			if (input.length() == 2) {
				if (ok != NULL) {
					*ok = true;
				}
				return 0;
			}
		}
	}
	if (input[0] == '-') {
		return input.toLongLong(ok, base);
	} else {
		return input.toULongLong(ok, base);
	}
}
