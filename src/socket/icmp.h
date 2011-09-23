/*
 * icmp.h
 *
 *  Created on: 2011-9-7
 *      Author: wuyangchun
 */

#ifndef ICMP_H_
#define ICMP_H_

#include "socket_public.h"
#include "socket_error.h"

class Icmp: public SocketError
{
public:
	Icmp();
	virtual ~Icmp();
public:
	bool sendto(const char* ip, void* icmp, int len, bool needCalcCheckNum);
private:
	int m_sockfd;
	pid_t m_pid;
	int m_seq;
};

#endif /* ICMP_H_ */
