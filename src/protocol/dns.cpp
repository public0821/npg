/*
 * dns.cpp
 *
 *  Created on: 2011-10-11
 *      Author: Young <public0821@gmail.com>
 */

#include "dns.h"
#include "socket/socket_public.h"

Dns::Dns() :
		m_seq(1)
{
	// TODO Auto-generated constructor stub

}

Dns::~Dns()
{
	// TODO Auto-generated destructor stub
}

bool Dns::sendto(const char* ip, const char* request, EDnsRequestType type)
{
	DnsRequest dnsRequest(request, type);
	const char* formatted_request = dnsRequest.getFormattedRequest();
	size_t formatted_request_len = dnsRequest.getFormattedRequestLen();
	if (formatted_request == NULL)
	{
		SET_ERROR_STR("NULL Request");
		return false;
	}

	size_t total_len = sizeof(struct dns_header) + formatted_request_len;

	char* buf = new char[total_len];

	struct dns_header* dns_header = (struct dns_header*) buf;

	bzero(dns_header, sizeof(struct dns_header));

	dns_header->seq = htons(m_seq++);
//	if (type == E_DNS_PTR)
//	{
//		dnsHeader->op_flag |= 0x0800; //SET OPCODE: E_DNS_PTR
//	}
	dns_header->op_flag |= 0x0100; //SET RD: 1

	dns_header->op_flag = htons(dns_header->op_flag);
	dns_header->query_num = htons(1);

	memcpy(buf + sizeof(struct dns_header), formatted_request,
			formatted_request_len);

	bool ret = m_udp.sendto(ip, 53, buf, total_len);
	if (!ret)
	{
		SET_ERROR_STR(m_udp.errorStr());
	}

	delete[] buf;

	return ret;
}

DnsRequest::DnsRequest() :
		m_request(NULL), m_type(E_DNS_A), m_class(1), m_length(0)
{

}

DnsRequest::~DnsRequest()
{
	if (m_request != NULL)
	{
		delete[] m_request;
	}
}

DnsRequest::DnsRequest(const char* request, EDnsRequestType type) :
		m_request(NULL), m_type(E_DNS_A), m_class(1), m_length(0)
{
	DnsRequest();
//	setType(type);
	setRequest(request, type);
}

void DnsRequest::setRequest(const char* request, EDnsRequestType type)
{
	if (m_request != NULL)
	{
		delete[] m_request;
	}

	if (request == NULL)
	{
		return;
	}

	m_type = type;

	char ptr_request_tail[] = "\007in-addr\004arpa";
	size_t ptr_request_tail_len = strlen(ptr_request_tail);

	size_t request_len = strlen(request);
	size_t max_len = request_len * 2 + 1;
	max_len += ptr_request_tail_len;
	max_len += sizeof(u_int16_t); //used to store type
	max_len += sizeof(u_int16_t); //used to store class

	m_request = new char[max_len];
	bzero(m_request, max_len);
	char* start = m_request;
	char* to_it = start + 1;

	if (m_type == E_DNS_A) //\003www\006google\003com
	{
		for (const char* from_it = request; *from_it != '\0'; from_it++)
		{
			if (*from_it == '.')
			{
				start = to_it;
				to_it = start + 1;
				continue;
			}
			(*start)++;
			*to_it = *from_it;
			to_it++;
		}
	}
	else if (m_type == E_DNS_PTR) //\0015\003209\00296\003202\007in-addr\004arpa
	{
		for (const char* it = request + request_len - 1;; it--)
		{
			if (*it == '.')
			{
				memcpy(start + 1, it + 1, *start);
				start = start + *start + 1;
				continue;
			}
			(*start)++;
			if (it == request) //arrive head
			{
				memcpy(start + 1, it, *start);
				break;
			}
		}
		memcpy(m_request + strlen(m_request), ptr_request_tail,
				ptr_request_tail_len);

	}

	size_t actual_len = strlen(m_request) + 1;
	u_int16_t dnstype = htons((u_int16_t) m_type);
	u_int16_t dnsclass = htons(m_class);
	memcpy(m_request + actual_len, &dnstype, sizeof(dnstype));
	memcpy(m_request + actual_len + sizeof(u_int16_t), &dnsclass,
			sizeof(dnsclass));

	m_length = actual_len + sizeof(u_int16_t) + sizeof(u_int16_t);
}

//void DnsRequest::setType(EDnsRequestType type)
//{
//	m_type = type;
//}

const char* DnsRequest::getFormattedRequest()
{
	return (const char*) m_request;
}

size_t DnsRequest::getFormattedRequestLen()
{
	return m_length;
}

//EDnsRequestType DnsRequest::getType()
//{
//	return m_type;
//}
//
//u_int16_t DnsRequest::getClass()
//{
//	return m_class;
//}

//void DnsRequest::reverseString(char* start, size_t len)
//{
//	char* tempStart = start;
//	char* tempEnd = start + len - 1;
//
//	while (tempEnd > tempStart)
//	{
//		char temp = *tempStart;
//		*tempStart = *tempEnd;
//		*tempEnd = temp;
//		tempStart++;
//		tempEnd--;
//	}
//}
