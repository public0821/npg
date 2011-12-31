#ifndef __BIT_BUILDER_H__
#define __BIT_BUILDER_H__
#include "system/features.h"
#include "system/types.h"
#include "system/error.h"

class BitBuilder:public Error
{
public:
	BitBuilder(u_int16_t length);	//Identifies the number of bytes
	~BitBuilder(void);
public:
	bool append(u_int32_t value, u_int16_t length);
	void set(u_int16_t index);
	void clr(u_int16_t index);
	bool test(u_int16_t index);
	const u_int8_t* data()const;
	u_int16_t length()const;
private:
	u_int16_t m_length;
	u_int8_t* m_buffer;
	u_int16_t m_pos;
};
#endif