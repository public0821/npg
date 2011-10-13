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
		SET_ERROR_STR(strerror(errno));
	}
}

Arp::~Arp()
{
	if (K_SOCKET_ERROR != m_sockfd)
	{
		close(m_sockfd);
	}
}

bool Arp::sendto(int interface, const char* eth_to_mac, const char* eth_from_mac, short op,
		const char* send_mac, const char* send_ip, const char* recv_mac,
		const char* recv_ip)
{
	//	int sock = socket(AF_PACKET, SOCK_DGRAM/*SOCK_RAW*/, htons(ETH_P_ARP));
	if (K_SOCKET_ERROR == m_sockfd)
	{
		return false;
	}

	uint32_t arp_size = sizeof(struct ethhdr) + sizeof(struct ether_arp);
	char* arp_buffer = new char[arp_size];
	bzero(arp_buffer, arp_size);

	struct ethhdr *ethhdr = (struct ethhdr *) arp_buffer;
//	memset(ethhdr->h_dest, 0xFF, sizeof(ethhdr->h_dest));
	toMac(eth_to_mac, ethhdr->h_dest);
	toMac(eth_from_mac, ethhdr->h_source);
	ethhdr->h_proto = htons(ETH_P_ARP);

	struct ether_arp* arp = (struct ether_arp *) (arp_buffer
			+ sizeof(struct ethhdr));
	arp->arp_hrd = htons(ETH_P_802_3); //MAC
	arp->arp_pro = htons(ETH_P_IP);
	arp->arp_pln = 4;
	arp->arp_hln = ETH_ALEN;
	arp->arp_op = htons(op); //arp request,arp response, rarp request, rarp response

	if (send_mac != NULL)
	{
		toMac(send_mac, arp->arp_sha);
	}
	if (recv_mac != NULL)
	{
		toMac(recv_mac, arp->arp_tha);
	}
	if (send_ip != NULL)
	{
		struct in_addr saddr;
		inet_pton(AF_INET, send_ip, &saddr);
		memcpy(arp->arp_spa, (uint8_t*) &saddr.s_addr, 4); /* sender protocol address */
	}
	if (recv_ip != NULL)
	{
		struct in_addr daddr;
		inet_pton(AF_INET, recv_ip, &daddr);
		memcpy(arp->arp_tpa, (uint8_t*) &daddr.s_addr, 4); /* target protocol address */
	}

	struct sockaddr_ll remote;
	bzero(&remote, sizeof(remote));
	remote.sll_ifindex = interface;
	//发送的时候其他字段用不着
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
		SET_ERROR_STR(strerror(errno));
		delete[] arp_buffer;
		return false;
	}

	delete[] arp_buffer;

	return true;
}

void Arp::toMac(const char* mac_str, uint8_t* mac)
{
	uint32_t temp_mac[6];
	sscanf(mac_str, "%x:%x:%x:%x:%x:%x", &temp_mac[0], &temp_mac[1], &temp_mac[2],
			&temp_mac[3], &temp_mac[4], &temp_mac[5]);

	for (int i = 0; i < 6; i++)
	{
		mac[i] = temp_mac[i];
	}

}
