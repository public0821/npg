/*
 * protocol_builder.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef __PROTOCOL_BUILDER_H__
#define __PROTOCOL_BUILDER_H__
#include <qstring.h>
#include "protocol/field.h"


class ProtocolBuilder
{
public:
	ProtocolBuilder(void);
	~ProtocolBuilder(void);
public:
	bool append(EFiledType field_type, uint16_t length, const QString& value);
	bool append(const char* buf, uint16_t length);
	bool set(uint32_t pos, EFiledType field_type, uint16_t length, const QString& value);
	char* data()const;
	uint32_t length()const;
//private:
//	int8_t toInt8(const QString& value);
//	int16_t toInt16(const QString& value);
//	int32_t toInt32(const QString& value);
//	int64_t toInt64(const QString& value);
private:
	uint32_t reallocBuffer(EFiledType field_type, uint16_t length, const QString& value);
	uint32_t reallocBuffer(uint32_t new_length);
private:
	char* m_buffer;
	uint32_t m_protocol_len;
	uint32_t m_buf_len;
	//std::vector<uint32_t> m_field_pos;
};

#endif
