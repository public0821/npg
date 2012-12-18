#include "ip.h"
#include "../../logger.h"
#include "socket.h"
#include <qobject.h>
#include "socket_address.h"

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

		IpAddress addr;
		addr.from_string("10.0.2.15");
		SocketAddress sockaddr(addr, 0);
		ret = bind(m_sockfd, sockaddr.addr(), sockaddr.addrlen());
		if (ret == -1) {
			LOG_ERROR(npg_errno);
			LOG_ERROR(QObject::tr("bind faild "));
			return -1;
		}
	}

	SocketAddress sockaddr(ip, 0);
	int ret = ::sendto(m_sockfd, (const char*) data, len, 0, sockaddr.addr(), sockaddr.addrlen());
	if (ret < 0) {
		LOG_ERROR(npg_errno);
		return false;
	}

	return true;
}
