#include "ip.h"
#include "../../logger.h"
#include "socket.h"
#include <qobject.h>
#include "socket_address.h"
#include <qobject.h>

Ip::Ip(int protocol, const IpAddress& addr) :
		m_sockfd(-1), m_protocol(protocol), m_addr(addr) {

}
Ip::Ip(int protocol) :
		m_sockfd(-1), m_protocol(protocol) {
}

Ip::~Ip(void) {
	if (-1 != m_sockfd) {
		closesocket(m_sockfd);
	}
}

bool Ip::sendto(const IpAddress& ip, const char* data, uint16_t len) {
	if (-1 == m_sockfd) {
		int domain = ip.version() == IpAddress::IPV4 ? AF_INET : AF_INET6;
		m_sockfd = socket(domain, SOCK_RAW, m_protocol);
		if (-1 == m_sockfd) {
			LOG_ERROR(npg_errno);
			return false;
		}
		int optval = 1;
		int ret = setsockopt(m_sockfd, SOL_SOCKET, SO_BROADCAST, (const char*) &optval, sizeof(optval));
		if (ret == -1) {
			LOG_ERROR(npg_errno);
			return false;
		}

		if (m_addr.isvalid()) {
			SocketAddress sockaddr(m_addr, 0);
			ret = bind(m_sockfd, sockaddr.addr(), sockaddr.addrlen());
			if (ret == -1) {
				LOG_ERROR(npg_errno);
				LOG_ERROR(QObject::tr("bind faild "));
				return false;
			}
		}
	}

	if (ip.version() == IpAddress::IPV4) {
		addChecksum(m_protocol, data, len);
	}

	SocketAddress sockaddr(ip, 0);
	int ret = ::sendto(m_sockfd, (const char*) data, len, 0, sockaddr.addr(), sockaddr.addrlen());
	if (ret < 0) {
		LOG_ERROR(npg_errno);
		return false;
	}

	return true;
}

void Ip::addChecksum(int protocol, const char* data, uint16_t len) {
	switch (protocol) {
	case IPPROTO_IGMP:
		//TODO
		break;
	case IPPROTO_ICMP: {
		if (len < sizeof(struct icmphdr)) {
			return;
		}
		struct icmp *icmp = (struct icmp*) data;
		if (icmp->icmp_cksum == 0) {
			icmp->icmp_cksum = checksum(data, len);
		}
		break;
	}
	case IPPROTO_UDP: {
		//TODO pseudo-header
//		if (len < sizeof(struct udphdr)) {
//			return;
//		}
//		struct udphdr *udp = (struct udphdr*) data;
//		if (udp->check == 0) {
//			udp->check = checksum(data, len);
//		}
		break;
	}
	case IPPROTO_TCP:
		//TODO
		break;
	default:
		break;
	}

//	if(protocol == ip->ip_p){
//
//	}
//	const struct ip* ip = data;
}

uint16_t Ip::checksum(const char* data, uint16_t len) {
	/* Compute Internet Checksum for "count" bytes
	 * beginning at location "addr".
	 */
	const unsigned char * addr = (const unsigned char *) data;
	int count = len;
	uint32_t sum = 0;

	while (count > 1) {
		/* This is the inner loop */
		sum += *((unsigned short*) (addr));
		addr += 2;
		count -= 2;
	}

	/* Add left-over byte, if any */
	if (count > 0)
		sum += *addr;

	/* Fold 32-bit sum to 16 bits */
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	return ~sum;
}
