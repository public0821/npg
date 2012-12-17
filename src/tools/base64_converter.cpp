#include "base64_converter.h"
#include <QObject>
#include "../logger.h"

static const unsigned char encode64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const unsigned char decode64[]={62, 127, 127, 127, 63
										, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61
										, 127, 127, 127, 126, 127, 127, 127
										, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
										, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
										, 20, 21, 22, 23, 24, 25
										, 127, 127, 127, 127, 127, 127
										, 26, 27, 28, 29
										, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39
										, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49
										, 50, 51};

Base64Converter::Base64Converter(void)
{
}

Base64Converter::~Base64Converter(void)
{
}

QString Base64Converter::title()
{
	return QObject::tr("Base64 Converter");
}

QString Base64Converter::fromTextTip()
{
	return QObject::tr("String:");
}

QString Base64Converter::toTextTip()
{
	return QObject::tr("Base64:");
}

QString Base64Converter::convert(const QString& text)
{
	QByteArray	byte_array = text.toLocal8Bit();
	const unsigned char* from_str = (const unsigned char*)byte_array.constData();
	int to_str_len = (byte_array.size() + 2) / 3 * 4;
	unsigned char* to_str = new unsigned char[to_str_len + 1];
	to_str[to_str_len] = '\0';
	for(int i = 0; i<byte_array.size()/3; i++)
	{
		encodeblock( &from_str[i*3], &to_str[i*4], 3);
	}
	if (byte_array.size()%3 != 0)
	{
		encodeblock( &from_str[byte_array.size()/3*3], &to_str[byte_array.size()/3*4], byte_array.size()%3);
	}
	
	QString result = QString::fromLocal8Bit((char*)to_str);
	delete[] to_str;
	return result;
}

//If the source data contains '\ 0', the result will be truncated
QString Base64Converter::revert(const QString& text)
{
	QByteArray	byte_array = text.toLocal8Bit();
	if (byte_array.size()%4 != 0)
	{
		return QObject::tr("Invalid base64 string length");
	}
	const unsigned char* from_str = (const unsigned char*)byte_array.constData();
	int to_str_len = byte_array.size() / 4 * 3;
	unsigned char* to_str = new unsigned char[to_str_len + 1];
	to_str[to_str_len] = '\0';
	int totallen = 0;
	for(int i = 0; i<byte_array.size()/4; i++)
	{
		int len = decodeblock( &from_str[i*4], &to_str[i*3]);
		totallen += len;
		if (len == 0)
		{
			LOG_ERROR(QObject::tr("Invalid base64 code"));
			delete[] to_str;
			return "";
		}
	}

	QString result = QString::fromLocal8Bit((char*)to_str);
	delete[] to_str;
	return result;
}


void Base64Converter::encodeblock( const unsigned char in[3], unsigned char out[4], int len )
{
	out[0] = encode64[ in[0] >> 2 ];
	out[1] = encode64[ ((in[0] & 0x03) << 4) | (in[1] >> 4) ];
	out[2] = (unsigned char) (len > 1 ? encode64[ ((in[1] & 0x0f) << 2) | (in[2] >> 6) ] : '=');
	out[3] = (unsigned char) (len > 2 ? encode64[ in[2] & 0x3f ] : '=');
}


int Base64Converter::decodeblock( const unsigned char in[4], unsigned char out[3])
{
	unsigned char indata[4];
	int bit_len = 0;
	int char_len = 3;
	for(int i = 0; i < 4; i++)
	{
		if (in[i] < '+' ||  in[i] > 'z') //Unrecognized char
		{
			return 0;
		}
		indata[i] = decode64[in[i] - '+'];
		if (indata[i] == 126)//equal '='
		{
			indata[i] = 0;
			char_len = bit_len/8;
			break;
		}
		else if (indata[i] > 63 )//Unrecognized char
		{
			return 0;
		}
		bit_len += 6;
	}

	
	out[0] = indata[0] <<2 | indata[1] >>4;
	out[1] = indata[1] <<4 | indata[2] >>2;
	out[2] = indata[2] <<6 | indata[3];

	return char_len;
}
