/*
 * icmp.cpp
 *
 *  Created on: 2011-9-7
 *      Author: wuyangchun
 */

#include "icmp.h"
#include    <netinet/in_systm.h>
#include    <netinet/ip.h>
#include    <netinet/ip_icmp.h>
#include   <sys/time.h>

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
	m_pid = getpid();
	setuid(getuid());
	m_seq = 0;
}

Icmp::~Icmp()
{
	// TODO Auto-generated destructor stub
}

uint16_t Icmp::inCheckSum(uint16_t * addr, int len)
{
	int nleft = len;
	uint32_t sum = 0;
	uint16_t *w = addr;
	uint16_t answer = 0;

	/*
	 * Our algorithm is simple, using a 32 bit accumulator (sum), we add
	 * sequential 16 bit words to it, and at the end, fold back all the
	 * carry bits from the top 16 bits into the lower 16 bits.
	 */
	while (nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}
	/* mop up an odd byte, if necessary */
	if (nleft == 1)
	{
		*(unsigned char *) (&answer) = *(unsigned char *) w;
		sum += answer;
	}

	/* add back carry outs from top 16 bits to low 16 bits */
	sum = (sum >> 16) + (sum & 0xffff); /* add hi 16 to low 16 */
	sum += (sum >> 16); /* add carry */
	answer = ~sum; /* truncate to 16 bits */
	return (answer);
}

bool Icmp::sendto(const char* ip, void* data, int len, bool needCalcCheckNum)
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
	if (needCalcCheckNum)
	{
		icmp->icmp_cksum = 0;
		icmp->icmp_cksum = inCheckSum((u_short *) icmp, len);
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
