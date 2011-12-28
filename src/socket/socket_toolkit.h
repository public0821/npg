/*
 * socket_toolkit.h
 *
 *  Created on: 2011-9-20
 *      Author: Young <public0821@gmail.com>
 */

#ifndef SOCKET_TOOLKIT_H_
#define SOCKET_TOOLKIT_H_

#include <vector>
#include "system/error.h"
#include "system/types.h"
#include "socket_public.h"


# define IF_HWADDRLEN	6
#define IF_NAME_SIZE 256

struct ifi_info
{
	char ifi_name[IF_NAME_SIZE]; /* interface name, null-terminated */
	short ifi_index; /* interface index */
//	short ifi_mtu; /* interface MTU */
	char ifi_haddr[IF_HWADDRLEN]; /* hardware address */
//	u_int16_t ifi_hlen; /* # bytes in hardware address: 0, 6, 8 */
	short ifi_flags; /* IFF_xxx constants from <net/if.h> */
//	short ifi_myflags; /* our own IFI_xxx flags */
	struct sockaddr ifi_addr; /* primary address */
//	struct sockaddr ifi_brdaddr; /* broadcast address */
//	struct sockaddr ifi_dstaddr; /* destination address */
//	struct ifi_info *ifi_next; /* next of these structures */
};

class SocketToolkit: public Error
{
public:
	SocketToolkit();
	~SocketToolkit();
public:
	std::vector<ifi_info> ifiInfo(int family = 0, int doaliases = 0);
	u_int16_t inCheckSum(u_int16_t * addr, size_t len);//return network byte order
	int macAddress(const char* ip, char* mac);
	bool toMac(const char* mac_str, u_int8_t* mac);
	void macToString(const u_int8_t* mac, char* mac_str, size_t len);
};

#endif /* SOCKET_TOOLKIT_H_ */
