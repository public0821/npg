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
	Udp(const IpAddress& addr, uint16_t port);
	Udp();
	~Udp();

public:
	bool sendto(const IpAddress& ip, uint16_t port, const char* buffer, size_t buffer_len);
	int new_socket(const IpAddress& ip, uint16_t port, bool nonblock);
private:
	int m_sockfd;
	IpAddress m_addr;
	uint16_t m_port;

};

#endif /* UDP_H_ */
