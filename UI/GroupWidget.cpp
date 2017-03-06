//==========================================================
//GroupWidget.cpp
//==========================================================
#include "GroupWidget.hpp"
#include "BaseWidget2.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Renderer/GLMeshRenderer.hpp"
#include "Engine/Renderer/Fonts.hpp"
#include "Engine/Math/Math2D.hpp"
#include "UISystem.hpp"
GroupWidget::GroupWidget()
	:BaseWidget2()
	,m_renderer(nullptr)
	,m_textRenderer(nullptr)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("offset", Vector2(000.0f, 00.0f));
		m_forStates[i].fromCode.Set("mins", Vector2(0.0f, 0.0f));
		m_forStates[i].fromCode.Set("text", "group");
		m_forStates[i].fromCode.Set("textScale", 30.0f);
		m_forStates[i].fromCode.Set("textColor", RGBA(0.0F, 0.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("BGColor", RGBA(0.0F, 0.0F, 0.0F, 1.0F));
	}
	m_widgets.clear();
}

void GroupWidget::Update(float deltaSeconds, Vector2& cursorPos)
{
	if (m_enableDrag)
	{
		Drag(cursorPos);
	}
	GetOffSet();
	for (unsigned int i = 0; i < m_widgets.size(); i++)
	{
		m_widgets[i]->Update(deltaSeconds, cursorPos);
	}
	m_currentStateProperty = m_forStates[m_currentState];
}
///----------------------------------------------------------
///
///----------------------------------------------------------


void GroupWidget::Draw(const Matrix4x4& ortho, const Matrix4x4& I)
{
	//if (m_renderer == nullptr || m_textRenderer == nullptr)
	//{
	//	m_renderer = new GLMeshRenderer(VAO_PCT);
	//	m_textRenderer = new GLMeshRenderer(VAO_PCT);
	//	m_textRenderer->m_material.m_sampler.gTexDiffuse = Texture::CreateOrGetTexture(s_font->m_fontTextureFileName);
	//}
	//int bottonVertsSize;
	//Vertex3D_PCT* buttonVerts = CreateVerts(bottonVertsSize);
	//m_renderer->m_mesh.UpdateVBO(buttonVerts, bottonVertsSize*sizeof(Vertex3D_PCT));
	//m_renderer->DrawShaderByMode(0, ortho, I,GL_LINE_LOOP);
	////////////////////////////////////////////////////////////////////////////
	//Vertex3D_PCT* textVerts = GetTextVerts(bottonVertsSize);
	//m_textRenderer->m_mesh.UpdateVBO(textVerts, bottonVertsSize*sizeof(Vertex3D_PCT));
	//m_textRenderer->DrawShader(bottonVertsSize, 0, ortho, I);
	//delete[] textVerts;
	//delete[] buttonVerts;
	for (unsigned int i = 0; i < m_widgets.size(); i++)
	{
		m_widgets[i]->Draw(ortho, I);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void GroupWidget::AddWidget(BaseWidget2* newWidget)
{
	m_widgets.push_back(newWidget);
	newWidget->m_parent = this;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void GroupWidget::SetDragable(bool enable)
{
	m_enableDrag = enable;
	if (enable == false)
	{
		m_mouseStartPosition = Vector2(0.0f, 0.0f);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void GroupWidget::SetWidgetByStyle(const std::string styleName)
{
	for (unsigned int i = 0; i < m_widgets.size(); i++)
	{
		UISystem::SetWidgetByStyle(styleName, m_widgets[i]);
	}
	
}

///----------------------------------------------------------
///
///----------------------------------------------------------

Vector2 GroupWidget::GetMins()
{
	Vector2 mins(10000.0f,10000.0f);
	for each (BaseWidget2* widget in m_widgets)
	{
		Vector2 currentMin = widget->GetWorldMins();
		if (currentMin.x< mins.x)
		{
			mins.x = currentMin.x;
		}
		if (currentMin.y < mins.y)
		{
			mins.y = currentMin.y;
		}
	}
	return mins;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vector2 GroupWidget::GetMaxs()
{
	Vector2 maxs(0.0f, 0.0f);
	for each (BaseWidget2* widget in m_widgets)
	{
		Vector2 currentMaxs = widget->GetWorldMaxs();
		if (currentMaxs.x > maxs.x)
		{
			maxs.x = currentMaxs.x;
		}
		if (currentMaxs.y > maxs.y)
		{
			maxs.y = currentMaxs.y;
		}
	}
	return maxs;
}

///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* GroupWidget::CreateVerts(int& size)
{
	Vector2 offset = GetOffSet();
	size = 0;
	Vector2 maxs = GetMaxs();
	Vector2 mins = GetMins();
	mins += offset;
	maxs += offset;
	RGBA BGColor;
	GetValueInCurrentState("BGColor", BGColor);
	std::vector<Vertex3D_PCT> verts;
	verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y, -1.0f), Vector2(0.0f, 0.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, -1.0f), Vector2(0.0f, 1.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y, -1.0f), Vector2(1.0f, 1.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, -1.0f), Vector2(1.0f, 0.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y, -1.0f), Vector2(0.0f, 0.0f), BGColor));
	//verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, -1.0f), Vector2(1.0f, 1.0f), BGColor));
	//verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y, -1.0f), Vector2(1.0f, 0.0f), BGColor));

	int finalSize = verts.size();
	Vertex3D_PCT edgeVerts[24];
	//finalSize += textSize;

	Vertex3D_PCT* passOutVerts = new Vertex3D_PCT[finalSize];
	memcpy(passOutVerts, verts.data(), verts.size()*sizeof(Vertex3D_PCT));
	size = finalSize;
	return passOutVerts;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* GroupWidget::GetTextVerts(int& size)
{
	Vector2 offset = GetOffSet();
	Vector2 maxs = GetMaxs();
	Vector2 mins = GetMins();
	std::string text;
	GetValueInCurrentState("text", text);
	float textScale;
	GetValueInCurrentState("textScale", textScale);
	RGBA color;
	GetValueInCurrentState("textColor", color);
	mins += offset;
	maxs += offset;
	return s_font->CreateCharactersVerts(Vector3(0.2f*(maxs.x - mins.x) + mins.x, -0.1f*(maxs.y - mins.y) + maxs.y, -1.0f), text, textScale, color, size);
}
