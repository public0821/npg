/*
 * socket_toolkit.h
 *
 *  Created on: 2011-9-20
 *      Author: root
 */

#ifndef SOCKET_TOOLKIT_H_
#define SOCKET_TOOLKIT_H_

#include <net/if.h>
#include <vector>
#include "socket_error.h"


# define IF_HWADDRLEN	6
#define IF_NAMESIZE 16

struct ifi_info
{
	char ifi_name[IF_NAMESIZE]; /* interface name, null-terminated */
	short ifi_index; /* interface index */
//	short ifi_mtu; /* interface MTU */
	char ifi_haddr[IFHWADDRLEN]; /* hardware address */
//	uint16_t ifi_hlen; /* # bytes in hardware address: 0, 6, 8 */
	short ifi_flags; /* IFF_xxx constants from <net/if.h> */
//	short ifi_myflags; /* our own IFI_xxx flags */
	struct sockaddr ifi_addr; /* primary address */
//	struct sockaddr ifi_brdaddr; /* broadcast address */
//	struct sockaddr ifi_dstaddr; /* destination address */
//	struct ifi_info *ifi_next; /* next of these structures */
};

class SocketToolkit: public SocketError
{
public:
	SocketToolkit();
	virtual ~SocketToolkit();
public:
	std::vector<ifi_info> getIfiInfo(int family = 0, int doaliases = 0);
	uint16_t inCheckSum(uint16_t * addr, int len);

};

#endif /* SOCKET_TOOLKIT_H_ */
