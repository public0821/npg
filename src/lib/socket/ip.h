/*
 * ip.h
 *
 *  Created on: 2011-9-7
 *      Author: Young <public0821@gmail.com>
 */

#ifndef IP_H_
#define IP_H_

#include "../types.h"
#include "ip_address.h"

class Ip
{
public:
	Ip(int protocol);
	~Ip(void);
public:
	bool sendto(const IpAddress& ip, const char* data, uint16_t len);
public:
	static uint16_t checksum(const char* data, uint16_t len);
private:
	int m_sockfd;
	int m_protocol;
};

#endif
