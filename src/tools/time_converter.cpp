#include "time_converter.h"
#include <QObject>

TimeConverter::TimeConverter(void)
{
}

TimeConverter::~TimeConverter(void)
{
}

QString TimeConverter::title()
{
	return QObject::tr("Time Converter");
}

QString TimeConverter::fromTextTip()
{
	return QObject::tr("TIME String(1998-02-21 12:21:00):");
}

QString TimeConverter::toTextTip()
{
	return QObject::tr("the time since the Epoch (00:00:00 UTC, January 1, 1970), measured in seconds:");
}

QString TimeConverter::convert(const QString& text)
{
	std::string temp_time_str = text.toStdString();
	const char* time_str = temp_time_str.c_str();
	struct tm tm1;
	::memset(&tm1, '\0', sizeof(tm1));
	int nRet = sscanf(time_str, "%4d-%2d-%2d %2d:%2d:%2d",     
		&tm1.tm_year, 
		&tm1.tm_mon, 
		&tm1.tm_mday,
		&tm1.tm_hour,
		&tm1.tm_min,
		&tm1.tm_sec
		);
	if (nRet != 6)
	{
		SET_QERROR_STR(QObject::tr("Invalid time format"));
		return "";
	}


	tm1.tm_year -= 1900;
	tm1.tm_mon --;
	tm1.tm_isdst=-1;

	time_t time = mktime(&tm1);

	return QString("%1").arg(time);
}

QString TimeConverter::revert(const QString& text)
{
	bool ok;
	time_t time_num = text.toULong(&ok);
	if (!ok)
	{
		SET_QERROR_STR(QObject::tr("Invalid number, maybe too long"));
		return "";
	}

	struct tm tm1 = *localtime(&time_num);

	return QString("%1-%2-%3 %4:%5:%6").arg(tm1.tm_year+1900).arg(tm1.tm_mon+1).arg(tm1.tm_mday)
		.arg(tm1.tm_hour).arg(tm1.tm_min).arg(tm1.tm_sec);
}