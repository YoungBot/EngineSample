//==========================================================
//Shader.cpp
//==========================================================
#include "Shader.hpp"
Shader::Shader()
{

}
Shader::~Shader()
{

}
Shader::Shader(char const *vertFilePath, char const *fragFilePath, char const *textureFilePath, Vertex3D_PCT* verts, size_t vertsSize)
{
	m_bufferSize = vertsSize;
	m_gProgram = LoadProgram(vertFilePath, fragFilePath);
	GLCheckError(__FILE__, __LINE__);
	m_gBuffer = CreateBuffer(verts, vertsSize*sizeof(Vertex3D_PCT));
	GLCheckError(__FILE__, __LINE__);
	m_gVAO = CreateVAO(m_gProgram, m_gBuffer);
	GLCheckError(__FILE__, __LINE__);
	m_gTex = Texture::CreateOrGetTexture(textureFilePath);
	GLCheckError(__FILE__, __LINE__);
	m_gTex2 = Texture::CreateOrGetTexture("Data/Images/brickNormalMap.png");
	GLCheckError(__FILE__, __LINE__);
	m_gSamp = CreateSampler(GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
	GLCheckError(__FILE__, __LINE__);
}
Shader::Shader(char const *vertFilePath, char const *fragFilePath, char const *textureFilePath,vert_t* verts, size_t vertsSize)
{
	m_bufferSize = vertsSize;
	m_gProgram = LoadProgram(vertFilePath, fragFilePath);
	GLCheckError(__FILE__, __LINE__);
	m_gBuffer = CreateBuffer(verts, vertsSize*sizeof(vert_t));
	GLCheckError(__FILE__, __LINE__);
	m_gVAO = CreateNormalVAO(m_gProgram, m_gBuffer);
	GLCheckError(__FILE__, __LINE__);
	m_gTex = Texture::CreateOrGetTexture(textureFilePath);
	GLCheckError(__FILE__, __LINE__);
	m_gTex2 = Texture::CreateOrGetTexture("Data/Images/testNormalMap.png");
	GLCheckError(__FILE__, __LINE__);
	m_gSamp = CreateSampler(GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
	GLCheckError(__FILE__, __LINE__);
}
//////////////////////////////////////////////////////////////////////////
void Shader::StartUp()
{
	
}
//////////////////////////////////////////////////////////////////////////
void Shader::Update(float deltaSecond)
{
	deltaSecond;
}
//////////////////////////////////////////////////////////////////////////
void Shader::GLCheckError(const char* fileName, int lineNum)
{
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
//////////////////////////////////////////////////////////////////////////
GLuint Shader::LoadProgram(char const *vertFilePath, char const *fragFilePath)
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
//////////////////////////////////////////////////////////////////////////
GLuint Shader::LoadShader(char const *fileName, GLenum shaderType)
{

	size_t source_length = 0;
	char* source = (char*)Utility::FileReadAll(fileName, &source_length);
	//may have bug here about unsigned char* and char*
	if (nullptr == source) {
		return NULL;
	}

	GLuint shaderID = glCreateShader(shaderType);
	if (NULL == shaderID) {
		return NULL;
	}

	// can take multiple strings - internally these will all be 
	// concantanated end-to-end
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
//////////////////////////////////////////////////////////////////////////
bool Shader::LinkProgram(GLuint programID, GLuint vertShader, GLuint fragShader)
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
//////////////////////////////////////////////////////////////////////////
bool Shader::CheckShaderStatus(GLuint shaderId, char const *fileName)
{
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
//////////////////////////////////////////////////////////////////////////
void Shader::FreeShader(GLuint shaderId)
{
	if (shaderId != NULL) {
		glDeleteShader(shaderId);
	}
}
//////////////////////////////////////////////////////////////////////////
bool Shader::CheckProgramStatus(GLuint programID)
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
//////////////////////////////////////////////////////////////////////////
void Shader::FormatAndPrintLog(char const *filename, char const *log)
{
	//ConsolePrintf("file name: %s, error %s", filename, log);
	MessageBoxA(NULL, filename, log, MB_OK);
}
//////////////////////////////////////////////////////////////////////////
GLuint Shader::CreateBuffer(void const *buffer, size_t size)
{
	GLuint buffer_id;
	glGenBuffers(1, &buffer_id);
	if (buffer_id == NULL) {
		return NULL;
	}

	if (buffer != nullptr) {
		CopyToBuffer(buffer_id, buffer, size);
	}

	return buffer_id;
}
//////////////////////////////////////////////////////////////////////////
void Shader::CopyToBuffer(GLuint buffer_id, void const *data, size_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	GLCheckError(__FILE__, __LINE__);

	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	GLCheckError(__FILE__, __LINE__);
}
//////////////////////////////////////////////////////////////////////////
void Shader::UpdateBuffer(void const *buffer, size_t size)
{
	if (m_gBuffer == NULL) {
		return;
	}

	if (buffer != nullptr) {
		CopyToBuffer(m_gBuffer, buffer, size);
		m_bufferSize = size;
	}
}
//////////////////////////////////////////////////////////////////////////
GLuint Shader::CreateVAO(GLuint program_id, GLuint buffer_id)
{
	GLuint vao_id;
	glGenVertexArrays(1, &vao_id);
	if (vao_id == NULL) {
		//ASSERT(0);
		return NULL;
	}
	GLint max_attribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_attribs);
	//Trace("class", "Max Vertex Attributes: %i", max_attribs);
	glBindVertexArray(vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

	ProgramBindAttribute(program_id, "inPosition", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D_PCT), offsetof(Vertex3D_PCT, m_position));
	ProgramBindAttribute(program_id, "inUV0", 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D_PCT), offsetof(Vertex3D_PCT, m_textureCoords));
	ProgramBindAttribute(program_id, "inColor", 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex3D_PCT), offsetof(Vertex3D_PCT, m_color));
	GLCheckError(__FILE__, __LINE__);

	return vao_id;
}
//////////////////////////////////////////////////////////////////////////
GLuint Shader::CreateNormalVAO(GLuint program_id, GLuint buffer_id)
{
	GLuint vao_id;
	glGenVertexArrays(1, &vao_id);
	if (vao_id == NULL) {
		//ASSERT(0);
		return NULL;
	}
	GLint max_attribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_attribs);
	//Trace("class", "Max Vertex Attributes: %i", max_attribs);
	glBindVertexArray(vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

	ProgramBindAttribute(program_id, "inPosition", 3, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, position));
	ProgramBindAttribute(program_id, "inUV0", 2, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, uv));
	ProgramBindAttribute(program_id, "inNormal", 3, GL_FLOAT, GL_TRUE, sizeof(vert_t), offsetof(vert_t, normal));
	GLCheckError(__FILE__, __LINE__);

	return vao_id;
}
//////////////////////////////////////////////////////////////////////////
GLuint Shader::CreateSampler(GLenum min_filter, GLenum mag_filter, GLenum u_wrap, GLenum v_wrap)
{
	GLuint sampler_id;
	glGenSamplers(1, &sampler_id);
	if (NULL == sampler_id) {
		return NULL;
	}

	glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, min_filter);			// Default: GL_NEAREST_MIPMAP_LINEAR
	glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, mag_filter);			// Default: GL_LINEAR
	glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, u_wrap);					// Default: GL_REPEAT
	glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, v_wrap);					// Default: GL_REPEAT

	return sampler_id;
}
//////////////////////////////////////////////////////////////////////////
bool Shader::ProgramBindAttribute(GLuint program_id, char const *name, GLint count, GLenum type, GLboolean normalize, GLsizei stride, GLsizei offset)
{
	GLint loc = glGetAttribLocation(program_id, name);
	GLCheckError(__FILE__, __LINE__);
	if (loc < 0)
	{
		return false;
	}
	glEnableVertexAttribArray(loc);
	GLCheckError(__FILE__, __LINE__);

	glVertexAttribPointer(loc, count, type, normalize, stride, (GLvoid*)offset);
	GLCheckError(__FILE__, __LINE__);

	return true;
}
//////////////////////////////////////////////////////////////////////////
bool Shader::ProgramBindSamplerIndex(GLuint prog_id, char const *name, GLint idx)
{
	GLint loc = glGetUniformLocation(prog_id, name);
	if (loc < 0) {
		// didn't exist
		return false;
	}
	glUniform1iv(loc, 1, (GLint*)&idx);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool Shader::ProgramBindMatrix(GLuint prog_id, char const *name, Matrix4x4 const &mat)
{
	GLint loc = glGetUniformLocation(prog_id, name);
	if (loc < 0) {
		// didn't exist
		return false;
	}

	GLuint index;
	glGetUniformIndices(prog_id, 1, &name, &index);
	if (index >= 0) {
		GLint count;
		GLenum type;
		glGetActiveUniform(prog_id, index, 0, NULL, &count, &type, NULL);
		//ASSERT(type == GL_FLOAT_MAT4);
	}
	glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat*)&mat);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool Shader::ProgramBindFloat(GLuint prog_id, char const *name, float const &val)
{
	GLint loc = glGetUniformLocation(prog_id, name);
	if (loc < 0) {
		// didn't exist
		return false;
	}
	GLuint index;
	glGetUniformIndices(prog_id, 1, &name, &index);
	if (index >= 0) {
		GLint count;
		GLenum type;
		glGetActiveUniform(prog_id, index, 0, NULL, &count, &type, NULL);
		//ASSERT(type == GL_FLOAT_MAT4);
	}
	glUniform1fv(loc, 1, &val);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool Shader::ProgramBindVector3(GLuint prog_id, char const *name, Vector3 const &vec3)
{
	GLint loc = glGetUniformLocation(prog_id, name);
	if (loc < 0) {
		// didn't exist
		return false;
	}
	GLuint index;
	glGetUniformIndices(prog_id, 1, &name, &index);
	if (index >= 0) {
		GLint count;
		GLenum type;
		glGetActiveUniform(prog_id, index, 0, NULL, &count, &type, NULL);
		//ASSERT(type == GL_FLOAT_MAT4);
	}
	glUniform3fv(loc, 1, vec3.GetAsFloatArray());
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool Shader::ProgramBindVector4(GLuint prog_id, char const *name, Vector4 const &vec4)
{
	GLint loc = glGetUniformLocation(prog_id, name);
	if (loc < 0) {
		// didn't exist
		return false;
	}
	GLuint index;
	glGetUniformIndices(prog_id, 1, &name, &index);
	if (index >= 0) {
		GLint count;
		GLenum type;
		glGetActiveUniform(prog_id, index, 0, NULL, &count, &type, NULL);
		//ASSERT(type == GL_FLOAT_MAT4);
	}
	glUniform4fv(loc, 1, vec4.GetAsFloatArray());
	return true;
}
//////////////////////////////////////////////////////////////////////////
void Shader::DrawShader(int arraySize,float deltaSecond, Matrix4x4 matrix1, Matrix4x4 matrix2)
{
	arraySize;
	Matrix4x4 mat1;
	Matrix4x4 mat2;
	mat1 = matrix1;
	mat2 = matrix2;
	static float totalTime = 0;
	totalTime += deltaSecond;
	GLCheckError(__FILE__, __LINE__);
	ProgramBind(m_gProgram);
	GLCheckError(__FILE__, __LINE__);

	glBindVertexArray(m_gBuffer);

	GLint textureIndex = 0;

	ProgramBindMatrix(m_gBuffer, "gProj", mat1);
	ProgramBindMatrix(m_gBuffer, "gView", mat2);
	ProgramBindFloat(m_gBuffer, "gTime", totalTime);
	ProgramBindSamplerIndex(m_gBuffer, "gTexture", textureIndex);

	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, m_gTex->GetPlatformHandle());
	glBindSampler(textureIndex, m_gSamp);

	glDrawArrays(GL_TRIANGLES, 0, m_bufferSize);
	glBindVertexArray(NULL);
	glUseProgram(NULL);
	GLCheckError(__FILE__, __LINE__);

}
//////////////////////////////////////////////////////////////////////////
void Shader::DrawLightShader(int arraySize,Vector3& cameraPos, float deltaSecond, Matrix4x4 matrix1, Matrix4x4 matrix2)
{
	arraySize;
	Matrix4x4 mat1;
	Matrix4x4 mat2;
	mat1 = matrix1;
	mat2 = matrix2;
	static float totalTime = 0;
	totalTime += deltaSecond;
	ProgramBind(m_gProgram);
	GLCheckError(__FILE__, __LINE__);
	glBindVertexArray(m_gBuffer);
	Vector3 cam_position = cameraPos;
	float light_power = 1.0f;
	Vector4 ambient_light(1.0f, 1.0f, 1.0f, 0.05f);
	Vector4 light_color(1.0f, 1.0f, 1.0f, light_power);
	GLint textureIndex = 0;
	ProgramBindSamplerIndex(m_gBuffer, "gTexDiffuse", textureIndex);
	ProgramBindSamplerIndex(m_gBuffer, "gTexNormal", textureIndex+1);
	ProgramBindMatrix(m_gBuffer, "gProj", mat1);
	ProgramBindMatrix(m_gBuffer, "gView", mat2);
	ProgramBindVector4(m_gBuffer, "gAmbientLight", ambient_light);
	ProgramBindVector4(m_gBuffer, "gLightColor", light_color);
	ProgramBindVector3(m_gBuffer, "gLightPosition", cam_position);

	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, m_gTex->GetPlatformHandle());
	glBindSampler(textureIndex, m_gSamp);
	textureIndex++;
	
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, m_gTex2->GetPlatformHandle());
	glBindSampler(textureIndex, m_gSamp);

	glDrawArrays(GL_TRIANGLES, 0, m_bufferSize);
	glBindVertexArray(NULL);
	glUseProgram(NULL);
	GLCheckError(__FILE__, __LINE__);
}
void Shader::ProgramBind(GLuint prog_id)
{
	glUseProgram(prog_id);
}
//////////////////////////////////////////////////////////////////////////
