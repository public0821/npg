#ifndef	__OS_LINUX_H__
#define __OS_LINUX_H__

#include <errno.h>
#include <string.h>
#include <string>

#define npg_errno   errno

inline int npg_strerror(int errorno, char *buf, int buflen) {
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
