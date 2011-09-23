/*
 * arp.cpp
 *
 *  Created on: 2011-9-14
 *      Author: wuyangchun
 */

#include "arp.h"
#include "socket_public.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h> /* the L2 protocols */
#include <netinet/if_ether.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <netpacket/packet.h>

Arp::Arp()
{
	// TODO Auto-generated constructor stub

}

Arp::~Arp()
{
	// TODO Auto-generated destructor stub
}

bool Arp::sendto(int interface, const char* ethToMac, const char* ethFromMac, short op,
		const char* sendMac, const char* sendIp, const char* recvMac,
		const char* recvIp)
{
	//	int sock = socket(AF_PACKET, SOCK_DGRAM/*SOCK_RAW*/, htons(ETH_P_ARP));
	int sock = socket(AF_PACKET, SOCK_RAW/*SOCK_RAW*/, htons(ETH_P_ALL));
	if (-1 == sock)
	{
		SET_ERROR_STR(strerror(errno));
		return false;
	}

	uint32_t size = sizeof(struct ethhdr) + sizeof(struct ether_arp);
	char* buffer = new char[size];
	bzero(buffer, size);

	struct ethhdr *ethhdr = (struct ethhdr *) buffer;
//	memset(ethhdr->h_dest, 0xFF, sizeof(ethhdr->h_dest));
	toMac(ethToMac, ethhdr->h_dest);
	toMac(ethFromMac, ethhdr->h_source);
	ethhdr->h_proto = htons(ETH_P_ARP);

	struct ether_arp* arp = (struct ether_arp *) (buffer
			+ sizeof(struct ethhdr));
	arp->arp_hrd = htons(ETH_P_802_3); //MAC
	arp->arp_pro = htons(ETH_P_IP);
	arp->arp_pln = 4;
	arp->arp_hln = ETH_ALEN;
	arp->arp_op = htons(op); //arp request,arp response, rarp request, rarp response

	if (sendMac != NULL)
	{
		toMac(sendMac, arp->arp_sha);
	}
	if (recvMac != NULL)
	{
		toMac(recvMac, arp->arp_tha);
	}
	if (sendIp != NULL)
	{
		struct in_addr saddr;
		inet_pton(AF_INET, sendIp, &saddr);
		memcpy(arp->arp_spa, (uint8_t*) &saddr.s_addr, 4); /* sender protocol address */
	}
	if (recvIp != NULL)
	{
		struct in_addr daddr;
		inet_pton(AF_INET, recvIp, &daddr);
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


	int ret = ::sendto(sock, buffer, size, 0, (struct sockaddr*) &remote,
			sizeof(remote));
	if (-1 == ret)
	{
		SET_ERROR_STR(strerror(errno));
		delete[] buffer;
		return false;
	}

	delete[] buffer;

	return true;
}

void Arp::toMac(const char* macStr, uint8_t* mac)
{
	uint32_t tempMac[6];
	sscanf(macStr, "%x:%x:%x:%x:%x:%x", &tempMac[0], &tempMac[1], &tempMac[2],
			&tempMac[3], &tempMac[4], &tempMac[5]);

	for (int i = 0; i < 6; i++)
	{
		mac[i] = tempMac[i];
	}

}
