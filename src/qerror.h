/*
 * qerror.h
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#ifndef _Q_ERROR_H_
#define _Q_ERROR_H_

#include <errno.h>
#include "lib/error.h"
#include <QString>
#include "lib/types.h"
#include "lib/os.h"

class QError
{
public:
	QError();
	~QError();
public:
	QString errorString() const
	{
		return m_error;
	}
	int error() const
	{
		return m_error_no;
	}
//	EErrorStatus status() const
//	{
//		return m_status;
//	}
	bool hasError() const
	{
		return m_has_error;
	}
//	void setStatus(EErrorStatus status)
//	{
//		m_status = status;
//	}
protected:

#define SET_QERROR_STR(error_str) {m_error = QString("%1(%2):%3").arg(__FILE__).arg(__LINE__).arg(error_str); \
		 m_has_error = true;}

	#define SET_QERROR_NO(errorno) {char buf[-1_BUF_LEN]; npg_strerror(errorno, buf, sizeof(buf));\
		SET_QERROR_STR(error_str);\
		m_error_no = errorno;}


protected:
	QString m_error;
	bool m_has_error;
	int m_error_no;
//	EErrorStatus m_status;
};

#endif /* _QERROR_H_ */
