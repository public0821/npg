/*
 * icmp.cpp
 *
 *  Created on: 2011-9-7
 *      Author: Young <public0821@gmail.com>
 */

#include "icmp.h"
#include "socket_toolkit.h"
#include "socket_public.h"

Icmp::Icmp()
{
	m_sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (K_SOCKET_ERROR == m_sockfd)
	{
		SET_ERROR_STR(strerror(errno));
		return;
	}
	int optval = 1;
	int ret = setsockopt(m_sockfd, SOL_SOCKET, SO_BROADCAST, &optval,
			sizeof(optval));
	if (ret == K_SOCKET_ERROR)
	{
		SET_ERROR_STR(strerror(errno));
		return;
	}
//	m_pid = getpid();
//	setuid(getuid());
	m_seq = 0;
}

Icmp::~Icmp()
{
	if (K_SOCKET_ERROR != m_sockfd)
	{
		close(m_sockfd);
	}
}


bool Icmp::sendto(const char* ip, void* data, int len, bool need_calc_checknum)
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

	struct icmp* icmp = (struct icmp*) data;
//	icmp.icmp_type = ICMP_ECHO;
//	icmp.icmp_code = 0;
//	icmp.icmp_id = m_pid;
//	icmp.icmp_seq = m_seq++;
//	struct   timeval   start;
//	gettimeofday(&start, NULL);
//	icmp.icmp_otime = start.tv_sec;
//	icmp.icmp_rtime = start.tv_usec;
	if (need_calc_checknum)
	{
		icmp->icmp_cksum = 0;
		SocketToolkit toolkit;
		icmp->icmp_cksum = toolkit.inCheckSum((u_short *) icmp, len);
	}

	ret = ::sendto(m_sockfd, icmp, len, 0, (const sockaddr*) &serv_addr,
			sizeof(serv_addr));
	if (ret < 0)
	{
		SET_ERROR_STR(strerror(errno));
		return false;
	}

	return true;
}
