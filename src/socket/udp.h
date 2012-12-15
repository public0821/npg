/*
 * udp.h
 *
 *  Created on: 2011-8-11
 *      Author: Young <public0821@gmail.com>
 */

#ifndef UDP_H_
#define UDP_H_

#include "ip_address.h"

class Udp {
public:
//	Udp(const char* ip = NULL, uint16_t port = 0);
	Udp();
	~Udp();

public:
	bool sendto(const IpAddress& addr, uint16_t port, const char* buffer, size_t buffer_len);

private:
	int m_sockfd;

};

#endif /* UDP_H_ */
