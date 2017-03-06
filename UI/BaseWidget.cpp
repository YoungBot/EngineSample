//==========================================================
//BaseWidget.cpp
//==========================================================
#include "BaseWidget.hpp"
#include "Engine/Renderer/OpenGLRenderer.hpp"
#include "Engine/Renderer/GLMeshRenderer.hpp"
#include "Engine/Renderer/Fonts.hpp"
#include "Engine/Input/InputSystem.hpp"
#include "Engine/EventSystem/NamedProperties.hpp"
#include "Engine/EventSystem/KeyFrameSequence.hpp"
#include "Engine/Utility/xmlParser.h"

BaseWidget::BaseWidget(const Vector2& mins, const Vector2& maxs, const RGBA& BGcolor, const RGBA& edgeColor, const float edgeThickness)
	:m_currentState(WIDGET_STATE_ENABLE)
	,m_timeCheck(0.0f)
	,m_type(WIDGET_TYPE_DEFAULT)
{
	for (int i = 0; i < NUM_WIDGET_STATE; i++)
	{
		m_mins[i] = mins;
		m_maxs[i] = maxs;
		m_BGColor[i] = BGcolor;
		m_edgeColor[i] = edgeColor;
		m_text[i] = "button";
		m_edgeThickness[i] = edgeThickness;
		m_fontFileName[i] = s_font->m_fontTextureFileName;
		m_textColor[i] = RGBA(1.0f, 1.0f, 1.0f, 1.0f);
		m_textScale[i] = 30.0f;
	}

	m_properties[WIDGET_STATE_SELECTING] = NamedProperties();
	KeyFrameSequence<RGBA> sequence;
	KeyFrame<RGBA> key1;
	key1.m_parametric = 0.0f;
	key1.m_valueAtParametric = RGBA(1.0f, 1.0f, 0.0f, 1.0f);
	KeyFrame<RGBA> key2;
	key2.m_parametric = 0.1f;
	key2.m_valueAtParametric = RGBA(1.0f, 0.0f, 0.0f, 1.0f);
	KeyFrame<RGBA> key3;
	key3.m_parametric = 0.4f;
	key3.m_valueAtParametric = RGBA(0.0f, 1.0f, 0.0f, 1.0f);
	KeyFrame<RGBA> key4;
	key4.m_parametric = 1.0f;
	key4.m_valueAtParametric = RGBA(0.0f, 1.0f, 1.0f, 1.0f);
	sequence.AddKeyFrame(key1);
	sequence.AddKeyFrame(key2);
	sequence.AddKeyFrame(key3);
	sequence.AddKeyFrame(key4);
	m_properties[WIDGET_STATE_SELECTING].Set("bgColor", sequence);
}

BaseWidget::BaseWidget()
	:m_currentState(WIDGET_STATE_ENABLE)
	, m_timeCheck(0.0f)
	, m_type(WIDGET_TYPE_DEFAULT)
{
	for (int i = 0; i < NUM_WIDGET_STATE; i++)
	{
		m_mins[i] = Vector2(0.0f,0.0f);
		m_maxs[i] = Vector2(100.0f, 100.0f);
		m_BGColor[i] = RGBA(1.0f,0.0f,1.0f,1.0f);
		m_edgeColor[i] = RGBA(0.5f, 0.0f, 0.5f, 1.0f);
		m_text[i] = "BW";
		m_edgeThickness[i] = 5.0f;
		m_fontFileName[i] = s_font->m_fontTextureFileName;
		m_textColor[i] = RGBA(1.0f, 1.0f, 1.0f, 1.0f);
		m_textScale[i] = 30.0f;
	}
}

