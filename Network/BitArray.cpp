//==========================================================
//BitArray.cpp
//==========================================================
#include "BitArray.hpp"
void BitArray::Reset(bool value)
{
	if (value)
		memset(m_buffer, 0xff, m_buffer_len);
	else
		memset(m_buffer, 0x00, m_buffer_len);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void BitArray::Set(uint_t index)
{
	uint_t byte_index = index / 8;
	uint_t bit_index = index % 8;
	//ASSERT(byte_index < m_buffer_len);
	byte_t b = m_buffer[byte_index];
	b = b | (1 << bit_index);
	m_buffer[byte_index] = b;
}

void BitArray::Unset(uint_t index)
{
	uint_t byte_index = index / 8;
	uint_t bit_index = index % 8;
	//ASSERT(byte_index < m_buffer_len);
	byte_t b = m_buffer[byte_index];
	b = b & ~(1 << bit_index);
	m_buffer[byte_index] = b;
}

bool BitArray::Get(uint_t index) const
{
	uint_t byte_index = index / 8;
	uint_t bit_index = index % 8;
	//ASSERT(byte_index < m_buffer_len);
	byte_t b = m_buffer[byte_index];
	return (b & (1 << bit_index)) != 0;
}

