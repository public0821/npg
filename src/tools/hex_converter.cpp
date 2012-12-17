#include "hex_converter.h"
#include <QObject>
#include "../logger.h"

HexConverter::HexConverter(void)
{
}

HexConverter::~HexConverter(void)
{
}

QString HexConverter::title()
{
	return QObject::tr("Hex Converter");
}

QString HexConverter::fromTextTip()
{
	return QObject::tr("String:");
}

QString HexConverter::toTextTip()
{
	return QObject::tr("Hex:");
}

QString HexConverter::convert(const QString& text)
{
	QByteArray	byte_array = text.toLocal8Bit();
	const char* from_str = byte_array.constData();
	char* to_str = new char[byte_array.size() * 2 + 1];
	to_str[byte_array.size() * 2] = '\0';
	for(int i = 0; i<byte_array.size(); i++)
	{
		unsigned char ch = from_str[i];
		to_str[i * 2] = toHex(ch / 0X10);
		to_str[i * 2 + 1] = toHex(ch % 0X10);
	}
	
	QString result = QString::fromLocal8Bit(to_str);
	delete[] to_str;
	return result;
}

QString HexConverter::revert(const QString& text)
{
	QByteArray	byte_array = text.toLocal8Bit();
	if (byte_array.size() % 2 == 1)
	{
		LOG_ERROR(QObject::tr("Invalid hex string length"));
		return "";
	}
	
	const char* from_str = byte_array.constData();
	char* to_str = new char[byte_array.size()/2 + 1];
	to_str[byte_array.size() / 2] = '\0';
	for(int i = 0; i<byte_array.size()/2; i++)
	{
		const uint8_t n1 = toUInt8(from_str[i*2]);
		const uint8_t n2 = toUInt8(from_str[i*2+1]);
		if (n1 == 0xFF || n2 == 0xFF)
		{
			delete[] to_str;
			return "";
		}
		to_str[i] = char(n1 * 0X10 + n2);
	}

	QString result = QString::fromLocal8Bit(to_str);
	delete[] to_str;
	return result;
}


uint8_t HexConverter::toUInt8(char hex)
{
	if('0' <= hex && hex <= '9')
	{
		return int(hex - '0');
	}
	else if('A' <= hex && hex <= 'F')
	{
		return int(hex - 'A')+10;
	}
	else if('a' <= hex && hex <= 'f')
	{
		return int(hex - 'a')+10;
	}
	else
	{
		LOG_ERROR(QObject::tr("Invalid hex char"));
		return 0xFF;
	}
}

char HexConverter::toHex(uint8_t ch)
{
	if(ch <= 0x09)
	{
		return char('0' + ch);
	}
	else if(0x0A <= ch && ch < 0X10)
	{
		return char('A' + ch - 10);
	}
	else
	{
		LOG_ERROR(QObject::tr("Invalid hex number"));
		return '\0';
	}
}
