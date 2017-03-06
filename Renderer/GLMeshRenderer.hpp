//==========================================================
//GLMeshRenderer.hpp
//==========================================================
#pragma once

#ifndef _GLMESHRENDERER_HPP_
#define _GLMESHRENDERER_HPP_

#include "GLMesh.hpp"
#include "GLMaterial.hpp"
#include "Engine/Math/Matrix4x4.hpp"
#include "Engine/Renderer/Light.hpp"
#include <vector>
#define OPENGL_CHECK_ERRORS

enum VAO_TYPE
{
	VAO_PCTNTB,
	VAO_PCT,
	NUM_VAO_TYPES
};
class GLMeshRenderer
{
public:
	GLMeshRenderer(VAO_TYPE type = VAO_PCT);
	GLMeshRenderer(GLMesh mesh, GLMaterial material);
	GLMeshRenderer(GLMesh mesh, GLMaterial material,VAO_TYPE type);
	void GLCheckError(const char* fileName, int lineNum);
	GLuint CreateVAO(GLuint program_id, GLuint buffer_id);
	GLuint CreatePCTVAO(GLuint program_id, GLuint buffer_id);
	GLuint ChangeVAOType(VAO_TYPE type);
	bool ProgramBindMatrix(GLuint prog_id, char const *name, Matrix4x4 const &mat);
	bool ProgramBindFloat(GLuint prog_id, char const *name, float const &val);
	bool ProgramBindInt(GLuint prog_id, char const *name, int const &val);
	bool ProgramBindFloatArray(GLuint prog_id, char const *name, float* const val,int count);
	bool ProgramBindVector3(GLuint prog_id, char const *name, Vector3 const &vec3);
	bool ProgramBindVector3Array(GLuint prog_id, char const *name, Vector3* const vec3,int count);
	bool ProgramBindVector4(GLuint prog_id, char const *name, Vector4 const &vec4);
	bool ProgramBindVector4Array(GLuint prog_id, char const *name, Vector4* const vec4,int count);
	bool ProgramBindSamplerIndex(GLuint prog_id, char const *name, GLint idx);
	bool ProgramBindTexture(GLint textureID, unsigned int textureHandle);
	bool ProgramBindAttribute(GLuint program_id, char const *name, GLint count, GLenum type, GLboolean normalize, GLsizei stride, GLsizei offset);
	void DrawLightShader(int arraySize, float deltaSecond, Matrix4x4 matrix1, Matrix4x4 matrix2, Matrix4x4 modelMatrix, Vector3 position, Vector3 cameraPosition);
	void DrawShader(int arraySize, float deltaSecond, const Matrix4x4& matrix1, const Matrix4x4& matrix2);
	void DrawShaderByMode(float deltaSecond, const Matrix4x4& matrix1, const Matrix4x4& matrix2,GLenum mode);
	void DrawShaderPolygon(float deltaSecond, Matrix4x4 matrix1, Matrix4x4 matrix2);
	void DrawMultLightsShader(float deltaSecond, Matrix4x4 matrix1, Matrix4x4 matrix2, Matrix4x4 modelMatrix, const std::vector<Light> &lights, Vector3 cameraPosition, float discardValue);
	void DrawLightModel(int arraySize, float deltaSecond, Matrix4x4 matrix1, Matrix4x4 matrix2, Matrix4x4 modelMatrix, Vector3 position, Vector3 cameraPosition);
	void DrawAxes(Matrix4x4 matrix1, Matrix4x4 matrix2, Matrix4x4 modelMatrix, Vector3 position, Vector3 cameraPosition);
	GLMesh m_mesh;
	GLMaterial m_material;
	GLuint m_VAO;
};

#endif
