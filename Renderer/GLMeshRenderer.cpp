//==========================================================
//GLMeshRenderer.cpp
//==========================================================

#include "GLMeshRenderer.hpp"
#include <sstream>
#include "Engine/Console/Console.hpp"
GLMeshRenderer::GLMeshRenderer(VAO_TYPE type)
{
	m_mesh = GLMesh();
	m_material = GLMaterial();
	ChangeVAOType(type);
}
GLMeshRenderer::GLMeshRenderer(GLMesh mesh, GLMaterial material)
{
	m_mesh = mesh;
	m_material = material;
	CreateVAO(m_material.m_program.m_gProgram, m_mesh.m_vboID);
}


GLMeshRenderer::GLMeshRenderer(GLMesh mesh, GLMaterial material, VAO_TYPE type)
{
	m_mesh = mesh;
	m_material = material;
	ChangeVAOType(type);
}

GLuint GLMeshRenderer::CreateVAO(GLuint program_id, GLuint buffer_id)
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

	ProgramBindAttribute(program_id, "inPosition", 3, GL_FLOAT, GL_FALSE, sizeof(NTBVertex3D_PCT), offsetof(NTBVertex3D_PCT, m_position));
	ProgramBindAttribute(program_id, "inUV0", 2, GL_FLOAT, GL_FALSE, sizeof(NTBVertex3D_PCT), offsetof(NTBVertex3D_PCT, m_textureCoords));
	ProgramBindAttribute(program_id, "inNormal", 3, GL_FLOAT, GL_TRUE, sizeof(NTBVertex3D_PCT), offsetof(NTBVertex3D_PCT, m_normal));
	ProgramBindAttribute(program_id, "inTangent", 3, GL_FLOAT, GL_TRUE, sizeof(NTBVertex3D_PCT), offsetof(NTBVertex3D_PCT, m_tangent));
	ProgramBindAttribute(program_id, "inBiTangent", 3, GL_FLOAT, GL_TRUE, sizeof(NTBVertex3D_PCT), offsetof(NTBVertex3D_PCT, m_biTangent));
	ProgramBindAttribute(program_id, "inColor", 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(NTBVertex3D_PCT), offsetof(NTBVertex3D_PCT, m_color));

	GLCheckError(__FILE__, __LINE__);
	m_VAO = vao_id;
	return vao_id;
}

GLuint GLMeshRenderer::CreatePCTVAO(GLuint program_id, GLuint buffer_id)
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
	m_VAO = vao_id;
	return vao_id;
}

///----------------------------------------------------------
///
///----------------------------------------------------------

