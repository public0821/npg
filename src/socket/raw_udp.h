/*
 * raw_udp.h
 *
 *  Created on: 2011-9-23
 *      Author: Young <public0821@gmail.com>
 */

#ifndef RAW_UDP_H_
#define RAW_UDP_H_

#include "ip_raw_socket.h"

class RawUdp: public Error
{
public:
	RawUdp();
	~RawUdp();
public:
	bool sendto(const char* srcip, const char* dstip, u_int16_t srcport, u_int16_t dstport, const char* data, u_int16_t datalen);
private:
	IpRawSocket  m_ipRawSocket;
};

#endif /* RAW_UDP_H_ */