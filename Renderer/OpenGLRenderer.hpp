//==========================================================
//OpenGLRenderer.hpp
//==========================================================

#pragma once

#include <Windows.h>
#include "gl/GL.h"
#include "gl/GLU.h"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Renderer/RGBA.hpp"
#include "Engine/Renderer/AnimatedTexture.hpp"
#include "Engine/Math/EulerAngles.hpp"
#include "Engine/Camera/Camera3D.hpp"
#include "Engine/Renderer/glext.h"
#include "Engine/Math/Matrix4x4.hpp"
//#include "Engine/Renderer/geometry.h"
#include <vector>



//extern PFNGLGETBOOLEANVPROC glGetBooleanv;
//extern PFNGLGETINTEGERVPROC glGetIntegerv;
//extern PFNGLGETERRORPROC glGetError;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLGETSHADERIVPROC  glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLLINKPROGRAMPROC  glLinkProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;

extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLGETUNIFORMINDICESPROC glGetUniformIndices;
extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLGETPROGRAMBINARYPROC glGetProgramBinary;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLGETUNIFORMINDICESPROC glGetUniformIndices;
extern PFNGLUNIFORM1FVPROC glUniform1fv;
extern PFNGLUNIFORM1IVPROC glUniform1iv;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLPROGRAMPARAMETERIPROC glProgramParameteri;
extern PFNGLBINDBUFFERPROC		glBindBuffer;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLBINDSAMPLERPROC glBindSampler;
extern PFNGLGENSAMPLERSPROC glGenSamplers;
extern PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri;
class DebugShape;
struct Vertex3D_PCT
{
	Vector3 m_position;
	Vector2 m_textureCoords;
	RGBA m_color;

	Vertex3D_PCT(Vector3 pos, Vector2 texCo,RGBA color)
	{
		m_position = pos;
		m_textureCoords = texCo;

		m_color = color;
	}
	Vertex3D_PCT(){}
};
struct NewVertex3D_PCT
{
	Vector3 m_position;
	Vector2 m_textureCoords;
	RGBA m_color;
	Vector3 m_normal;
	NewVertex3D_PCT(Vector3 pos, Vector2 texCo, Vector3 normal, RGBA color)
	{
		m_position = pos;
		m_textureCoords = texCo;
		m_normal = normal;
		m_color = color;
	}
	NewVertex3D_PCT(){}
};
struct NTBVertex3D_PCT
{
	Vector3 m_position;
	RGBA m_color;
	Vector2 m_textureCoords;	
	Vector3 m_normal;
	Vector3 m_tangent;
	Vector3 m_biTangent;
	NTBVertex3D_PCT(Vector3 pos, Vector2 texCo, Vector3 normal, Vector3 tangent, Vector3 biTangent, RGBA color)
	{
		m_position = pos;
		m_textureCoords = texCo;
		m_normal = normal;
		m_color = color;
		m_tangent = tangent;
		m_biTangent = biTangent;
	}
	NTBVertex3D_PCT(){}
};

struct BoneIndex
{
	unsigned char m_indexes[4];
	BoneIndex(unsigned char firstIndex, unsigned char secondIndex, unsigned char thirdIndex, unsigned char fourthIndex)
	{
		m_indexes[0] = firstIndex;
		m_indexes[1] = secondIndex;
		m_indexes[2] = thirdIndex;
		m_indexes[3] = fourthIndex;
	}
	BoneIndex(){}
};

struct Vertex3D_Skeletal
{
	Vector3 m_position;
	RGBA m_color;
	Vector2 m_textureCoords;
	Vector3 m_normal;
	Vector3 m_tangent;
	Vector3 m_biTangent;
	BoneIndex m_boneIndex;
	Vector3 m_boneWeights;
	Vertex3D_Skeletal(Vector3 pos, Vector2 texCo, Vector3 normal, Vector3 tangent, Vector3 biTangent, RGBA color, BoneIndex boneIndex, Vector3 boneWeights)
	{
		m_position = pos;
		m_textureCoords = texCo;
		m_normal = normal;
		m_color = color;
		m_tangent = tangent;
		m_biTangent = biTangent;
		m_boneIndex = boneIndex;
		m_boneWeights = boneWeights;
	}
	Vertex3D_Skeletal(){}
};
///------------------------------------------------------
///
///------------------------------------------------------

class OpenGLRenderer
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();
///------------------------------------------------------
/// Get display data
///------------------------------------------------------
	float					GetDisplayWidth()const		{return m_displayWidth ;}
	float					GetDisplayHeight()const		{return m_displayHeight;}
