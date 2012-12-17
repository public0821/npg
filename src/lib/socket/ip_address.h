/*
 *
 *  Created on: 2012-12-13
 *      Author: Young <public0821@gmail.com>
 */

#ifndef IPADDRESS_H_
#define IPADDRESS_H_

#include "lib/types.h"
#include <string>

class IpAddress {
public:
	const static uint8_t IPV4 = 4;
	const static uint8_t IPV6 = 6;

public:
	IpAddress();
	IpAddress(const IpAddress&);

	bool isvalid() {
		return m_version != 0;
	}
	std::string to_string();
	bool from_string(const std::string& ip);

public:
	uint8_t version() const {
		return m_version;
	}
	void set_version(uint8_t version) {
		m_version = version;
	}

	uint32_t ipv4() const {
		return m_ipv4;
	}

	const char* ipv6() const {
		return m_ipv6;
	}

private:
	uint8_t m_version;
	uint32_t m_ipv4; //network order
	char m_ipv6[16];
};

#endif /* IPADDRESS_H_ */
