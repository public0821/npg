#include "protocol_builder.h"
#include <qstring.h>
#include "logger.h"
#include "socket/socket_public.h"

const u_int16_t BUFFER_INCREMENT =  128;

ProtocolBuilder::ProtocolBuilder(void)
:m_buffer(NULL), m_protocol_len(0), m_buf_len(0)
{
}

ProtocolBuilder::~ProtocolBuilder(void)
{
	if (m_buffer != NULL)
	{
		delete[] m_buffer;
		m_buffer = NULL;
	}
}

u_int32_t ProtocolBuilder::reallocBuffer(EFiledType field_type, u_int16_t length, const QString& value)
{
	if (m_buffer == NULL)
	{
		m_buffer = new char[BUFFER_INCREMENT];
		m_buf_len = BUFFER_INCREMENT;
	}

	u_int32_t new_protocol_len;
	switch (field_type)
	{
	case E_FIELD_TYPE_BIT:	
		new_protocol_len = m_protocol_len + (length+7)/8;
		break;
	case E_FIELD_TYPE_STRING:
		if (length != 0)
		{
			new_protocol_len = m_protocol_len + length;
		}
		else
		{
			sstring value_str = value.toStdString();
			new_protocol_len = m_protocol_len + value_str.length();
		}
		break;
	default:
		new_protocol_len = m_protocol_len + length;
		break;
	}

	if( new_protocol_len > m_buf_len)
	{
		char* new_buf = new char[m_buf_len + BUFFER_INCREMENT];
		memcpy(new_buf, m_buffer, m_protocol_len);
		delete[] m_buffer;
		m_buffer = new_buf;
		m_buf_len += BUFFER_INCREMENT;
	}

	u_int32_t old_protocol_len = m_protocol_len;
	m_protocol_len = new_protocol_len;

	return old_protocol_len;
}

bool ProtocolBuilder::append(EFiledType field_type, u_int16_t length, const QString& value)
{
	u_int32_t old_protocol_len = reallocBuffer(field_type, length, value);

	bool ret = true;
	switch (field_type)
	{
	case E_FIELD_TYPE_INT:	
		switch(length)
		{
		case 1:
			{
				int8_t number = (int8_t)value.toInt();
				memcpy(m_buffer + old_protocol_len, &number, sizeof(number));
			}	
			break;
		case 2:
			{
				int16_t number = (int16_t)value.toInt();
				number = htons(number);
				memcpy(m_buffer + old_protocol_len, &number, sizeof(number));
			}
			break;
		case 4:
			{
				int32_t number = (int32_t)value.toInt();
				number = htonl(number);
				memcpy(m_buffer + old_protocol_len, &number, sizeof(number));
			}
			break;
		case 8:
		default:
			{
				int64_t number = (int64_t)value.toLongLong();
				number = ntohll(number);
				memcpy(m_buffer + old_protocol_len, &number, sizeof(number));
			}
			break;
		}
		break;
	case E_FIELD_TYPE_IP:
		{
			sstring ip = value.toStdString();
			struct in_addr addr;
			addr.s_addr = 0;
			if (!ip.empty() && ip != "...")
			{
				addr.s_addr = inet_addr(ip.c_str());
				if (addr.s_addr == INADDR_NONE)
				{
					SET_ERROR_STR("Not in presentation format");
					ret = false;
				}
			}
			memcpy(m_buffer + old_protocol_len, &addr.s_addr, sizeof(addr.s_addr));
		}
		break;
	case E_FIELD_TYPE_STRING:
		{
			sstring data = value.toStdString();
			int data_len = data.length(); 
			if (length != 0)
			{
				data_len = length;
			}
			memcpy(m_buffer + old_protocol_len, data.c_str(), data_len);
		}
		break;
	default:
		SET_ERROR_STR("Unsupported type");
		ret = false;
		bzero(m_buffer + old_protocol_len, length);
		break;
	}

	return ret;
}

char* ProtocolBuilder::data()const
{
	return m_buffer;
}
u_int32_t ProtocolBuilder::length()const
{
	return m_protocol_len;
}

//int8_t ProtocolBuilder::toInt8(const QString& value)
//{
//	
//}
//
//int16_t ProtocolBuilder::toInt16(const QString& value)
//{
//
//}
//
//int32_t ProtocolBuilder::toInt32(const QString& value)
//{
//
//}
//
//int64_t ProtocolBuilder::toInt64(const QString& value)
//{
//	
//}