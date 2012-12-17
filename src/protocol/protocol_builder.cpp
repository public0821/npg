#include "protocol_builder.h"
#include <qstring.h>
#include "lib/socket/socket.h"
#include "lib/socket/socket_toolkit.h"
#include <QObject>

const uint16_t BUFFER_INCREMENT =  128;

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

uint32_t ProtocolBuilder::reallocBuffer(EFiledType field_type, uint16_t length, const QString& value)
{
	uint32_t new_protocol_len;
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
			std::string value_str = value.toLocal8Bit().constData();
			new_protocol_len = m_protocol_len + value_str.length();
		}
		break;
	default:
		new_protocol_len = m_protocol_len + length;
		break;
	}

	return reallocBuffer(new_protocol_len);
}

uint32_t ProtocolBuilder::reallocBuffer(uint32_t new_length)
{
	if (m_buffer == NULL)
	{
		m_buffer = new char[BUFFER_INCREMENT];
		m_buf_len = BUFFER_INCREMENT;
	}

	if( new_length > m_buf_len)
	{
		uint32_t new_buffer_len = m_buf_len + ((new_length-m_buf_len)/BUFFER_INCREMENT + 1) * BUFFER_INCREMENT;
		char* new_buf = new char[new_buffer_len];
		memcpy(new_buf, m_buffer, m_protocol_len);
		delete[] m_buffer;
		m_buffer = new_buf;
		m_buf_len = new_buffer_len;
	}

	uint32_t old_protocol_len = m_protocol_len;
	m_protocol_len = new_length;

	return old_protocol_len;
}

bool ProtocolBuilder::append(EFiledType field_type, uint16_t length, const QString& value)
{
	uint32_t old_protocol_len = reallocBuffer(field_type, length, value);

	return set(old_protocol_len, field_type, length, value);

}

char* ProtocolBuilder::data()const
{
	return m_buffer;
}
uint32_t ProtocolBuilder::length()const
{
	return m_protocol_len;
}

bool ProtocolBuilder::set(uint32_t pos, EFiledType field_type, uint16_t length, const QString& value)
{
	if (pos + length > m_protocol_len)
	{
		SET_QERROR_STR(QObject::tr("Parameter length out of range"));
		return false;
	}

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
			std::string ip = value.toLocal8Bit().constData();
			struct in_addr addr;
			addr.s_addr = 0;
			if (!ip.empty() && ip != "...")
			{
				addr.s_addr = inet_addr(ip.c_str());
				if (addr.s_addr == INADDR_NONE)
				{
					SET_QERROR_STR(QObject::tr("IP address format error"));
					ret = false;
				}
			}
			memcpy(m_buffer + pos, &addr.s_addr, sizeof(addr.s_addr));
		}
		break;
	case E_FIELD_TYPE_MAC:
		{
			std::string mac_str = value.toLocal8Bit().constData();
			uint8_t mac[IF_HWADDRLEN];
			SocketToolkit toolkit;
			if (!toolkit.toMac(mac_str.c_str(), mac))
			{
				SET_QERROR_STR(QObject::tr("MAC address format error"));
				ret = false;
			}
			memcpy(m_buffer + pos, mac, sizeof(mac));
		}
		break;
	case E_FIELD_TYPE_STRING:
		{
			std::string data = value.toLocal8Bit().constData();
			int data_len = data.length(); 
			if (length != 0)
			{
				data_len = length;
			}
			memcpy(m_buffer + pos, data.c_str(), data_len);
		}
		break;
	default:
		SET_QERROR_STR(QString(QObject::tr("Unsupported type:%1")).arg((int)field_type));
		ret = false;
		bzero(m_buffer + pos, length);
		break;
	}

	return ret;
}

bool ProtocolBuilder::append(const char* buf, uint16_t length)
{
	uint32_t pos = reallocBuffer(m_protocol_len + length);
	memcpy(m_buffer + pos, buf, length);

	return true;
}