GLuint GLMeshRenderer::ChangeVAOType(VAO_TYPE type)
{
	switch (type)
	{
	case VAO_PCTNTB:
		return CreateVAO(m_material.m_program.m_gProgram, m_mesh.m_vboID);
	case VAO_PCT:
		return CreatePCTVAO(m_material.m_program.m_gProgram, m_mesh.m_vboID);
	default:
		return 0;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void GLMeshRenderer::GLCheckError(const char* fileName, int lineNum)
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

void GLMeshRenderer::DrawLightShader(int arraySize, float deltaSecond, Matrix4x4 perspectiveMatrix, Matrix4x4 viewMatrix,Matrix4x4 modelMatrix,Vector3 lPosition,Vector3 cameraPosition)
{
	//////////////////////////////////////////////////////////////////////////
	arraySize;
	static float totalTime = 0;
	totalTime += deltaSecond;
	glUseProgram(m_material.m_program.m_gProgram);
	GLCheckError(__FILE__, __LINE__);
	glBindVertexArray(m_VAO);
	Vector3 cam_position = cameraPosition;
	Vector3 lightPosition = lPosition;
	float light_power = 2.1f;
	Vector4 ambient_light(1.0f, 1.0f, 1.0f, 0.05f);
	Vector4 light_color(1.0f, 1.0f, 1.0f, light_power);
	GLint textureIndex = 0;
	GLuint m_gBuffer = m_material.m_program.m_gProgram;
	ProgramBindSamplerIndex(m_gBuffer, "gTexDiffuse", textureIndex);
	ProgramBindSamplerIndex(m_gBuffer, "gTexNormal", textureIndex+1);
	ProgramBindSamplerIndex(m_gBuffer, "gTexSpecular", textureIndex + 2);
	ProgramBindSamplerIndex(m_gBuffer, "gTexEmissive", textureIndex + 3);
	ProgramBindMatrix(m_gBuffer, "gProj", perspectiveMatrix);
	ProgramBindMatrix(m_gBuffer, "gView", viewMatrix);
	ProgramBindMatrix(m_gBuffer, "gModel", modelMatrix);
	ProgramBindVector4(m_gBuffer, "gAmbientLight", ambient_light);
	ProgramBindVector4(m_gBuffer, "gLightColor", light_color);
	ProgramBindVector3(m_gBuffer, "gLightPosition", lightPosition);
	ProgramBindVector3(m_gBuffer, "gCameraPosition", cam_position);
	
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexDiffuse->GetPlatformHandle());
	textureIndex++;
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexNormal->GetPlatformHandle());
	textureIndex++;
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexSpecular->GetPlatformHandle());
	textureIndex++;
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexEmissive->GetPlatformHandle());
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, m_mesh.m_vboNumBytes);
	glBindVertexArray(NULL);
	glUseProgram(NULL);
	GLCheckError(__FILE__, __LINE__);

}
//////////////////////////////////////////////////////////////////////////
void GLMeshRenderer::DrawLightModel(int arraySize, float deltaSecond, Matrix4x4 perspectiveMatrix, Matrix4x4 viewMatrix, Matrix4x4 modelMatrix, Vector3 lPosition, Vector3 cameraPosition)
{
	//////////////////////////////////////////////////////////////////////////
	arraySize;
	static float totalTime = 0;
	totalTime += deltaSecond;
	glUseProgram(m_material.m_program.m_gProgram);
	GLCheckError(__FILE__, __LINE__);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh.m_iboID);
	Vector3 cam_position = cameraPosition;
	Vector3 lightPosition = lPosition;
	float light_power = 10000.1f;
	Vector4 ambient_light(1.0f, 1.0f, 1.0f, 0.05f);
	Vector4 light_color(1.0f, 1.0f, 1.0f, light_power);
	GLint textureIndex = 0;
	GLuint m_gBuffer = m_material.m_program.m_gProgram;
	ProgramBindSamplerIndex(m_gBuffer, "gTexDiffuse", textureIndex);
	ProgramBindSamplerIndex(m_gBuffer, "gTexNormal", textureIndex + 1);
	ProgramBindSamplerIndex(m_gBuffer, "gTexSpecGlossEmit", textureIndex + 2);
	ProgramBindMatrix(m_gBuffer, "gProj", perspectiveMatrix);
	ProgramBindMatrix(m_gBuffer, "gView", viewMatrix);
	ProgramBindMatrix(m_gBuffer, "gModel", modelMatrix);
	ProgramBindVector4(m_gBuffer, "gAmbientLight", ambient_light);
	ProgramBindVector4(m_gBuffer, "gLightColor", light_color);
	ProgramBindVector3(m_gBuffer, "gLightPosition", lightPosition);
	ProgramBindVector3(m_gBuffer, "gCameraPosition", cam_position);

	if (m_material.m_sampler.gTexDiffuse == nullptr)
	{
		unsigned char defaultWhiteTexel[3] = { 255, 255, 255 };
		m_material.m_sampler.gTexDiffuse = Texture::CreateMissingTexture("DefaultDiffuse", defaultWhiteTexel, Vector2(1.0f, 1.0f), 3);
	}
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexDiffuse->GetPlatformHandle());
	textureIndex++;

	if (m_material.m_sampler.gTexNormal == nullptr)
	{
		unsigned char defaultBlueTexel[3] = { 127, 127, 255 };
		m_material.m_sampler.gTexNormal = Texture::CreateMissingTexture("DefaultNormal", defaultBlueTexel, Vector2(1.0f, 1.0f), 3);
	}
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexNormal->GetPlatformHandle());
	textureIndex++;

	if (m_material.m_sampler.gTexSpecGlossEmit == nullptr)
	{
		unsigned char defaultYellowTexel[3] = { 127, 127, 0 };
		m_material.m_sampler.gTexSpecGlossEmit = Texture::CreateMissingTexture("DefaultSpecGlossEmit", defaultYellowTexel, Vector2(1.0f, 1.0f), 3);
	}
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexSpecGlossEmit->GetPlatformHandle());

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDrawArrays(GL_TRIANGLES, 0, m_mesh.m_vboNumBytes);
	glDrawElements(GL_TRIANGLES,m_mesh.m_iboNumIndexes , GL_UNSIGNED_INT,(void*)0 );
	glBindVertexArray(NULL);
	glUseProgram(NULL);
	GLCheckError(__FILE__, __LINE__);

}
//////////////////////////////////////////////////////////////////////////
bool GLMeshRenderer::ProgramBindAttribute(GLuint program_id, char const *name, GLint count, GLenum type, GLboolean normalize, GLsizei stride, GLsizei offset)
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

