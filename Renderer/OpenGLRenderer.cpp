//==========================================================
//OpenGLRenerer.cpp
//==========================================================

#include "Engine/Renderer/OpenGLRenderer.hpp"
PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;
PFNGLCREATESHADERPROC glCreateShader= nullptr;
PFNGLSHADERSOURCEPROC glShaderSource= nullptr;
PFNGLDELETESHADERPROC glDeleteShader= nullptr;
PFNGLGETSHADERIVPROC  glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLDETACHSHADERPROC glDetachShader = nullptr;
PFNGLLINKPROGRAMPROC  glLinkProgram = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
PFNGLGETUNIFORMINDICESPROC glGetUniformIndices = nullptr;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = nullptr;
PFNGLGETPROGRAMBINARYPROC glGetProgramBinary = nullptr;
PFNGLUNIFORM1FVPROC glUniform1fv = nullptr;
PFNGLUNIFORM1IVPROC glUniform1iv = nullptr;
PFNGLUNIFORM3FVPROC glUniform3fv = nullptr;
PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLPROGRAMPARAMETERIPROC glProgramParameteri = nullptr;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = nullptr;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;
PFNGLBINDSAMPLERPROC glBindSampler = nullptr;
PFNGLGENSAMPLERSPROC glGenSamplers = nullptr;
PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri = nullptr;


///------------------------------------------------------
///
///------------------------------------------------------
OpenGLRenderer::OpenGLRenderer()
	:m_windowHandle(NULL)
	,m_deviceContext(NULL)
	,m_renderingContext(NULL)
	,m_displayWidth(0.0f)
	,m_displayHeight(0.0f)
{

}

OpenGLRenderer::~OpenGLRenderer()
{

}


void OpenGLRenderer::Startup(HWND windowHandle)
{
	m_windowHandle= windowHandle;
	m_deviceContext = GetDC( windowHandle );

	CreateOpenGLRenderingContext();
	InitializeAdvancedOpenGLFunctions();
}

void OpenGLRenderer::Shutdown()
{
	delete this;
}

