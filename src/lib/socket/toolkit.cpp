/*
 * socket_toolkit.cpp
 *
 *  Created on: 2011-9-20
 *      Author: Young <public0821@gmail.com>
 */

#include "toolkit.h"
#include "../../logger.h"
#include "socket.h"
#include <qobject.h>

SocketToolkit::SocketToolkit()
{

}

SocketToolkit::~SocketToolkit()
{
}

uint16_t SocketToolkit::inCheckSum(uint16_t * addr, size_t len) {
	int nleft = len;
	uint32_t sum = 0;
	uint16_t *w = addr;
	uint16_t answer = 0;

	/*
	 * Our algorithm is simple, using a 32 bit accumulator (sum), we add
	 * sequential 16 bit words to it, and at the end, fold back all the
	 * carry bits from the top 16 bits into the lower 16 bits.
	 */
	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}
	/* mop up an odd byte, if necessary */
	if (nleft == 1) {
		*(unsigned char *) (&answer) = *(unsigned char *) w;
		sum += answer;
	}

	/* add back carry outs from top 16 bits to low 16 bits */
	sum = (sum >> 16) + (sum & 0xffff); /* add hi 16 to low 16 */
	sum += (sum >> 16); /* add carry */
	answer = ~sum; /* truncate to 16 bits */
	return (answer);
}

bool SocketToolkit::toMac(const char* mac_str, uint8_t* mac) {
	uint32_t temp_mac[6];
	bzero(temp_mac, sizeof(temp_mac));
	int n = sscanf(mac_str, "%x:%x:%x:%x:%x:%x", &temp_mac[0], &temp_mac[1], &temp_mac[2],
			&temp_mac[3], &temp_mac[4], &temp_mac[5]);

	if (n != 6) {
		n = sscanf(mac_str, "%x-%x-%x-%x-%x-%x", &temp_mac[0], &temp_mac[1], &temp_mac[2],
				&temp_mac[3], &temp_mac[4], &temp_mac[5]);
	}

	if (n != 6) {
		return false;
	}

	for (int i = 0; i < 6; i++) {
		mac[i] = temp_mac[i];
	}

	return true;
}

void SocketToolkit::macToString(const uint8_t* mac, char* mac_str, size_t len) {
	bzero(mac_str, sizeof(len));
	snprintf(mac_str, len, "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x",
			(uint8_t) mac[0], (uint8_t) mac[1],
			(uint8_t) mac[2], (uint8_t) mac[3],
			(uint8_t) mac[4], (uint8_t) mac[5]);
}