bool GLMeshRenderer::ProgramBindSamplerIndex(GLuint prog_id, char const *name, GLint idx)
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
bool GLMeshRenderer::ProgramBindMatrix(GLuint prog_id, char const *name, Matrix4x4 const &mat)
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
bool GLMeshRenderer::ProgramBindInt(GLuint prog_id, char const *name, int const &val)
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
	glUniform1iv(loc, 1, &val);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool GLMeshRenderer::ProgramBindFloat(GLuint prog_id, char const *name, float const &val)
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
bool GLMeshRenderer::ProgramBindFloatArray(GLuint prog_id, char const *name, float* const val,int count)
{
	GLint loc = glGetUniformLocation(prog_id, name);
	if (loc < 0) {
		// didn't exist
		return false;
	}
	GLuint index;
	glGetUniformIndices(prog_id, 1, &name, &index);
	if (index >= 0) {
		GLint counter;
		GLenum type;
		glGetActiveUniform(prog_id, index, 0, NULL, &counter, &type, NULL);
		//ASSERT(type == GL_FLOAT_MAT4);
	}
	glUniform1fv(loc, count, val);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool GLMeshRenderer::ProgramBindVector3(GLuint prog_id, char const *name, Vector3 const &vec3)
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
bool GLMeshRenderer::ProgramBindVector3Array(GLuint prog_id, char const *name, Vector3* const vec3,int count)
{
	GLint loc = glGetUniformLocation(prog_id, name);
	if (loc < 0) {
		// didn't exist
		return false;
	}
	GLuint index;
	glGetUniformIndices(prog_id, 1, &name, &index);
	if (index >= 0) {
		GLint counter;
		GLenum type;
		glGetActiveUniform(prog_id, index, 0, NULL, &counter, &type, NULL);
		//ASSERT(type == GL_FLOAT_MAT4);
	}
	glUniform3fv(loc, count, (float*)vec3);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool GLMeshRenderer::ProgramBindVector4(GLuint prog_id, char const *name, Vector4 const &vec4)
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
bool GLMeshRenderer::ProgramBindVector4Array(GLuint prog_id, char const *name, Vector4* const vec4,int count)
{
	GLint loc = glGetUniformLocation(prog_id, name);
	if (loc < 0) {
		// didn't exist
		return false;
	}
	GLuint index;
	glGetUniformIndices(prog_id, 1, &name, &index);
	if (index >= 0) {
		GLint counter;
		GLenum type;
		glGetActiveUniform(prog_id, index, 0, NULL, &counter, &type, NULL);
		//ASSERT(type == GL_FLOAT_MAT4);
	}
	glUniform4fv(loc, count, (float*)vec4);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool GLMeshRenderer::ProgramBindTexture(GLint textureID, unsigned int textureHandle)
{
	glActiveTexture(GL_TEXTURE0 + textureID);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glBindSampler(textureID, m_material.m_sampler.m_samplerID);
	return true;
}

void GLMeshRenderer::DrawShader(int arraySize, float deltaSecond, const Matrix4x4& matrix1, const Matrix4x4& matrix2)
{
	arraySize;

	static float totalTime = 0;
	totalTime += deltaSecond;
	GLCheckError(__FILE__, __LINE__);
	glUseProgram(m_material.m_program.m_gProgram);
	GLCheckError(__FILE__, __LINE__);

	glBindVertexArray(m_VAO);
	
	GLint textureIndex = 0;
	GLuint m_gBuffer = m_material.m_program.m_gProgram;
	ProgramBindMatrix(m_gBuffer, "gProj", matrix1);
	ProgramBindMatrix(m_gBuffer, "gView", matrix2);
	ProgramBindFloat(m_gBuffer, "gTime", totalTime);
	ProgramBindSamplerIndex(m_gBuffer, "gTexture", textureIndex);

	glActiveTexture(GL_TEXTURE0 + textureIndex);
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexDiffuse->GetPlatformHandle());


	glDrawArrays(GL_TRIANGLES, 0, m_mesh.m_vboNumBytes);
	glBindVertexArray(NULL);
	glUseProgram(NULL);
	GLCheckError(__FILE__, __LINE__);

}

void GLMeshRenderer::DrawShaderByMode(float deltaSecond, const Matrix4x4& matrix1, const Matrix4x4& matrix2, GLenum mode)
{
	static float totalTime = 0;
	totalTime += deltaSecond;
	GLCheckError(__FILE__, __LINE__);
	glUseProgram(m_material.m_program.m_gProgram);
	GLCheckError(__FILE__, __LINE__);

	glBindVertexArray(m_VAO);

	GLint textureIndex = 0;
	GLuint m_gBuffer = m_material.m_program.m_gProgram;
	ProgramBindMatrix(m_gBuffer, "gProj", matrix1);
	ProgramBindMatrix(m_gBuffer, "gView", matrix2);
	ProgramBindFloat(m_gBuffer, "gTime", totalTime);
	ProgramBindSamplerIndex(m_gBuffer, "gTexture", textureIndex);

	glActiveTexture(GL_TEXTURE0 + textureIndex);
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexDiffuse->GetPlatformHandle());

	glDrawArrays(mode, 0, m_mesh.m_vboNumBytes);
	glBindVertexArray(NULL);
	glUseProgram(NULL);
	GLCheckError(__FILE__, __LINE__);
}

//////////////////////////////////////////////////////////////////////////

void GLMeshRenderer::DrawMultLightsShader(float deltaSecond, Matrix4x4 perspectiveMatrix, Matrix4x4 viewMatrix, Matrix4x4 modelMatrix, const std::vector<Light> &lights, Vector3 cameraPosition, float discardValue)
{
	std::vector<Light> tempLights = lights;
	if (tempLights.size()>16)
	{
		return;
	}
	////////////////////////////////////////////////////////////////////
	Vector3 lightPositions[16];
	Vector3 lightDirections[16];
	Vector4 lightColors[16];
	float lVWeights[16];
	float lightAngles[16];
	float spotPowers[16];
	float minSfs[16];
	float minIntensitys[16];
	float maxIntensitys[16];
	for (unsigned int i = 0; i < tempLights.size(); i++)
	{
		lightPositions[i] = tempLights[i].m_lightPosition;
		lightDirections[i] = tempLights[i].m_lightDirection;
		lightColors[i] = tempLights[i].m_lightColor;
		lVWeights[i] = tempLights[i].m_lVWeight;
		lightAngles[i] = tempLights[i].m_lightAngle;
		spotPowers[i] = tempLights[i].m_spotPower;
		minSfs[i] = tempLights[i].m_minSf;
		minIntensitys[i] = tempLights[i].m_minIntensity;
		maxIntensitys[i] = tempLights[i].m_maxIntensity;
	}
	////////////////////////////////////////////////////////////////////
	static float totalTime = 0;
	totalTime += deltaSecond;
	discardValue = 1.5f*cos(totalTime*0.1f);
	glUseProgram(m_material.m_program.m_gProgram);
	GLCheckError(__FILE__, __LINE__);
	glBindVertexArray(m_VAO);
	Vector3 cam_position = cameraPosition;
	Vector4 ambient_light(1.0f, 1.0f, 1.0f, 0.05f);
	GLint textureIndex = 0;
	GLuint m_gBuffer = m_material.m_program.m_gProgram;
	//////////////////////////////////////////////////////////////////////////
	ProgramBindSamplerIndex(m_gBuffer, "gTexDiffuse", textureIndex);
	ProgramBindSamplerIndex(m_gBuffer, "gTexNormal", textureIndex + 1);
	ProgramBindSamplerIndex(m_gBuffer, "gTexSpecular", textureIndex + 2);
	ProgramBindSamplerIndex(m_gBuffer, "gTexEmissive", textureIndex + 3);
	ProgramBindMatrix(m_gBuffer, "gProj", perspectiveMatrix);
	ProgramBindMatrix(m_gBuffer, "gView", viewMatrix);
	ProgramBindMatrix(m_gBuffer, "gModel", modelMatrix);
	ProgramBindVector4(m_gBuffer, "gAmbientLight", ambient_light);
	ProgramBindVector4Array(m_gBuffer, "gLightColors[0]", lightColors, (int)tempLights.size());
	ProgramBindVector3Array(m_gBuffer, "gLightPositions[0]", lightPositions, (int)tempLights.size());
	ProgramBindVector3Array(m_gBuffer, "gLightDirections[0]", lightDirections, (int)tempLights.size());
	ProgramBindVector3(m_gBuffer, "gCameraPosition", cam_position);
	ProgramBindFloatArray(m_gBuffer, "gLVWeights[0]", lVWeights, (int)tempLights.size());
	ProgramBindFloatArray(m_gBuffer, "gLightAngles[0]", lightAngles, (int)tempLights.size());
	ProgramBindFloatArray(m_gBuffer, "gSpotPowers[0]", spotPowers, (int)tempLights.size());
	ProgramBindFloatArray(m_gBuffer, "gMinSfs[0]", minSfs, (int)tempLights.size());
	ProgramBindFloatArray(m_gBuffer, "gMinIntensitys[0]", minIntensitys, (int)tempLights.size());
	ProgramBindFloatArray(m_gBuffer, "gMaxIntensitys[0]", maxIntensitys, (int)tempLights.size());
	ProgramBindInt(m_gBuffer, "gLightNumber", (int)tempLights.size());
	ProgramBindFloat(m_gBuffer, "gDiscardValue", discardValue);
	
	
	//////////////////////////////////////////////////////////////////////////
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexDiffuse->GetPlatformHandle());
	textureIndex++;
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexNormal->GetPlatformHandle());
	textureIndex++;
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexSpecular->GetPlatformHandle());
	textureIndex++;
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexEmissive->GetPlatformHandle());
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, m_mesh.m_vboNumBytes);
	glBindVertexArray(NULL);
	glUseProgram(NULL);
	GLCheckError(__FILE__, __LINE__);
}

