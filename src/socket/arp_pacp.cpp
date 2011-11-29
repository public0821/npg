#ifdef _MSC_VER
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
#include "pcap.h"


Arp::Arp()
{

}

Arp::~Arp()
{

}

bool Arp::sendto(const ifi_info& dev, const char* eth_to_mac, const char* eth_from_mac, short op,
		const char* send_mac, const char* send_ip, const char* recv_mac,
		const char* recv_ip)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *adhandle = NULL;
	if ((adhandle = pcap_open_live(dev.ifi_name, 65536, 1, 1000, errbuf))
		== NULL)
	{
		SET_ERROR_STR(errbuf);
		return false;
	}
	/* check if the ethernet*/
	if (pcap_datalink(adhandle) != DLT_EN10MB)	
	{
		pcap_close(adhandle);
		SET_ERROR_STR("This program works only on Ethernet networks.");
		return false;
	}
	u_int32_t arp_size = sizeof(struct ethhdr) + sizeof(struct ether_arp);
	const u_char * arp_buffer = buildArp(eth_to_mac, eth_from_mac, op,
		send_mac, send_ip, recv_mac, recv_ip);
	if (arp_buffer == NULL)
	{
		pcap_close(adhandle);
		return false;
	}
	if (pcap_sendpacket(adhandle, arp_buffer, arp_size) != 0)
	{
		SET_ERROR_STR((sstring("Error sending the packet: ") + pcap_geterr(adhandle)).c_str());
		delete[] arp_buffer;
		return false;
	}

	delete[] arp_buffer;

	return true;
}


#endif