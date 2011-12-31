#include "protocol_builder.h"
#include <qstring.h>
#include "logger.h"
#include "socket/socket_public.h"
#include "socket/socket_toolkit.h"

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

	return reallocBuffer(new_protocol_len);
}

u_int32_t ProtocolBuilder::reallocBuffer(u_int32_t new_length)
{
	if (m_buffer == NULL)
	{
		m_buffer = new char[BUFFER_INCREMENT];
		m_buf_len = BUFFER_INCREMENT;
	}

	if( new_length > m_buf_len)
	{
		char* new_buf = new char[m_buf_len + (new_length-m_buf_len)/BUFFER_INCREMENT + BUFFER_INCREMENT];
		memcpy(new_buf, m_buffer, m_protocol_len);
		delete[] m_buffer;
		m_buffer = new_buf;
		m_buf_len += BUFFER_INCREMENT;
	}

	u_int32_t old_protocol_len = m_protocol_len;
	m_protocol_len = new_length;

	return old_protocol_len;
}

bool ProtocolBuilder::append(EFiledType field_type, u_int16_t length, const QString& value)
{
	u_int32_t old_protocol_len = reallocBuffer(field_type, length, value);

	return set(old_protocol_len, field_type, length, value);

}

char* ProtocolBuilder::data()const
{
	return m_buffer;
}
u_int32_t ProtocolBuilder::length()const
{
	return m_protocol_len;
}

bool ProtocolBuilder::set(u_int32_t pos, EFiledType field_type, u_int16_t length, const QString& value)
{
	if (pos + length > m_protocol_len)
	{
		SET_ERROR_STR("Out of range");
		return false;
	}
	/*if (field_type == E_FIELD_TYPE_STRING)
	{
		SET_ERROR_STR("Field length must fixed");
		return false;
	}*/

	bool ret = true;
	switch (field_type)
	{
	case E_FIELD_TYPE_INT:	
		switch(length)
		{
		case 1:
			{
				int8_t number = (int8_t)value.toInt();
				memcpy(m_buffer + pos, &number, sizeof(number));
			}	
			break;
		case 2:
			{
				int16_t number = (int16_t)value.toInt();
				number = htons(number);
				memcpy(m_buffer + pos, &number, sizeof(number));
			}
			break;
		case 4:
			{
				int32_t number = (int32_t)value.toInt();
				number = htonl(number);
				memcpy(m_buffer + pos, &number, sizeof(number));
			}
			break;
		case 8:
		default:
			{
				int64_t number = (int64_t)value.toLongLong();
				number = ntohll(number);
				memcpy(m_buffer + pos, &number, sizeof(number));
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
			memcpy(m_buffer + pos, &addr.s_addr, sizeof(addr.s_addr));
		}
		break;
	case E_FIELD_TYPE_MAC:
		{
			sstring mac_str = value.toStdString();
			u_int8_t mac[IF_HWADDRLEN];
			SocketToolkit toolkit;
			if (!toolkit.toMac(mac_str.c_str(), mac))
			{
				SET_ERROR_STR("Unsupported type");
				ret = false;
			}
			memcpy(m_buffer + pos, mac, sizeof(mac));
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
			memcpy(m_buffer + pos, data.c_str(), data_len);
		}
		break;
	default:
		SET_ERROR_STR("Unsupported type");
		ret = false;
		bzero(m_buffer + pos, length);
		break;
	}

	return ret;
}

bool ProtocolBuilder::append(const char* buf, u_int16_t length)
{
	u_int32_t pos = reallocBuffer(m_protocol_len + length);
	memcpy(m_buffer + pos, buf, length);

	return true;
}