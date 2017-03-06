//==========================================================
//BitArray.hpp
//==========================================================
#pragma once
typedef unsigned char byte_t;
typedef unsigned int uint_t;
#include <string>
class BitArray
{
public:
	BitArray(void* buffer, size_t byte_len, bool initial_value)
	{
		m_buffer = (byte_t*)buffer;
		m_buffer_len = byte_len;
		Reset(initial_value);
	}

	void Reset(bool value);
	void Set(uint_t index);
	void Unset(uint_t index);
	bool Get(uint_t index) const;
private:
	byte_t *m_buffer;
	size_t m_buffer_len;
};

template <size_t BIT_SIZE>
class TBitArray : public BitArray
{
public:
	TBitArray(bool initial_calue);
	TBitArray();
private:
	byte_t m_fixed_buffer[(BIT_SIZE + 7) / 8];
};

template <size_t BIT_SIZE>
TBitArray<BIT_SIZE>::TBitArray()
	:BitArray(m_fixed_buffer, (BIT_SIZE + 7) / 8, false)
{

}

template <size_t BIT_SIZE>
TBitArray<BIT_SIZE>::TBitArray(bool initial_calue)
	:BitArray(m_fixed_buffer, (BIT_SIZE+7)/8, initial_value)
{

}
