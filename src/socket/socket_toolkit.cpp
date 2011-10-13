/*
 * socket_toolkit.cpp
 *
 *  Created on: 2011-9-20
 *      Author: Young <public0821@gmail.com>
 */

#include "socket_toolkit.h"
#include "socket_public.h"


SocketToolkit::SocketToolkit()
{
	// TODO Auto-generated constructor stub

}

SocketToolkit::~SocketToolkit()
{
	// TODO Auto-generated destructor stub
}

std::vector<ifi_info> SocketToolkit::getIfiInfo(int family, int doaliases)
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
				SET_ERROR_STR(strerror(errno));
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
			SET_ERROR_STR(strerror(errno));
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
			SET_ERROR_STR(strerror(errno));
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

uint16_t SocketToolkit::inCheckSum(uint16_t * addr, int len)
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
