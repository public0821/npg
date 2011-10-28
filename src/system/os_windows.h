/*
 * os_windows.h
 *
 *  Created on: 2011-10-25
 *      Author: Young <public0821@gmail.com>
 */

#ifndef	__OS_WINDOWS_H__
#define __OS_WINDOWS_H__

#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <time.h>

#define bzero(buf, size)  ZeroMemory(buf,size)
#define snprintf _snprintf

inline int gettimeofday(struct timeval *tp, void *tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year     = wtm.wYear - 1900;
	tm.tm_mon     = wtm.wMonth - 1;
	tm.tm_mday     = wtm.wDay;
	tm.tm_hour     = wtm.wHour;
	tm.tm_min     = wtm.wMinute;
	tm.tm_sec     = wtm.wSecond;
	tm. tm_isdst    = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}

#endif
