//==========================================================
//GLShader.cpp
//==========================================================

#include "GLShader.hpp"
#include <sstream>
#include "Engine/Console/Console.hpp"
void GLShader::FreeShader(GLuint shaderId)
{
	if (shaderId != NULL) {
		glDeleteShader(shaderId);
	}
}
GLuint GLShader::LoadProgram(char const *vertFilePath, char const *fragFilePath)
{
	GLuint program_id = glCreateProgram();
	if (program_id == NULL) {
		return NULL;
	}
	GLuint vert_shader = LoadShader(vertFilePath, GL_VERTEX_SHADER);
	GLCheckError(__FILE__, __LINE__);
	GLuint frag_shader = LoadShader(fragFilePath, GL_FRAGMENT_SHADER);
	GLCheckError(__FILE__, __LINE__);
	if (!LinkProgram(program_id, vert_shader, frag_shader))
	{
		glDeleteProgram(program_id);
		program_id = NULL;
	}
	FreeShader(vert_shader);
	GLCheckError(__FILE__, __LINE__);

	FreeShader(frag_shader);
	GLCheckError(__FILE__, __LINE__);

	return program_id;
}
GLuint GLShader::LoadShader(char const *fileName, GLenum shaderType)
{
	size_t source_length = 0;
	char* source = (char*)Utility::FileReadAll(fileName, &source_length);
	if (nullptr == source) {
		return NULL;
	}
	GLuint shaderID = glCreateShader(shaderType);
	if (NULL == shaderID) {
		return NULL;
	}
	GLint len = (GLint)(source_length);
	glShaderSource(shaderID, 1, &source, &len);
	free(source);

	glCompileShader(shaderID);
	GLCheckError(__FILE__, __LINE__);

	if (CheckShaderStatus(shaderID, fileName)) {
		return shaderID;
	}
	else {
		glDeleteShader(shaderID);
		return NULL;
	}
}
void GLShader::GLCheckError(const char* fileName, int lineNum)
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

bool GLShader::LinkProgram(GLuint programID, GLuint vertShader, GLuint fragShader)
{
	if ((vertShader == NULL) || (fragShader == NULL) || (programID == NULL))
	{
		return false;
	}
	glAttachShader(programID, vertShader);
	glAttachShader(programID, fragShader);
	GLCheckError(__FILE__, __LINE__);
	bool save_binary = false;
	if (true == save_binary)
	{
		glProgramParameteri(programID, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);
		GLCheckError(__FILE__, __LINE__);
	}
	glLinkProgram(programID);
	GLCheckError(__FILE__, __LINE__);
	glDetachShader(programID, vertShader);
	glDetachShader(programID, fragShader);
	GLCheckError(__FILE__, __LINE__);

	if (!CheckProgramStatus(programID))
	{
		return false;
	}

	return true;
}

bool GLShader::CheckShaderStatus(GLuint shaderId, char const *fileName)
{
	fileName;
	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		// failed to compile
		GLint log_len = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &log_len);

		if (log_len > 0) {
			char *log = (char*)malloc(log_len);

			glGetShaderInfoLog(shaderId, log_len, &log_len, log);
			FormatAndPrintLog(fileName, log);
			//////////////////////////////////////////////////////////////////////////
			free(log);
		}
		else {
			// Failed, unknown reason - shouldn't happen
			// make note of this method
			GLCheckError(__FILE__, __LINE__);
		}

		return false;
	}

	return true;
}
bool GLShader::CheckProgramStatus(GLuint programID)
{
	GLint link_status;
	glGetProgramiv(programID, GL_LINK_STATUS, &link_status);

	if (link_status == GL_FALSE)
	{
		GLint log_length = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &log_length);
		if (log_length > 0)
		{
			char *buffer = (char*)malloc(log_length);
			glGetProgramInfoLog(programID, sizeof(buffer), &log_length, (GLchar*)buffer);

			//MessageBoxA("class", "Failed to link;\n%s", buffer);
			free(buffer);
		}
		else
		{
			GLCheckError(__FILE__, __LINE__);
		}

		return false;
	}

	return true;
}
void GLShader::FormatAndPrintLog(char const *filename, char const *log)
{
	ConsolePrintf("file name: %s, error %s",filename, log);
	MessageBoxA(NULL, filename, log, MB_OK);
}