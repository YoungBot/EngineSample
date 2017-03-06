//==========================================================
//RectButton.cpp
//==========================================================
#include "RectButton.hpp"
#include "Engine/Renderer/GLMeshRenderer.hpp"
#include "Engine/Renderer/Fonts.hpp"
#include "Engine/Math/AABB2D.hpp"
#include "Engine/Utility/xmlParser.h"
#include "Engine/Input/InputSystem.hpp"

RectButton::RectButton()
	:Button2()
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("mins", Vector2(800.0f,100.0f));
		m_forStates[i].fromCode.Set("maxs", Vector2(900.0f,200.0f));
	}
	m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("BGColor", RGBA(1.0f,1.0f,0.0f,1.0f));
	m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("textColor", RGBA(0.0f, 0.0f, 1.0f, 1.0f));
	m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("textScale", 40.0f);
	m_currentStateProperty = m_forStates[0];
	//Startup();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

RectButton::RectButton(const XMLNode& node)
	:Button2(node)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("mins", Vector2(800.0f, 100.0f));
		m_forStates[i].fromCode.Set("maxs", Vector2(900.0f, 200.0f));
	}
	m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("BGColor", RGBA(1.0f, 1.0f, 0.0f, 1.0f));
	m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("textColor", RGBA(0.0f, 0.0f, 1.0f, 1.0f));
	m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("textScale", 40.0f);
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
		j++ ;
		stateNode = node.getChildNode(j);
	}
	//Startup();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

RectButton::RectButton(const std::string& str)
	:Button2()
{
	std::string option = str;
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("mins", Vector2(800.0f, 100.0f));
		m_forStates[i].fromCode.Set("maxs", Vector2(900.0f, 200.0f));
		m_forStates[i].fromCode.Set("textScale", 20.0f);
		m_forStates[i].fromCode.Set("text", option);
	}
	m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("BGColor", RGBA(1.0f, 1.0f, 0.0f, 1.0f));
	m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("edgeColor", RGBA(0.0f, 0.0f, 1.0f, 1.0f));
	m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("textColor", RGBA(0.0f, 0.0f, 1.0f, 1.0f));
	
	
	m_currentStateProperty = m_forStates[0];
	//Startup();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

