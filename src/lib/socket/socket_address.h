/*
 *
 *  Created on: 2012-12-13
 *      Author: Young <public0821@gmail.com>
 */

#ifndef SOCKET_ADDRESS_H_
#define SOCKET_ADDRESS_H_

#include "lib/types.h"
#include "socket.h"
#include "ip_address.h"

class SocketAddress {
public:
	SocketAddress(const IpAddress& ip, uint16_t port);

	const struct sockaddr * addr() const {
		if (m_ip_version == IpAddress::IPV4) {
			return (const struct sockaddr *)&m_sockaddr4;
		} else {
			return (const struct sockaddr *)&m_sockaddr6;
		}
	}

	socklen_t addrlen() const {
		if (m_ip_version == IpAddress::IPV4) {
			return sizeof(m_sockaddr4);
		} else {
			return sizeof(m_sockaddr6);
		}
	}

private:
	uint8_t m_ip_version;
	struct sockaddr_in m_sockaddr4;
	struct sockaddr_in6 m_sockaddr6;
};

#endif /* IPADDRESS_H_ */
