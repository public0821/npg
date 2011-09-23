/*
 * arp.h
 *
 *  Created on: 2011-9-14
 *      Author: wuyangchun
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
	bool sendto(int interface, const char* ethToMac, const char* ethFromMac, short op, const char* sendMac, const char* sendIp,
			const char* recvMac, const char* recvIp);
private:
	void toMac(const char* macStr, uint8_t* mac);
};

#endif /* ARP_H_ */
