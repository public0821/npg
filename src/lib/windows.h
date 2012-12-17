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

#define errno   WSAGetLastError()

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


inline std::string npg_strerror(int errorno)
{
	char buf[2048];
	int buflen = sizeof(buf);
	bzero(buf, buflen);
#define TEMP_BUF_SIZE 512
	WCHAR tempBuf[TEMP_BUF_SIZE];
	DWORD ret = FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			errorno,
			MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), // Default language
			//MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			tempBuf,
			TEMP_BUF_SIZE,
			NULL
	);

	if (ret == 0)
	{
		return buf;
	}

	WideCharToMultiByte( CP_ACP,
			0,
			tempBuf,
			-1,
			buf,
			buflen, //
			NULL,
			NULL );

	return buf;
}

#endif
