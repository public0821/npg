/*
 * ip_raw_socket.h
 *
 *  Created on: 2011-9-23
 *      Author: Young <public0821@gmail.com>
 */

#ifndef IP_RAW_SOCKET_H_
#define IP_RAW_SOCKET_H_

#include "../types.h"

class IpRawSocket
{
public:
	IpRawSocket();
	~IpRawSocket();
public:
	bool sendto(const char* srcip, const char* dstip, uint8_t protocol_type, const char* data, uint16_t datalen);
protected:
	int m_sockfd;
};

#endif /* IP_RAW_SOCKET_H_ */
