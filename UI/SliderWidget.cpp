//==========================================================
//SliderWidget.cpp
//==========================================================
#include "SliderWidget.hpp"
#include "Engine/Renderer/GLMeshRenderer.hpp"
#include "Engine/Renderer/Fonts.hpp"
#include "Engine/Math/AABB2D.hpp"
#include "Engine/Utility/xmlParser.h"
#include "Engine/Input/InputSystem.hpp"

SliderWidget::SliderWidget()
	:BaseWidget2()
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
	,m_percentage(0.0f)
	,m_mouseStartPositionForSlider(Vector2(0.0f,0.0f))
	, m_startSlide(false)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("text", "Label");
		m_forStates[i].fromCode.Set("textScale", 20.0f);
		m_forStates[i].fromCode.Set("textColor", RGBA(1.0F, 1.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("edgeThickness", 2.0f);
		m_forStates[i].fromCode.Set("mins", Vector2(200.0f, 320.0f));
		m_forStates[i].fromCode.Set("maxs", Vector2(600.0f, 340.0f));
	}
	m_currentStateProperty = m_forStates[0];
}
///----------------------------------------------------------
///
///----------------------------------------------------------

SliderWidget::SliderWidget(const XMLNode& node)
	:BaseWidget2(node)
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
	, m_percentage(0.0f)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("text", "Label");
		m_forStates[i].fromCode.Set("textScale", 20.0f);
		m_forStates[i].fromCode.Set("textColor", RGBA(1.0F, 1.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("edgeThickness", 2.0f);
		m_forStates[i].fromCode.Set("mins", Vector2(200.0f, 320.0f));
		m_forStates[i].fromCode.Set("maxs", Vector2(600.0f, 340.0f));
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

SliderWidget::SliderWidget(SliderWidget* slider)
	:BaseWidget2(*(BaseWidget2*)slider)
	,m_percentage(slider->m_percentage)
	,m_renderer(nullptr)
	,m_textRenderer(nullptr)
	,m_mouseStartPositionForSlider(slider->m_mouseStartPositionForSlider)
	,m_startSlide(slider->m_startSlide)
{

}

///----------------------------------------------------------
///
///----------------------------------------------------------

void SliderWidget::Draw(const Matrix4x4& Ortho, const Matrix4x4& I)
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

void SliderWidget::SetRenderer()
{
	m_renderer = new GLMeshRenderer(VAO_PCT);
	m_textRenderer = new GLMeshRenderer(VAO_PCT);
	m_textRenderer->m_material.m_sampler.gTexDiffuse = Texture::CreateOrGetTexture(s_font->m_fontTextureFileName);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void SliderWidget::Update(float deltaSecond, Vector2& mousePosition)
{
	deltaSecond;
	m_currentStateProperty = m_forStates[m_currentState];
	Vector2 offset = GetOffSet();
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	mins += offset;
	maxs += offset;
	AABB2D box(mins, maxs);
	if (s_theInputSystem->IsMouseButtonDown(VK_LBUTTON) && s_theInputSystem->IsKeyDown('C'))
	{
		if (box.IsPointInside(mousePosition))
		{
			SetDragable(true);
		}
	}
	else
		SetDragable(false);
	if (m_enableDrag)
	{
		Drag(mousePosition);
		return;
	}
	if (s_theInputSystem->IsMouseButtonDown(VK_LBUTTON))
	{
		
		float boxSize = maxs.y - mins.y;
		float startX = MathUtils::Interpolate(mins.x, maxs.x - boxSize, m_percentage);
		Vector2 boxMins = Vector2(startX, mins.y);
		Vector2 boxMaxs = Vector2(startX + boxSize, maxs.y);
		AABB2D sliderBox(boxMins, boxMaxs);
		if (sliderBox.IsPointInside(mousePosition))
		{
			m_startSlide = true;
		}
	}
	else
	{
		m_startSlide = false;
		m_mouseStartPositionForSlider = Vector2(0.0f, 0.0f);
	}
	if (m_startSlide)
	{
		if (m_mouseStartPositionForSlider == Vector2(0.0f,0.0f))
		{
			m_mouseStartPositionForSlider = mousePosition;
		}
		float thisoffset = mousePosition.x - m_mouseStartPositionForSlider.x;
		float percentage = thisoffset / (maxs.x - mins.x);
		m_percentage += percentage;
		m_mouseStartPositionForSlider = mousePosition;
	}

	m_percentage = MathUtils::Clamp(m_percentage, 0.0f, 1.0f);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* SliderWidget::CreateVerts(int& size)
{
	size = 0;
	Vector2 offset = GetOffSet();
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	mins += offset;
	maxs += offset;
	RGBA BGColor;
	GetValueInCurrentState("BGColor", BGColor);
	std::vector<Vertex3D_PCT> verts;
	verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y, 0.0f), Vector2(0.0f, 1.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), BGColor));

	verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y, 0.0f), Vector2(1.0f, 0.0f), BGColor));

	int finalSize = verts.size();
	int textSize = 6;
	Vertex3D_PCT edgeVerts[6];
	GetSliderVerts(edgeVerts);
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

