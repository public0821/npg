/*
 * ip_converter.h
 *
 *  Created on: 2012-03-19
 *      Author: Young <public0821@gmail.com>
 */
#ifndef	__TIME_CONVERTER_H__
#define __TIME_CONVERTER_H__

#include "converter.h"

class TimeConverter : public Converter
{
public:
	TimeConverter(void);
	~TimeConverter(void);
public:
	QString title();
	QString fromTextTip();
	QString toTextTip();

	QString convert(const QString& text);
	QString revert(const QString& text);
};

#endif