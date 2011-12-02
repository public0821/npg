/*
 * icmp.h
 *
 *  Created on: 2011-9-7
 *      Author: Young <public0821@gmail.com>
 */

#ifndef ICMP_H_
#define ICMP_H_

#include "system/error.h"

class Icmp: public Error
{
public:
	Icmp();
	~Icmp();
public:
	bool sendto(const char* ip, void* icmp, u_int16_t len, bool need_calc_checknum);
private:
	int m_sockfd;
//	pid_t m_pid;
	int m_seq;
};

#endif /* ICMP_H_ */
