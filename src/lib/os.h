/*
 * os.h
 *
 *  Created on: 2011-10-25
 *      Author: Young <public0821@gmail.com>
 */
#ifndef	__OS_H__
#define __OS_H__

#if defined(WIN32)
	#include "windows.h"
#elif defined(__GNUC__)
	#include "linux.h"
#else
	#error "Unsupported platform"
#endif

#include "types.h"

#endif
