/*
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#ifndef	__NPG_SOCKET_H__
#define __NPG_SOCKET_H__

#include "lib/features.h"
#include "lib/types.h"
#include "lib/os.h"

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define ntohll(n)  ((uint64_t)ntohl((uint64_t)(n) >> 32) |\
					((uint64_t)ntohl(((uint64_t)(n) << 32)>>32))<<32)
#else
	#define ntohll(n) n
	#define htonll(n) n
#endif

#ifdef _MSC_VER
//	#define sock_last_error()   ""//WSAGetLastError()

#include <winsock2.h>
#include <Ws2tcpip.h>

#include <windows.h>
#include <iphlpapi.h>

#include "net/ethernet.h"
#include "net/if_ether.h"
#include "net/if_arp.h"
#include "net/ip.h"
#include "net/ip_icmp.h"
#include "net/udp.h"

#define EWOULDBLOCK             WSAEWOULDBLOCK
#define EINPROGRESS             WSAEINPROGRESS
#define EAGAIN					EWOULDBLOCK

#define inet_ntop(a, b, c, d)		WSAAddressToString(a,b,NULL, c,d)
#define inet_pton(a, b, c, d)		WSAStringToAddress(a,b,NULL, c,d)
//#define npg_ioctl(sock, code, data, size) WSAIoctl(sock, code, data, size, NULL, 0, NULL, NULL, NULL)
inline int npg_ioctl(int sock, int code, void* data, uint32_t size)
{
	DWORD bytes_returned = 0; 
	return WSAIoctl(sock, code, data, size, NULL, 0, &bytes_returned, NULL, NULL);
}

#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "ws2_32.lib")

#endif

#ifdef __GNUC__


#include    <fcntl.h>
#include    <netdb.h>
#include    <unistd.h>

#include    <sys/socket.h>
#include    <sys/time.h>
#include    <sys/stat.h>
#include    <sys/uio.h>
#include    <sys/wait.h>
#include    <sys/ioctl.h>
#include    <arpa/inet.h>
#include    <netpacket/packet.h>
#include    <net/ethernet.h>
#include    <net/if.h>

#include    <netinet/in.h>
#include    <netinet/if_ether.h>
#include    <netinet/in_systm.h>
#include    <netinet/ip.h>
#include    <netinet/ip_icmp.h>
#include    <netinet/udp.h>


#define closesocket(sock) close(sock)

#define npg_ioctl(sock, code, data, size) ioctl(sock, code, data)

#endif

#endif
