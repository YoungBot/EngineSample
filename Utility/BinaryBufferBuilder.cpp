//==========================================================
//BinaryBufferBuilder.cpp
//==========================================================
#include "BinaryBufferBuilder.hpp"

bool BinaryBufferBuilder::WriteBufferToFile(const std::string fileName)
{
	return Utility::WriteBufferToBinaryFile(m_buffer.data(), m_buffer.size(), fileName);	
}

bool BinaryBufferBuilder::CanAppendNextSizeofData(size_t size)
{
	if ((m_buffer.data() + m_bufferSize) > (m_nextByteToAppend+ size))
	{
		return true;
	}
	else
		return false;
}

bool BinaryBufferBuilder::AppendUnsignedChar(unsigned char nextUnsignedChar)
{
	if (!CanAppendNextSizeofData(sizeof(unsigned char)))
	{
		return false;
	}
	(*m_nextByteToAppend) = nextUnsignedChar;
	m_nextByteToAppend += sizeof(unsigned char);
	return true;
}
bool BinaryBufferBuilder::AppendChar(char nextChar)
{
	if (!CanAppendNextSizeofData(sizeof(char)))
	{
		return false;
	}
	(*m_nextByteToAppend) = nextChar;
	m_nextByteToAppend += sizeof(char);
	return true;
}
bool BinaryBufferBuilder::AppendUnsignedInt(unsigned int nextUnsignedInt)
{
	if (!CanAppendNextSizeofData(sizeof(unsigned int)))
	{
		return false;
	}

	unsigned char* intPointer = (unsigned char*)&nextUnsignedInt;
	(*m_nextByteToAppend) = intPointer[0];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = intPointer[1];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = intPointer[2];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = intPointer[3];
	m_nextByteToAppend += sizeof(unsigned char);
	return true;
}
bool BinaryBufferBuilder::AppendInt(int nextInt)
{
	if (!CanAppendNextSizeofData(sizeof(int)))
	{
		return false;
	}
	unsigned char* intPointer = (unsigned char*)&nextInt;
	(*m_nextByteToAppend) = intPointer[0];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = intPointer[1];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = intPointer[2];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = intPointer[3];
	m_nextByteToAppend += sizeof(unsigned char);
	return true;
}
bool BinaryBufferBuilder::AppendFloat(float nextFloat)
{
	if (!CanAppendNextSizeofData(sizeof(float)))
	{
		return false;
	}

	unsigned char* floatPointer = (unsigned char*)&nextFloat;
	(*m_nextByteToAppend) = floatPointer[0];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = floatPointer[1];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = floatPointer[2];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = floatPointer[3];
	m_nextByteToAppend += sizeof(unsigned char);
	return true;
}
bool BinaryBufferBuilder::AppendUnsignedShort(unsigned short nextUnsignedShort)
{
	if (!CanAppendNextSizeofData(sizeof(unsigned short)))
	{
		return false;
	}
	unsigned char* shortPointer = (unsigned char*)&nextUnsignedShort;
	(*m_nextByteToAppend) = shortPointer[0];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = shortPointer[1];
	m_nextByteToAppend += sizeof(unsigned char);
	return true;
}
bool BinaryBufferBuilder::AppendShort(short nextShort)
{
	if (!CanAppendNextSizeofData(sizeof(short)))
	{
		return false;
	}
	unsigned char* shortPointer = (unsigned char*)&nextShort;
	(*m_nextByteToAppend) = shortPointer[0];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = shortPointer[1];
	m_nextByteToAppend += sizeof(unsigned char);
	return true;
}
bool BinaryBufferBuilder::AppendDouble(double nextDouble)
{
	if (!CanAppendNextSizeofData(sizeof(double)))
	{
		return false;
	}
	unsigned char* doublePointer = (unsigned char*)&nextDouble;
	(*m_nextByteToAppend) = doublePointer[0];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = doublePointer[1];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = doublePointer[2];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = doublePointer[3];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = doublePointer[4];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = doublePointer[5];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = doublePointer[6];
	m_nextByteToAppend += sizeof(unsigned char);
	(*m_nextByteToAppend) = doublePointer[7];
	m_nextByteToAppend += sizeof(unsigned char);


	return true;
}
bool BinaryBufferBuilder::AppendBool(bool nextBool)
{
	if (!CanAppendNextSizeofData(sizeof(double)))
	{
		return false;
	}
	(*m_nextByteToAppend) = nextBool;
	m_nextByteToAppend += sizeof(bool);
	return true;
}
bool BinaryBufferBuilder::AppendString(const std::string& nextString)
{
	if (!CanAppendNextSizeofData(nextString.size()))
	{
		return false;
	}
	for (unsigned int i = 0; i < nextString.size(); i++)
	{
		(*m_nextByteToAppend) = nextString[i];
		m_nextByteToAppend += sizeof(char);
	}
	//(*m_nextByteToAppend) = (*nextString.data());
	
	return true;
}
bool BinaryBufferBuilder::AppendVector2(const Vector2& nextVector2)
{
	if (!CanAppendNextSizeofData(sizeof(Vector2)))
	{
		return false;
	}
	AppendFloat(nextVector2.x);
	AppendFloat(nextVector2.y);
	return true;
}
bool BinaryBufferBuilder::AppendVector3(const Vector3& nextVector3)
{
	if (!CanAppendNextSizeofData(sizeof(Vector3)))
	{
		return false;
	}
	AppendFloat(nextVector3.x);
	AppendFloat(nextVector3.y);
	AppendFloat(nextVector3.z);
	return true;
}
bool BinaryBufferBuilder::AppendVector4(const Vector4& nextVector4)
{
	if (!CanAppendNextSizeofData(sizeof(Vector4)))
	{
		return false;
	}
	AppendFloat(nextVector4.x);
	AppendFloat(nextVector4.y);
	AppendFloat(nextVector4.z);
	AppendFloat(nextVector4.w);
	return true;
}
bool BinaryBufferBuilder::AppendMatrix4x4(const Matrix4x4& nextMatrix)
{
	if (!CanAppendNextSizeofData(sizeof(Matrix4x4)))
	{
		return false;
	}
	AppendVector4(nextMatrix.m_iBasis);
	AppendVector4(nextMatrix.m_jBasis);
	AppendVector4(nextMatrix.m_kBasis);
	AppendVector4(nextMatrix.m_translation);
	return true;
}