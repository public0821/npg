/*
 * udp.h
 *
 *  Created on: 2011-8-11
 *      Author: Young <public0821@gmail.com>
 */

#ifndef UDP_H_
#define UDP_H_

#include "system/error.h"

class Udp: public Error
{
public:
//	Udp(const char* ip = NULL, uint16_t port = 0);
	Udp();
	~Udp();
	public:
	bool sendto(const char* ip, uint16_t port, const char* buffer, size_t buffer_len);
	private:

private:
	int m_sockfd;

};

#endif /* UDP_H_ */
