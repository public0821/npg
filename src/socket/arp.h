/*
 * arp.h
 *
 *  Created on: 2011-9-14
 *      Author: Young <public0821@gmail.com>
 */

#ifndef ARP_H_
#define ARP_H_

#include "socket_error.h"
#include "socket_toolkit.h"

class Arp: public SocketError
{
public:
	Arp();
	virtual ~Arp();
public:
	bool sendto(const ifi_info& dev, const char* eth_to_mac, const char* eth_from_mac, short op, const char* send_mac, const char* send_ip,
			const char* recv_mac, const char* recv_ip);
private:
	const u_char* buildArp(const char* eth_to_mac, const char* eth_from_mac, short op, const char* send_mac, const char* send_ip,
		const char* recv_mac, const char* recv_ip)
	{
		u_int32_t arp_size = sizeof(struct ethhdr) + sizeof(struct ether_arp);
		char* arp_buffer = new char[arp_size];
		bzero(arp_buffer, arp_size);

		SocketToolkit toolkit;

		struct ethhdr *ethhdr = (struct ethhdr *) arp_buffer;
		//	memset(ethhdr->h_dest, 0xFF, sizeof(ethhdr->h_dest));
		if(!toolkit.toMac(eth_to_mac, ethhdr->h_dest))
		{
			SET_ERROR_STR((sstring("The format is not supported: ") +eth_to_mac).c_str());
			return NULL;
		}
		if(!toolkit.toMac(eth_from_mac, ethhdr->h_source))
		{
			SET_ERROR_STR((sstring("The format is not supported: ") +eth_from_mac).c_str());
			return NULL;
		}
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
			if(!toolkit.toMac(send_mac, arp->arp_sha))
			{
				SET_ERROR_STR((sstring("The format is not supported: ") +send_mac).c_str());
				return NULL;
			}
		}
		if (recv_mac != NULL)
		{
			if(!toolkit.toMac(recv_mac, arp->arp_tha))
			{
				SET_ERROR_STR((sstring("The format is not supported: ") +recv_mac).c_str());
				return NULL;
			}
		}
		if (send_ip != NULL)
		{
			struct in_addr saddr;
			saddr.s_addr = inet_addr(send_ip);
			memcpy(arp->arp_spa, (u_int8_t*) &saddr.s_addr, 4); /* sender protocol address */
		}
		if (recv_ip != NULL)
		{
			struct in_addr daddr;
			daddr.s_addr = inet_addr(recv_ip);
			memcpy(arp->arp_tpa, (u_int8_t*) &daddr.s_addr, 4); /* target protocol address */
		}

		return (const u_char*)arp_buffer;
	}
private:
	int m_sockfd;
};

#endif /* ARP_H_ */
