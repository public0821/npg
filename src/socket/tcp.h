/*
 * tcp.h
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#ifndef TCP_H_
#define TCP_H_

#include "socket_error.h"

class Tcp: public SocketError
{
public:
	Tcp();
	virtual ~Tcp();
public:
	bool connect(const char* ip, u_int16_t port, time_t timeout);
	bool send(const char* buffer, size_t buffer_len);
private:
	int m_sockfd;
};

#endif /* TCP_H_ */
