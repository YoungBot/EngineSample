//==========================================================
//ProgressBar.cpp
//==========================================================
#include "ProgressBar.hpp"
#include "Engine/Renderer/GLMeshRenderer.hpp"
#include "Engine/Renderer/Fonts.hpp"
#include "Engine/Math/Math2D.hpp"
#include <string>
ProgressBar::ProgressBar()
	:BaseWidget2()
	,m_percentage(0.0f)
	,m_renderer(nullptr)
	,m_textRenderer(nullptr)
	,m_progressBarStyle(PROGRESSBAR_LEFT_TO_RIGHT)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("filledColor", RGBA(1.0F, 0.0F, 0.0F, 1.0F));
		m_forStates[i].fromCode.Set("emptyColor", RGBA(0.0F, 0.0F, 0.0F, 1.0F));
		m_forStates[i].fromCode.Set("textColor", RGBA(1.0F, 1.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("textScale", 30.0f);
		m_forStates[i].fromCode.Set("mins", Vector2(800.0f, 100.0f));
		m_forStates[i].fromCode.Set("maxs", Vector2(900.0f, 200.0f));
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

ProgressBar::ProgressBar(const XMLNode& node)
	:BaseWidget2(node)
	, m_percentage(0.0f)
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
	, m_progressBarStyle(PROGRESSBAR_LEFT_TO_RIGHT)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("filledColor", RGBA(1.0F, 0.0F, 0.0F, 1.0F));
		m_forStates[i].fromCode.Set("emptyColor", RGBA(0.0F, 0.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("textColor", RGBA(1.0F, 1.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("textScale", 30.0f);
		m_forStates[i].fromCode.Set("mins", Vector2(800.0f, 100.0f));
		m_forStates[i].fromCode.Set("maxs", Vector2(900.0f, 200.0f));
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
		const char* position = stateNode.getAttribute("position");
		if (position != NULL)
		{
			std::string str = position;
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
			Vector2 currentPosition = Vector2(minsChar[0], minsChar[1]);
			m_forStates[currentState].fromWidget.Set("position", currentPosition);

		}
		//////////////////////////////////////////////////////////////////////////
		SetColorFromXMLByNameInState("textColor", stateNode, PROPERTIES_FROM_BASE);
		//////////////////////////////////////////////////////////////////////////
		const char* progressBarStyle = stateNode.getAttribute("progressBarStyle");
		if (progressBarStyle != NULL)
		{
			m_progressBarStyle = (ProgressBarStyle)atoi(progressBarStyle);
		}
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
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void ProgressBar::Draw(const Matrix4x4& Ortho, const Matrix4x4& I)
{
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
void ProgressBar::Update(float deltaSecond, Vector2& mousePosition)
{
	deltaSecond;
	m_currentStateProperty = m_forStates[m_currentState];
	m_percentage += 0.001f;
	m_percentage = MathUtils::Clamp(m_percentage, 0.0f, 1.0f);
	Vector2 offset = GetOffSet();
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	AABB2D box(mins + offset, maxs + offset);
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
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void ProgressBar::SetPercentage(float percentage)
{
	m_percentage = percentage;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void ProgressBar::SetMinsMaxs(const Vector2& mins, const Vector2& maxs)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromWidget.Set("mins", mins);
		m_forStates[i].fromWidget.Set("maxs", maxs);
	}
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void ProgressBar::SetRenderer()
{
	m_renderer = new GLMeshRenderer(VAO_PCT);
	m_textRenderer = new GLMeshRenderer(VAO_PCT);
	m_textRenderer->m_material.m_sampler.gTexDiffuse = Texture::CreateOrGetTexture(s_font->m_fontTextureFileName);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* ProgressBar::CreateVerts(int& size)
{
	size = 0;
	Vector2 offset = GetOffSet();
	std::vector<Vertex3D_PCT> verts;
	switch (m_progressBarStyle)
	{
		case PROGRESSBAR_LEFT_TO_RIGHT:
		{
			Vector2 maxs;
			GetValueInCurrentState("maxs", maxs);
			Vector2 mins;
			GetValueInCurrentState("mins", mins);
			mins += offset;
			maxs += offset;
			Vector2 midMaxs(Math2D::Interpolate(mins, maxs, m_percentage));
			midMaxs.y = maxs.y;
			Vector2 midMins(midMaxs);
			midMins.y = mins.y;
			RGBA filledColor;
			GetValueInCurrentState("filledColor", filledColor);		
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, midMaxs.y, 0.0f), Vector2(0.0f, 0.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y, 0.0f), Vector2(0.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(midMaxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, midMaxs.y, 0.0f), Vector2(0.0f, 0.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(midMaxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(midMaxs.x, midMaxs.y, 0.0f), Vector2(1.0f, 0.0f), filledColor));
			//////////////////////////////////////////////////////////////////////////
			RGBA emptyColor;
			GetValueInCurrentState("emptyColor", emptyColor);
			verts.push_back(Vertex3D_PCT(Vector3(midMins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(midMins.x, midMins.y, 0.0f), Vector2(0.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, midMins.y, 0.0f), Vector2(1.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(midMins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, midMins.y, 0.0f), Vector2(1.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y, 0.0f), Vector2(1.0f, 0.0f), emptyColor));
			break;
		}
		case PROGRESSBAR_RIGHT_TO_LEFT:
		{
			Vector2 maxs;
			GetValueInCurrentState("maxs", maxs);
			Vector2 mins;
			GetValueInCurrentState("mins", mins);
			mins += offset;
			maxs += offset;
			Vector2 midMaxs(Math2D::Interpolate(mins, maxs, (1-m_percentage)));
			midMaxs.y = maxs.y;
			Vector2 midMins(midMaxs);
			midMins.y = mins.y;
			RGBA emptyColor;
			GetValueInCurrentState("emptyColor", emptyColor);
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, midMaxs.y, 0.0f), Vector2(0.0f, 0.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y, 0.0f), Vector2(0.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(midMaxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, midMaxs.y, 0.0f), Vector2(0.0f, 0.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(midMaxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(midMaxs.x, midMaxs.y, 0.0f), Vector2(1.0f, 0.0f), emptyColor));
			//////////////////////////////////////////////////////////////////////////
			RGBA filledColor;
			GetValueInCurrentState("filledColor", filledColor);
			verts.push_back(Vertex3D_PCT(Vector3(midMins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(midMins.x, midMins.y, 0.0f), Vector2(0.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, midMins.y, 0.0f), Vector2(1.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(midMins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, midMins.y, 0.0f), Vector2(1.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y, 0.0f), Vector2(1.0f, 0.0f), filledColor));
			break;
		}
		case PROGRESSBAR_TOP_TO_BOTTOM:
		{
			Vector2 maxs;
			GetValueInCurrentState("maxs", maxs);
			Vector2 mins;
			GetValueInCurrentState("mins", mins);
			mins += offset;
			maxs += offset;
			Vector2 midMaxs(Math2D::Interpolate(mins, maxs, (1-m_percentage)));
			midMaxs.x = maxs.x;
			Vector2 midMins(midMaxs);
			midMins.x = mins.x;
			RGBA filledColor;
			GetValueInCurrentState("filledColor", filledColor);
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, midMins.y, 0.0f), Vector2(0.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, midMins.y, 0.0f), Vector2(1.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, midMins.y, 0.0f), Vector2(1.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y, 0.0f), Vector2(1.0f, 0.0f), filledColor));
			//////////////////////////////////////////////////////////////////////////
			RGBA emptyColor;
			GetValueInCurrentState("emptyColor", emptyColor);
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, midMaxs.y, 0.0f), Vector2(0.0f, 0.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y, 0.0f), Vector2(0.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, midMaxs.y, 0.0f), Vector2(0.0f, 0.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, midMaxs.y, 0.0f), Vector2(1.0f, 0.0f), emptyColor));
			break;
		}
		case PROGRESSBAR_BOTTOM_TO_TOP:
		{
			Vector2 maxs;
			GetValueInCurrentState("maxs", maxs);
			Vector2 mins;
			GetValueInCurrentState("mins", mins);
			mins += offset;
			maxs += offset;
			Vector2 midMaxs(Math2D::Interpolate(mins, maxs, m_percentage));
			midMaxs.x = maxs.x;
			Vector2 midMins(midMaxs);
			midMins.x = mins.x;
			RGBA emptyColor;
			GetValueInCurrentState("emptyColor", emptyColor);
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, midMins.y, 0.0f), Vector2(0.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, midMins.y, 0.0f), Vector2(1.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, midMins.y, 0.0f), Vector2(1.0f, 1.0f), emptyColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y, 0.0f), Vector2(1.0f, 0.0f), emptyColor));
			//////////////////////////////////////////////////////////////////////////
			RGBA filledColor;
			GetValueInCurrentState("filledColor", filledColor);
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, midMaxs.y, 0.0f), Vector2(0.0f, 0.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y, 0.0f), Vector2(0.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, midMaxs.y, 0.0f), Vector2(0.0f, 0.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), filledColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, midMaxs.y, 0.0f), Vector2(1.0f, 0.0f), filledColor));
			break;
		}
		
	}
	//////////////////////////////////////////////////////////////////////////
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

void ProgressBar::GetEdgeVerts(Vertex3D_PCT* edgeVerts)
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

Vertex3D_PCT* ProgressBar::GetTextVerts(int& size)
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
	textFloat = textFloat.substr(1,3);
	textInt = textInt + textFloat + '%';

	float textScale;
	GetValueInCurrentState("textScale", textScale);
	RGBA color;
	GetValueInCurrentState("textColor", color);

	return s_font->CreateCharactersVerts(Vector3(0.2f*(maxs.x - mins.x) + mins.x, -0.1f*(maxs.y - mins.y) + maxs.y, -1.0f), textInt, textScale, color, size);
}
