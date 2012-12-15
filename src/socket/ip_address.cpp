/*
 *
 *  Created on: 2012-12-13
 *      Author: Young <public0821@gmail.com>
 */

#include "ip_address.h"
#include "socket.h"

IpAddress::IpAddress() :
		m_version(0), m_ipv4(0) {
	bzero(m_ipv6, sizeof(m_ipv6));
}

IpAddress::IpAddress(const IpAddress& addr) {
	m_version = addr.m_version;
	m_ipv4 = addr.m_ipv4;
	memcpy(m_ipv6, addr.m_ipv6, sizeof(m_ipv6));
}

std::string IpAddress::to_string() {
	if (m_version == IpAddress::IPV4) {
		char address[INET_ADDRSTRLEN];
		if (inet_ntop(AF_INET, &m_ipv4, address, INET_ADDRSTRLEN) == NULL)
			return std::string();
		return address;
	} else {
		char address[INET6_ADDRSTRLEN];
		if (inet_ntop(AF_INET6, &m_ipv6, address, INET6_ADDRSTRLEN) == NULL)
			return std::string();
		return address;
	}
}

bool IpAddress::from_string(const std::string& ip) {
	char address[16];
	if (inet_pton(AF_INET, ip.c_str(), address) == 1) {
		m_version = IPV4;
		memcpy(&m_ipv4, address, 4);
		return true;
	} else if (inet_pton(AF_INET6, ip.c_str(), address) == 1) {
		m_version = IPV6;
		memcpy(&m_ipv6, address, 16);
		return true;
	}
	return false;
}
