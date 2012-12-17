/*
 * bit_builder.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef __BIT_BUILDER_H__
#define __BIT_BUILDER_H__
#include "lib/features.h"
#include "lib/types.h"
#include "lib/error.h"

class BitBuilder:public Error
{
public:
	BitBuilder(uint16_t length);	//Identifies the number of bytes
	~BitBuilder(void);
public:
	bool append(uint32_t value, uint16_t length);
	void set(uint16_t index);
	void clr(uint16_t index);
	bool test(uint16_t index);
	const uint8_t* data()const;
	uint16_t length()const;
private:
	uint16_t m_length;
	uint8_t* m_buffer;
	uint16_t m_pos;
};
#endif