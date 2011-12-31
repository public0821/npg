#include "bit_builder.h"
#include "system/os.h"
#include "socket/socket_public.h"

const u_int8_t BYTE_SIZE = 8;
const u_int8_t SHIFT = 3;
const u_int8_t MASK = 0X07;


BitBuilder::BitBuilder(u_int16_t length) :
		m_length(length), m_pos(0)
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

void BitBuilder::append(u_int32_t value, u_int16_t length)
{

	u_int32_t* start_byte = (u_int32_t*) &(m_buffer[m_pos / BYTE_SIZE]);
	u_int8_t start_bit = m_pos % BYTE_SIZE;

	u_int16_t move_len = sizeof(u_int32_t) * BYTE_SIZE - length - start_bit;
	u_int32_t new_value = ((htonl(*start_byte) >> move_len) + value)
			<< move_len;

	new_value = htonl(new_value);

	memcpy((u_int8_t*) start_byte, &new_value, sizeof(u_int32_t));

	m_pos += length;
}

const u_int8_t* BitBuilder::data() const
{
	return m_buffer;
}

u_int16_t BitBuilder::length() const
{
	return m_length;
}


void BitBuilder::set(u_int16_t index)
{
	m_buffer[index >> SHIFT] |= (1 << (index & MASK));
}

void BitBuilder::clr(u_int16_t index)
{
	m_buffer[index >> SHIFT] &= ~(1 << (index & MASK));
}

bool BitBuilder::test(u_int16_t index)
{
	return m_buffer[index >> SHIFT] & (1 << (index & MASK));
}