/*
 *
 *  Created on: 2012-12-13
 *      Author: Young <public0821@gmail.com>
 */

#ifndef IPADDRESS_H_
#define IPADDRESS_H_

#include "system/types.h"
#include <string>

class IpAddress {
public:
	const static uint8_t IPV4 = 4;
	const static uint8_t IPV6 = 6;
public:
	IpAddress();
	IpAddress(const IpAddress&);

//	bool isvalid();
	std::string to_string();
	bool from_string(const std::string& ip);

private:
	uint8_t m_version;
	uint32_t m_ipv4; 	//network order
	char m_ipv6[16];
};

#endif /* IPADDRESS_H_ */
