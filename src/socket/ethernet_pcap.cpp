#ifdef _MSC_VER
/*
 * arp.cpp
 *
 *  Created on: 2011-9-14
 *      Author: Young <public0821@gmail.com>
 */

#include "ethernet.h"
#include "socket.h"

#include <string.h>
#include <stdio.h>
#include "pcap.h"


Ethernet::Ethernet()
{

}

Ethernet::~Ethernet()
{

}

bool Ethernet::sendto(const ifi_info& dev, const char* eth_to_mac, const char* eth_from_mac, uint16_t protocol, const char* data, size_t len)
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


	uint32_t ethernet_size = sizeof(struct ethhdr) + sizeof(struct ether_arp);
	char* buffer = new char[ethernet_size];
	bzero(buffer, ethernet_size);
	memcpy(buffer+sizeof(struct ethhdr), data, len);

	SocketToolkit toolkit;
	struct ethhdr *ethhdr = (struct ethhdr *) buffer;
	//	memset(ethhdr->h_dest, 0xFF, sizeof(ethhdr->h_dest));
	if(!toolkit.toMac(eth_to_mac, ethhdr->h_dest))
	{
		SET_ERROR_STR((std::string("The format is not supported: ") +eth_to_mac).c_str());
		pcap_close(adhandle);
		return false;
	}
	if(!toolkit.toMac(eth_from_mac, ethhdr->h_source))
	{
		SET_ERROR_STR((std::string("The format is not supported: ") +eth_from_mac).c_str());
		pcap_close(adhandle);
		return false;
	}
	ethhdr->h_proto = htons(protocol);

	//char buffer1[128];
	//memcpy(buffer1,buffer,  ethernet_size);
	if (pcap_sendpacket(adhandle, (u_char*)buffer, ethernet_size) != 0)
	{
		SET_ERROR_STR((std::string("Error sending the packet: ") + pcap_geterr(adhandle)).c_str());
		pcap_close(adhandle);
		delete[] buffer;
		return false;
	}

	delete[] buffer;

	pcap_close(adhandle);

	return true;
}


#endif