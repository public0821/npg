/*
 *
 *  Created on: 2011-8-23
 *      Author: Young <public0821@gmail.com>
 */

#ifndef	__SOCKET_H__
#define __SOCKET_H__

#include "system/features.h"
#include "system/types.h"
#include "system/os.h"

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define ntohll(n)  ((uint64_t)ntohl((uint64_t)(n) >> 32) |\
					((uint64_t)ntohl(((uint64_t)(n) << 32)>>32))<<32)
#else
	#define ntohll(n) n
	#define htonll(n) n
#endif

#ifdef _MSC_VER
#define npg_errno   WSAGetLastError()
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
//#define npg_ioctl(sock, code, data, size) WSAIoctl(sock, code, data, size, NULL, 0, NULL, NULL, NULL)
inline int npg_ioctl(int sock, int code, void* data, uint32_t size)
{
	DWORD bytes_returned = 0; 
	return WSAIoctl(sock, code, data, size, NULL, 0, &bytes_returned, NULL, NULL);
}

#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "ws2_32.lib")

inline int npg_strerror(int errorno, char* buf, int buflen)
{
#define TEMP_BUF_SIZE 512
	bzero(buf, buflen);
	WCHAR tempBuf[TEMP_BUF_SIZE];
	DWORD ret = FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			errorno,
			MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), // Default language
			//MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			tempBuf,
			TEMP_BUF_SIZE,
			NULL
	);

	if (ret == 0)
	{
		return 0;
	}

	WideCharToMultiByte( CP_ACP,
			0,
			tempBuf,
			-1,
			buf,
			buflen, //
			NULL,
			NULL );

	return 0;
}
#endif

#ifdef __GNUC__

#include    <time.h>

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>

#include    <errno.h>
#include    <fcntl.h>
#include    <netdb.h>
#include    <signal.h>
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
#define npg_errno   errno
//	#define npg_strerror   strerror
inline int npg_strerror(int errorno, char* buf, int buflen)
{
	bzero(buf, buflen);
#if  (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE
	int ret = strerror_r(errorno, buf, buflen);
	return ret;
#else
	char * ret = strerror_r(errorno, buf, buflen);
	strncpy(buf, ret, buflen);
	return 0;
#endif

}

#endif

#endif
