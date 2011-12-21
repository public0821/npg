#include "ip.h"
#include "socket_public.h"

Ip::Ip(int protocol)
{
	m_sockfd = socket(AF_INET, SOCK_RAW, protocol);
	if (K_SOCKET_ERROR == m_sockfd)
	{
		SET_ERROR_NO(npg_errno);
		return;
	}
	int optval = 1;
	int ret = setsockopt(m_sockfd, SOL_SOCKET, SO_BROADCAST, (const char*)&optval,
		sizeof(optval));
	if (ret == K_SOCKET_ERROR)
	{
		SET_ERROR_NO(npg_errno);
		return;
	}
}

Ip::~Ip(void)
{
	if (K_SOCKET_ERROR != m_sockfd)
	{
		closesocket(m_sockfd);
	}
}


bool Ip::sendto(const char* ip, const char* data, u_int16_t len)
{
	if (K_SOCKET_ERROR == m_sockfd)
	{
		return false;
	}

	struct in_addr addr;
	addr.s_addr = inet_addr(ip);
	if (addr.s_addr == INADDR_NONE)
	{
		SET_ERROR_STR(("Not in presentation format"));
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
		SET_ERROR_NO(npg_errno);
		return false;
	}

	return true;
}