void GLMeshRenderer::DrawAxes(Matrix4x4 matrix1, Matrix4x4 matrix2, Matrix4x4 modelMatrix, Vector3 position, Vector3 cameraPosition)
{
	GLCheckError(__FILE__, __LINE__);
	glUseProgram(m_material.m_program.m_gProgram);
	GLCheckError(__FILE__, __LINE__);

	glBindVertexArray(m_VAO);
	GLuint m_gBuffer = m_material.m_program.m_gProgram;
	ProgramBindMatrix(m_gBuffer, "gProj", matrix1);
	ProgramBindMatrix(m_gBuffer, "gView", matrix2);
	ProgramBindMatrix(m_gBuffer, "gModel", modelMatrix);
	unsigned char defaultWhiteTexel[3] = { 255, 255, 255 };
	m_material.m_sampler.gTexDiffuse = Texture::CreateMissingTexture("DefaultDiffuse", defaultWhiteTexel, Vector2(1.0f, 1.0f), 3);
	GLint textureIndex = 0;
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexDiffuse->GetPlatformHandle());
	glDrawArrays(GL_LINES, 0, m_mesh.m_vboNumBytes);
	glBindVertexArray(NULL);
	glUseProgram(NULL);
	GLCheckError(__FILE__, __LINE__);
}

