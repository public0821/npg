/*
 * ip_raw_socket.cpp
 *
 *  Created on: 2011-9-23
 *      Author: Young <public0821@gmail.com>
 */

#include "ip_raw_socket.h"
#include "socket_public.h"

#define TTL_OUT     64          /* outgoing TTL */

IpRawSocket::IpRawSocket()
{
	m_sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);//IPPROTO_IP);
	if (K_SOCKET_ERROR == m_sockfd)
	{
		SET_ERROR_NO(npg_errno);
		return;
	}
	int optval = 1;
	int ret = setsockopt(m_sockfd, IPPROTO_IP, IP_HDRINCL, (const char*)&optval,
			sizeof(optval));
	if (ret == K_SOCKET_ERROR)
	{
		SET_ERROR_NO(npg_errno);
		return;
	}
}

IpRawSocket::~IpRawSocket()
{
	if (K_SOCKET_ERROR != m_sockfd)
	{
		closesocket(m_sockfd);
	}
}

bool IpRawSocket::sendto(const char* srcip, const char* dstip, u_int8_t protocol_type,
		const char* data, u_int16_t datalen)
{
	if (K_SOCKET_ERROR == m_sockfd)
	{
		return false;
	}

	struct in_addr src_addr;
	src_addr.s_addr = inet_addr(srcip);
	if (src_addr.s_addr == INADDR_NONE)
	{
		SET_ERROR_STR(("Not in presentation format"));
		return false;
	}

	struct in_addr dst_addr;
	dst_addr.s_addr = inet_addr(dstip);
	if (dst_addr.s_addr == INADDR_NONE)
	{
		SET_ERROR_STR(("Not in presentation format"));
		return false;
	}

	char *buf = new char[sizeof(struct ip) + datalen];
	struct ip	*ip = (struct ip *) buf;
	bzero(ip, sizeof(*ip));
	memcpy(buf + sizeof(struct ip), data, datalen);

	ip->ip_v = IPVERSION;
	ip->ip_hl = sizeof(struct ip) >> 2;
	ip->ip_tos = 0;
	ip->ip_len = htons(sizeof(struct ip) + datalen); /* network byte order */
	ip->ip_id = 0; /* let IP set this */
	ip->ip_off = 0; /* frag offset, MF and DF flags */
	ip->ip_ttl = TTL_OUT;
	ip->ip_p = protocol_type;

	ip->ip_src.s_addr = src_addr.s_addr;
	ip->ip_dst.s_addr = dst_addr.s_addr;

	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = dst_addr.s_addr;

	int ret = ::sendto(m_sockfd, buf, sizeof(struct ip) + datalen, 0,
			(const sockaddr*) &serv_addr, sizeof(serv_addr));
	if (ret < 0)
	{
		SET_ERROR_NO(npg_errno);
		delete[] buf;
		return false;
	}

	delete[] buf;

	return true;
}
