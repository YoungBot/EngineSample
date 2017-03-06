//==========================================================
//GLShader.hpp
//==========================================================
#pragma once

#ifndef _GLSHADER_HPP_
#define _GLSHADER_HPP_

#include <string>
#include "OpenGLRenderer.hpp"
#include "Engine/Utility/Utility.hpp"
#define OPENGL_CHECK_ERRORS

class GLShader
{
public:
	GLShader(){}
	GLShader(char const *vertFilePath, char const *fragFilePath)
	{
		m_gProgram = LoadProgram(vertFilePath, fragFilePath);
	}
	GLuint LoadProgram(char const *vertFilePath, char const *fragFilePath);
	GLuint LoadShader(char const *filename, GLenum shader_type);
	bool LinkProgram(GLuint programID, GLuint vertShader, GLuint fragShader);
	void FreeShader(GLuint shaderId);
	void GLCheckError(const char* fileName, int lineNum);
	bool CheckShaderStatus(GLuint shaderId, char const *fileName);
	bool CheckProgramStatus(GLuint programID);
	void FormatAndPrintLog(char const *filename, char const *log);
	GLuint m_gProgram;
};

#endif
