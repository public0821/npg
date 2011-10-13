/*
 * socket_error.h
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#ifndef SOCKET_ERROR_H_
#define SOCKET_ERROR_H_

const int K_SOCKET_ERROR = -1;
const int K_SOCKET_ERROR_BUF_LEN = 512;

#include "socket_public.h"
#include <errno.h>

class SocketError
{
public:
	SocketError();
	virtual ~SocketError();
public:
	const char* errorStr() const
	{
		return m_error;
	}
protected:

#define SET_ERROR_STR(error_str) {snprintf(m_error, sizeof(m_error), "%s(%d):%s", \
		__FILE__, __LINE__,error_str);}
//	void fillErrorStr(char* error_buffer, int buffer_len, const char* error_str)
//	{
//		snprintf(error_buffer, buffer_len, "%s(%d):%s", __FILE__, __LINE__,
//				error_str);
//	}
//	;
//	void SET_ERROR_STR(const char* error_str)
//	{
//		fillErrorStr(m_error, sizeof(m_error), error_str);
//	}
//	;
//	void setErrorStr()
//	{
//		fillErrorStr(m_error, sizeof(m_error), strerror(errno));
//	}
//	;
protected:
	char m_error[K_SOCKET_ERROR_BUF_LEN];
};

#endif /* SOCKET_ERROR_H_ */
