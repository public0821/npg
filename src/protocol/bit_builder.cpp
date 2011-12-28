#include "bit_builder.h"
#include "system/os.h"

BitBuilder::BitBuilder(u_int16_t length)
:m_length(length)
,m_pos(0)
{
	m_buffer = new u_int8_t[length + sizeof(u_int32_t)];
	bzero(m_buffer, length + sizeof(u_int32_t));
}

BitBuilder::~BitBuilder(void)
{
	if (m_buffer != NULL)
	{
		delete[] m_buffer;
	}
	m_buffer = NULL;
}

const u_int8_t BYTE_SIZE = 8;
void BitBuilder::append(u_int32_t value, u_int16_t length)
{

	u_int32_t* start_byte = (u_int32_t*)&(m_buffer[m_pos/BYTE_SIZE]);
	u_int8_t start_bit = m_pos % BYTE_SIZE;

	u_int16_t move_len = sizeof(u_int32_t)*BYTE_SIZE - length - start_bit;
	u_int32_t new_value =  ( (htonl(*start_byte) >> move_len) + value) << move_len;

	new_value = htonl(new_value);

	memcpy((u_int8_t*)start_byte, &new_value, sizeof(u_int32_t));

	m_pos += length;
}

const u_int8_t* BitBuilder::data()const
{
	return m_buffer;
}

u_int16_t BitBuilder::length()const
{
	return m_length;
}