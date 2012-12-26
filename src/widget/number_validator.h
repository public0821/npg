/*
 * number_validator.h
 *
 *  Created on: 2012-12-24
 *      Author: Young <public0821@gmail.com>
 */

#ifndef NUMBER_VALIDATOR_H_
#define NUMBER_VALIDATOR_H_

#include <qvalidator.h>
#include "lib/types.h"

class NumberValidator: public QValidator {
public:
	NumberValidator(QObject * parent = 0);
	NumberValidator(int64_t bottom, int64_t top, QObject * parent = 0);
	virtual ~NumberValidator();
	virtual State validate(QString & input, int & pos) const;
	int64_t value(const QString & input, bool *ok = NULL) const;
private:
	int64_t m_bottom;
	int64_t m_top;
};

#endif /* NUMBER_VALIDATOR_H_ */
