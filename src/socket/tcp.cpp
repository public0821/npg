/*
 * tcp.cpp
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#include "tcp.h"
#include "socket_public.h"

Tcp::Tcp()
{
	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (K_SOCKET_ERROR == m_sockfd)
	{
		SET_ERROR_NO(npg_errno);
	}
}

Tcp::~Tcp()
{
	if (K_SOCKET_ERROR != m_sockfd)
	{
		closesocket(m_sockfd);
	}
}

int Tcp::send(const char* buffer, int buffer_len)
{
	if (K_SOCKET_ERROR == m_sockfd)
	{
		return false;
	}

	int len_remaining = buffer_len;
	while (len_remaining > 0)
	{
		int len = ::send(m_sockfd, buffer, len_remaining, 0);
		if (len == -1)
		{
			SET_ERROR_NO(npg_errno);
			return K_SOCKET_ERROR;
		}
		len_remaining -= len;
	}
	return buffer_len;
}

//#include <iostream>
bool Tcp::connect(const char* ip, u_int16_t port, time_t timeout)
{
	if (K_SOCKET_ERROR == m_sockfd)
	{
		return false;
	}

	struct in_addr addr;
	addr.s_addr = inet_addr(ip);
	if (addr.s_addr == INADDR_NONE)
	{
		SET_ERROR_STR(("Not in presentation format"));
		return false;
	}

	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = addr.s_addr;
	serv_addr.sin_port = htons(port);

	unsigned long ul = 1;
	npg_ioctl(m_sockfd, FIONBIO, &ul, sizeof(ul)); //set Non-blocking

	bool ret_value = false;
	int retConn = ::connect(m_sockfd, (struct sockaddr*) &serv_addr,
			sizeof(serv_addr));
	if (retConn == K_SOCKET_ERROR && npg_errno == EINPROGRESS)
	{
		timeval tm;
		fd_set set;
		tm.tv_sec = timeout;
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(m_sockfd, &set);
		int ret_select = select(m_sockfd + 1, NULL, &set, NULL, &tm);
		if (ret_select > 0)
		{
			int error_no = -1;
			int len = sizeof(error_no);
			int ret = getsockopt(m_sockfd, SOL_SOCKET, SO_ERROR, (char*)&error_no,
					(socklen_t *) &len);
			if (ret == K_SOCKET_ERROR)
			{
				SET_ERROR_NO(npg_errno);
			}
			else
			{
				if (error_no == 0)
				{
					ret_value = true;
				}
				else
				{
					SET_ERROR_STR(strerror(error_no));
				}
			}
		}
		else if (ret_select == 0) //timeout
		{
			SET_ERROR_STR("timeout");
		}
		else //error
		{
			if (npg_errno == EINPROGRESS)
			{
				SET_ERROR_STR("timeout");
			}
			else
			{
				SET_ERROR_NO(npg_errno);
			}
		}
	}
	else if (retConn == K_SOCKET_ERROR)
	{
		SET_ERROR_NO(npg_errno);
	}

	ul = 0;
	npg_ioctl(m_sockfd, FIONBIO, &ul, sizeof(ul)); //set blocking

	return ret_value;
}
