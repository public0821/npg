/*
 * raw_udp.cpp
 *
 *  Created on: 2011-9-23
 *      Author: Young <public0821@gmail.com>
 */

#include "raw_udp.h"
#include "socket_public.h"
#include "socket_toolkit.h"

RawUdp::RawUdp()
{
	// TODO Auto-generated constructor stub

}

RawUdp::~RawUdp()
{
	// TODO Auto-generated destructor stub
}

bool RawUdp::sendto(const char* srcip, const char* dstip, u_int16_t srcport, u_int16_t dstport, const char* data, u_int16_t datalen)
{
	u_int16_t len = sizeof(struct udphdr) + datalen;
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
		SET_ERROR_STR(m_ipRawSocket.errorString());
	}

	delete[] buf;
	return ret;
}


