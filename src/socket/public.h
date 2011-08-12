#ifndef	__PUBLIC_H__
#define __PUBLIC_H__

#include    <sys/types.h>       /* basic system data types */
#include    <sys/socket.h>      /* basic socket definitions */
#include    <sys/time.h>        /* timeval{} for select() */
#include    <time.h>            /* timespec{} for pselect() */
#include    <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include    <arpa/inet.h>       /* inet(3) functions */
#include    <errno.h>
#include    <fcntl.h>           /* for nonblocking */
#include    <netdb.h>
#include    <signal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sys/stat.h>        /* for S_xxx file mode constants */
#include    <sys/uio.h>         /* for iovec{} and readv/writev */
#include    <unistd.h>
#include    <sys/wait.h>


const int	K_SOCKET_ERROR =  -1;
const int	K_SOCKET_ERROR_BUF_LEN =  512;

inline void fillErrorStr(char* error_buffer, int buffer_len, const char* error_str)
{
	snprintf(error_buffer, buffer_len, "%s%d:%s", __FILE__, __LINE__, error_str);
}


#endif
