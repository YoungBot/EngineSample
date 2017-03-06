//==========================================================
//OpenGLRenerer.cpp
//==========================================================

#include "Engine/Renderer/OpenGLRenderer.hpp"

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

}

void OpenGLRenderer::Shutdown()
{

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
	HDC hdc				=	GetDC(myWindowHandle);

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


void OpenGLRenderer::DrawDisc(const Vector2& center, const float radious,const RGBA& tint)
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
void OpenGLRenderer::DrawTexturedQuadByRowNCol(const Texture& texture, const std::vector<Vector3>& vertices,const int row, const int col,const RGBA& tint)
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
	//std::vector<Vector2>::const_iterator textureCoordIter = textureCoordinate.begin();

	for(;vertexIter != vertices.end(); ++vertexIter)
	{
		const Vector3& vertex = (*vertexIter);
		
		//glTexCoord2f();
		glVertex3f(vertex.x,vertex.y,vertex.z);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
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