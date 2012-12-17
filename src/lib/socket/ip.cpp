#include "ip.h"
#include "socket.h"
#include "../../logger.h"
#include <qobject.h>

Ip::Ip(int protocol)
{
	m_sockfd = socket(AF_INET, SOCK_RAW, protocol);
	if (-1 == m_sockfd)
	{
		LOG_ERROR(errno);
		return;
	}
	int optval = 1;
	int ret = setsockopt(m_sockfd, SOL_SOCKET, SO_BROADCAST, (const char*)&optval,
		sizeof(optval));
	if (ret == -1)
	{
		LOG_ERROR(errno);
		return;
	}
}

Ip::~Ip(void)
{
	if (-1 != m_sockfd)
	{
		closesocket(m_sockfd);
	}
}


bool Ip::sendto(const char* ip, const char* data, uint16_t len)
{
	if (-1 == m_sockfd)
	{
		return false;
	}

	struct in_addr addr;
	addr.s_addr = inet_addr(ip);
	if (addr.s_addr == INADDR_NONE)
	{
		LOG_ERROR(("Not in presentation format"));
		return false;
	}

	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = addr.s_addr;

	int ret = ::sendto(m_sockfd, (const char*)data, len, 0, (const sockaddr*) &serv_addr,
		sizeof(serv_addr));
	if (ret < 0)
	{
		LOG_ERROR(errno);
		return false;
	}

	return true;
}
