//==========================================================
//Button2.cpp
//==========================================================
#include "Button2.hpp"
#include "Engine/Renderer/GLMeshRenderer.hpp"
#include "Engine/Renderer/Fonts.hpp"
#include "Engine/Utility/xmlParser.h"
Button2::Button2()
	:BaseWidget2()
	,m_renderer(nullptr)
	,m_textRenderer(nullptr)
	,m_eventName("testEvent")
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("text", "OUT");
		m_forStates[i].fromCode.Set("textScale", 30.0f);
		m_forStates[i].fromCode.Set("textColor", RGBA(0.0F,1.0F,1.0F,1.0F));
	}
	m_currentStateProperty = m_forStates[0];
}

Button2::Button2(const XMLNode& node)
	:BaseWidget2(node)
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
	, m_eventName("testEvent")
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("text", "OUT");
		m_forStates[i].fromCode.Set("textScale", 30.0f);
		m_forStates[i].fromCode.Set("textColor", RGBA(0.0F, 1.0F, 1.0F, 1.0F));
	}
	m_currentStateProperty = m_forStates[0];
	//////////////////////////////////////////////////////////////////////////
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
		const char* text = stateNode.getAttribute("text");
		if (text != NULL)
		{
			std::string t = text;
			m_forStates[currentState].fromWidget.Set("text", t);
		}
		const char* eventName = stateNode.getAttribute("eventName");
		if (eventName != NULL)
		{
			m_eventName = eventName;
		}
		const char* textScale = stateNode.getAttribute("textScale");
		if (textScale != NULL)
		{
			float textScalef = (float)atof(textScale);
			m_forStates[currentState].fromWidget.Set("textScale", textScalef);
		}
		j++;
		stateNode = node.getChildNode(j);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Button2::Button2(BaseWidget2 copy)
	:BaseWidget2(copy)
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
{

}

///----------------------------------------------------------
///
///----------------------------------------------------------

void Button2::Draw(const Matrix4x4& Ortho, const Matrix4x4& I)
{
	if (m_isHidden)
		return;
	I;
	Ortho;
	if (m_renderer == nullptr || m_textRenderer == nullptr)
	{
		SetRenderer();
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Button2::SetText(const std::string& text, RGBA color, float scale, WidgetState2 state /*= WIDGET_STATE_ENABLE*/)
{
	m_forStates[state].fromCode.Set("text", text);
	m_forStates[state].fromCode.Set("textColor", color);
	m_forStates[state].fromCode.Set("textScale", scale);
}

void Button2::SetRenderer()
{
	m_renderer = new GLMeshRenderer(VAO_PCT);
	std::string backgroundTextureName = "";
	if (m_forStates[m_currentState].fromCode.Get("backgroundTextureName", backgroundTextureName) == RESULT_SUCCESS)
	{
		m_renderer->m_material.m_sampler.gTexDiffuse = Texture::CreateOrGetTexture(backgroundTextureName);
	}
	m_textRenderer = new GLMeshRenderer(VAO_PCT);
	m_textRenderer->m_material.m_sampler.gTexDiffuse = Texture::CreateOrGetTexture(s_font->m_fontTextureFileName);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Button2::Update(float deltaSecond, Vector2& mousePosition)
{
	deltaSecond;
	mousePosition;
	std::string backgroundTextureName = "";
	if (m_renderer != nullptr)
	{
		if (GetValueInCurrentState("backgroundTextureName", backgroundTextureName) == RESULT_SUCCESS)
		{
			m_renderer->m_material.m_sampler.gTexDiffuse = Texture::CreateOrGetTexture(backgroundTextureName);
		}
		else
		{
			unsigned char defaultWhiteTexel[3] = { 255, 255, 255 };
			m_renderer->m_material.m_sampler.gTexDiffuse = Texture::CreateMissingTexture("DefaultDiffuse", defaultWhiteTexel,Vector2(1.0f, 1.0f), 3);
		}
	}
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void Button2::SetEvent(const std::string& eventName)
{
	m_eventName = eventName;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Button2::CallEvent(NamedProperties* properties)
{
	if (m_eventName!="")
	{
		Utility::FireEvent(m_eventName, properties);
	}
	
}

