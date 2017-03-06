//==========================================================
//BinaryBufferParser.cpp
//==========================================================
#include "Engine/Utility/BinaryBufferParser.hpp"

BinaryBufferParser::BinaryBufferParser()
{

}
BinaryBufferParser::BinaryBufferParser(const unsigned char* buffer, size_t size)
{
	m_bufferStart = nullptr;
	m_bufferStart = (unsigned char*)buffer;
	m_bufferSize = size;

}
BinaryBufferParser::BinaryBufferParser(const std::vector< unsigned char >& bytes)
{
	m_bufferSize = bytes.size()* sizeof(unsigned char);
	m_bufferStart = (unsigned char*)bytes.data();
}

BinaryBufferParser::~BinaryBufferParser()
{
}

void BinaryBufferParser::ReadNextInt(int& nextInt)
{
	if (!CanReadNextSizeofData(sizeof(int)))
	{
		return;
	}
	nextInt = *(int*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(int);
}
int BinaryBufferParser::ReadNextInt()
{
	if (!CanReadNextSizeofData(sizeof(int)))
	{
		return 0;
	}
	int nextInt = *(int*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(int);
	return nextInt;
}
void BinaryBufferParser::ReadNextShort(short& nextShort)
{
	if (!CanReadNextSizeofData(sizeof(short)))
	{
		return;
	}
	nextShort = *(short*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(short);
}
short BinaryBufferParser::ReadNextShort()
{
	if (!CanReadNextSizeofData(sizeof(short)))
	{
		return 0;
	}
	short nextShort = *(short*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(short);
	return nextShort;
}
void BinaryBufferParser::ReadNextChar(char& nextChar)
{
	if (!CanReadNextSizeofData(sizeof(char)))
	{
		return;
	}
	nextChar = *(char*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(char);
}
char BinaryBufferParser::ReadNextChar()
{
	if (!CanReadNextSizeofData(sizeof(char)))
	{
		return 0;
	}
	char nextChar = *(char*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(char);
	return nextChar;
}
void BinaryBufferParser::ReadNextUnsignedChar(unsigned char nextUnsignedChar)
{
	if (!CanReadNextSizeofData(sizeof(unsigned char)))
	{
		return;
	}
	nextUnsignedChar = *(unsigned char*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(unsigned char);
}
unsigned char BinaryBufferParser::ReadNextUnsignedChar()
{
	if (!CanReadNextSizeofData(sizeof(unsigned char)))
	{
		return 0;
	}
	unsigned char nextUnsignedChar = *(unsigned char*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(unsigned char);
	return nextUnsignedChar;
}
void BinaryBufferParser::ReadNextUnsignedShort(unsigned short nextUnsignedShort)
{
	if (!CanReadNextSizeofData(sizeof(unsigned short)))
	{
		return;
	}
	nextUnsignedShort = *(unsigned short*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(unsigned short);
}
unsigned short BinaryBufferParser::ReadNextUnsignedShort()
{
	if (!CanReadNextSizeofData(sizeof(unsigned short)))
	{
		return 0;
	}
	unsigned short nextUnsignedShort = *(unsigned short*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(unsigned short);
	return nextUnsignedShort;
}
void BinaryBufferParser::ReadNextUnsignedInt(unsigned int nextUnsignedInt)
{
	if (!CanReadNextSizeofData(sizeof(unsigned int)))
	{
		return;
	}
	nextUnsignedInt = *(unsigned int*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(unsigned int);
}
unsigned int BinaryBufferParser::ReadNextUnsignedInt()
{
	if (!CanReadNextSizeofData(sizeof(unsigned int)))
	{
		return 0;
	}
	unsigned int nextUnsignedInt = *(unsigned int*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(unsigned int);
	return nextUnsignedInt;
}
void BinaryBufferParser::ReadNextFloat(float& nextFloat)
{
	if (!CanReadNextSizeofData(sizeof(float)))
	{
		return;
	}
	nextFloat = *(float*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(float);
}
float BinaryBufferParser::ReadNextFloat()
{
	if (!CanReadNextSizeofData(sizeof(float)))
	{
		return 0.0f;
	}
	float nextFloat = *(float*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(float);
	return nextFloat;
}
void BinaryBufferParser::ReadNextDouble(double& nextDouble)
{
	if (!CanReadNextSizeofData(sizeof(double)))
	{
		return;
	}
	nextDouble = *(double*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(double);
}
double BinaryBufferParser::ReadNextDouble()
{
	if (!CanReadNextSizeofData(sizeof(double)))
	{
		return 0.0;
	}
	double nextDouble = *(double*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(double);
	return nextDouble;
}
void BinaryBufferParser::ReadNextBool(bool& nextBool)
{
	if (!CanReadNextSizeofData(sizeof(bool)))
	{
		return;
	}
	nextBool = *(bool*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(bool);
}
bool BinaryBufferParser::ReadNextBool()
{
	if (!CanReadNextSizeofData(sizeof(bool)))
	{
		return false;
	}
	bool nextBool = *(bool*)(m_nextByteToRead);
	m_nextByteToRead += sizeof(bool);
	return nextBool;
}
void BinaryBufferParser::ReadNextString(std::string& nextString,int stringSize)
{
	if (!CanReadNextSizeofData(stringSize))
	{
		return;
	}
	nextString.resize(stringSize);
	for (int i = 0; i < stringSize ; i++)
	{
		nextString[i] = ReadNextChar();
	}
}
std::string BinaryBufferParser::ReadNextString(int stringSize)
{
	if (!CanReadNextSizeofData(stringSize))
	{
		return "";
	}
	std::string nextString;
	nextString.resize(stringSize);
	for (int i = 0; i < stringSize; i++)
	{
		nextString[i] = ReadNextChar();
	}
	return nextString;
}
std::string BinaryBufferParser::ReadNextString()
{
	std::string nextString = "";
	unsigned char nextChar;
	nextChar = ReadNextUnsignedChar();
	nextString += nextChar;
	while (nextChar != '\0')
	{
		nextChar = ReadNextUnsignedChar();
		nextString += nextChar;
	}
	return nextString;
}

void BinaryBufferParser::ReadNextVector2(Vector2& nextVector2)
{
	if (!CanReadNextSizeofData(sizeof(Vector2)))
	{
		return;
	}
	nextVector2.x = ReadNextFloat();
	nextVector2.y = ReadNextFloat();
}
Vector2 BinaryBufferParser::ReadNextVector2()
{
	if (!CanReadNextSizeofData(sizeof(Vector2)))
	{
		return Vector2(0.0f,0.0f);
	}
	Vector2 nextVector2;
	nextVector2.x = ReadNextFloat();
	nextVector2.y = ReadNextFloat();
	return nextVector2;
}
void BinaryBufferParser::ReadNextVector3(Vector3& nextVector3)
{
	if (!CanReadNextSizeofData(sizeof(Vector3)))
	{
		return;
	}
	nextVector3.x = ReadNextFloat();
	nextVector3.y = ReadNextFloat();
	nextVector3.z = ReadNextFloat();
}
Vector3 BinaryBufferParser::ReadNextVector3()
{
	if (!CanReadNextSizeofData(sizeof(Vector3)))
	{
		return Vector3(0.0f, 0.0f,0.0f);
	}
	Vector3 nextVector3;
	nextVector3.x = ReadNextFloat();
	nextVector3.y = ReadNextFloat();
	nextVector3.z = ReadNextFloat();
	return nextVector3;
}
void BinaryBufferParser::ReadNextVector4(Vector4& nextVector4)
{
	if (!CanReadNextSizeofData(sizeof(Vector4)))
	{
		return;
	}
	nextVector4.x = ReadNextFloat();
	nextVector4.y = ReadNextFloat();
	nextVector4.z = ReadNextFloat();
	nextVector4.w = ReadNextFloat();
}
Vector4 BinaryBufferParser::ReadNextVector4()
{
	if (!CanReadNextSizeofData(sizeof(Vector3)))
	{
		return Vector4(0.0f,0.0f,0.0f,0.0f);
	}
	Vector4 nextVector4;
	nextVector4.x = ReadNextFloat();
	nextVector4.y = ReadNextFloat();
	nextVector4.z = ReadNextFloat();
	nextVector4.w = ReadNextFloat();
	return nextVector4;
}
void BinaryBufferParser::ReadNextMatrix4x4(Matrix4x4& nextMatrix4x4)
{
	if (!CanReadNextSizeofData(sizeof(Matrix4x4)))
	{
		return;
	}
	nextMatrix4x4.m_iBasis = ReadNextVector4();
	nextMatrix4x4.m_jBasis = ReadNextVector4();
	nextMatrix4x4.m_kBasis = ReadNextVector4();
	nextMatrix4x4.m_translation = ReadNextVector4();
}
Matrix4x4 BinaryBufferParser::ReadNextMatrix4x4()
{
	if (!CanReadNextSizeofData(sizeof(Matrix4x4)))
	{
		Matrix4x4 I;
		I.MakeIdentity();
		return I;
	}
	Matrix4x4 nextMatrix4x4;
	nextMatrix4x4.m_iBasis = ReadNextVector4();
	nextMatrix4x4.m_jBasis = ReadNextVector4();
	nextMatrix4x4.m_kBasis = ReadNextVector4();
	nextMatrix4x4.m_translation = ReadNextVector4();
	return nextMatrix4x4;
}
//////////////////////////////////////////////////////////////////////////
bool BinaryBufferParser::DoReachEndOfData()
{
	if ((m_bufferStart + m_bufferSize) <= (m_nextByteToRead + 1))
	{
		return true;
	}
	else
		return false;
}

bool BinaryBufferParser::CanReadNextSizeofData(size_t size)
{
	if ((m_bufferStart + m_bufferSize) >= (m_nextByteToRead + size))
	{
		return true;
	}
	else
		return false;
}

RGBA BinaryBufferParser::ReadNextRGBA()
{
	RGBA nextRGBA;
	if (!CanReadNextSizeofData(4 * sizeof(unsigned char)))
	{
		return nextRGBA;
	}
	nextRGBA.R = ReadNextUnsignedChar();
	nextRGBA.G = ReadNextUnsignedChar();
	nextRGBA.B = ReadNextUnsignedChar();
	nextRGBA.A = ReadNextUnsignedChar();
	return nextRGBA;
}
bool BinaryBufferParser::ReadNextRGBA(RGBA& nextRGBA)
{
	if (!CanReadNextSizeofData(4*sizeof(unsigned char)))
	{
		return false;
	}
	nextRGBA.R = ReadNextUnsignedChar();
	nextRGBA.G = ReadNextUnsignedChar();
	nextRGBA.B = ReadNextUnsignedChar();
	nextRGBA.A = ReadNextUnsignedChar();
	return true;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool BinaryBufferParser::ReadNextBoneIndex(BoneIndex& nextBoneIndex)
{
	if (!CanReadNextSizeofData(4 * sizeof(unsigned char)))
	{
		return false;
	}
	nextBoneIndex.m_indexes[0] = ReadNextUnsignedChar();
	nextBoneIndex.m_indexes[1] = ReadNextUnsignedChar();
	nextBoneIndex.m_indexes[2] = ReadNextUnsignedChar();
	nextBoneIndex.m_indexes[3] = ReadNextUnsignedChar();
	return true;
}
///----------------------------------------------------------
///
///----------------------------------------------------------
BoneIndex BinaryBufferParser::ReadNextBoneIndex()
{
	BoneIndex nextBoneIndex;
	if (!CanReadNextSizeofData(4 * sizeof(unsigned char)))
	{
		return nextBoneIndex;
	}
	nextBoneIndex.m_indexes[0] = ReadNextUnsignedChar();
	nextBoneIndex.m_indexes[1] = ReadNextUnsignedChar();
	nextBoneIndex.m_indexes[2] = ReadNextUnsignedChar();
	nextBoneIndex.m_indexes[3] = ReadNextUnsignedChar();
	return nextBoneIndex;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

NTBVertex3D_PCT BinaryBufferParser::ReadNextNTB_Vert3D()
{
	NTBVertex3D_PCT nextVert;
	if (!CanReadNextSizeofData(sizeof(NTBVertex3D_PCT)))
	{
		return nextVert;
	}
	nextVert.m_position = ReadNextVector3();
	nextVert.m_color = ReadNextRGBA();
	nextVert.m_textureCoords = ReadNextVector2();
	nextVert.m_normal = ReadNextVector3();
	nextVert.m_tangent = ReadNextVector3();
	nextVert.m_biTangent = ReadNextVector3();
	return nextVert;
}
bool BinaryBufferParser::ReadNextNTB_Vert3D(NTBVertex3D_PCT& nextNTBVert)
{
	if (!CanReadNextSizeofData(sizeof(NTBVertex3D_PCT)))
	{
		return false;
	}
	nextNTBVert.m_position = ReadNextVector3();
	nextNTBVert.m_color = ReadNextRGBA();
	nextNTBVert.m_textureCoords = ReadNextVector2();
	nextNTBVert.m_normal = ReadNextVector3();
	nextNTBVert.m_tangent = ReadNextVector3();
	nextNTBVert.m_biTangent = ReadNextVector3();
	return true;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool BinaryBufferParser::ReadNextSkeletonVert(Vertex3D_Skeletal& nextSkeletonVert)
{
	if (!CanReadNextSizeofData(sizeof(Vertex3D_Skeletal)))
	{
		return false;
	}
	nextSkeletonVert.m_position = ReadNextVector3();
	nextSkeletonVert.m_color = ReadNextRGBA();
	nextSkeletonVert.m_textureCoords = ReadNextVector2();
	nextSkeletonVert.m_normal = ReadNextVector3();
	nextSkeletonVert.m_tangent = ReadNextVector3();
	nextSkeletonVert.m_biTangent = ReadNextVector3();
	nextSkeletonVert.m_boneIndex = ReadNextBoneIndex();
	nextSkeletonVert.m_boneWeights = ReadNextVector3();
	
	return true;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_Skeletal BinaryBufferParser::ReadNextSkeletonVert()
{
	Vertex3D_Skeletal nextSkeletonVert;
	if (!CanReadNextSizeofData(sizeof(Vertex3D_Skeletal)))
	{
		return nextSkeletonVert;
	}
	nextSkeletonVert.m_position = ReadNextVector3();
	nextSkeletonVert.m_color = ReadNextRGBA();
	nextSkeletonVert.m_textureCoords = ReadNextVector2();
	nextSkeletonVert.m_normal = ReadNextVector3();
	nextSkeletonVert.m_tangent = ReadNextVector3();
	nextSkeletonVert.m_biTangent = ReadNextVector3();
	nextSkeletonVert.m_boneIndex = ReadNextBoneIndex();
	nextSkeletonVert.m_boneWeights = ReadNextVector3();

	return nextSkeletonVert;
}