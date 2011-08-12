/*
 * Udp.h
 *
 *  Created on: 2011-8-11
 *      Author: wuyangchun
 */

#ifndef UDP_H_
#define UDP_H_
#include "public.h"

class Udp
{
public:
	Udp();
	virtual ~Udp();
public:
	bool send(const char* ip, int port, const char* buffer, int buffer_len);
	const char* errorStr() const;
private:
	void setErrorStr(const char* error_str)
	{
		fillErrorStr(m_error, sizeof(m_error), error_str);
	}
	;
	void setErrorStr()
	{
		fillErrorStr(m_error, sizeof(m_error), strerror(errno));
	}
	;
private:
	int m_sockfd;
	char m_error[K_SOCKET_ERROR_BUF_LEN];
};

#endif /* UDP_H_ */
