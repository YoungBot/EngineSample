//==========================================================
//GLMesh.hpp
//==========================================================
#pragma once

#ifndef _GLMESH_HPP_
#define _GLMESH_HPP_
#include "OpenGLRenderer.hpp"
#include "Engine/Utility/Utility.hpp"
#include "Engine/Utility/BinaryFileParser.hpp"
#define OPENGL_CHECK_ERRORS

class GLMesh
{
public:
	GLMesh();
	GLMesh(void const *vertexArray, size_t numVertexes);
	GLuint CreateVBO(void const *vertexArray, size_t numVertexes);
	GLuint CreateIBO(unsigned int* intIndex, size_t numInt);
	void SendVBOData(GLuint buffer_id, void const *vertexArray, size_t numBytes);
	void SendIBOData(GLuint ibo_id, unsigned int* intIndexArray, size_t numInts);
	void UpdateVBO(void const *buffer, size_t numBytes);
	//GLuint CreateVAO(GLuint program_id, GLuint buffer_id);
	//GLuint CreateNormalVAO(GLuint program_id, GLuint buffer_id);
	void GLCheckError(const char* fileName, int lineNum);
	bool ProgramBindAttribute(GLuint program_id, char const *name, GLint count, GLenum type, GLboolean normalize, GLsizei stride, GLsizei offset);
	void CreateBufferFromC23File(const std::string& filePath, const std::string& fourChars);
	GLuint m_vboID;
	GLuint m_iboID;
	size_t m_vboNumBytes;
	size_t m_iboNumIndexes;

};


#endif

