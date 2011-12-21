#ifndef __PROTOCOL_BUILDER_H__
#define __PROTOCOL_BUILDER_H__
#include <qstring.h>
#include "system/error.h"
#include "protocol/field.h"
class ProtocolBuilder:public Error
{
public:
	ProtocolBuilder(void);
	~ProtocolBuilder(void);
public:
	bool append(EFiledType field_type, u_int16_t length, const QString& value);
	char* data()const;
	u_int32_t length()const;
//private:
//	int8_t toInt8(const QString& value);
//	int16_t toInt16(const QString& value);
//	int32_t toInt32(const QString& value);
//	int64_t toInt64(const QString& value);
private:
	u_int32_t reallocBuffer(EFiledType field_type, u_int16_t length, const QString& value);
private:
	char* m_buffer;
	u_int32_t m_protocol_len;
	u_int32_t m_buf_len;
};

#endif