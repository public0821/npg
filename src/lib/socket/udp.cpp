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
#include "socket_address.h"

Udp::Udp(const IpAddress& addr, uint16_t port) :
		m_sockfd(-1), m_addr(addr), m_port(port) {

}

Udp::Udp() :
		m_sockfd(-1), m_port(0) {
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
		m_sockfd = new_socket(m_addr, m_port);
		if (-1 == m_sockfd) {
			return false;
		}
		int optval = 1;
		int ret = setsockopt(m_sockfd, SOL_SOCKET, SO_BROADCAST,
				(const char *) &optval, sizeof(optval));
		if (ret == -1) {
			LOG_ERROR(npg_errno);
			return false;
		}
	}

	SocketAddress sockaddr(ip, port);
	int len = ::sendto(m_sockfd, buffer, buffer_len, 0, sockaddr.addr(), sockaddr.addrlen());
	if (len == -1) {
		LOG_ERROR(npg_errno);
		return false;
	}

	return true;
}

int Udp::new_socket(const IpAddress& ip, uint16_t port) {
	int sockfd = socket(ip.version() == IpAddress::IPV4 ? AF_INET : AF_INET6, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		LOG_ERROR(npg_errno);
		LOG_ERROR(QObject::tr("create udp socket failed"));
		return -1;
	}

	int optval = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &optval,
			sizeof(int)) < 0) {
		LOG_ERROR(npg_errno);
		LOG_ERROR(QObject::tr("set REUSEADDR failed"));
		closesocket(sockfd);
		return -1;
	}

	SocketAddress sockaddr(ip, port);
	int ret = bind(sockfd, sockaddr.addr(), sockaddr.addrlen());
	if (ret == -1) {
		LOG_ERROR(npg_errno);
		LOG_ERROR(QObject::tr("bind faild (%1)").arg(port));
		closesocket(sockfd);
		return -1;
	}

	return sockfd;
}
