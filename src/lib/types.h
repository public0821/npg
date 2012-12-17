/*
 * types.h
 *
 *  Created on: 2011-10-25
 *      Author: Young <public0821@gmail.com>
 */
#ifndef	__NGP_TYPE_H__
#define __NGP_TYPE_H__

#include "features.h"

#ifdef _MSC_VER
	typedef unsigned char u_char;
	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned int uint32_t;

	#ifndef _WINSOCK2API_
	typedef unsigned __int64 uint64_t;
	#endif

	typedef signed char int8_t;
	typedef signed short int16_t;
	typedef signed int int32_t;
	typedef signed __int64 int64_t;

	
	#if defined(_WIN64) || __WORDSIZE == 64
		#define __INT64_C(c)	c ## L
		#define __UINT64_C(c)	c ## UL
	#else
		#define __INT64_C(c)	c ## LL
		#define __UINT64_C(c)	c ## ULL
	#endif

	/* Minimum of signed integral types.  */
	# define INT8_MIN		(-128)
	# define INT16_MIN		(-32767-1)
	# define INT32_MIN		(-2147483647-1)
	# define INT64_MIN		(-__INT64_C(9223372036854775807)-1)
		/* Maximum of signed integral types.  */
	# define INT8_MAX		(127)
	# define INT16_MAX		(32767)
	# define INT32_MAX		(2147483647)
	# define INT64_MAX		(__INT64_C(9223372036854775807))

		/* Maximum of unsigned integral types.  */
	# define UINT8_MAX		(255)
	# define UINT16_MAX		(65535)
	# define UINT32_MAX		(4294967295U)
	# define UINT64_MAX		(__UINT64_C(18446744073709551615))
#endif

#ifdef __GNUC__
//	#include <sys/types.h>
	#include <cstdint>
#endif

#endif
