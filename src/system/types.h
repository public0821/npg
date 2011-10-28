/*
 * types.h
 *
 *  Created on: 2011-10-25
 *      Author: Young <public0821@gmail.com>
 */
#ifndef	__TYPE_H__
#define __TYPE_H__

#include "features.h"
#include <string>

typedef std::string sstring;


#ifdef WIN32
	typedef unsigned char u_char;
	typedef unsigned char u_int8_t;
	typedef unsigned short u_int16_t;
	typedef unsigned int u_int32_t;

	#ifndef _WINSOCK2API_
	typedef unsigned __int64 u_int64_t;
	#endif

	typedef signed char int8_t;
	typedef signed short int16_t;
	typedef signed int int32_t;
	typedef signed __int64 int64_t;

#endif

#ifdef LINUX32
	#include <sys/types.h>
#endif

#endif
