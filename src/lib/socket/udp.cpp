/*
 * Udp.cpp
 *
 *  Created on: 2011-8-11
 *      Author: Young <public0821@gmail.com>
 */

#include "udp.h"
#include "../../logger.h"
#include "socket.h"
#include <qobject.h>

Udp::Udp(const IpAddress& addr, uint16_t port) :
		m_sockfd(-1), m_addr(addr), m_port(port) {

}

Udp::Udp() :
		m_sockfd(-1) {
}

Udp::~Udp() {
	if (-1 != m_sockfd) {
		closesocket(m_sockfd);
	}

}

bool Udp::sendto(const IpAddress& ip, uint16_t port, const char* buffer, size_t buffer_len) {

	if (-1 == m_sockfd) {
		if (m_addr.isvalid() && ip.version() != m_addr.version()) {
			LOG_ERROR("incorrect bind ip version");
			return false;
		}
		if (!m_addr.isvalid()) {
			m_addr.set_version(ip.version());
		}
		m_sockfd = new_socket(m_addr, m_port, 0);
		if (-1 == m_sockfd) {
			return false;
		}
		int optval = 1;
		int ret = setsockopt(m_sockfd, SOL_SOCKET, SO_BROADCAST,
				(const char *) &optval, sizeof(optval));
		if (ret == -1) {
			LOG_ERROR(errno);
			return false;
		}
	}

	struct sockaddr_in sockaddr4;
	struct sockaddr_in6 sockaddr6;
	struct sockaddr *addr = NULL;
	socklen_t addr_len;
	if (ip.version() == IpAddress::IPV4) {
		bzero(&sockaddr4, sizeof(sockaddr4));
		sockaddr4.sin_family = AF_INET;
		sockaddr4.sin_port = htons(port);
		sockaddr4.sin_addr.s_addr = ip.ipv4();
		addr = (struct sockaddr *) &sockaddr4;
		addr_len = sizeof(sockaddr4);
	} else if (ip.version() == IpAddress::IPV6) {
		bzero(&sockaddr6, sizeof(sockaddr6));
		sockaddr6.sin6_family = AF_INET6;
		sockaddr6.sin6_port = htons(port);
		memcpy(&sockaddr6.sin6_addr, ip.ipv6(), sizeof(sockaddr6.sin6_addr));
		addr = (struct sockaddr *) &sockaddr6;
		addr_len = sizeof(sockaddr6);

	} else {
		LOG_ERROR(QObject::tr("unsupported ip version: %1").arg(ip.version()));
		return false;
	}

	int len = ::sendto(m_sockfd, buffer, buffer_len, 0, addr, addr_len);
	if (len == -1) {
		LOG_ERROR(errno);
		return false;
	}

	return true;
}

int Udp::new_socket(const IpAddress& ip, uint16_t port, bool nonblock) {
	int sockfd = socket(ip.version() == IpAddress::IPV4 ? AF_INET : AF_INET6, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		LOG_ERROR(errno);
		LOG_ERROR(QObject::tr("create udp socket failed"));
		return -1;
	}

	int optval = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &optval,
			sizeof(int)) < 0) {
		LOG_ERROR(errno);
		LOG_ERROR(QObject::tr("set REUSEADDR failed"));
		closesocket(sockfd);
		return -1;
	}

	struct sockaddr_in sockaddr4;
	struct sockaddr_in6 sockaddr6;
	struct sockaddr *addr;
	socklen_t len;

	if (ip.version() == IpAddress::IPV4) {
		bzero(&sockaddr4, sizeof(sockaddr4));
		sockaddr4.sin_family = AF_INET;
		sockaddr4.sin_port = htons(port);
		sockaddr4.sin_addr.s_addr = ip.ipv4();
		addr = (struct sockaddr *) &sockaddr4;
		len = sizeof(sockaddr4);
	} else if (ip.version() == IpAddress::IPV6) {
		bzero(&sockaddr6, sizeof(sockaddr6));
		sockaddr6.sin6_family = AF_INET6;
		sockaddr6.sin6_port = htons(port);
		memcpy(&sockaddr6.sin6_addr, ip.ipv6(), sizeof(sockaddr6.sin6_addr));
		addr = (struct sockaddr *) &sockaddr6;
		len = sizeof(sockaddr6);
	} else {
		LOG_ERROR(QObject::tr("unsupported ip version: %1").arg(ip.version()));
		closesocket(sockfd);
		return -1;
	}

	int ret = bind(sockfd, addr, len);
	if (ret == -1) {
		LOG_ERROR(errno);
		LOG_ERROR(QObject::tr("bind faild (%d):%s").arg(port));
		closesocket(sockfd);
		return -1;
	}

//	if (nonblock) {
//		if (!socket_set_blocking(sockfd, false)) {
//			close(sockfd);
//			return -1;
//		}
//	}

	return sockfd;
}
