/*
 * ip_converter.h
 *
 *  Created on: 2012-03-19
 *      Author: Young <public0821@gmail.com>
 */
#ifndef	__IP_CONVERTER_H__
#define __IP_CONVERTER_H__

#include "converter.h"

class IpConverter : public Converter
{
public:
	IpConverter(void);
	~IpConverter(void);
public:
	QString title();
	QString fromTextTip();
	QString toTextTip();

	QString convert(const QString& text);
	QString revert(const QString& text);
};

#endif