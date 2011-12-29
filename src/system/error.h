/*
 * socket_error.h
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#ifndef _ERROR_H_
#define _ERROR_H_

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "system/types.h"
#include "system/os.h"

const size_t K_ERROR_BUF_LEN = 512;

class Error
{
public:
	Error();
	~Error();
public:
	const char* errorStr() const
	{
		return m_error;
	}
	bool hasError() const
	{
		return m_has_error;
	}
protected:

#define SET_ERROR_STR(error_str) {snprintf(m_error, sizeof(m_error), "%s(%d):%s", \
		__FILE__, __LINE__,error_str);\
		 m_has_error = true;}

	#define SET_ERROR_NO(errorno) {char buf[K_SOCKET_ERROR_BUF_LEN]; npg_strerror(errorno, buf, sizeof(buf));\
		snprintf(m_error, sizeof(m_error), "%s(%d):%s", \
		__FILE__, __LINE__,buf);\
		 m_has_error = true;}


protected:
	char m_error[K_ERROR_BUF_LEN];
	bool m_has_error;
};

#endif /* _ERROR_H_ */
