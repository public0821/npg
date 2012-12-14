#include "bit_builder.h"
#include "system/os.h"
#include "socket/socket.h"

const uint8_t BYTE_SIZE = 8;
const uint8_t SHIFT = 3;
const uint8_t MASK = 0X07;


BitBuilder::BitBuilder(uint16_t length) :
		m_length(length), m_pos(0)
{
	m_buffer = new uint8_t[length + sizeof(uint32_t)];
	bzero(m_buffer, length + sizeof(uint32_t));
}

BitBuilder::~BitBuilder(void)
{
	if (m_buffer != NULL)
	{
		delete[] m_buffer;
	}
	m_buffer = NULL;
}

bool BitBuilder::append(uint32_t value, uint16_t length)
{

	if (length >= sizeof(uint32_t) * BYTE_SIZE  //too long
		|| length+m_pos < m_pos) //overflow
	{
		SET_ERROR_STR("Out of range");
		return false;
	}
	uint32_t* start_byte = (uint32_t*) &(m_buffer[m_pos >> SHIFT]);
	uint8_t start_bit = m_pos & MASK;

	uint16_t move_len = sizeof(uint32_t) * BYTE_SIZE - length - start_bit;
	uint32_t new_value = ((htonl(*start_byte) >> move_len) + value)
			<< move_len;

	new_value = htonl(new_value);

	memcpy((uint8_t*) start_byte, &new_value, sizeof(uint32_t));

	m_pos += length;

	return true;
}

const uint8_t* BitBuilder::data() const
{
	return m_buffer;
}

uint16_t BitBuilder::length() const
{
	return m_length;
}


void BitBuilder::set(uint16_t index)
{
	m_buffer[index >> SHIFT] |= (1 << (index & MASK));
}

void BitBuilder::clr(uint16_t index)
{
	m_buffer[index >> SHIFT] &= ~(1 << (index & MASK));
}

bool BitBuilder::test(uint16_t index)
{
	return m_buffer[index >> SHIFT] & (1 << (index & MASK));
}
