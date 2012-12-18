/*
 * tcp.cpp
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#include "tcp.h"
#include "../../logger.h"
#include "socket.h"
#include <qobject.h>
#include "socket_address.h"

Tcp::Tcp(const IpAddress& addr, uint16_t port) :
		m_sockfd(-1), m_blocking(true), m_addr(addr), m_port(port) {

}

Tcp::Tcp() :
		m_sockfd(-1), m_blocking(true), m_port(0) {
}

Tcp::~Tcp() {
	if (-1 != m_sockfd) {
		closesocket(m_sockfd);
	}
}

bool Tcp::send(const char* buffer, size_t buffer_len) {
	if (-1 == m_sockfd) {
		return false;
	}

	size_t len_remaining = buffer_len;
	while (len_remaining > 0) {
		int len = ::send(m_sockfd, buffer, len_remaining, 0);
		if (len == -1) {
			LOG_ERROR(npg_errno);
			return false;
		}
		if (!m_blocking) {
			break;
		}
		len_remaining -= len;
	}
	return true;
}

int Tcp::recv(char* buffer, size_t buffer_len) {
	if (-1 == m_sockfd) {
		return -1;
	}

	size_t len_remaining = buffer_len;
	while (len_remaining > 0) {
		int len = ::recv(m_sockfd, buffer, len_remaining, 0);
		m_errno = npg_errno;
		if (len == -1 && (m_errno == EWOULDBLOCK || m_errno == EAGAIN)) {
			LOG_ERROR(npg_errno);
			return buffer_len - len_remaining;
		} else if (len == -1) {
			LOG_ERROR(npg_errno);
			return -1;
		}
		else if (len == 0) { //the peer has performed an orderly shutdown
			return buffer_len - len_remaining;
		}
		len_remaining -= len;
	}

	return buffer_len;
}

//#include <iostream>
bool Tcp::connect(const IpAddress& ip, uint16_t port, time_t timeout) {
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
	}

	SocketAddress sockaddr(ip, port);
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
	if (timeout > 0) {
		bool ret = setBlocking(false);
		if (!ret) {
			return false;
		}
	}

	bool ret_value = false;
	int ret_conn = ::connect(m_sockfd, sockaddr.addr(), sockaddr.addrlen());
	if (ret_conn == -1 && (npg_errno == EINPROGRESS || npg_errno == EWOULDBLOCK)) {
		timeval tm;
		fd_set set;
		tm.tv_sec = timeout;
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(m_sockfd, &set);
		int ret_select = select(m_sockfd + 1, NULL, &set, NULL, &tm);
		if (ret_select > 0) {
			int temp_error_no = -1;
			int len = sizeof(temp_error_no);
			int ret = getsockopt(m_sockfd, SOL_SOCKET, SO_ERROR,
					(char*) &temp_error_no, (socklen_t *) &len);
			if (ret == -1) {
				LOG_ERROR(npg_errno);
			} else {
				if (temp_error_no == 0) {
					ret_value = true;
				} else {
					LOG_ERROR(temp_error_no);
				}
			}
		} else if (ret_select == 0) { //timeout
			LOG_ERROR("timeout");
		} else { //error
			if (npg_errno == EINPROGRESS || npg_errno == EWOULDBLOCK) {
				LOG_ERROR("timeout");
			} else {
				LOG_ERROR(npg_errno);
			}
		}
	}
	else if (ret_conn == -1) {
		LOG_ERROR(npg_errno);
	}

	if (timeout > 0) {
		bool ret = setBlocking(true);
		if (!ret) {
			return false;
		}
	}

	return ret_value;
}

bool Tcp::setBlocking(bool blocking) {
	unsigned long ul = blocking ? 0 : 1;
	int ret_ioctl = npg_ioctl(m_sockfd, FIONBIO, &ul, sizeof(ul)); //set Non-blocking
	if (ret_ioctl == -1) {
		LOG_ERROR(npg_errno);
		return false;
	};

	return true;
}

int Tcp::new_socket(const IpAddress& ip, uint16_t port) {
	int domain = ip.version() == IpAddress::IPV4 ? AF_INET : AF_INET6;
	int sockfd = socket(domain, SOCK_STREAM, 0);
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

