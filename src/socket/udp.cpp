/*
 * Udp.cpp
 *
 *  Created on: 2011-8-11
 *      Author: wuyangchun
 */

#include "udp.h"

Udp::Udp()
{
	m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (K_SOCKET_ERROR == m_sockfd)
	{
		setErrorStr();
	}
}

Udp::~Udp()
{
	if (K_SOCKET_ERROR != m_sockfd)
	{
		close(m_sockfd);
	}

}


bool Udp::send(const char* ip, int port, const char* buffer, int buffer_len)
{
	if (K_SOCKET_ERROR == m_sockfd)
	{
		return false;
	}

	struct in_addr addr;
	int ret = inet_pton(AF_INET, ip, &addr);
	if (ret == 0)
	{
		setErrorStr("Not in presentation format");
		return false;
	}
	else if (ret < 0)
	{
		setErrorStr();
		return false;
	}
	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = addr.s_addr;
	serv_addr.sin_port = htons(port);

	ssize_t len = sendto(m_sockfd, buffer, buffer_len, 0,
			(struct sockaddr*) &serv_addr, sizeof(serv_addr));
	if (len == K_SOCKET_ERROR)
	{
		setErrorStr();
		return false;
	}

	return true;
}