void OpenGLRenderer::CreateOpenGLRenderingContext()
{
	PIXELFORMATDESCRIPTOR pixelFormatDescription ;
	memset(&pixelFormatDescription, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pixelFormatDescription.nSize		=	sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescription.cColorBits	=	32;
	pixelFormatDescription.nVersion		=	1;	
	pixelFormatDescription.dwFlags		=	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER ;

	HWND myWindowHandle =	(HWND)(m_windowHandle );
	HDC hdc;
	hdc =	GetDC(myWindowHandle);

	int pixelFormat		=	ChoosePixelFormat( m_deviceContext, &pixelFormatDescription );
	BOOL didSetFormat	=	SetPixelFormat(m_deviceContext, pixelFormat, &pixelFormatDescription);


	if(didSetFormat)
	{
		m_renderingContext	=	wglCreateContext( m_deviceContext );
		wglMakeCurrent(m_deviceContext, m_renderingContext); 

		float dimensions[4];
		glGetFloatv(GL_VIEWPORT,dimensions);
		m_displayWidth=dimensions[2];
		m_displayHeight=dimensions[3];
		
	}
	glLineWidth(2.0f);
	glEnable(GL_LINE_SMOOTH);
	glPointSize(3.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
}
///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::DestoryOpenGLRenderingContext()
{
	wglDeleteContext(m_renderingContext);
}
///------------------------------------------------------
///
///------------------------------------------------------



void OpenGLRenderer::SetOrthographicView()
{
	glLoadIdentity();
	glOrtho(0.0f, m_displayWidth, 0.0f, m_displayHeight ,0.0f,0.1f);
}
void OpenGLRenderer::SwapBuffers()
{
	
	::SwapBuffers( m_deviceContext );
}
///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::PerspectiveSetting(float fieldOfViewDegreesVertical,float aspectRatio, float nearDepth, float farDepth)
{
	gluPerspective(fieldOfViewDegreesVertical,aspectRatio,nearDepth,farDepth);
}
///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::DrawTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2, const RGBA& tint)
{
	RGBA color = tint;
	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
	//glColor4f(1.0f,1.0f,0.0f,1.0f);
	glBegin(GL_TRIANGLES);
		glVertex2f(v0.x, v0.y);
		glVertex2f(v1.x, v1.y);
		glVertex2f(v2.x, v2.y);
	glEnd();
}
///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::DrawTriangle3D(const Vector3& v0, const Vector3& v1, const Vector3& v2, const RGBA& tint)
{
	RGBA color = tint;
	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
	//glColor4f(1.0f,1.0f,0.0f,1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(v0.x, v0.y, v0.z);
	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glEnd();

}

void OpenGLRenderer::DrawDot(const Vector2& v)
{

	glBegin(GL_POINTS);
		glVertex2f(v.x,v.y);
	glEnd();
}

void OpenGLRenderer::DrawStarPoint(const Vector3& position,const RGBA& color,unsigned int depthTestType)
{
	
	glDisable(GL_TEXTURE_2D);
	const float pointLength = 0.05f;
	const float pointLengthDi = sqrt(pointLength*pointLength * 3)/3;
	Vector3 pos = position;

	DrawLineSegment(pos - Vector3(0.0f, 0.0f, pointLength), pos + Vector3(0.0f, 0.0f, pointLength), color, depthTestType);
	DrawLineSegment(pos - Vector3(0.0f, pointLength, 0.0f), pos + Vector3(0.0f, pointLength, 0.0f), color, depthTestType);
	DrawLineSegment(pos - Vector3(pointLength, 0.0f, 0.0f), pos + Vector3(pointLength, 0.0f, 0.0f), color, depthTestType);
	DrawLineSegment(pos - Vector3(pointLengthDi, pointLengthDi, pointLengthDi), pos + Vector3(pointLengthDi, pointLengthDi, pointLengthDi), color, depthTestType);
	DrawLineSegment(pos - Vector3(-pointLengthDi, pointLengthDi, pointLengthDi), pos + Vector3(-pointLengthDi, pointLengthDi, pointLengthDi), color, depthTestType);
	DrawLineSegment(pos - Vector3(pointLengthDi, -pointLengthDi, pointLengthDi), pos + Vector3(pointLengthDi, -pointLengthDi, pointLengthDi), color, depthTestType);
	DrawLineSegment(pos - Vector3(-pointLengthDi, -pointLengthDi, pointLengthDi), pos + Vector3(-pointLengthDi, -pointLengthDi, pointLengthDi), color, depthTestType);

	
}

void OpenGLRenderer::SetModelViewTranslation(float x, float y, float z)
{
	glTranslatef(x,y,z);
}

void OpenGLRenderer::ClearBuffer(float red, float green, float blue)
{
	glClearColor(red,green,blue,1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::PushMatrix()
{
	glPushMatrix();
}

void OpenGLRenderer::PopMatrix()
{
	glPopMatrix();
}

void OpenGLRenderer::SetModelViewMatrixMode()
{
	glMatrixMode(GL_MODELVIEW);
}

void OpenGLRenderer::DrawPolygon(const std::vector <Vector2> & vertices,const RGBA& tint)
{
	if(vertices.size()<3)
	{
		return;
	}
	RGBA color = tint;
	//glColor3f(1.0f,0.0f,0.0f);
	//float a= color.GetRed();
	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
	//glColor4f(1.0f,0.0f,1.0f,1.0f);
	glBegin(GL_LINE_LOOP);
	for(std::vector<Vector2>::const_iterator vertexIter = vertices.begin(); vertexIter != vertices.end() ; ++vertexIter)
	{
		const Vector2& vertex = (*vertexIter);
		glVertex2f(vertex.x,vertex.y);
	}
	glEnd();
}
///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::DrawPolygon3D(const std::vector<Vector3> & vertices,const RGBA& tint)
{
	if(vertices.size()<3)
	{
		return;
	}
	RGBA color = tint;
	
	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
	//glColor4f(1.0f,0.0f,1.0f,1.0f);
	glBegin(GL_LINE_STRIP);
	for(std::vector<Vector3>::const_iterator vertexIter = vertices.begin(); vertexIter != vertices.end() ; ++vertexIter)
	{
		const Vector3& vertex = (*vertexIter);
		glVertex3f(vertex.x,vertex.y,vertex.z);
	}
	glEnd();
}

void OpenGLRenderer::DrawRect3D(const std::vector<Vector3> & vertices,const RGBA& tint)
{
	if(vertices.size()<3)
	{
		return;
	}
	RGBA color = tint;
	//glColor3f(1.0f,0.0f,0.0f);
	//float a= color.GetRed();
	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
	//glColor4f(1.0f,0.0f,1.0f,1.0f);
	glBegin(GL_POLYGON);
	for(std::vector<Vector3>::const_iterator vertexIter = vertices.begin(); vertexIter != vertices.end() ; ++vertexIter)
	{
		const Vector3& vertex = (*vertexIter);
		glVertex3f(vertex.x,vertex.y,vertex.z);
	}
	glEnd();
}
///------------------------------------------------------
///
///------------------------------------------------------

void OpenGLRenderer::DrawRect(const std::vector<Vector2> & vertices,const RGBA& tint)
{
	if(vertices.size()<3)
	{
		return;
	}
	RGBA color = tint;
	//glColor3f(1.0f,0.0f,0.0f);
	//float a= color.GetRed();
	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
	//glColor4f(1.0f,0.0f,1.0f,1.0f);
	glBegin(GL_POLYGON);
	for(std::vector<Vector2>::const_iterator vertexIter = vertices.begin(); vertexIter != vertices.end() ; ++vertexIter)
	{
		const Vector2& vertex = (*vertexIter);
		glVertex2f(vertex.x,vertex.y);
	}
	glEnd();
}


void OpenGLRenderer::SetModelViewRotation(float angleDegrees,	float amountAroundX, 
																float amountAroundY,
																float amountAroundZ)
{
	glRotatef(angleDegrees,amountAroundX,amountAroundY,amountAroundZ);
}

void OpenGLRenderer::DrawCircle(const Vector2& center, const float radious,const RGBA& tint)
{
	const int numSides = 24;
	std::vector<Vector2> vertices;
	float radianPerSide=2.0f * PI / (float)numSides;
	for (unsigned int i= 0; i< numSides; i++)
	{
		float currentRadian =radianPerSide*(float) i;
		Vector2 point(center.x+radious*cos(currentRadian),center.y + radious*sin(currentRadian));
		vertices.push_back(point);
		
	}
	RGBA color = tint;
	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
	
	glBegin(GL_LINE_LOOP);
	for(std::vector<Vector2>::const_iterator vertexIter = vertices.begin(); vertexIter != vertices.end() ; ++vertexIter)
	{
		const Vector2& vertex = (*vertexIter);
		glVertex2f(vertex.x,vertex.y);
	}
	glEnd();
}
///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::DrawCircle3D(const Vector3& center, const float radious,const RGBA& tint)
{
	const int numSides = 24;
	std::vector<Vector3> vertices;
	float radianPerSide=2.0f * PI / (float)numSides;
	for (unsigned int i= 0; i< numSides; i++)
	{
		float currentRadian =radianPerSide*(float) i;
		Vector3 point(center.x+radious*cos(currentRadian),center.y + radious*sin(currentRadian),center.z);
		vertices.push_back(point);

	}
	RGBA color = tint;
	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());

	glBegin(GL_LINE_LOOP);
	for(std::vector<Vector3>::const_iterator vertexIter = vertices.begin(); vertexIter != vertices.end() ; ++vertexIter)
	{
		const Vector3& vertex = (*vertexIter);
		glVertex3f(vertex.x,vertex.y,vertex.z);
	}
	glEnd();
}
///------------------------------------------------------
///
///------------------------------------------------------


void OpenGLRenderer::DrawDisc(const Vector2& center, const float radius,const RGBA& tint)
{
	const int numSides = 24;
	std::vector<Vector2> vertices;
	float radianPerSide=2.0f * PI / (float)numSides;
	for (unsigned int i= 0; i< numSides; i++)
	{
		float currentRadian =radianPerSide*(float) i;
		Vector2 point(center.x+radius*cos(currentRadian),center.y + radius*sin(currentRadian));
		vertices.push_back(point);

	}
	RGBA color = tint;
	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());

	glBegin(GL_POLYGON);
	for(std::vector<Vector2>::const_iterator vertexIter = vertices.begin(); vertexIter != vertices.end() ; ++vertexIter)
	{
		const Vector2& vertex = (*vertexIter);
		glVertex2f(vertex.x,vertex.y);
	}
	glEnd();
}

void OpenGLRenderer::DrawTexturedQuad(const Texture& texture, const std::vector<Vector2>& vertices, const std::vector<Vector2>& textureCoordinate, const RGBA& tint)
{
	if (vertices.size()!=4)
	{
		return;
	}
	
		glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture.GetPlatformHandle());
	
	//glColor4f(color.GetRed(),tint.fg(),tint.fb(),tint.fa());
	RGBA color = tint;
	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
	glBegin(GL_QUADS);
		std::vector<Vector2>::const_iterator vertexIter  = vertices.begin();
		std::vector<Vector2>::const_iterator textureCoordIter = textureCoordinate.begin();

		for(;vertexIter != vertices.end(); ++vertexIter,++textureCoordIter)
		{
			const Vector2& vertex = (*vertexIter);
			const Vector2& textureCoordinate = (*textureCoordIter);
			glTexCoord2f(textureCoordinate.x,textureCoordinate.y);
			glVertex2f(vertex.x,vertex.y);
			

		}
		glEnd();
		glDisable(GL_TEXTURE_2D);

}

///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::DrawTexturedQuad3D(const Texture& texture, const std::vector<Vector3>& vertices, const std::vector<Vector2>& textureCoordinate, const RGBA& tint)
{
	if (vertices.size()!=4)
	{
		return;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture.GetPlatformHandle());

	//glColor4f(color.GetRed(),tint.fg(),tint.fb(),tint.fa());
	RGBA color = tint;
	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
	glBegin(GL_QUADS);
	std::vector<Vector3>::const_iterator vertexIter  = vertices.begin();
	std::vector<Vector2>::const_iterator textureCoordIter = textureCoordinate.begin();

	for(;vertexIter != vertices.end(); ++vertexIter,++textureCoordIter)
	{
		const Vector3& vertex = (*vertexIter);
		const Vector2& textureCoordinate = (*textureCoordIter);
		glTexCoord2f(textureCoordinate.x,textureCoordinate.y);
		glVertex3f(vertex.x,vertex.y,vertex.z);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

}
///------------------------------------------------------
///
///------------------------------------------------------
NTBVertex3D_PCT* OpenGLRenderer::CreateAxesVerts()
{
	NTBVertex3D_PCT* verts = new NTBVertex3D_PCT[6];
	RGBA red(1.0f, 0.0f, 0.0f,1.0f);
	RGBA green(0.0f, 1.0f, 0.0f, 1.0f);
	RGBA blue(0.0f, 0.0f, 1.0f, 1.0f);
	verts[0] = NTBVertex3D_PCT(Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), red);
	verts[1] = NTBVertex3D_PCT(Vector3(10.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), red);
	verts[2] = NTBVertex3D_PCT(Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), green);
	verts[3] = NTBVertex3D_PCT(Vector3(0.0f, 10.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), green);
	verts[4] = NTBVertex3D_PCT(Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), blue);
	verts[5] = NTBVertex3D_PCT(Vector3(0.0f, 0.0f, 10.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), blue);
	return verts;
}
///------------------------------------------------------
///
///------------------------------------------------------
//void OpenGLRenderer::DrawTexturedQuadByRowNCol(const Texture& texture, const std::vector<Vector3>& vertices,const int row, const int col,const RGBA& tint)
//{
//	if (vertices.size()!=4)
//	{
//		return;
//	}
//
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D,texture.GetPlatformHandle());
//
//	//glColor4f(color.GetRed(),tint.fg(),tint.fb(),tint.fa());
//	RGBA color = tint;
//	glColor4f(color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
//	glBegin(GL_QUADS);
//	std::vector<Vector3>::const_iterator vertexIter  = vertices.begin();
//	//std::vector<Vector2>::const_iterator textureCoordIter = textureCoordinate.begin();
//
//	for(;vertexIter != vertices.end(); ++vertexIter)
//	{
//		const Vector3& vertex = (*vertexIter);
//		
//		//glTexCoord2f();
//		glVertex3f(vertex.x,vertex.y,vertex.z);
//	}
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//}
///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::DrawAxes()
{
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
	{
		glColor4f(1.0f,0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(2.0f,0.0f,0.0f);

		glColor4f(0.0f,1.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,2.0f,0.0f);

		glColor4f(0.0f,0.0f,1.0f,1.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,2.0f);
	}
	
	glEnd();
}
///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::DrawAxesWithVA()
{
	struct Vertex
	{
		float x;
		float y;
		float z;
	};

	glColor3f(1.f, 0.f, 1.f);
	Vertex lineVerts[6];
	lineVerts[0].x = 0.f;
	lineVerts[0].y = 0.f;
	lineVerts[0].z = 0.f;
	lineVerts[1].x = 1.f;
	lineVerts[1].y = 0.f;
	lineVerts[0].z = 0.f;
	lineVerts[2].x = 1.f;
	lineVerts[2].y = 1.f;
	lineVerts[3].x = 0.f;
	lineVerts[3].y = 1.f;

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &lineVerts[0].x);
	glDrawArrays(GL_LINES, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}
///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::DrawLineSegment(const Vector3& FP, const Vector3& LP, const RGBA& tint, unsigned int depthTestType)
{
	glDisable(GL_TEXTURE_2D);
	
	if (depthTestType == 0)
	{
		glDisable(GL_DEPTH_TEST);
		glBegin(GL_LINES);
		{
	
			glColor4f(tint.R, tint.G, tint.B, tint.A);
			//glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(LP.x, LP.y, LP.z);
			glVertex3f(FP.x, FP.y, FP.z);
	
		}
	}
	else
	{
		glEnable(GL_DEPTH_TEST);
		glBegin(GL_LINES);
		{
	
			glColor4f(tint.R, tint.G, tint.B, tint.A);
			//glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(LP.x, LP.y, LP.z);
			glVertex3f(FP.x, FP.y, FP.z);
	
		}
	}
	if (depthTestType == 3)
	{
		glDisable(GL_DEPTH_TEST);
		glBegin(GL_LINES);
		{
	
			glColor4f(tint.R, tint.G, tint.B, tint.A);
			//glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(LP.x, LP.y, LP.z);
			glVertex3f(FP.x, FP.y, FP.z);
	
		}
	}

	glEnd();
}

///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::ApplyCameraTransform(const Camera3D& camera)
{
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	glRotatef(90.0f,0.0f,0.0f,1.0f);
	

	glRotatef(-camera.m_orientation.rollDegreesAboutX, 1.0,0.0f,0.0f);
	glRotatef(-camera.m_orientation.pitchDegreesAboutY, 0.0,1.0f,0.0f);
	glRotatef(-camera.m_orientation.yawDegreesAboutZ, 0.0,0.0f,1.0f);
	glTranslatef(-camera.m_position.x,-camera.m_position.y,-camera.m_position.z);
}
///------------------------------------------------------
///
///------------------------------------------------------

void OpenGLRenderer::DrawQuad(Vector3 tlPos, Vector2 tlCo,Vector3 blPos, Vector2 blCo,Vector3 trPos, Vector2 trCo,Vector3 brPos, Vector2 brCo)
{	
	glTexCoord2f(blCo.x,blCo.y);            //bl
	glVertex3f(trPos.x,trPos.y,trPos.z);	//
	glTexCoord2f(brCo.x,brCo.y);			//br
	glVertex3f(tlPos.x,tlPos.y,tlPos.z);	//
	glTexCoord2f(trCo.x,trCo.y);			//tr
	glVertex3f(blPos.x,blPos.y,blPos.z);	//
	glTexCoord2f(tlCo.x,tlCo.y);			//tl
	glVertex3f(brPos.x,brPos.y,brPos.z);	//
}
//////////////////////////////////////////////////////////////////////////

void OpenGLRenderer::DrawArrow(const Vector3& startPoint, const Vector3& endPoint, const RGBA& color, unsigned int depthTestType)
{
	DrawLineSegment(startPoint, endPoint, color, depthTestType);
	Vector3 startPos = startPoint;
	Vector3 endPos = endPoint;
	float length = 0.01f;
	Vector3 point = Vector3::Interpolate(startPos, endPos, 0.95F);
	DrawLineSegment(endPos, point + Vector3(0.0f, 0.0f, length), color, depthTestType);
	DrawLineSegment(endPos, point + Vector3(0.0f, 0.0f, -length), color, depthTestType);
	DrawLineSegment(endPos, point + Vector3(0.0f, length, 0.0f), color, depthTestType);
	DrawLineSegment(endPos, point + Vector3(0.0f, -length, 0.0f), color, depthTestType);
	DrawLineSegment(endPos, point + Vector3(length, 0.0f, 0.0f), color, depthTestType);
	DrawLineSegment(endPos, point + Vector3(-length, 0.0f, 0.0f), color, depthTestType);
}
///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::DrawAABB3DFrame(const Vector3& mins, const Vector3& maxs, const RGBA& color, unsigned int depthTestType)
{
	Vector3 NorthEastTop = maxs;
	Vector3 NorthWestTop = Vector3(mins.x,maxs.y,maxs.z);
	Vector3 NorthEastBot = Vector3(maxs.x, maxs.y, mins.z);
	Vector3 NorthWestBot = Vector3(mins.x, maxs.y, mins.z);
	Vector3 SouthEastTop = Vector3(maxs.x, mins.y, maxs.z);
	Vector3 SouthWestTop = Vector3(mins.x, mins.y, maxs.z);
	Vector3 SouthEastBot = Vector3(maxs.x, mins.y, mins.z);
	Vector3 SouthWestBot = mins;
	
	DrawLineSegment(NorthEastTop, NorthEastBot, color, depthTestType);
	DrawLineSegment(NorthEastTop, NorthWestTop, color, depthTestType);
	DrawLineSegment(NorthEastTop, SouthEastTop, color, depthTestType);
	DrawLineSegment(SouthEastBot, NorthEastBot, color, depthTestType);
	DrawLineSegment(SouthEastBot, SouthWestBot, color, depthTestType);
	DrawLineSegment(SouthEastBot, SouthEastTop, color, depthTestType);
	DrawLineSegment(SouthWestTop, NorthWestTop, color, depthTestType);
	DrawLineSegment(SouthWestTop, SouthEastTop, color, depthTestType);
	DrawLineSegment(SouthWestTop, SouthWestBot, color, depthTestType);
	DrawLineSegment(NorthWestBot, NorthWestTop, color, depthTestType);
	DrawLineSegment(NorthWestBot, NorthEastBot, color, depthTestType);
	DrawLineSegment(NorthWestBot, SouthWestBot, color, depthTestType);
}

void OpenGLRenderer::DrawAABB3D(const Vector3& mins, const Vector3& maxs, const RGBA& color, unsigned int depthTestType)
{
	Vector3 NorthEastTop = maxs;
	Vector3 NorthWestTop = Vector3(mins.x, maxs.y, maxs.z);
	Vector3 NorthEastBot = Vector3(maxs.x, maxs.y, mins.z);
	Vector3 NorthWestBot = Vector3(mins.x, maxs.y, mins.z);
	Vector3 SouthEastTop = Vector3(maxs.x, mins.y, maxs.z);
	Vector3 SouthWestTop = Vector3(mins.x, mins.y, maxs.z);
	Vector3 SouthEastBot = Vector3(maxs.x, mins.y, mins.z);
	Vector3 SouthWestBot = mins;
	
	DrawFace(NorthEastTop, NorthWestTop, NorthWestBot, NorthEastBot, color, depthTestType);
	DrawFace(SouthEastTop, SouthWestTop, SouthWestBot, SouthEastBot, color, depthTestType);
	DrawFace(NorthWestTop, SouthWestTop, SouthWestBot, NorthWestBot, color, depthTestType);
	DrawFace(NorthEastTop, SouthEastTop, SouthEastBot, NorthEastBot, color, depthTestType);
	DrawFace(SouthEastTop, SouthWestTop, NorthWestTop, NorthEastTop, color, depthTestType);
	DrawFace(SouthEastBot, SouthWestBot, NorthWestBot, NorthEastBot, color, depthTestType);
	RGBA frameColor(0.0f,0.0f,0.0f,1.0f);

	frameColor.R = (unsigned char)255 - color.R;
	frameColor.G = (unsigned char)255 - color.G;
	frameColor.B = (unsigned char)255 - color.B;

	DrawAABB3DFrame(mins, maxs, frameColor,depthTestType);
	
}
//////////////////////////////////////////////////////////////////////////

void OpenGLRenderer::DrawFace(const Vector3& topLeft, const Vector3& topRight, const Vector3& botRight, const Vector3& botLeft, const RGBA& color, unsigned int depthTestType)
{
	std::vector<Vector3> vertices;
	vertices.push_back(topLeft);
	vertices.push_back(topRight);
	vertices.push_back(botRight);
	vertices.push_back(botLeft);
	if (depthTestType == 0)
	{
		glDisable(GL_DEPTH_TEST);
		DrawRect3D(vertices, color);
	}
	else
	{
		glEnable(GL_DEPTH_TEST);
		DrawRect3D(vertices, color);
	}
	if (depthTestType == 3)
	{
		glDisable(GL_DEPTH_TEST);
		DrawRect3D(vertices, color);
	}
	vertices.clear();
	vertices.push_back(topRight);
	vertices.push_back(topLeft);
	vertices.push_back(botLeft);
	vertices.push_back(botRight);
	if (depthTestType == 0)
	{
		glDisable(GL_DEPTH_TEST);
		DrawRect3D(vertices, color);
	}
	else
	{
		glEnable(GL_DEPTH_TEST);
		DrawRect3D(vertices, color);
	}
	if (depthTestType == 3)
	{
		glDisable(GL_DEPTH_TEST);
		DrawRect3D(vertices, color);
	}

}
///------------------------------------------------------
///
///------------------------------------------------------
void OpenGLRenderer::DrawSphere(const Vector3& center, float radius, const RGBA& color, unsigned int depthTestType)
{
	std::vector<Vector3> spherePoints;
	spherePoints.clear();

	for (float phi = 0.0f; phi < 2.0f * PI; phi += PI / 10.0f) // Azimuth [0, 2PI]
	{
		for (float theta = 0.0f; theta < PI; theta += PI / 10.0f) // Elevation [0, PI]
		{
			Vector3 point;
			point.x = radius * cos(phi) * sin(theta) + center.x;
			point.y = radius * sin(phi) * sin(theta) + center.y;
			point.z = radius           * cos(theta) + center.z;
			spherePoints.push_back(point);
		}
	}
	if (depthTestType == 0)
	{
		glDisable(GL_DEPTH_TEST);
		DrawPolygon3D(spherePoints, color);
	}
	else
	{
		glEnable(GL_DEPTH_TEST);
		DrawPolygon3D(spherePoints, color);
	}
	if (depthTestType == 3)
	{
		glDisable(GL_DEPTH_TEST);
		DrawPolygon3D(spherePoints, color);
	}
	
	return;

	
}
///------------------------------------------------------
///
///------------------------------------------------------



void OpenGLRenderer::InitializeAdvancedOpenGLFunctions()
{
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)wglGetProcAddress("glGetProgramBinary");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)wglGetProcAddress("glGetUniformIndices");
	glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)wglGetProcAddress("glGetActiveUniform");																										  
	//glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	//glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)wglGetProcAddress("glGetUniformIndices");
	glUniform1fv = (PFNGLUNIFORM1FVPROC)wglGetProcAddress("glUniform1fv");
	glUniform1iv = (PFNGLUNIFORM1IVPROC)wglGetProcAddress("glUniform1iv");
	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)wglGetProcAddress("glProgramParameteri");																													  
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	glBindSampler = (PFNGLBINDSAMPLERPROC)wglGetProcAddress("glBindSampler");
	glGenSamplers = (PFNGLGENSAMPLERSPROC)wglGetProcAddress("glGenSamplers");
	glSamplerParameteri= (PFNGLSAMPLERPARAMETERIPROC)wglGetProcAddress("glSamplerParameteri");

}
///------------------------------------------------------
///
///------------------------------------------------------
Vertex3D_PCT* OpenGLRenderer::CreateCubeVerts(Vector3 mins, Vector3 maxs, int& size)
{
	Vertex3D_PCT* verts = new Vertex3D_PCT[36];
	
		//top
	verts[0] = Vertex3D_PCT(Vector3(mins.x, maxs.y, maxs.z), Vector2(0.0f, 0.0f), RGBA(0.0f, 0.0f, 1.0f));
	verts[1] = Vertex3D_PCT(Vector3(mins.x, mins.y, maxs.z), Vector2(0.0f, 1.0f), RGBA(1.0f, 0.0f, 0.0f));
	verts[2] = Vertex3D_PCT(Vector3(maxs.x, mins.y, maxs.z), Vector2(1.0f, 1.0f), RGBA(1.0f, 1.0f, 0.0f));

	verts[3] = Vertex3D_PCT(Vector3(mins.x, maxs.y, maxs.z), Vector2(0.0f, 0.0f), RGBA(0.0f, 0.0f, 1.0f));
	verts[4] = Vertex3D_PCT(Vector3(maxs.x, mins.y, maxs.z), Vector2(1.0f, 1.0f), RGBA(1.0f, 1.0f, 0.0f));
	verts[5] = Vertex3D_PCT(Vector3(maxs.x, maxs.y, maxs.z), Vector2(1.0f, 0.0f), RGBA(1.0f, 0.0f, 1.0f));
	//north							 																	 ;
	verts[6] = Vertex3D_PCT(Vector3(mins.x, maxs.y, maxs.z), Vector2(1.0f, 0.0f), RGBA(0.0f, 0.0f, 1.0f));
	verts[7] = Vertex3D_PCT(Vector3(maxs.x, maxs.y, maxs.z), Vector2(0.0f, 0.0f), RGBA(1.0f, 1.0f, 0.0f));
	verts[8] = Vertex3D_PCT(Vector3(maxs.x, maxs.y, mins.z), Vector2(0.0f, 1.0f), RGBA(1.0f, 0.0f, 1.0f));

	verts[9] = Vertex3D_PCT(Vector3(maxs.x, maxs.y, mins.z), Vector2(0.0f, 1.0f), RGBA(1.0f, 0.0f, 1.0f));
	verts[10] = Vertex3D_PCT(Vector3(mins.x, maxs.y, mins.z), Vector2(1.0f, 1.0f), RGBA(0.0f, 0.0f, 1.0f));
	verts[11] = Vertex3D_PCT(Vector3(mins.x, maxs.y, maxs.z), Vector2(1.0f, 0.0f), RGBA(0.0f, 0.0f, 1.0f));
	//west
	verts[12] = Vertex3D_PCT(Vector3(mins.x, mins.y, maxs.z), Vector2(1.0f, 0.0f), RGBA(0.0f, 0.0f, 1.0f));
	verts[13] = Vertex3D_PCT(Vector3(mins.x, maxs.y, maxs.z), Vector2(0.0f, 0.0f), RGBA(1.0f, 0.0f, 1.0f));
	verts[14] = Vertex3D_PCT(Vector3(mins.x, mins.y, mins.z), Vector2(1.0f, 1.0f), RGBA(1.0f, 0.0f, 1.0f));

	verts[15] = Vertex3D_PCT(Vector3(mins.x, maxs.y, maxs.z), Vector2(0.0f, 0.0f), RGBA(1.0f, 0.0f, 1.0f));
	verts[16] = Vertex3D_PCT(Vector3(mins.x, maxs.y, mins.z), Vector2(0.0f, 1.0f), RGBA(0.0f, 0.0f, 1.0f));
	verts[17] = Vertex3D_PCT(Vector3(mins.x, mins.y, mins.z), Vector2(1.0f, 1.0f), RGBA(1.0f, 0.0f, 1.0f));
	//south	 
	verts[18] = Vertex3D_PCT(Vector3(mins.x, mins.y, maxs.z), Vector2(0.0f, 0.0f), RGBA(0.0f, 0.0f, 1.0f));
	verts[19] = Vertex3D_PCT(Vector3(mins.x, mins.y, mins.z), Vector2(0.0f, 1.0f), RGBA(1.0f, 1.0f, 0.0f));
	verts[20] = Vertex3D_PCT(Vector3(maxs.x, mins.y, maxs.z), Vector2(1.0f, 0.0f), RGBA(1.0f, 0.0f, 1.0f));

	verts[21] = Vertex3D_PCT(Vector3(maxs.x, mins.y, maxs.z), Vector2(1.0f, 0.0f), RGBA(1.0f, 0.0f, 1.0f));
	verts[22] = Vertex3D_PCT(Vector3(mins.x, mins.y, mins.z), Vector2(0.0f, 1.0f), RGBA(1.0f, 1.0f, 0.0f));
	verts[23] = Vertex3D_PCT(Vector3(maxs.x, mins.y, mins.z), Vector2(1.0f, 1.0f), RGBA(0.0f, 0.0f, 1.0f));
	//east
	verts[24] = Vertex3D_PCT(Vector3(maxs.x, maxs.y, maxs.z), Vector2(1.0f, 0.0f), RGBA(0.0f, 0.0f, 1.0f));
	verts[25] = Vertex3D_PCT(Vector3(maxs.x, mins.y, maxs.z), Vector2(0.0f, 0.0f), RGBA(1.0f, 1.0f, 0.0f));
	verts[26] = Vertex3D_PCT(Vector3(maxs.x, mins.y, mins.z), Vector2(0.0f, 1.0f), RGBA(1.0f, 0.0f, 1.0f));

	verts[27] = Vertex3D_PCT(Vector3(maxs.x, maxs.y, maxs.z), Vector2(1.0f, 0.0f), RGBA(1.0f, 0.0f, 1.0f));
	verts[28] = Vertex3D_PCT(Vector3(maxs.x, mins.y, mins.z), Vector2(0.0f, 1.0f), RGBA(0.0f, 0.0f, 1.0f));
	verts[29] = Vertex3D_PCT(Vector3(maxs.x, maxs.y, mins.z), Vector2(1.0f, 1.0f), RGBA(0.0f, 0.0f, 1.0f));
	//bot	 
	verts[30] = Vertex3D_PCT(Vector3(maxs.x, mins.y, mins.z), Vector2(1.0f, 0.0f), RGBA(0.0f, 0.0f, 1.0f));
	verts[31] = Vertex3D_PCT(Vector3(mins.x, mins.y, mins.z), Vector2(0.0f, 0.0f), RGBA(1.0f, 1.0f, 0.0f));
	verts[32] = Vertex3D_PCT(Vector3(mins.x, maxs.y, mins.z), Vector2(0.0f, 1.0f), RGBA(1.0f, 0.0f, 1.0f));

	verts[33] = Vertex3D_PCT(Vector3(maxs.x, mins.y, mins.z), Vector2(1.0f, 0.0f), RGBA(0.0f, 0.0f, 1.0f));
	verts[34] = Vertex3D_PCT(Vector3(mins.x, maxs.y, mins.z), Vector2(0.0f, 1.0f), RGBA(1.0f, 0.0f, 1.0f));
	verts[35] = Vertex3D_PCT(Vector3(maxs.x, maxs.y, mins.z), Vector2(1.0f, 1.0f), RGBA(0.0f, 0.0f, 1.0f));
	
	size = 36;
	return verts;
}
//////////////////////////////////////////////////////////////////////////

