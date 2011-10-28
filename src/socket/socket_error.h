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

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "system/types.h"

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

	#define SET_ERROR_NO(errorno) {char buf[K_SOCKET_ERROR_BUF_LEN]; npg_strerror(errorno, buf, sizeof(buf));\
		snprintf(m_error, sizeof(m_error), "%s(%d):%s", \
		__FILE__, __LINE__,buf);}


protected:
	char m_error[K_SOCKET_ERROR_BUF_LEN];
};

#endif /* SOCKET_ERROR_H_ */
