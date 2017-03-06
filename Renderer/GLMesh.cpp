//==========================================================
//GLMesh.cpp
//==========================================================
#include "GLMesh.hpp"
#include <sstream>
#include "Engine/Console/Console.hpp"
GLMesh::GLMesh()
	: m_vboID(0)
	, m_iboID(0)
	, m_iboNumIndexes(0)
	, m_vboNumBytes(0)
{
	CreateVBO(nullptr, 6 * sizeof(Vertex3D_PCT));
}
GLMesh::GLMesh(void const *vertexArray, size_t size) 
	: m_vboID(0)
	, m_iboID( 0 )
	, m_iboNumIndexes( 0 )
	, m_vboNumBytes( 0 )
{
	CreateVBO(vertexArray, size);
	
}

void GLMesh::GLCheckError(const char* fileName, int lineNum)
{
	fileName;
	lineNum;
#if defined(OPENGL_CHECK_ERRORS)
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::stringstream out;
		out << lineNum;
		std::string header = "Error:" + ConsolePrintf("0x%04x\n", error) + "at" + out.str();
		std::string mesage1 = fileName;

		MessageBoxA(NULL, mesage1.c_str(), header.c_str(), MB_OK);
	}

#endif
}
GLuint GLMesh::CreateVBO(void const *buffer, size_t numBytes)
{
	GLuint buffer_id;
	glGenBuffers(1, &buffer_id);
	if (buffer_id == NULL) {
		return NULL;
	}

	if (buffer != nullptr) {
		SendVBOData(buffer_id, buffer, numBytes);
	}
	m_vboID = buffer_id;
	m_vboNumBytes = numBytes;
	return m_vboID;
}
//////////////////////////////////////////////////////////////////////////
GLuint GLMesh::CreateIBO(unsigned int* intIndexArray, size_t numInts)
{
	GLuint ibo_id;
	glGenBuffers(1, &ibo_id);
	if (ibo_id == NULL) {
		return NULL;
	}

	if (intIndexArray != nullptr) {
		SendIBOData(ibo_id, intIndexArray, numInts);
	}
	m_iboID = ibo_id;
	m_iboNumIndexes = numInts;
	return m_iboID;
}
//////////////////////////////////////////////////////////////////////////
void GLMesh::SendIBOData(GLuint ibo_id, unsigned int* intIndexArray, size_t numInts)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , ibo_id);//gl_element_array_buffer
	GLCheckError(__FILE__, __LINE__);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numInts, intIndexArray, GL_STATIC_DRAW);//gl_element_array_buffer
	GLCheckError(__FILE__, __LINE__);
}
//////////////////////////////////////////////////////////////////////////
void GLMesh::SendVBOData(GLuint buffer_id, void const *vertexArray, size_t numBytes)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);//gl_element_array_buffer
	GLCheckError(__FILE__, __LINE__);

	glBufferData(GL_ARRAY_BUFFER, numBytes, vertexArray, GL_STATIC_DRAW);//gl_element_array_buffer
	GLCheckError(__FILE__, __LINE__);
}
//////////////////////////////////////////////////////////////////////////
void GLMesh::UpdateVBO(void const *vertexArray, size_t numBytes)
{
	if (m_vboID == NULL) {
		return;
	}

	if (vertexArray != nullptr) {
		SendVBOData(m_vboID, vertexArray, numBytes);
		m_vboNumBytes = numBytes;
	}
}
///------------------------------------------------------
///
///------------------------------------------------------
void GLMesh::CreateBufferFromC23File(const std::string& filePath, const std::string& fourChars)
{
	BinaryFileParser modelParser(filePath);
	std::string nextFourChars = modelParser.ReadNextString(4);

	if (!Utility::TestFourChars((unsigned char*)nextFourChars.data(), fourChars))
	{
		return ;
	}
	unsigned char subType;
	subType = modelParser.ReadNextUnsignedChar();
	unsigned char version = modelParser.ReadNextChar();
	std::string comments = modelParser.ReadNextString();
	version;
	//////////////////////////////////////////////////////////////////////////
	if (subType == 1 || subType == 2)
	{	
	unsigned int vertsNum = modelParser.ReadNextUnsignedInt();
	//qNTBVertex3D_PCT* vertexArray = new NTBVertex3D_PCT[vertsNum];
	NTBVertex3D_PCT* vertexArray = new NTBVertex3D_PCT[vertsNum];
	for (unsigned int i = 0; i < vertsNum; i++)
	{
		NTBVertex3D_PCT newVert;
		newVert = modelParser.ReadNextNTB_Vert3D();
		vertexArray[i] = newVert;
	}
	CreateVBO(vertexArray, vertsNum*sizeof(NTBVertex3D_PCT));
	unsigned int intIndexNum = modelParser.ReadNextUnsignedInt();
	unsigned int* intIndex = new unsigned int[intIndexNum];
	for (unsigned int i = 0; i < intIndexNum;i++)
	{
		intIndex[i] = modelParser.ReadNextUnsignedInt();
	}

	CreateIBO(intIndex, intIndexNum*4);
	return;
	}
	//////////////////////////////////////////////////////////////////////////
	if (subType == 4)
	{
		unsigned int vertsNum = modelParser.ReadNextUnsignedInt();
		//qNTBVertex3D_PCT* vertexArray = new NTBVertex3D_PCT[vertsNum];
		Vertex3D_Skeletal* vertexArray = new Vertex3D_Skeletal[vertsNum];
		vertexArray = new Vertex3D_Skeletal[vertsNum];
		for (unsigned int i = 0; i < vertsNum; i++)
		{
			Vertex3D_Skeletal newVert;
			newVert = modelParser.ReadNextSkeletonVert();
			vertexArray[i] = newVert;
		}
		CreateVBO(vertexArray, vertsNum*sizeof(Vertex3D_Skeletal));
		unsigned int intIndexNum = modelParser.ReadNextUnsignedInt();
		unsigned int* intIndex = new unsigned int[intIndexNum];
		for (unsigned int i = 0; i < intIndexNum; i++)
		{
			intIndex[i] = modelParser.ReadNextUnsignedInt();
		}

		CreateIBO(intIndex, intIndexNum * 4);
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	//newVert.
}