void OpenGLRenderer::MakeViewMatrix(Matrix4x4* result, Vector3& cameraPosition, Vector3& forwardVector)
{
	Vector3 Up(0.0f, 0.0f, 1.0f);
	Vector3 Jc = -1.0F * forwardVector;
	Jc.Normalize();
	Vector3 Ic = Vector3::CrossProduct(Up, Jc);
	Ic.Normalize();
	Vector3 Kc;
	Kc = Vector3::CrossProduct(Jc, Ic);
	Matrix4x4 TCI;
	TCI.MakeIdentity();
	TCI.m_translation.x = -cameraPosition.x;
	TCI.m_translation.y = -cameraPosition.y;
	TCI.m_translation.z = -cameraPosition.z;
	Matrix4x4 RCT;
	RCT.MakeIdentity();
	RCT.m_iBasis.x = Ic.x; RCT.m_iBasis.y = Jc.x; RCT.m_iBasis.z = Kc.x;
	RCT.m_jBasis.x = Ic.y; RCT.m_jBasis.y = Jc.y; RCT.m_jBasis.z = Kc.y;
	RCT.m_kBasis.x = Ic.z; RCT.m_kBasis.y = Jc.z; RCT.m_kBasis.z = Kc.z;
	Matrix4x4::Mult(TCI, RCT, (*result));
	//result->Transpose();
	return;
}
//////////////////////////////////////////////////////////////////////////
void OpenGLRenderer::MakePerspectiveMatrix(Matrix4x4* result, float f, float n, float aspect, float FOV)
{

	Vector4 iBasis(1.0f, 0.0f, 0.0f, 0.0f);
	Vector4 jBasis(0.0f, 0.0f, 1.0f, 0.0f);
	Vector4 kBasis(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 translation(0.0f, 0.0f, 0.0f, 1.0f);
	const Matrix4x4 ZYXMatrix(iBasis, jBasis, kBasis, translation);
	float fovRad = FOV*DEG2RAD;
	float size = atan2(fovRad, 2.0f);
	float w = size;
	float h = size;
	if (aspect > 1.0f)
	{
		w *= aspect;
	}
	else
	{
		h /= aspect;
	}
	float q = f / (f - n);

	Matrix4x4 perspective;
	perspective.m_iBasis = Vector4(1.0f / w, 0.0f, 0.0f, 0.0f);
	perspective.m_jBasis = Vector4(0.0f, 1.0f / h, 0.0f, 0.0f);
	perspective.m_kBasis = Vector4(0.0f, 0.0f, -q, -1.0f);
	perspective.m_translation = Vector4(0.0f, 0.0f, -2.0f*n*q, 0.0f);

	Matrix4x4::Mult(ZYXMatrix, perspective, (*result));
}
//////////////////////////////////////////////////////////////////////////
void OpenGLRenderer::MakeOrthogonalMatrix(Matrix4x4* result, float h, float w, float zmax, float zmin)
{
	result->m_iBasis = Vector4(2.0f / w, 0.0f, 0.0f, 0.0f);
	result->m_jBasis = Vector4(0.0f, 2.0f / h, 0.0f, 0.0f);
	result->m_kBasis = Vector4(0.0f, 0.0f, 2.0f / (zmax - zmin), 0.0f);
	result->m_translation = Vector4(-1.0f, -1.0f, -(zmax + zmin) / (zmax - zmin), 1.0f);

}
//////////////////////////////////////////////////////////////////////////
NewVertex3D_PCT* OpenGLRenderer::CreateSphereVerts(const Vector3& center, float radius, int& size)
{
	std::vector<Vector3> spherePoints;
	spherePoints.clear();
	unsigned int n = 50;
	float x;
	float y;
	float z;
	const float pi = 3.1415926f;
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < n; j++)
		{
			x = center.x + radius*(float)(sin(j*pi*2.0 / (n - 1))*cos(-pi / 2.0 + i*pi / (n - 1)));
			y = center.y + radius*(float)(cos(j*pi*2.0 / (n - 1))*(cos(-pi / 2.0 + i*pi / (n - 1))));
			z = center.z + radius*(float)(sin(-pi / 2.0 + i*pi / (n - 1)));
			spherePoints.push_back(Vector3(x, y, z));
		}
	}
	//u = 0.5 - arctan2(dz,dx)/2pi
	//v = 0.5 - arcsin(dy)/pi
	size = 6 * spherePoints.size();
	NewVertex3D_PCT* verts = new NewVertex3D_PCT[size];

	for (unsigned int i = 0; i < n - 1; i++)
	{
		for (unsigned int j = 0; j < n - 1; j++)
		{
			verts[i*n * 6 + j * 6] = NewVertex3D_PCT(spherePoints[i*n + j], Vector2((float)i / (float)n, (float)j / (float)n), Vector3(0.0f, 0.0f, 0.0f), RGBA(1.0F, 1.0F, 1.0F));
			verts[i*n * 6 + j * 6 + 1] = NewVertex3D_PCT(spherePoints[i*n + j + 1], Vector2((float)i / (float)n, (float)(j + 1) / (float)n), Vector3(0.0f, 0.0f, 0.0f), RGBA(1.0F, 1.0F, 1.0F));
			verts[i*n * 6 + j * 6 + 2] = NewVertex3D_PCT(spherePoints[(i + 1)*n + j + 1], Vector2((float)(i + 1) / (float)n, (float)(j + 1) / (float)n), Vector3(0.0f, 0.0f, 0.0f), RGBA(1.0F, 1.0F, 1.0F));

			verts[i*n * 6 + j * 6 + 3] = NewVertex3D_PCT(spherePoints[i*n + j], Vector2((float)i / (float)n, (float)j / (float)n), Vector3(0.0f, 0.0f, 0.0f), RGBA(1.0F, 1.0F, 1.0F));
			verts[i*n * 6 + j * 6 + 4] = NewVertex3D_PCT(spherePoints[(i + 1)*n + j + 1], Vector2((float)(i + 1) / (float)n, (float)(j + 1) / (float)n), Vector3(0.0f, 0.0f, 0.0f), RGBA(1.0F, 1.0F, 1.0F));
			verts[i*n * 6 + j * 6 + 5] = NewVertex3D_PCT(spherePoints[(i + 1)*n + j], Vector2((float)(i + 1) / (float)n, (float)j / (float)n), Vector3(0.0f, 0.0f, 0.0f), RGBA(1.0F, 1.0F, 1.0F));
		}
	}

	return verts;
}

