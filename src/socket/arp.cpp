#ifdef __GNUC__

/*
 * arp.cpp
 *
 *  Created on: 2011-9-14
 *      Author: Young <public0821@gmail.com>
 */

#include "arp.h"
#include "socket_public.h"

#include <string.h>
#include <stdio.h>


Arp::Arp()
{
	m_sockfd = socket(AF_PACKET, SOCK_RAW/*SOCK_RAW*/, htons(ETH_P_ALL));
	if (-1 == m_sockfd)
	{
		SET_ERROR_NO(npg_errno);
	}
}

Arp::~Arp()
{
	if (K_SOCKET_ERROR != m_sockfd)
	{
		closesocket(m_sockfd);
	}
}

bool Arp::sendto(const ifi_info& dev, const char* eth_to_mac, const char* eth_from_mac, short op,
		const char* send_mac, const char* send_ip, const char* recv_mac,
		const char* recv_ip)
{
	//	int sock = socket(AF_PACKET, SOCK_DGRAM/*SOCK_RAW*/, htons(ETH_P_ARP));
	if (K_SOCKET_ERROR == m_sockfd)
	{
		return false;
	}

	u_int32_t arp_size = sizeof(struct ethhdr) + sizeof(struct ether_arp);
	const u_char* arp_buffer = buildArp(eth_to_mac, eth_from_mac, op,
		send_mac, send_ip, recv_mac, recv_ip);
	if (arp_buffer == NULL)
	{
		return false;
	}
	

	struct sockaddr_ll remote;
	bzero(&remote, sizeof(remote));
	remote.sll_ifindex = dev.ifi_index;
	//other fields not used when send data
//	remote.sll_family = htons(AF_PACKET);
//	remote.sll_protocol = htons(ETH_P_ARP);
//	remote.sll_hatype = htons(ARPHRD_ETHER);
//	remote.sll_halen = ETH_ALEN;
//	remote.sll_pkttype = PACKET_OTHERHOST;
//	memcpy(remote.sll_addr, arp->arp_sha, ETH_ALEN);


	int ret = ::sendto(m_sockfd, arp_buffer, arp_size, 0, (struct sockaddr*) &remote,
			sizeof(remote));
	if (-1 == ret)
	{
		SET_ERROR_NO(npg_errno);
		delete[] arp_buffer;
		return false;
	}

	delete[] arp_buffer;

	return true;
}
#endif
