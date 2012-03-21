/*
 * ip_converter.h
 *
 *  Created on: 2012-03-19
 *      Author: Young <public0821@gmail.com>
 */
#ifndef	__BASE64_CONVERTER_H__
#define __BASE64_CONVERTER_H__

#include "converter.h"

class Base64Converter : public Converter
{
public:
	Base64Converter(void);
	~Base64Converter(void);
public:
	QString title();
	QString fromTextTip();
	QString toTextTip();

	QString convert(const QString& text);
	QString revert(const QString& text);
private:
	void encodeblock( const unsigned char in[3], unsigned char out[4], int len );
	int decodeblock( const unsigned char in[4], unsigned char out[3]);
};

#endif