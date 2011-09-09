/*
 * tcp.cpp
 *
 *  Created on: 2011-8-23
 *      Author: wuyangchun
 */

#include "tcp.h"

Tcp::Tcp()
{
	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (K_SOCKET_ERROR == m_sockfd)
	{
		SET_ERROR_STR(strerror(errno));
	}
}

Tcp::~Tcp()
{
	if (K_SOCKET_ERROR != m_sockfd)
	{
		close(m_sockfd);
	}
}

int Tcp::send(const char* buffer, int buffer_len)
{
	if (K_SOCKET_ERROR == m_sockfd)
	{
		return false;
	}

	int lenRemaining = buffer_len;
	while (lenRemaining > 0)
	{
		ssize_t len = ::send(m_sockfd, buffer, lenRemaining, 0);
		if (len == -1)
		{
			SET_ERROR_STR(strerror(errno));
			return K_SOCKET_ERROR;
		}
		lenRemaining -= len;
	}
	return buffer_len;
}

//#include <iostream>
bool Tcp::connect(const char* ip, uint16_t port, time_t timeout)
{
	if (K_SOCKET_ERROR == m_sockfd)
	{
		return false;
	}

	struct in_addr addr;
	int ret = inet_pton(AF_INET, ip, &addr);
	if (ret == 0)
	{
		SET_ERROR_STR(("Not in presentation format"));
		return false;
	}
	else if (ret < 0)
	{
		SET_ERROR_STR(strerror(errno));
		return false;
	}

	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = addr.s_addr;
	serv_addr.sin_port = htons(port);

	unsigned long ul = 1;
	ioctl(m_sockfd, FIONBIO, &ul); //set Non-blocking

	bool retValue = false;
	int retConn = ::connect(m_sockfd, (struct sockaddr*) &serv_addr,
			sizeof(serv_addr));
	if (retConn == K_SOCKET_ERROR && errno == EINPROGRESS)
	{
		timeval tm;
		fd_set set;
		tm.tv_sec = timeout;
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(m_sockfd, &set);
		int retSelect = select(m_sockfd + 1, NULL, &set, NULL, &tm);
		if (retSelect > 0)
		{
			int error_no = -1;
			int len = sizeof(error_no);
			ret = getsockopt(m_sockfd, SOL_SOCKET, SO_ERROR, &error_no,
					(socklen_t *) &len);
			if (ret == K_SOCKET_ERROR)
			{
				SET_ERROR_STR(strerror(errno));
			}
			else
			{
				if (error_no == 0)
				{
					retValue = true;
				}
				else
				{
					SET_ERROR_STR(strerror(error_no));
				}
			}
		}
		else if (retSelect == 0) //timeout
		{
			SET_ERROR_STR("timeout");
		}
		else //error
		{
			if (errno == EINPROGRESS)
			{
				SET_ERROR_STR("timeout");
			}
			else
			{
				SET_ERROR_STR(strerror(errno));
			}
		}
	}
	else if (retConn == K_SOCKET_ERROR)
	{
		SET_ERROR_STR(strerror(errno));
	}

	ul = 0;
	ioctl(m_sockfd, FIONBIO, &ul); //设置为阻塞模式

	return retValue;
}
