/*
 * socket_toolkit.cpp
 *
 *  Created on: 2011-9-20
 *      Author: Young <public0821@gmail.com>
 */
#ifdef _MSC_VER
#include "toolkit.h"
#include "../../logger.h"
#include "socket.h"
#include <qobject.h>
#include "pcap.h"

std::vector<ifi_info> SocketToolkit::ifiInfo(int family, int doaliases)
{
	std::vector<ifi_info> ifi_infos;

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *alldevs = NULL;

	/* get all device */
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		LOG_ERROR(QObject::tr( "Error in pcap_findalldevs: %s").arg( errbuf));
		return ifi_infos;
	}
	if (alldevs == NULL)
	{
		LOG_ERROR("No interfaces found! Make sure WinPcap is installed.");
		return ifi_infos;
	}

	pcap_if_t *device = NULL;
	for (device = alldevs; device; device = device->next)
	{
		struct ifi_info ifi;
		strncpy(ifi.ifi_name, device->name, sizeof(ifi.ifi_name));
		pcap_addr_t *local_address;
		//get ip address and netmask
		for (local_address = device->addresses; local_address != NULL; local_address = local_address->next)
		{
			if (local_address->addr->sa_family != AF_INET)
			{
				continue;
			}
			ifi.ifi_addr = *(local_address->addr);
			struct sockaddr_in * sin = (struct sockaddr_in *) &(ifi.ifi_addr);
			int ret = macAddress(inet_ntoa(sin->sin_addr), ifi.ifi_haddr);
			if(-1 != ret)
			{
				ifi_infos.push_back(ifi);
			}
			break;
		}
	}

	pcap_freealldevs(alldevs);

	return ifi_infos;
}

int SocketToolkit::macAddress(const char* ip, char* mac)
{
	IP_ADAPTER_INFO * info = NULL;
	IP_ADAPTER_INFO * pos = NULL;
	DWORD size = 0;

	GetAdaptersInfo(info, &size);

	info = (IP_ADAPTER_INFO *) malloc(size);

	GetAdaptersInfo(info, &size);

	for (pos = info; pos != NULL; pos = pos->Next)
	{
		IP_ADDR_STRING *ip_addr = &pos->IpAddressList;
		do
		{
			if (strcmp(ip, ip_addr->IpAddress.String) == 0)
			{
				memcpy(mac, pos->Address, 6);
				free(info);
				return 0;
			}
		}while (ip_addr->Next != NULL);
	}

	free(info);

	return -1;
}
#endif
