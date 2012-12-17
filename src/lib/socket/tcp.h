/*
 * tcp.h
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#ifndef TCP_H_
#define TCP_H_

#include "../types.h"
#include <time.h>

class Tcp
{
public:
	Tcp();
	~Tcp();
public:
	bool connect(const char* ip, uint16_t port, time_t timeout);
	bool send(const char* buffer, size_t buffer_len);
	int recv(char* buffer, size_t buffer_len);
	bool setBlocking(bool blocking);
	int error_no()const{
		return m_errno;
	}
private:
	int m_sockfd;
	bool m_blocking;
	int m_errno;
};

#endif /* TCP_H_ */
