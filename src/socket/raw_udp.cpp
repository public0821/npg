/*
 * raw_udp.cpp
 *
 *  Created on: 2011-9-23
 *      Author: root
 */

#include "raw_udp.h"
#include "socket_public.h"
#include <netinet/udp.h>
#include "socket_toolkit.h"

RawUdp::RawUdp()
{
	// TODO Auto-generated constructor stub

}

RawUdp::~RawUdp()
{
	// TODO Auto-generated destructor stub
}

bool RawUdp::sendto(const char* srcip, const char* dstip, uint16_t srcport, uint16_t dstport, const char* data, int datalen)
{
	int len = sizeof(struct udphdr) + datalen;
	char * buf = new char[len];
	bzero(buf, sizeof(struct udphdr));
	memcpy(buf+sizeof(struct udphdr), data, datalen);

	struct udphdr *udphdr = (struct udphdr *)buf;
	udphdr->source = htons(srcport);
	udphdr->dest = htons(dstport);
	udphdr->len = htons(len);
//	SocketToolkit toolkit;
//	udphdr->check = toolkit.inCheckSum((u_short *) buf, len);
//
//	40         if ( (ui->ui_sum = in_cksum((u_int16_t *) ui, userlen)) == 0)
//	41              ui->ui_sum = 0xffff;

	bool ret = m_ipRawSocket.sendto(srcip, dstip, IPPROTO_UDP, buf, len);
	if(!ret)
	{
		SET_ERROR_STR(m_ipRawSocket.errorStr());
		delete[] buf;
		return false;
	}

	delete[] buf;
	return true;
}


