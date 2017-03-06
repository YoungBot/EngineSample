//==========================================================
//BinaryBufferBuilder.hpp
//==========================================================

#pragma once

#ifndef _BINARY_BUFFER_BUILDER_HPP_
#define _BINARY_BUFFER_BUILDER_HPP_
#include <vector>
#include "Engine/Utility/Utility.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector4.hpp"
#include "Engine/Math/Matrix4x4.hpp"

class BinaryBufferBuilder
{
public:
	BinaryBufferBuilder()
	{
		m_buffer.clear();
		m_nextByteToAppend = m_buffer.data();
	}
	BinaryBufferBuilder(size_t bufferSize)
	{
		m_bufferSize = bufferSize;
		m_buffer.resize(bufferSize);
		m_nextByteToAppend = m_buffer.data();
	}
	~BinaryBufferBuilder()
	{
	}
	//signed/unsigned char, short, int, as well as float, double, bool, std::string, Vector2/3/4, Matrix4x4)

	bool AppendUnsignedChar(unsigned char nextUnsignedChar);
	bool AppendChar(char nextChar);
	bool AppendUnsignedInt(unsigned int nextUnsignedInt);
	bool AppendInt(int nextInt);
	bool AppendFloat(float nextFloat);
	bool AppendUnsignedShort(unsigned short nextUnsignedShort);
	bool AppendShort(short nextShort);
	bool AppendDouble(double nextDouble);
	bool AppendBool(bool nextBool);
	bool AppendString(const std::string& nextString);
	bool AppendVector2(const Vector2& nextVector2);
	bool AppendVector3(const Vector3& nextVector3);
	bool AppendVector4(const Vector4& nextVector4);
	bool AppendMatrix4x4(const Matrix4x4& nextMatrix);



	bool WriteBufferToFile(const std::string fileName);
	bool CanAppendNextSizeofData(size_t size);
	std::vector< unsigned char > m_buffer;
	size_t m_bufferSize;
	unsigned char* m_nextByteToAppend;

};

#endif