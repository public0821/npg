/*
 * Udp.h
 *
 *  Created on: 2011-8-11
 *      Author: wuyangchun
 */

#ifndef UDP_H_
#define UDP_H_
#include "socket_public.h"
#include "socket_error.h"

class Udp:public SocketError
{
public:
	Udp();
	virtual ~Udp();
public:
	bool sendto(const char* ip, uint16_t port, const char* buffer, int buffer_len);
private:

private:
	int m_sockfd;
};

#endif /* UDP_H_ */
