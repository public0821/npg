/*
 * protocol_builder.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef __PROTOCOL_BUILDER_H__
#define __PROTOCOL_BUILDER_H__
#include <qstring.h>
#include "qerror.h"
#include "protocol/field.h"


class ProtocolBuilder:public QError
{
public:
	ProtocolBuilder(void);
	~ProtocolBuilder(void);
public:
	bool append(EFiledType field_type, u_int16_t length, const QString& value);
	bool append(const char* buf, u_int16_t length);
	bool set(u_int32_t pos, EFiledType field_type, u_int16_t length, const QString& value);
	char* data()const;
	u_int32_t length()const;
//private:
//	int8_t toInt8(const QString& value);
//	int16_t toInt16(const QString& value);
//	int32_t toInt32(const QString& value);
//	int64_t toInt64(const QString& value);
private:
	u_int32_t reallocBuffer(EFiledType field_type, u_int16_t length, const QString& value);
	u_int32_t reallocBuffer(u_int32_t new_length);
private:
	char* m_buffer;
	u_int32_t m_protocol_len;
	u_int32_t m_buf_len;
	//std::vector<u_int32_t> m_field_pos;
};

#endif
