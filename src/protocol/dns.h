/*
 * dns.h
 *
 *  Created on: 2011-10-11
 *      Author: Young <public0821@gmail.com>
 */

#ifndef DNS_H_
#define DNS_H_

#include "socket/udp.h"

struct dns_header
{
	u_int16_t seq;
	u_int16_t op_flag;
	u_int16_t query_num;
	u_int16_t resources_num;
	u_int16_t authorized_res_num;
	u_int16_t additional_res_num;
};

enum EDnsRequestType
{
	E_DNS_A = 1,
	E_DNS_PTR = 12,
};

class DnsRequest
{
public:
	DnsRequest();
	DnsRequest(const char* request, EDnsRequestType type);
	~DnsRequest();
public:
	void setRequest(const char* request, EDnsRequestType type);
//	void setType(EDnsRequestType type);
	const char* getFormattedRequest();
	size_t getFormattedRequestLen();
//	EDnsRequestType getType();
//	u_int16_t getClass();
//private:
//	void reverseString(char* start, size_t len);
private:
	char* m_request;
	EDnsRequestType m_type;
	u_int16_t m_class;
	size_t m_length;
//	bool m_isReverse;
};

class Dns: public SocketError
{
public:
	Dns();
	virtual ~Dns();
public:
	bool sendto(const char* ip, const char* request, EDnsRequestType type);
private:
	Udp	m_udp;
	u_int16_t m_seq;
};

#endif /* DNS_H_ */