void SliderWidget::GetSliderVerts(Vertex3D_PCT* sliderVerts)
{
	Vector2 offset = GetOffSet();
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	mins += offset;
	maxs += offset;
	float boxSize = maxs.y - mins.y;
	float startX = MathUtils::Interpolate(mins.x, maxs.x-boxSize, m_percentage);
	Vector2 boxMins = Vector2(startX, mins.y);
	Vector2 boxMaxs = Vector2(startX + boxSize, maxs.y);

	RGBA edgeColor;
	GetValueInCurrentState("edgeColor", edgeColor);

	sliderVerts[0] = Vertex3D_PCT(Vector3(boxMins.x, boxMaxs.y, -1.0f), Vector2(0.0f, 0.0f), edgeColor);
	sliderVerts[1] = Vertex3D_PCT(Vector3(boxMins.x, boxMins.y, -1.0f), Vector2(0.0f, 1.0f), edgeColor);
	sliderVerts[2] = Vertex3D_PCT(Vector3(boxMaxs.x, boxMins.y, -1.0f), Vector2(1.0f, 1.0f), edgeColor);
	sliderVerts[3] = Vertex3D_PCT(Vector3(boxMins.x, boxMaxs.y, -1.0f), Vector2(0.0f, 0.0f), edgeColor);
	sliderVerts[4] = Vertex3D_PCT(Vector3(boxMaxs.x, boxMins.y, -1.0f), Vector2(1.0f, 1.0f), edgeColor);
	sliderVerts[5] = Vertex3D_PCT(Vector3(boxMaxs.x, boxMaxs.y, -1.0f), Vector2(1.0f, 0.0f), edgeColor);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* SliderWidget::GetTextVerts(int& size)
{
	Vector2 offset = GetOffSet();
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	mins += offset;
	maxs += offset;
	int percentageInt = (int)(m_percentage * 100);
	std::string textInt;
	std::string textFloat;
	float percentageFloat = m_percentage *100.0f;
	percentageFloat -= percentageInt;
	textInt = std::to_string(percentageInt);
	textFloat = std::to_string(percentageFloat);;
	textFloat = textFloat.substr(1, 3);
	textInt = textInt + textFloat + '%';
	float textScale;
	GetValueInCurrentState("textScale", textScale);
	RGBA color;
	GetValueInCurrentState("textColor", color);
	float boxSize = maxs.y - mins.y;
	float startX = MathUtils::Interpolate(mins.x, maxs.x - boxSize, m_percentage);
	return s_font->CreateCharactersVerts(Vector3(startX, maxs.y + textScale, -1.0f), textInt, textScale, color, size);
}
///----------------------------------------------------------
///
///----------------------------------------------------------
