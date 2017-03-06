//==========================================================
//BinaryBufferParser.hpp
//==========================================================
#pragma once

#ifndef _BINARY_BUFFER_PARSER_
#define _BINARY_BUFFER_PARSER_

#include <vector>
#include <string>
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector4.hpp"
#include "Engine/Math/Matrix4x4.hpp"
#include "Engine/Renderer/OpenGLRenderer.hpp"


class BinaryBufferParser
{
public:
	BinaryBufferParser();
	BinaryBufferParser(const unsigned char* buffer, size_t size);
	BinaryBufferParser(const std::vector< unsigned char >& bytes);
	~BinaryBufferParser();
	//////////////////////////////////////////////////////////////////////////
	void ReadNextInt(int& nextInt);
	int ReadNextInt();
	void ReadNextShort(short& nextShort);
	short ReadNextShort();
	void ReadNextChar(char& nextChar);
	char ReadNextChar();
	void ReadNextUnsignedChar(unsigned char nextChar);
	unsigned char ReadNextUnsignedChar();
	void ReadNextUnsignedShort(unsigned short nextShort);
	unsigned short ReadNextUnsignedShort();
	void ReadNextUnsignedInt(unsigned int nextInt);
	unsigned int ReadNextUnsignedInt();
	void ReadNextFloat(float& nextFloat);
	float ReadNextFloat();
	void ReadNextDouble(double& nextDouble);
	double ReadNextDouble();
	void ReadNextBool(bool& nextBool);
	bool ReadNextBool();
	void ReadNextString(std::string& nextString,int stringSize);
	std::string ReadNextString();
	std::string ReadNextString(int stringSize);
	void ReadNextVector2(Vector2& nextVector2);
	Vector2 ReadNextVector2();
	void ReadNextVector3(Vector3& nextVector3);
	Vector3 ReadNextVector3();
	void ReadNextVector4(Vector4& nextVector4);
	Vector4 ReadNextVector4();
	void ReadNextMatrix4x4(Matrix4x4& nextMatrix4x4);
	Matrix4x4 ReadNextMatrix4x4();
	RGBA ReadNextRGBA();
	bool ReadNextRGBA(RGBA& nextRGBA);
	BoneIndex ReadNextBoneIndex();
	bool ReadNextBoneIndex(BoneIndex& nextBoneIndex);
	NTBVertex3D_PCT ReadNextNTB_Vert3D();
	bool ReadNextNTB_Vert3D(NTBVertex3D_PCT& nextNTBVert);
	Vertex3D_Skeletal ReadNextSkeletonVert();
	bool ReadNextSkeletonVert(Vertex3D_Skeletal& nextSkeletonVert);
	bool DoReachEndOfData();
	bool CanReadNextSizeofData(size_t size);
	
	//////////////////////////////////////////////////////////////////////////


	unsigned char* m_bufferStart;
	size_t m_bufferSize;
	unsigned char* m_nextByteToRead;
};




#endif