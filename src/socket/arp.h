/*
 * arp.h
 *
 *  Created on: 2011-9-14
 *      Author: Young <public0821@gmail.com>
 */

#ifndef ARP_H_
#define ARP_H_

#include "socket_error.h"

class Arp: public SocketError
{
public:
	Arp();
	virtual ~Arp();
public:
	bool sendto(int interface, const char* eth_to_mac, const char* eth_from_mac, short op, const char* send_mac, const char* send_ip,
			const char* recv_mac, const char* recv_ip);
private:
	void toMac(const char* mac_str, uint8_t* mac);
private:
	int m_sockfd;
};

#endif /* ARP_H_ */
