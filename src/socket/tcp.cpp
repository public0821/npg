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

bool Tcp::send(const char* buffer, size_t buffer_len)
{
	if (K_SOCKET_ERROR == m_sockfd)
	{
		return false;
	}

	size_t len_remaining = buffer_len;
	while (len_remaining > 0)
	{
		int len = ::send(m_sockfd, buffer, len_remaining, 0);
		if (len == K_SOCKET_ERROR)
		{
			SET_ERROR_NO(npg_errno);
			return false;
		}
		len_remaining -= len;
	}
	return true;
}

size_t Tcp::recv(char* buffer, size_t buffer_len)
{
	if (K_SOCKET_ERROR == m_sockfd)
	{
		return false;
	}

	size_t len_remaining = buffer_len;
	while (len_remaining > 0)
	{
		int len = ::recv(m_sockfd, buffer, len_remaining, 0);
		if (len == K_SOCKET_ERROR)
		{
			SET_ERROR_NO(npg_errno);
			return buffer_len - len_remaining;
		}
		if (len == 0)//the peer has performed an orderly shutdown
		{
			return buffer_len - len_remaining;;
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
	int ret_ioctl = npg_ioctl(m_sockfd, FIONBIO, &ul, sizeof(ul)); //set Non-blocking
	if (ret_ioctl == K_SOCKET_ERROR)
	{
		SET_ERROR_NO(npg_errno);
		return false;
	}
	
	/*
	windows
	#define WSABASEERR              10000
	#define WSAEWOULDBLOCK          (WSABASEERR+35)
	#define EWOULDBLOCK             WSAEWOULDBLOCK
	Resource temporarily unavailable.
	This error is returned from operations on nonblocking sockets that cannot be completed immediately, for example recv when no data is queued to be read from the socket. It is a nonfatal error, and the operation should be retried later. It is normal for WSAEWOULDBLOCK to be reported as the result from calling connect on a nonblocking SOCK_STREAM socket, since some time must elapse for the connection to be established.
	
	linux
	#define    EINPROGRESS    115 
	The socket is marked as nonblocking. The connection cannot be immediately completed. The application program can
	select the socket for writing during the connection process.
	*/
	bool ret_value = false;
	int ret_conn = ::connect(m_sockfd, (struct sockaddr*) &serv_addr,
			sizeof(serv_addr));
	if (ret_conn == K_SOCKET_ERROR && (npg_errno == EINPROGRESS || npg_errno == EWOULDBLOCK))
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
			if (npg_errno == EINPROGRESS || npg_errno == EWOULDBLOCK)
			{
				SET_ERROR_STR("timeout");
			}
			else
			{
				SET_ERROR_NO(npg_errno);
			}
		}
	}
	else if (ret_conn == K_SOCKET_ERROR)
	{
		SET_ERROR_NO(npg_errno);
	}

	ul = 0;
	ret_ioctl = npg_ioctl(m_sockfd, FIONBIO, &ul, sizeof(ul)); //set blocking
	if (ret_ioctl == K_SOCKET_ERROR)
	{
		SET_ERROR_NO(npg_errno);
		return false;
	}

	return ret_value;
}
