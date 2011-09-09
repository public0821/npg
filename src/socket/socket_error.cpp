/*
 * socket_error.cpp
 *
 *  Created on: 2011-8-23
 *      Author: wuyangchun
 */

#include "socket_error.h"

SocketError::SocketError()
{
	bzero(m_error, sizeof(m_error));
}

SocketError::~SocketError()
{
	// TODO Auto-generated destructor stub
}

