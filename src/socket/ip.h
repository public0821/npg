/*
 * ip.h
 *
 *  Created on: 2011-9-7
 *      Author: Young <public0821@gmail.com>
 */

#ifndef IP_H_
#define IP_H_
#include "system/error.h"

class Ip: public Error
{
public:
	Ip(int protocol);
	~Ip(void);
public:
	bool sendto(const char* ip, const char* data, u_int16_t len);
private:
	int m_sockfd;
};

#endif