void GLMeshRenderer::DrawShaderPolygon(float deltaSecond, Matrix4x4 matrix1, Matrix4x4 matrix2)
{
	Matrix4x4 mat1;
	Matrix4x4 mat2;
	mat1 = matrix1;
	mat2 = matrix2;
	static float totalTime = 0;
	totalTime += deltaSecond;
	GLCheckError(__FILE__, __LINE__);
	glUseProgram(m_material.m_program.m_gProgram);
	GLCheckError(__FILE__, __LINE__);

	glBindVertexArray(m_VAO);

	GLint textureIndex = 0;
	GLuint m_gBuffer = m_material.m_program.m_gProgram;
	ProgramBindMatrix(m_gBuffer, "gProj", mat1);
	ProgramBindMatrix(m_gBuffer, "gView", mat2);
	ProgramBindFloat(m_gBuffer, "gTime", totalTime);
	ProgramBindSamplerIndex(m_gBuffer, "gTexture", textureIndex);

	glActiveTexture(GL_TEXTURE0 + textureIndex);
	ProgramBindTexture(textureIndex, m_material.m_sampler.gTexDiffuse->GetPlatformHandle());


	glDrawArrays(GL_QUADS, 0, m_mesh.m_vboNumBytes);
	glBindVertexArray(NULL);
	glUseProgram(NULL);
	GLCheckError(__FILE__, __LINE__);
}
