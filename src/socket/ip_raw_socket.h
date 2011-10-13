/*
 * ip_raw_socket.h
 *
 *  Created on: 2011-9-23
 *      Author: Young <public0821@gmail.com>
 */

#ifndef IP_RAW_SOCKET_H_
#define IP_RAW_SOCKET_H_

#include "socket_error.h"

class IpRawSocket: public SocketError
{
public:
	IpRawSocket();
	virtual ~IpRawSocket();
public:
	virtual bool sendto(const char* srcip, const char* dstip, int protocol_type, const char* data, int datalen);
protected:
	int m_sockfd;
};

#endif /* IP_RAW_SOCKET_H_ */
