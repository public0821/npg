/*
 * socket_toolkit.cpp
 *
 *  Created on: 2011-9-20
 *      Author: Young <public0821@gmail.com>
 */

#include "socket_toolkit.h"
#include "socket.h"
#include "../logger.h"

SocketToolkit::SocketToolkit()
{

}

SocketToolkit::~SocketToolkit()
{
}

#ifdef __GNUC__
#include <net/if.h>
std::vector<ifi_info> SocketToolkit::ifiInfo(int family, int doaliases)
{
//	struct ifi_info *ifi, *ifihead, **ifipnext;
//	int sockfd, len, lastlen, flags, myflags, idx = 0, hlen = 0;
//	char *ptr, *buf, lastname[IFNAMSIZ], *cptr, *haddr, *sdlname;
//	struct ifconf ifc;
//	struct ifreq *ifr, ifrcopy;
//	struct sockaddr_in *sinptr;
//	struct sockaddr_in6 *sin6ptr;

	std::vector<ifi_info> ifiInfos;

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	int len = 100 * sizeof(struct ifreq); /* initial buffer size guess */
	struct ifconf ifc;
	char *buf = NULL;
	for (int lastlen = 0;;)
	{
		buf = new char[len];

		ifc.ifc_len = len;
		ifc.ifc_buf = buf;
		if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0)
		{
			if (errno != EINVAL || lastlen != 0)
			{
				LOG_ERROR(npg_strerror(errno));
				goto END;
			}

		}
		else
		{
			if (ifc.ifc_len == lastlen)
			{
				break; /* success, len has not changed */
			}
			lastlen = ifc.ifc_len;
		}
		len += 10 * sizeof(struct ifreq); /* increment */
		delete[] buf;
	}

	for (char* ptr = buf; ptr < buf + ifc.ifc_len;)
	{
		struct ifi_info ifi_info;
		bzero(&ifi_info, sizeof(ifi_info));
		struct ifreq * ifr = (struct ifreq *) ptr;
#ifdef   HAVE_SOCKADDR_SA_LEN
		len = max(sizeof(struct sockaddr), ifr->ifr_addr.sa_len);
#else
		switch (ifr->ifr_addr.sa_family)
		{
#ifdef   IPV6
			case AF_INET6:
			len = sizeof(struct sockaddr_in6);
			break;
#endif
			case AF_INET:
			default:
			len = sizeof(struct sockaddr);
			break;
		}
#endif   /* HAVE_SOCKADDR_SA_LEN */
		ptr += sizeof(ifr->ifr_name) + len; /* for next one in buffer */

//		if (ifr->ifr_addr.sa_family != family)
//			continue; /* ignore if not desired address family */
		char* cptr = strchr(ifr->ifr_name, ':');
		if (cptr != NULL)
		{
			*cptr = 0; /* replace colon with null */
		}

		memcpy(ifi_info.ifi_name, ifr->ifr_name, IF_NAMESIZE);
		ifi_info.ifi_name[IF_NAMESIZE - 1] = '\0';
		struct ifreq ifrcopy = *ifr;
		if (ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy) < 0)
		{
			LOG_ERROR(npg_strerror(errno));
			goto END;
		}
		if ((ifrcopy.ifr_flags & IFF_UP) == 0)
		continue; /* ignore if interface not up */

		ifi_info.ifi_flags = ifrcopy.ifr_flags; /* IFF_xxx values */

		struct sockaddr_in * sinptr = NULL;
		struct sockaddr_in6 * sin6ptr = NULL;
		switch (ifr->ifr_addr.sa_family)
		{
			case AF_INET:
			sinptr = (struct sockaddr_in *) &ifr->ifr_addr;
			memcpy(&ifi_info.ifi_addr, sinptr, sizeof(struct sockaddr_in));
			break;
			case AF_INET6:
			sin6ptr = (struct sockaddr_in6 *) &ifr->ifr_addr;
			memcpy(&ifi_info.ifi_addr, sin6ptr, sizeof(struct sockaddr_in6));
			break;
			default:
			break;
		}

		if (ioctl(sockfd, SIOCGIFHWADDR, &ifrcopy) < 0)
		{
			LOG_ERROR(npg_strerror(errno));
			goto END;
		}

		memcpy(ifi_info.ifi_haddr, ifrcopy.ifr_hwaddr.sa_data, IFHWADDRLEN);

		ifiInfos.push_back(ifi_info);
	}
	END: if (buf != NULL)
	{
		delete[] buf;
	}
	return ifiInfos; /* pointer to first structure in linked list */
}

#include <sys/ioctl.h>
int SocketToolkit::macAddress(const char* name, char* mac)
{
	int sock = socket (PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock == -1)
	{
		return -1;
	}

	struct ifreq ifr;
	strcpy (ifr.ifr_name , name);
	int status = ioctl (sock, SIOCGIFHWADDR, &ifr);
	if (status < 0)
	{
		closesocket (sock);
		return -2;
	}

	memcpy(mac, ifr.ifr_hwaddr.sa_data, 6);

	return 0;
}
#endif
#ifdef _MSC_VER
#include "pcap.h"
std::vector<ifi_info> SocketToolkit::ifiInfo(int family, int doaliases)
{
	std::vector<ifi_info> ifi_infos;

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *alldevs = NULL;

	/* get all device */
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		LOG_ERROR( "Error in pcap_findalldevs: %s", errbuf);
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

uint16_t SocketToolkit::inCheckSum(uint16_t * addr, size_t len)
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

bool SocketToolkit::toMac(const char* mac_str, uint8_t* mac)
		{
	uint32_t temp_mac[6];
	bzero(temp_mac, sizeof(temp_mac));
	int n = sscanf(mac_str, "%x:%x:%x:%x:%x:%x", &temp_mac[0], &temp_mac[1], &temp_mac[2],
			&temp_mac[3], &temp_mac[4], &temp_mac[5]);

	if (n != 6)
			{
		n = sscanf(mac_str, "%x-%x-%x-%x-%x-%x", &temp_mac[0], &temp_mac[1], &temp_mac[2],
				&temp_mac[3], &temp_mac[4], &temp_mac[5]);
	}

	if (n != 6)
			{
		return false;
	}

	for (int i = 0; i < 6; i++)
	{
		mac[i] = temp_mac[i];
	}

	return true;
}

void SocketToolkit::macToString(const uint8_t* mac, char* mac_str, size_t len)
		{
	bzero(mac_str, sizeof(len));
	snprintf(mac_str, len, "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x",
			(uint8_t) mac[0], (uint8_t) mac[1],
			(uint8_t) mac[2], (uint8_t) mac[3],
			(uint8_t) mac[4], (uint8_t) mac[5]);
}
