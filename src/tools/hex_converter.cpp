#include "hex_converter.h"
#include <QObject>

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
	for(size_t i = 0u; i<byte_array.size(); i++)
	{
		unsigned char ch = from_str[i];
		to_str[i * 2u] = toHex(ch / 0X10);
		to_str[i * 2u + 1u] = toHex(ch % 0X10);
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
		SET_QERROR_STR(QObject::tr("Invalid hex char length"));
		return "";
	}
	
	const char* from_str = byte_array.constData();
	char* to_str = new char[byte_array.size()/2 + 1];
	to_str[byte_array.size() / 2] = '\0';
	for(size_t i = 0u; i<byte_array.size()/2; i++)
	{
		const u_int8_t n1 = toUInt8(from_str[i*2u]);
		const u_int8_t n2 = toUInt8(from_str[i*2u+1u]);
		if (n1 == -1 || n2 == -1)
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


u_int8_t HexConverter::toUInt8(char hex)
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
		SET_QERROR_STR(QObject::tr("Invalid hex char"));
		return -1;
	}
}

char HexConverter::toHex(u_int8_t ch)
{
	if(0 <= ch && ch < 10)
	{
		return char('0' + ch);
	}
	else if(10 <= ch && ch < 0X10)
	{
		return char('A' + ch - 10);
	}
	else
	{
		SET_QERROR_STR(QObject::tr("Invalid hex number"));
		return '\0';
	}
}
