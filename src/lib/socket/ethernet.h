/*
 * ethernet.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef ETHERNET_H_
#define ETHERNET_H_

#include "toolkit.h"

class Ethernet
{
public:
	Ethernet(void);
	~Ethernet(void);
public:
	bool sendto(const ifi_info& dev, const char* eth_to_mac, const char* eth_from_mac, uint16_t protocol, const char* data, size_t len);
private:
	int m_sockfd;
};

#endif
