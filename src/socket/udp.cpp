/*
 * Udp.cpp
 *
 *  Created on: 2011-8-11
 *      Author: Young <public0821@gmail.com>
 */

#include "udp.h"
#include "socket.h"

Udp::Udp() {
}

Udp::~Udp() {
	if (-1 != m_sockfd) {
		closesocket(m_sockfd);
	}

}

bool Udp::sendto(const IpAddress& addr, uint16_t port, const char* buffer, size_t buffer_len) {

	if (-1 == m_sockfd) {
		m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		if (-1 == m_sockfd) {
			SET_ERROR_NO(npg_errno);
			return false;
		}
		int optval = 1;
		int ret = setsockopt(m_sockfd, SOL_SOCKET, SO_BROADCAST,
				(const char *) &optval, sizeof(optval));
		if (ret == -1) {
			SET_ERROR_NO(npg_errno);
			return false;
		}
	}

	struct in_addr addr;
	addr.s_addr = inet_addr(ip);
	if (addr.s_addr == INADDR_NONE) {
		SET_ERROR_STR("Not in presentation format");
		return false;
	}

	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = addr.s_addr;
	serv_addr.sin_port = htons(port);

	int len = ::sendto(m_sockfd, buffer, buffer_len, 0,
			(struct sockaddr*) &serv_addr, sizeof(serv_addr));
	if (len == -1) {
		SET_ERROR_NO(npg_errno);
		return false;
	}

	return true;
}
