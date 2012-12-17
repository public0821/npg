/*
 * qerror.cpp
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#include "qerror.h"
#include "lib/os.h"

QError::QError()
:m_has_error(false)
,m_error_no(0)
//,m_status(E_ERROR_STATUS_NONE)
{
}

QError::~QError()
{
}