NTBVertex3D_PCT* OpenGLRenderer::CreateNTBSphereVerts(const Vector3& center, float radius, int& size, const RGBA color)
{
	std::vector<Vector3> spherePoints;
	std::vector<Vector3> normal;
	std::vector<Vector3> tangent;
	std::vector<Vector3> biTangent;
	spherePoints.clear();
	unsigned int n = 50;
	float x;
	float y;
	float z;
	const float pi = 3.1415926f;
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < n; j++)
		{
			x = center.x + radius*(float)(sin(j*pi*2.0 / (n - 1))*cos(-pi / 2.0 + i*pi / (n - 1)));
			y = center.y + radius*(float)(cos(j*pi*2.0 / (n - 1))*(cos(-pi / 2.0 + i*pi / (n - 1))));
			z = center.z + radius*(float)(sin(-pi / 2.0 + i*pi / (n - 1)));
			spherePoints.push_back(Vector3(x, y, z));
			Vector3 normalVec = Vector3(x, y, z) - center;
			normalVec.Normalize();
			normal.push_back(normalVec);
			Vector3 tangentVec;
			tangentVec.x = (float)(cos(j*pi*2.0 / (n - 1))*cos(-pi / 2.0 + i*pi / (n - 1)));
			tangentVec.y = (float)(-sin(j*pi*2.0 / (n - 1))*(cos(-pi / 2.0 + i*pi / (n - 1))));
			tangentVec.z = 0.0f;
			tangentVec.Normalize();
			tangent.push_back(tangentVec);
			Vector3 biTangentVec = Vector3::CrossProduct(tangentVec,normalVec);
			biTangent.push_back(biTangentVec);
		}
	}
	//u = 0.5 - arctan2(dz,dx)/2pi
	//v = 0.5 - arcsin(dy)/pi
	size = 6 * spherePoints.size();
	NTBVertex3D_PCT* verts = new NTBVertex3D_PCT[size];

	for (unsigned int i = 0; i < n - 1; i++)
	{
		for (unsigned int j = 0; j < n - 1; j++)
		{
			verts[i*n * 6 + j * 6] = NTBVertex3D_PCT(spherePoints[i*n + j], Vector2((float)i / (float)n, (float)j / (float)n), normal[i*n + j], tangent[i*n + j], biTangent[i*n + j], color);
			verts[i*n * 6 + j * 6 + 1] = NTBVertex3D_PCT(spherePoints[i*n + j + 1], Vector2((float)i / (float)n, (float)(j + 1) / (float)n), normal[i*n + j + 1], tangent[i*n + j + 1], biTangent[i*n + j + 1], color);
			verts[i*n * 6 + j * 6 + 2] = NTBVertex3D_PCT(spherePoints[(i + 1)*n + j + 1], Vector2((float)(i + 1) / (float)n, (float)(j + 1) / (float)n), normal[(i + 1)*n + j + 1], tangent[(i + 1)*n + j + 1], biTangent[(i + 1)*n + j + 1], color);

			verts[i*n * 6 + j * 6 + 3] = NTBVertex3D_PCT(spherePoints[i*n + j], Vector2((float)i / (float)n, (float)j / (float)n), normal[i*n + j], tangent[i*n + j], biTangent[i*n + j], color);
			verts[i*n * 6 + j * 6 + 4] = NTBVertex3D_PCT(spherePoints[(i + 1)*n + j + 1], Vector2((float)(i + 1) / (float)n, (float)(j + 1) / (float)n), normal[(i + 1)*n + j + 1], tangent[(i + 1)*n + j + 1], biTangent[(i + 1)*n + j + 1], color);
			verts[i*n * 6 + j * 6 + 5] = NTBVertex3D_PCT(spherePoints[(i + 1)*n + j], Vector2((float)(i + 1) / (float)n, (float)j / (float)n), normal[(i + 1)*n + j], tangent[(i + 1)*n + j], biTangent[(i + 1)*n + j], color);
		}
	}

	return verts;
}