///------------------------------------------------------
/// Start up and shut down function
///------------------------------------------------------
	void					Startup(HWND windowHandle);
	void					Shutdown();
	void					SwapBuffers();
	void					ClearBuffer(float red, float green, float blue);
	void					PerspectiveSetting(float fieldOfViewDegreesVertical=45.0f,float aspectRatio=16.0f/9.0f,
											   float nearDepth=0.1f, float farDepth=10000.0f);			
	void					InitializeAdvancedOpenGLFunctions();
///------------------------------------------------------
/// Set display data
///------------------------------------------------------	
	void					SetOrthographicView();
	void					SetModelViewTranslation(float x, float y, float z=0.0f);
///------------------------------------------------------
/// Draw
///------------------------------------------------------
	void					DrawTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2, const RGBA& tint );
	void					DrawPolygon(const std::vector <Vector2> & vertices,const RGBA& tint);
	void					DrawDot(const Vector2& v);
	void					DrawTexturedQuad(const Texture& texture, const std::vector<Vector2>& vertices, const std::vector<Vector2>& textureCoordinate, const RGBA& tint);
	void					DrawCircle(const Vector2& center, const float radious,const RGBA& tint);
	void					DrawDisc(const Vector2& center, const float radious,const RGBA& tint);
	void					DrawRect(const std::vector <Vector2> & vertices,const RGBA& tint);
	void					DrawLineSegment(const Vector3& FP, const Vector3& LP, const RGBA& tint, unsigned int depthTestType);
///------------------------------------------------------
/// Draw3D
///------------------------------------------------------
	void					DrawTriangle3D(const Vector3& v0, const Vector3& v1, const Vector3& v2, const RGBA& tint );
	void					DrawPolygon3D(const std::vector <Vector3> & vertices,const RGBA& tint);
	void					DrawRect3D(const std::vector<Vector3> & vertices,const RGBA& tint);
	void					DrawTexturedQuad3D(const Texture& texture, const std::vector<Vector3>& vertices, const std::vector<Vector2>& textureCoordinate, const RGBA& tint);
	void					DrawCircle3D(const Vector3& center, const float radious,const RGBA& tint);
	//void					DrawTexturedQuadByRowNCol(const Texture& texture, const std::vector<Vector3>& vertices,const int row, const int col,const RGBA& tint);
	void					DrawQuad(Vector3 tlPos, Vector2 tlCo,Vector3 blPos, Vector2 blCo,Vector3 trPos, Vector2 trCo,Vector3 brPos, Vector2 brCo);
	void					DrawAxes();
	void					DrawAxesWithVA();

	void					DrawStarPoint(const Vector3& position, const RGBA& color,unsigned int depthTestType);
	void					DrawArrow(const Vector3& startPoint, const Vector3& endPoint, const RGBA& color, unsigned int depthTestType);
	void					DrawAABB3DFrame(const Vector3& mins, const Vector3& maxs, const RGBA& color, unsigned int depthTestType);
	void					DrawAABB3D(const Vector3& mins, const Vector3& maxs, const RGBA& color, unsigned int depthTestType);
	void					DrawFace(const Vector3& topLeft, const Vector3& topRight, const Vector3& botRight, const Vector3& botLeft, const RGBA& color, unsigned int depthTestType);
	void					DrawSphere(const Vector3& center, float radius, const RGBA& color, unsigned int depthTestType);
///------------------------------------------------------
///
///------------------------------------------------------
	static Vertex3D_PCT*	CreateCubeVerts(Vector3 mins, Vector3 maxs, int& size);
	static NewVertex3D_PCT*	CreateSphereVerts(const Vector3& center, float radius, int& size);
	static NTBVertex3D_PCT* CreateNTBSphereVerts(const Vector3& center, float radius, int& size, const RGBA color);
	static NTBVertex3D_PCT* CreateAxesVerts();
///------------------------------------------------------
///
///------------------------------------------------------
	void					PushMatrix();
	void					PopMatrix();
	void					SetModelViewMatrixMode();
	void					SetModelViewRotation(float angleDegrees,	float amountAroundX, 
																		float amountAroundY,
																		float amountAroundZ);
	void					ApplyCameraTransform( const Camera3D& camera);
	static void				MakeViewMatrix(Matrix4x4* result, Vector3& cameraPosition, Vector3& forwardVector);
	static void				MakePerspectiveMatrix(Matrix4x4* result, float f, float n, float aspect, float FOV);
	static void				MakeOrthogonalMatrix(Matrix4x4* result, float h, float w, float zmax, float zmin);
protected:
	void					CreateOpenGLRenderingContext();
	void					DestoryOpenGLRenderingContext();
///------------------------------------------------------
///
///------------------------------------------------------

///------------------------------------------------------
///
///------------------------------------------------------
	
///------------------------------------------------------
///
///------------------------------------------------------
private:
	HWND					m_windowHandle;
	HDC						m_deviceContext;
	HGLRC					m_renderingContext;

	float					m_displayWidth;
	float					m_displayHeight;

};