///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* BaseWidget::CreateVerts(int& size)
{
	
	size = 0;
	std::vector<Vertex3D_PCT> verts;	
	verts.push_back(Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x, m_maxs[WIDGET_CURRENT_STATE].y,0.0f), Vector2(0.0f,0.0f), m_BGColor[WIDGET_CURRENT_STATE]));
	verts.push_back(Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x, m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(0.0f, 1.0f), m_BGColor[WIDGET_CURRENT_STATE]));
	verts.push_back(Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x, m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 1.0f), m_BGColor[WIDGET_CURRENT_STATE]));
											   							 
	verts.push_back(Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x, m_maxs[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(0.0f, 0.0f), m_BGColor[WIDGET_CURRENT_STATE]));
	verts.push_back(Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x, m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 1.0f), m_BGColor[WIDGET_CURRENT_STATE]));
	verts.push_back(Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x, m_maxs[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 0.0f), m_BGColor[WIDGET_CURRENT_STATE]));

	int finalSize = verts.size();
	int textSize = 24;
	Vertex3D_PCT edgeVerts[24];
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

void BaseWidget::SetRenderer()
{
	m_renderer = new GLMeshRenderer(VAO_PCT);
	m_textRenderer = new GLMeshRenderer(VAO_PCT);
	m_textRenderer->m_material.m_sampler.gTexDiffuse = Texture::CreateOrGetTexture(m_fontFileName[WIDGET_CURRENT_STATE]);
	// nothing here right now
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget::SetAnimatedProperty()
{

}
///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget::CopyData()
{
	m_mins[0] = m_mins[m_currentState];
	m_maxs[0] = m_maxs[m_currentState];
	m_BGColor[0] = m_BGColor[m_currentState];
	m_edgeColor[0] = m_edgeColor[m_currentState];
	m_text[0] = "button";
	m_edgeThickness[0] = m_edgeThickness[m_currentState];
	m_fontFileName[0] = s_font->m_fontTextureFileName;
	m_textColor[0] = m_textColor[m_currentState];
	m_textScale[0] = m_textScale[m_currentState];
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget::SetDefaultByXML(const XMLNode& node)
{
	float defaultEdgeThickness;
	RGBA defaultBGColor;
	RGBA defaultEdgeColor;
	RGBA defaultTextColor;
	Vector2 defaultSize;
	const char* edgeThickness = node.getAttribute("edgeThickness");

	if (edgeThickness == NULL)
	{
		defaultEdgeThickness = 6.6f;
	}
	else
	{
		defaultEdgeThickness =(float)atof(edgeThickness);
	}

	const char* defaultText = node.getAttribute("text");
	if (defaultText == NULL)
		defaultText = "BAD";

	std::string color = node.getAttribute("BGColor");
	std::vector<std::string> colorRgbaStr;
	unsigned char colorChar[4];
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	for (unsigned int i = 0; i < colorRgbaStr.size(); i++)
	{
		if (colorRgbaStr[i] == "")
			colorChar[i] = 0;
		else
			colorChar[i] = (unsigned char)atoi(colorRgbaStr[i].c_str());
		if (i == 3 && colorRgbaStr[3] == "")
		{
			colorChar[i] = 255;
		}
	}
	defaultBGColor = RGBA(colorChar[0], colorChar[1], colorChar[2], colorChar[3]);

	color = node.getAttribute("edgeColor");
	colorRgbaStr.clear();
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	for (unsigned int i = 0; i < colorRgbaStr.size(); i++)
	{
		if (colorRgbaStr[i] == "")
			colorChar[i] = 0;
		else
			colorChar[i] = (unsigned char)atoi(colorRgbaStr[i].c_str());
		if (i == 3 && colorRgbaStr[3] == "")
		{
			colorChar[i] = 255;
		}
	}
	defaultEdgeColor = RGBA(colorChar[0], colorChar[1], colorChar[2], colorChar[3]);

	color = node.getAttribute("textColor");
	colorRgbaStr.clear();
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
	for (unsigned int i = 0; i < colorRgbaStr.size(); i++)
	{
		if (colorRgbaStr[i] == "")
			colorChar[i] = 0;
		else
			colorChar[i] = (unsigned char)atoi(colorRgbaStr[i].c_str());
		if (i == 3 && colorRgbaStr[3] == "")
		{
			colorChar[i] = 255;
		}
	}
	defaultTextColor = RGBA(colorChar[0], colorChar[1], colorChar[2], colorChar[3]);

	//Utility::CutString(color, ',');
	for (int i = 0; i < NUM_WIDGET_STATE; i++)
	{
		m_mins[i] = Vector2(0.0f, 0.0f);
		m_maxs[i] = Vector2(100.0f, 100.0f);
		m_BGColor[i] = defaultBGColor;
		m_edgeColor[i] = defaultEdgeColor;
		m_text[i] = defaultText;
		m_edgeThickness[i] = defaultEdgeThickness;
		m_textColor[i] = defaultTextColor;
		m_textScale[i] = 30.0f;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget::SetStateByXML(WidgetState state, const XMLNode& node)
{
	const char* edgeThickness = node.getAttribute("edgeThickness");
	if (edgeThickness != NULL)
	{
		m_edgeThickness[state] = (float)atof(edgeThickness);
	}
	const char* textScale = node.getAttribute("textScale");
	if (textScale != NULL)
	{
		m_textScale[state] = (float)atof(textScale);
	}
	const char* defaultText = node.getAttribute("text");
	if (defaultText != NULL)
		m_text[state] = defaultText;

	const char* colorStr = node.getAttribute("BGColor");
	//////////////////////////////////////////////////////////////////////////
	if (colorStr!=NULL)
	{
		std::string color = colorStr;
		std::vector<std::string> colorRgbaStr;
		unsigned char colorChar[4];
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		for (unsigned int i = 0; i < colorRgbaStr.size(); i++)
		{
			if (colorRgbaStr[i] == "")
				colorChar[i] = 0;
			else
				colorChar[i] = (unsigned char)atoi(colorRgbaStr[i].c_str());
			if (i == 3 && colorRgbaStr[3] == "")
			{
				colorChar[i] = 255;
			}
		}
		m_BGColor[state] = RGBA(colorChar[0], colorChar[1], colorChar[2], colorChar[3]);
	}
	//////////////////////////////////////////////////////////////////////////
	colorStr = node.getAttribute("textColor");
	if (colorStr!=NULL)
	{
		std::string color = colorStr;
		std::vector<std::string> colorRgbaStr;
		unsigned char colorChar[4];
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		for (unsigned int i = 0; i < colorRgbaStr.size(); i++)
		{
			if (colorRgbaStr[i] == "")
				colorChar[i] = 0;
			else
				colorChar[i] = (unsigned char)atoi(colorRgbaStr[i].c_str());
			if (i == 3 && colorRgbaStr[3] == "")
			{
				colorChar[i] = 255;
			}
		}
		m_textColor[state] = RGBA(colorChar[0], colorChar[1], colorChar[2], colorChar[3]);
	}
	//////////////////////////////////////////////////////////////////////////
	colorStr = node.getAttribute("edgeColor");
	if (colorStr!=NULL)
	{
		std::string color = colorStr;
		std::vector<std::string> colorRgbaStr;
		unsigned char colorChar[4];
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		colorRgbaStr.push_back(Utility::CutString(color, ',').c_str());
		for (unsigned int i = 0; i < colorRgbaStr.size(); i++)
		{
			if (colorRgbaStr[i] == "")
				colorChar[i] = 0;
			else
				colorChar[i] = (unsigned char)atoi(colorRgbaStr[i].c_str());
			if (i == 3 && colorRgbaStr[3] == "")
			{
				colorChar[i] = 255;
			}
		}
		m_edgeColor[state] = RGBA(colorChar[0], colorChar[1], colorChar[2], colorChar[3]);
	}
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget::GetEdgeVerts(Vertex3D_PCT* edgeVerts)
{
	//left
	edgeVerts[0] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x - m_edgeThickness[WIDGET_CURRENT_STATE], m_maxs[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(0.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[1] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x - m_edgeThickness[WIDGET_CURRENT_STATE], m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(0.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[2] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x, m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[3] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x - m_edgeThickness[WIDGET_CURRENT_STATE], m_maxs[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(0.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[4] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x, m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[5] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x, m_maxs[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	//right
	edgeVerts[6] = Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x, m_maxs[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(0.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[7] = Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x, m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(0.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[8] = Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x + m_edgeThickness[WIDGET_CURRENT_STATE], m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[9] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x, m_maxs[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(0.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[10] = Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x + m_edgeThickness[WIDGET_CURRENT_STATE], m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[11] = Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x + m_edgeThickness[WIDGET_CURRENT_STATE], m_maxs[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	//top
	edgeVerts[12] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x - m_edgeThickness[WIDGET_CURRENT_STATE], m_maxs[WIDGET_CURRENT_STATE].y + m_edgeThickness[WIDGET_CURRENT_STATE], 0.0f), Vector2(0.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[13] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x - m_edgeThickness[WIDGET_CURRENT_STATE], m_maxs[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(0.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[14] = Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x + m_edgeThickness[WIDGET_CURRENT_STATE], m_maxs[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[15] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x - m_edgeThickness[WIDGET_CURRENT_STATE], m_maxs[WIDGET_CURRENT_STATE].y + m_edgeThickness[WIDGET_CURRENT_STATE], 0.0f), Vector2(0.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[16] = Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x + m_edgeThickness[WIDGET_CURRENT_STATE], m_maxs[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[17] = Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x + m_edgeThickness[WIDGET_CURRENT_STATE], m_maxs[WIDGET_CURRENT_STATE].y + m_edgeThickness[WIDGET_CURRENT_STATE], 0.0f), Vector2(1.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	//bot
	edgeVerts[18] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x - m_edgeThickness[WIDGET_CURRENT_STATE], m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(0.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[19] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x - m_edgeThickness[WIDGET_CURRENT_STATE], m_mins[WIDGET_CURRENT_STATE].y -m_edgeThickness[WIDGET_CURRENT_STATE], 0.0f), Vector2(0.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[20] = Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x + m_edgeThickness[WIDGET_CURRENT_STATE], m_mins[WIDGET_CURRENT_STATE].y - m_edgeThickness[WIDGET_CURRENT_STATE], 0.0f), Vector2(1.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[21] = Vertex3D_PCT(Vector3(m_mins[WIDGET_CURRENT_STATE].x - m_edgeThickness[WIDGET_CURRENT_STATE], m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(0.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[22] = Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x + m_edgeThickness[WIDGET_CURRENT_STATE], m_mins[WIDGET_CURRENT_STATE].y - m_edgeThickness[WIDGET_CURRENT_STATE], 0.0f), Vector2(1.0f, 1.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	edgeVerts[23] = Vertex3D_PCT(Vector3(m_maxs[WIDGET_CURRENT_STATE].x + m_edgeThickness[WIDGET_CURRENT_STATE], m_mins[WIDGET_CURRENT_STATE].y, 0.0f), Vector2(1.0f, 0.0f), m_edgeColor[WIDGET_CURRENT_STATE]);
	
	return;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* BaseWidget::GetTextVerts(int& size)
{
	return s_font->CreateCharactersVerts(Vector3(0.2f*(m_maxs[WIDGET_CURRENT_STATE].x - m_mins[WIDGET_CURRENT_STATE].x) + m_mins[WIDGET_CURRENT_STATE].x, 0.5f*(m_maxs[WIDGET_CURRENT_STATE].y - m_mins[WIDGET_CURRENT_STATE].y) + m_mins[WIDGET_CURRENT_STATE].y, -1.0f),m_text[WIDGET_CURRENT_STATE],m_textScale[WIDGET_CURRENT_STATE],m_textColor[WIDGET_CURRENT_STATE],size);
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget::Draw(const Matrix4x4& Ortho, const Matrix4x4& I)
{
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

void BaseWidget::SetText(const std::string& text, RGBA color, float scale,WidgetState state)
{
	m_text[state] = text;
	m_textColor[state] = color;
	m_textScale[state] = scale;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void BaseWidget::Update(float deltaSecond, Vector2& mousePosition)
{
	mousePosition;
	m_timeCheck += deltaSecond;
	KeyFrameSequence<RGBA> resultC;
	m_properties[WIDGET_STATE_SELECTING].Get("bgColor", resultC);
	resultC.GetValueAtParametric(m_timeCheck);
}
