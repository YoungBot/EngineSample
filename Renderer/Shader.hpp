//==========================================================
//Shader.hpp
//==========================================================
#include "Engine/Renderer/Texture.hpp"
#include "OpenGLRenderer.hpp"
#include "Engine/Console/Console.hpp"
#include "Engine/Utility/Utility.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#define OPENGL_CHECK_ERRORS

struct vert_t
{
	Vector3  position;
	Vector3  normal;
	Vector2  uv;

	vert_t(Vector3 p, Vector2 t, Vector3 n)
		: position(p), uv(t), normal(n) {}
};

class Shader
{
public:
	Shader();
	Shader(char const *vertFilePath, char const *fragFilePath, char const *textureFilePath,Vertex3D_PCT* verts,size_t vertsSize);
	Shader(char const *vertFilePath, char const *fragFilePath, char const *textureFilePath, vert_t* verts, size_t vertsSize);
	~Shader();
	void StartUp();
	void Update(float deltaSecond);
	void GLCheckError(const char* fileName, int lineNum);
	GLuint LoadProgram(char const *vertFilePath, char const *fragFilePath);
	GLuint LoadShader(char const *filename, GLenum shader_type);
	bool LinkProgram(GLuint programID, GLuint vertShader, GLuint fragShader);
	bool CheckShaderStatus(GLuint shaderId, char const *fileName);
	static void FreeShader(GLuint shaderId);
	bool CheckProgramStatus(GLuint programID);
	static void FormatAndPrintLog(char const *filename, char const *log);


	GLuint CreateBuffer(void const *buffer, size_t size);
	void CopyToBuffer(GLuint buffer_id, void const *data, size_t size);
	void UpdateBuffer(void const *buffer, size_t size);
	
	GLuint CreateNormalVAO(GLuint program_id, GLuint buffer_id);
	GLuint CreateSampler(GLenum min_filter, GLenum mag_filter, GLenum u_wrap, GLenum v_wrap);

	
	bool ProgramBindAttribute(GLuint program_id, char const *name, GLint count, GLenum type, GLboolean normalize, GLsizei stride, GLsizei offset);
	GLuint CreateVAO(GLuint program_id, GLuint buffer_id);
	bool ProgramBindMatrix(GLuint prog_id, char const *name, Matrix4x4 const &mat);
	bool ProgramBindFloat(GLuint prog_id, char const *name, float const &val);
	bool ProgramBindVector3(GLuint prog_id, char const *name, Vector3 const &vec3);
	bool ProgramBindVector4(GLuint prog_id, char const *name, Vector4 const &vec4);
	bool ProgramBindSamplerIndex(GLuint prog_id, char const *name, GLint idx);
	void DrawShader(int arraySize, float deltaSecond, Matrix4x4 matrix1, Matrix4x4 matrix2);
	void DrawLightShader(int arraySize,Vector3& cameraPos, float deltaSecond, Matrix4x4 matrix1, Matrix4x4 matrix2);
	void ProgramBind(GLuint prog_id);
private:
	GLuint m_gBuffer;
	size_t m_bufferSize;
	GLuint m_gProgram;
	GLuint m_gVAO;
	Texture* m_gTex; 
	Texture* m_gTex2;
	GLuint m_gSamp;
};

