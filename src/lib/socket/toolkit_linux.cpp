/*
 * socket_toolkit.cpp
 *
 *  Created on: 2011-9-20
 *      Author: Young <public0821@gmail.com>
 */

#ifdef __GNUC__
#include "toolkit.h"
#include "../../logger.h"
#include "socket.h"
#include <qobject.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <ifaddrs.h>

std::vector<ifi_info> SocketToolkit::ifiInfo(int family, int doaliases) {
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
	for (int lastlen = 0;;) {
		buf = new char[len];
		ifc.ifc_len = len;
		ifc.ifc_buf = buf;
		if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0) {
			if (npg_errno != EINVAL || lastlen != 0) {
				LOG_ERROR(npg_errno);
				goto END;
			}

		} else {
			if (ifc.ifc_len == lastlen) {
				break; /* success, len has not changed */
			}
			lastlen = ifc.ifc_len;
		}
		len += 10 * sizeof(struct ifreq); /* increment */
		delete[] buf;
	}

	for (char* ptr = buf; ptr < buf + ifc.ifc_len;) {
		struct ifi_info ifi_info;
		bzero(&ifi_info, sizeof(ifi_info));
		struct ifreq * ifr = (struct ifreq *) ptr;
        ptr += sizeof(struct ifreq); /* for next one in buffer */

//		if (ifr->ifr_addr.sa_family != family)
//			continue; /* ignore if not desired address family */
		char* cptr = strchr(ifr->ifr_name, ':');
		if (cptr != NULL) {
			*cptr = 0; /* replace colon with null */
		}

		memcpy(ifi_info.ifi_name, ifr->ifr_name, IF_NAMESIZE);
		ifi_info.ifi_name[IF_NAMESIZE - 1] = '\0';
		struct ifreq ifrcopy = *ifr;
		if (ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy) < 0) {
			LOG_ERROR(npg_errno);
			goto END;
		}
		if ((ifrcopy.ifr_flags & IFF_UP) == 0)
		continue; /* ignore if interface not up */

		ifi_info.ifi_flags = ifrcopy.ifr_flags; /* IFF_xxx values */

		struct sockaddr_in * sinptr = NULL;
		struct sockaddr_in6 * sin6ptr = NULL;
		switch (ifr->ifr_addr.sa_family) {
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

		if (ioctl(sockfd, SIOCGIFHWADDR, &ifrcopy) < 0) {
			LOG_ERROR(npg_errno);
			goto END;
		}

		memcpy(ifi_info.ifi_haddr, ifrcopy.ifr_hwaddr.sa_data, IFHWADDRLEN);

		ifiInfos.push_back(ifi_info);
	}
	END: if (buf != NULL) {
		delete[] buf;
	}
	return ifiInfos; /* pointer to first structure in linked list */
}

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

std::vector<IpAddress> SocketToolkit::ipAddressInfo()
{
	std::vector<IpAddress> ipaddrs;
	struct ifaddrs *all_addr;
	int ret = getifaddrs(&all_addr);
	if (ret == -1) {
		LOG_ERROR(npg_errno);
		return ipaddrs;
	}
	struct ifaddrs *cur;
	for (cur = all_addr; cur; cur = cur->ifa_next) {
		if (cur->ifa_addr == NULL) {
			continue;
		}
		if (cur->ifa_addr->sa_family != AF_INET
				&& cur->ifa_addr->sa_family != AF_INET6) {
			continue;
		}

		if (cur->ifa_addr->sa_family == AF_INET) { //ipv4 addr
			IpAddress addr;
			addr.set_version(IpAddress::IPV4);
			struct sockaddr_in *ipv4_addr = (struct sockaddr_in *)cur->ifa_addr;
			addr.set_ipv4(ipv4_addr->sin_addr.s_addr);
			ipaddrs.push_back(addr);
		} else { //ipv6 addr
			IpAddress addr;
			addr.set_version(IpAddress::IPV6);
			struct sockaddr_in6 *ipv6_addr = (struct sockaddr_in6 *)cur->ifa_addr;
			addr.set_ipv6((char*)&ipv6_addr->sin6_addr);
			ipaddrs.push_back(addr);
		}
	}/*end of for*/

	freeifaddrs(all_addr);

	return ipaddrs;
}

#endif
