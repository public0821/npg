/*
 * socket_error.cpp
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#include "error.h"
#include "system/os.h"

Error::Error()
:m_has_error(false)
,m_error_no(0)
{
	bzero(m_error, sizeof(m_error));
}

Error::~Error()
{
	// TODO Auto-generated destructor stub
}

