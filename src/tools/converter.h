/*
 * converter.h
 *
 *  Created on: 2012-03-19
 *      Author: Young <public0821@gmail.com>
 */
#ifndef	__CONVERTER_H__
#define __CONVERTER_H__
#include <QString>
#include "system/qerror.h"

enum EConverterType
{
	E_CONVERTER_IP
	,E_CONVERTER_HEX
	,E_CONVERTER_TIME
	,E_CONVERTER_BASE64
};

class Converter : public QError
{
public:
	Converter(void);
	virtual ~Converter(void);
public:
	virtual QString title()=0;
	virtual QString fromTextTip()=0;
	virtual QString toTextTip()=0;

	virtual QString convert(const QString& text)=0;
	virtual QString revert(const QString& text)=0;
};

#endif