#pragma once
#include "Label.hpp"
#include "Engine/Renderer/GLMeshRenderer.hpp"
#include "Engine/Renderer/Fonts.hpp"
#include "Engine/Math/AABB2D.hpp"
#include "Engine/Utility/xmlParser.h"
#include "Engine/Input/InputSystem.hpp"

Label::Label()
	:BaseWidget2()
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
	, m_editable(false)
	, m_isEditing(false)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("text", "Label");
		m_forStates[i].fromCode.Set("textScale", 30.0f);
		m_forStates[i].fromCode.Set("textColor", RGBA(0.0F, 0.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("edgeThickness", 2.0f);
		m_forStates[i].fromCode.Set("mins", Vector2(1200.0f, 100.0f));
		m_forStates[i].fromCode.Set("maxs", Vector2(1300.0f, 140.0f));
	}
	m_currentStateProperty = m_forStates[0];
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Label::Label(const XMLNode& node)
	:BaseWidget2(node)
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
	, m_editable(false)
	, m_isEditing(false)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("text", "Label");
		m_forStates[i].fromCode.Set("textScale", 30.0f);
		m_forStates[i].fromCode.Set("textColor", RGBA(0.0F, 0.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("edgeThickness", 2.0f);
		m_forStates[i].fromCode.Set("mins", Vector2(1200.0f, 100.0f));
		m_forStates[i].fromCode.Set("maxs", Vector2(1300.0f, 140.0f));
	}
	int j = 0;
	XMLNode stateNode = node.getChildNode(j);
	while (!stateNode.isEmpty())
	{
		SetColorFromXMLByNameInState("textColor", stateNode, PROPERTIES_FROM_BASE);
		//////////////////////////////////////////////////////////////////////////
		const char* stateNum = stateNode.getAttribute("state");
		int currentState;
		if (stateNum != NULL)
			currentState = atoi(stateNum);
		else
			continue;
		//////////////////////////////////////////////////////////////////////////
		const char* mins = stateNode.getAttribute("mins");
		if (mins != NULL)
		{
			std::string str = mins;
			std::vector<std::string> minsVec;
			float minsChar[2];
			minsVec.push_back(Utility::CutString(str, ',').c_str());
			minsVec.push_back(Utility::CutString(str, ',').c_str());

			for (unsigned int i = 0; i < minsVec.size(); i++)
			{
				if (minsVec[i] == "")
					minsChar[i] = 0.0f;
				else
					minsChar[i] = (float)atof(minsVec[i].c_str());
			}
			Vector2 currentMins = Vector2(minsChar[0], minsChar[1]);
			m_forStates[currentState].fromWidget.Set("mins", currentMins);
			//////////////////////////////////////////////////////////////////////////
			const char* maxs = stateNode.getAttribute("maxs");
			str = maxs;
			std::vector<std::string> maxsVec;
			float maxsChar[2];
			maxsVec.push_back(Utility::CutString(str, ',').c_str());
			maxsVec.push_back(Utility::CutString(str, ',').c_str());

			for (unsigned int i = 0; i < maxsVec.size(); i++)
			{
				if (maxsVec[i] == "")
					maxsChar[i] = 0.0f;
				else
					maxsChar[i] = (float)atof(maxsVec[i].c_str());
			}
			Vector2 currentMaxs = Vector2(maxsChar[0], maxsChar[1]);
			m_forStates[currentState].fromWidget.Set("maxs", currentMaxs);

		}
		//////////////////////////////////////////////////////////////////////////
		SetColorFromXMLByNameInState("textColor", stateNode, PROPERTIES_FROM_BASE);
		//////////////////////////////////////////////////////////////////////////
		const char* text = stateNode.getAttribute("text");
		if (text != NULL)
		{
			std::string t = text;
			m_forStates[currentState].fromWidget.Set("text", t);
		}
		//////////////////////////////////////////////////////////////////////////
		const char* textScale = stateNode.getAttribute("textScale");
		if (textScale != NULL)
		{
			float textScalef = (float)atof(textScale);
			m_forStates[currentState].fromWidget.Set("textScale", textScalef);
		}
		//////////////////////////////////////////////////////////////////////////
		j++;
		stateNode = node.getChildNode(j);
	}
	m_currentStateProperty = m_forStates[0];
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Label::Label(BaseWidget2 copy)
	:BaseWidget2(copy)
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
{

}

///----------------------------------------------------------
///
///----------------------------------------------------------

void Label::Draw(const Matrix4x4& Ortho, const Matrix4x4& I)
{
	if (m_isHidden)
		return;
	if (m_renderer == nullptr || m_textRenderer == nullptr)
	{
		SetRenderer();
	}
	int bottonVertsSize;
	Vertex3D_PCT* buttonVerts = CreateVerts(bottonVertsSize);
	m_renderer->m_mesh.UpdateVBO(buttonVerts, bottonVertsSize*sizeof(Vertex3D_PCT));
	m_renderer->DrawShader(bottonVertsSize, 0, Ortho, I);
	//////////////////////////////////////////////////////////////////////////
	Vertex3D_PCT* textVerts = GetTextVerts(bottonVertsSize);
	m_textRenderer->m_mesh.UpdateVBO(textVerts, bottonVertsSize*sizeof(Vertex3D_PCT));
	m_textRenderer->DrawShader(bottonVertsSize, 0, Ortho, I);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Label::SetText(const std::string& text, RGBA color, float scale, WidgetState2 state /*= WIDGET_STATE_ENABLE_*/)
{
	m_forStates[state].fromCode.Set("text", text);
	m_forStates[state].fromCode.Set("textColor", color);
	m_forStates[state].fromCode.Set("textScale", scale);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Label::SetRenderer()
{
	m_renderer = new GLMeshRenderer(VAO_PCT);
	m_textRenderer = new GLMeshRenderer(VAO_PCT);
	m_textRenderer->m_material.m_sampler.gTexDiffuse = Texture::CreateOrGetTexture(s_font->m_fontTextureFileName);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Label::Update(float deltaSecond, Vector2& mousePosition)
{
	deltaSecond;
	m_currentStateProperty = m_forStates[m_currentState];
	Vector2 offset = GetOffSet();
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	maxs += offset;
	mins += offset;
	AABB2D box(mins, maxs);
	if (s_theInputSystem->IsMouseButtonDown(VK_LBUTTON) && s_theInputSystem->IsKeyDown('C'))
	{
		if (box.IsPointInside(mousePosition))
		{
			SetDragable(true);
		}		
	}
	else
	{
		SetDragable(false);
	}
		
	if (m_enableDrag)
	{
		Drag(mousePosition);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* Label::CreateVerts(int& size)
{
	Vector2 offset = GetOffSet();
	size = 0;
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	RGBA BGColor;
	GetValueInCurrentState("BGColor", BGColor);
	std::vector<Vertex3D_PCT> verts;
	mins += offset;
	maxs += offset;
	verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y, 0.0f), Vector2(0.0f, 1.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), BGColor));

	verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y, 0.0f), Vector2(1.0f, 0.0f), BGColor));

	int finalSize = verts.size();
	int textSize = 6;
	Vertex3D_PCT edgeVerts[6];
	GetEdgeVerts(edgeVerts);
	finalSize += textSize;

	Vertex3D_PCT* passOutVerts = new Vertex3D_PCT[finalSize];
	memcpy(passOutVerts, verts.data(), verts.size()*sizeof(Vertex3D_PCT));
	memcpy(&passOutVerts[verts.size()], edgeVerts, textSize*sizeof(Vertex3D_PCT));

	size = finalSize;
	return passOutVerts;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Label::GetEdgeVerts(Vertex3D_PCT* edgeVerts)
{
	Vector2 offset = GetOffSet();
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	float edgeThickness;
	GetValueInCurrentState("edgeThickness", edgeThickness);
	RGBA edgeColor;
	GetValueInCurrentState("edgeColor", edgeColor);
	mins += offset;
	maxs += offset;
	edgeVerts[0] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, maxs.y + edgeThickness, 0.0f), Vector2(0.0f, 0.0f), edgeColor);
	edgeVerts[1] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, mins.y - edgeThickness, 0.0f), Vector2(0.0f, 1.0f), edgeColor);
	edgeVerts[2] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, mins.y - edgeThickness, 0.0f), Vector2(1.0f, 1.0f), edgeColor);
	edgeVerts[3] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, maxs.y + edgeThickness, 0.0f), Vector2(0.0f, 0.0f), edgeColor);
	edgeVerts[4] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, mins.y - edgeThickness, 0.0f), Vector2(1.0f, 1.0f), edgeColor);
	edgeVerts[5] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, maxs.y + edgeThickness, 0.0f), Vector2(1.0f, 0.0f), edgeColor);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* Label::GetTextVerts(int& size)
{
	Vector2 offset = GetOffSet();
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
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
