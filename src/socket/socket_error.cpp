/*
 * socket_error.cpp
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#include "socket_error.h"
#include "system/os.h"

SocketError::SocketError()
{
	bzero(m_error, sizeof(m_error));
}

SocketError::~SocketError()
{
	// TODO Auto-generated destructor stub
}

