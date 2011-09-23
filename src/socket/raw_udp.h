/*
 * raw_udp.h
 *
 *  Created on: 2011-9-23
 *      Author: root
 */

#ifndef RAW_UDP_H_
#define RAW_UDP_H_

#include "ip_raw_socket.h"

class RawUdp: public SocketError
{
public:
	RawUdp();
	virtual ~RawUdp();
public:
	bool sendto(const char* srcip, const char* dstip, uint16_t srcport, uint16_t dstport, const char* data, int datalen);
private:
	IpRawSocket  m_ipRawSocket;
};

#endif /* RAW_UDP_H_ */