RectButton::RectButton(BaseWidget2 copy)
	:Button2(copy)
{
	//Startup();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void RectButton::Startup()
{
	Matrix4x4 I; 
	I.MakeIdentity();
	Button2::Draw(I, I);
	//UpdateVerts();
	
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void RectButton::Draw(const Matrix4x4& Ortho, const Matrix4x4& I)
{
	if (m_isHidden)
	{
		return;
	}
	if (m_renderer==nullptr)
	{
		Button2::Draw(Ortho, I);
		UpdateVerts();
	}
	//UpdateVerts();
	int bottonVertsSize;
	Vertex3D_PCT* buttonVerts = CreateVerts(bottonVertsSize);
	m_renderer->m_mesh.UpdateVBO(buttonVerts, bottonVertsSize*sizeof(Vertex3D_PCT));
	m_renderer->DrawShader(0, 0, Ortho, I);
	////////////////////////////////////////////////////////////////////////////
	Vertex3D_PCT* textVerts = GetTextVerts(bottonVertsSize);
	if (textVerts == nullptr)
	{
		return;
	}
	m_textRenderer->m_mesh.UpdateVBO(textVerts, bottonVertsSize*sizeof(Vertex3D_PCT));
	m_textRenderer->DrawShader(0, 0, Ortho, I);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void RectButton::Update(float deltaSecond, Vector2& mousePosition,NamedProperties* np)
{
	//return;
	Button2::Update(deltaSecond,mousePosition);
	m_currentStateProperty = m_forStates[m_currentState];
	m_timeCheck += deltaSecond;
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
	if (box.IsPointInside(mousePosition))
	{
		//m_currentState = WIDGET_STATE_SELECT_;
		m_currentStateProperty = m_forStates[WIDGET_STATE_SELECT_];
		m_currentState = WIDGET_STATE_SELECT_;
		if (s_theInputSystem->WasMouseButtonJustDown(VK_LBUTTON))
		{
			CallEvent(np);
		}
	}
	else
	{
		m_currentStateProperty = m_forStates[WIDGET_STATE_ENABLE_];
		m_currentState = WIDGET_STATE_ENABLE_;
		//m_currentState = WIDGET_STATE_ENABLE_;
	}		
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void RectButton::Update(float deltaSecond, Vector2& mousePosition)
{
	Update(deltaSecond, mousePosition, nullptr);
}

///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* RectButton::CreateVerts(int& size)
{
	Vector2 offset = GetOffSet();
	size = 0;
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	mins += offset;
	maxs += offset;
	RGBA BGColor;
	GetValueInCurrentState("BGColor", BGColor);
	Vector2 texCoTopLeft(0.0f,0.0f);
	GetValueInCurrentState("texCoTopLeft", texCoTopLeft);
	Vector2 texCoBotRight(1.0f,1.0f);
	GetValueInCurrentState("texCoBotRight", texCoBotRight);
	std::vector<Vertex3D_PCT> verts;
	verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(texCoTopLeft.x, texCoTopLeft.y), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y, 0.0f), Vector2(texCoTopLeft.x, texCoBotRight.y), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(texCoBotRight.x, texCoBotRight.y), BGColor));

	verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(texCoTopLeft.x, texCoTopLeft.y), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(texCoBotRight.x, texCoBotRight.y), BGColor));
	verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y, 0.0f), Vector2(texCoBotRight.x, texCoTopLeft.y), BGColor));

	int finalSize = verts.size();
	int textSize = 24;
	
	finalSize += textSize;

	Vertex3D_PCT* passOutVerts = new Vertex3D_PCT[finalSize];
	memcpy(passOutVerts, verts.data(), verts.size()*sizeof(Vertex3D_PCT));

	Vertex3D_PCT edgeVerts[24];
	GetEdgeVerts(edgeVerts);
	if (edgeVerts == nullptr)
	{
		size = finalSize;
		return passOutVerts;
	}
	memcpy(&passOutVerts[verts.size()], edgeVerts, textSize*sizeof(Vertex3D_PCT));

	size = finalSize;
	return passOutVerts;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void RectButton::GetEdgeVerts(Vertex3D_PCT* edgeVerts)
{
	Vector2 offset = GetOffSet();
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	mins += offset;
	maxs += offset;
	float edgeThickness;
	GetValueInCurrentState("edgeThickness", edgeThickness);
	if (edgeThickness == 0.0f)
	{
		edgeVerts = nullptr;
		return;
	}
	RGBA edgeColor;
	GetValueInCurrentState("edgeColor", edgeColor);
	//left
	edgeVerts[0] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, maxs.y, 0.0f), Vector2(0.0f, 0.0f), edgeColor);
	edgeVerts[1] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, mins.y, 0.0f), Vector2(0.0f, 1.0f), edgeColor);
	edgeVerts[2] = Vertex3D_PCT(Vector3(mins.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), edgeColor);
	edgeVerts[3] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, maxs.y, 0.0f), Vector2(0.0f, 0.0f), edgeColor);
	edgeVerts[4] = Vertex3D_PCT(Vector3(mins.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), edgeColor);
	edgeVerts[5] = Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(1.0f, 0.0f), edgeColor);
	//right
	edgeVerts[6] = Vertex3D_PCT(Vector3(maxs.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), edgeColor);
	edgeVerts[7] = Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(0.0f, 1.0f), edgeColor);
	edgeVerts[8] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, mins.y, 0.0f), Vector2(1.0f, 1.0f), edgeColor);
	edgeVerts[9] = Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), edgeColor);
	edgeVerts[10] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, mins.y, 0.0f), Vector2(1.0f, 1.0f), edgeColor);
	edgeVerts[11] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, maxs.y, 0.0f), Vector2(1.0f, 0.0f), edgeColor);
	//top
	edgeVerts[12] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, maxs.y + edgeThickness, 0.0f), Vector2(0.0f, 0.0f), edgeColor);
	edgeVerts[13] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, maxs.y, 0.0f), Vector2(0.0f, 1.0f), edgeColor);
	edgeVerts[14] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, maxs.y, 0.0f), Vector2(1.0f, 1.0f), edgeColor);
	edgeVerts[15] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, maxs.y + edgeThickness, 0.0f), Vector2(0.0f, 0.0f), edgeColor);
	edgeVerts[16] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, maxs.y, 0.0f), Vector2(1.0f, 1.0f), edgeColor);
	edgeVerts[17] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, maxs.y + edgeThickness, 0.0f), Vector2(1.0f, 0.0f), edgeColor);
	//bot
	edgeVerts[18] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, mins.y, 0.0f), Vector2(0.0f, 0.0f), edgeColor);
	edgeVerts[19] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, mins.y - edgeThickness, 0.0f), Vector2(0.0f, 1.0f), edgeColor);
	edgeVerts[20] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, mins.y - edgeThickness, 0.0f), Vector2(1.0f, 1.0f), edgeColor);
	edgeVerts[21] = Vertex3D_PCT(Vector3(mins.x - edgeThickness, mins.y, 0.0f), Vector2(0.0f, 0.0f), edgeColor);
	edgeVerts[22] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, mins.y - edgeThickness, 0.0f), Vector2(1.0f, 1.0f), edgeColor);
	edgeVerts[23] = Vertex3D_PCT(Vector3(maxs.x + edgeThickness, mins.y, 0.0f), Vector2(1.0f, 0.0f), edgeColor);

	return;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* RectButton::GetTextVerts(int& size)
{
	Vector2 offset = GetOffSet();
	Vector2 maxs;
	GetValueInCurrentState("maxs", maxs);
	Vector2 mins;
	GetValueInCurrentState("mins", mins);
	mins += offset;
	maxs += offset;
	std::string text;
	GetValueInCurrentState("text", text);
	if (text == "")
	{
		return nullptr;
	}

	float textScale;
	GetValueInCurrentState("textScale", textScale);
	RGBA color;
	GetValueInCurrentState("textColor", color);

	return s_font->CreateCharactersVerts(Vector3(0.1f*(maxs.x - mins.x) + mins.x, 0.9f*(maxs.y - mins.y) + mins.y, -1.0f), text, textScale, color, size);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void RectButton::SetMinsAndMaxs(const Vector2& mins, const Vector2& maxs)
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

void RectButton::SetTexCo(const Vector2& texCoTopLeft, const Vector2& texCoBotRight)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromWidget.Set("texCoTopLeft", texCoTopLeft);
		m_forStates[i].fromWidget.Set("texCoBotRight", texCoBotRight);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vector2 RectButton::GetTexCoTopLeft() const
{
	Vector2 texCoTopLeft;
	GetValueInCurrentState("texCoTopLeft", texCoTopLeft);
	return texCoTopLeft;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vector2 RectButton::GetTexCoBotRight() const 
{
	Vector2 texCoBotRight;
	GetValueInCurrentState("texCoBotRight", texCoBotRight);
	return texCoBotRight;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void RectButton::UpdateVerts()
{
	int bottonVertsSize;
	Vertex3D_PCT* buttonVerts = CreateVerts(bottonVertsSize);
	m_renderer->m_mesh.UpdateVBO(buttonVerts, bottonVertsSize*sizeof(Vertex3D_PCT));
	//////////////////////////////////////////////////////////////////////////
	Vertex3D_PCT* textVerts = GetTextVerts(bottonVertsSize);
	if (textVerts == nullptr)
	{
		return;
	}
	m_textRenderer->m_mesh.UpdateVBO(textVerts, bottonVertsSize*sizeof(Vertex3D_PCT));
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void RectButton::SetText(const std::string& text)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromWidget.Set("text", text);
		m_forStates[i].fromWidget.Set("text", text);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

