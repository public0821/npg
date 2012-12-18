/*
 *
 *  Created on: 2012-12-13
 *      Author: Young <public0821@gmail.com>
 */

#include "socket_address.h"
#include "socket.h"
#include <qobject.h>
#include "logger.h"

SocketAddress::SocketAddress(const IpAddress& ip, uint16_t port) {
	m_ip_version = ip.version();
	if (ip.version() == IpAddress::IPV4) {
		bzero(&m_sockaddr4, sizeof(m_sockaddr4));
		m_sockaddr4.sin_family = AF_INET;
		m_sockaddr4.sin_port = htons(port);
		m_sockaddr4.sin_addr.s_addr = ip.ipv4();
	} else if (ip.version() == IpAddress::IPV6) {
		bzero(&m_sockaddr6, sizeof(m_sockaddr6));
		m_sockaddr6.sin6_family = AF_INET6;
		m_sockaddr6.sin6_port = htons(port);
		memcpy(&m_sockaddr6.sin6_addr, ip.ipv6(), sizeof(m_sockaddr6.sin6_addr));

	} else {
		LOG_ERROR(QObject::tr("unsupported ip version: %1").arg(ip.version()));
	}
}
