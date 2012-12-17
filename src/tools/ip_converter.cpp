#include "ip_converter.h"
#include <QObject>
#include "lib/socket/socket.h"

IpConverter::IpConverter(void)
{
}

IpConverter::~IpConverter(void)
{
}

QString IpConverter::title()
{
	return QObject::tr("IP Converter");
}

QString IpConverter::fromTextTip()
{
	return QObject::tr("IP String:");
}

QString IpConverter::toTextTip()
{
	return QObject::tr("IP Number(Network byte order):");
}

QString IpConverter::convert(const QString& text)
{
	struct in_addr addr;
	addr.s_addr = inet_addr(text.toStdString().c_str());
	if (addr.s_addr == INADDR_NONE)
	{
		SET_QERROR_STR(QObject::tr("Invalid ip address"));
		return "";
	}

	return QString("%1").arg(addr.s_addr);
}

QString IpConverter::revert(const QString& text)
{
	struct in_addr addr;
	bool ok;
	addr.s_addr = text.toULong(&ok);
	if (!ok)
	{
		SET_QERROR_STR(QObject::tr("Invalid number"));
		return "";
	}

	char* ip = inet_ntoa(addr);
	if (ip == NULL)
	{
		SET_QERROR_STR(QObject::tr("Invalid ip number"));
		return "";
	}

	return ip;
}
