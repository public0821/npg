/*
 * ip_converter.h
 *
 *  Created on: 2012-03-19
 *      Author: Young <public0821@gmail.com>
 */
#ifndef	__HEX_CONVERTER_H__
#define __HEX_CONVERTER_H__

#include "converter.h"

class HexConverter : public Converter
{
public:
	HexConverter(void);
	~HexConverter(void);
public:
	QString title();
	QString fromTextTip();
	QString toTextTip();

	QString convert(const QString& text);
	QString revert(const QString& text);
private:
	char toHex(uint8_t);
	uint8_t toUInt8(char hex);
};

#endif