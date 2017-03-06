//==========================================================
//CheckBox.cpp
//==========================================================
#include "CheckBox.hpp"
#include "Engine/Renderer/GLMeshRenderer.hpp"
#include "Engine/Renderer/Fonts.hpp"
#include "Engine/Math/Math2D.hpp"
const float GAPSCALE = 1.2f;
CheckBox::CheckBox()
	:BaseWidget2()
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
	, m_checkBoxStyle(RADIO_SINGLE_WIDGET)
{
	m_options.clear();
	m_selectedIndexes.clear();
	m_selectedIndexes.push_back(0);
	m_selectedIndexes.push_back(1);
	m_options.push_back("OPTION 1");
	m_options.push_back("OPTION 2");
	m_options.push_back("OPTION 3");
	m_options.push_back("OPTION 4");
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("BGColor", RGBA(0.0F, 0.0F, 0.0F, 1.0F));
		m_forStates[i].fromCode.Set("edgeColor", RGBA(1.0F, 1.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("position", Vector2(1200.0f, 500.0f));
		m_forStates[i].fromCode.Set("textColor", RGBA(1.0F, 1.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("textScale", 30.0f);
		m_forStates[i].fromCode.Set("edgeThickness", 3.0f);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

CheckBox::CheckBox(const XMLNode& node)
	:BaseWidget2(node)
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
	, m_checkBoxStyle(RADIO_SINGLE_WIDGET)
{
	m_options.clear();
	m_selectedIndexes.clear();
	m_selectedIndexes.push_back(0);
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
		const char* options = stateNode.getAttribute("options");
		if (options != NULL)
		{
			std::string t = options;
			m_forStates[currentState].fromWidget.Set("text", t);
			std::string option = Utility::CutString(t, ',');
			while (option != "")
			{
				m_options.push_back(option);
				option = Utility::CutString(t, ',');

			}
		}
		j++;
		stateNode = node.getChildNode(j);
	}
	m_currentStateProperty = m_forStates[0];
}
///----------------------------------------------------------
///
///----------------------------------------------------------

CheckBox::CheckBox(CheckBoxStyle style)
	:BaseWidget2()
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
	, m_checkBoxStyle(style)
{
	m_options.clear();
	m_selectedIndexes.clear();
	m_selectedIndexes.push_back(0);
	m_options.push_back("OPTION 1");
	m_options.push_back("OPTION 2");
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("position", Vector2(1200.0f, 500.0f));
		m_forStates[i].fromCode.Set("textColor", RGBA(1.0F, 1.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("textScale", 30.0f);
		m_forStates[i].fromCode.Set("edgeThickness", 10.0f);
	}
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void CheckBox::Draw(const Matrix4x4& Ortho, const Matrix4x4& I)
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
	delete[] textVerts;
	delete[] buttonVerts;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void CheckBox::Update(float deltaSecond, Vector2& mousePosition)
{
	m_currentStateProperty = m_forStates[m_currentState];
	Vector2 offset = GetOffSet();
	m_timeCheck += deltaSecond;
	std::vector<AABB2D> boxes;
	Vector2 position;
	GetValueInCurrentState("position", position);
	float textScale;
	GetValueInCurrentState("textScale", textScale);
	
	Vector2 edgeMins = Vector2(position.x - 2 * textScale, position.y - m_options.size()*textScale);
	Vector2 edgeMaxs = Vector2(position.x + 5 * textScale, position.y);
	AABB2D edgebox(edgeMins + offset, edgeMaxs + offset);
	if (s_theInputSystem->IsMouseButtonDown(VK_LBUTTON) && s_theInputSystem->IsKeyDown('C'))
	{
		if (edgebox.IsPointInside(mousePosition))
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
	for (unsigned int i = 0; i < m_options.size(); i++)
	{
		
		Vector2 mins = Vector2(position.x - 2 * textScale, position.y - textScale) +offset;
		Vector2 maxs = Vector2(position.x - textScale, position.y) + offset;
		AABB2D box(mins, maxs);
		boxes.push_back(box);
		position.y -= textScale*GAPSCALE;
	}
	for (unsigned int i = 0; i < boxes.size(); i++)
	{
		if (boxes[i].IsPointInside(mousePosition) && s_theInputSystem->WasMouseButtonJustDown(VK_LBUTTON))
		{
			if (m_checkBoxStyle == RADIO_SINGLE_WIDGET)
			{
				m_selectedIndexes[0] = i;
			}
			else if (m_checkBoxStyle == CHECKBOX_MULTIPLE)
			{
				AddSelection(i);
			}
		}
	}
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void CheckBox::SetRenderer()
{
	m_renderer = new GLMeshRenderer(VAO_PCT);
	m_textRenderer = new GLMeshRenderer(VAO_PCT);
	m_textRenderer->m_material.m_sampler.gTexDiffuse = Texture::CreateOrGetTexture(s_font->m_fontTextureFileName);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* CheckBox::CreateVerts(int& size)
{
	size = 0;
	Vector2 position;
	GetValueInCurrentState("position", position);
	Vector2 offset = GetOffSet();
	float textScale;
	GetValueInCurrentState("textScale", textScale);
	RGBA edgeColor;
	GetValueInCurrentState("edgeColor", edgeColor);
	std::vector<Vertex3D_PCT> verts;
	if (m_checkBoxStyle == CHECKBOX_MULTIPLE)
	{
		for (unsigned int i = 0; i < m_options.size(); i++)
		{
			Vector2 mins = Vector2(position.x - 2 * textScale, position.y - textScale) + offset;
			Vector2 maxs = Vector2(position.x - textScale, position.y) + offset;
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), edgeColor));
			verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y, 0.0f), Vector2(0.0f, 1.0f), edgeColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), edgeColor));

			verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, 0.0f), Vector2(0.0f, 0.0f), edgeColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, 0.0f), Vector2(1.0f, 1.0f), edgeColor));
			verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y, 0.0f), Vector2(1.0f, 0.0f), edgeColor));
			position.y -= textScale*GAPSCALE;
		}
	}
	else
	{
		const int numSides = 24;
		std::vector<Vector2> vertices;
		float radianPerSide = 2.0f * PI / (float)numSides;
		Vector2 center = Vector2(position.x - 1.5f*textScale, position.y - 0.5f *textScale) + offset;
		for (unsigned int i = 0; i < m_options.size(); i++)
		{
			for (unsigned int j = 0; j < numSides; j++)
			{
				float currentRadian = (float)(radianPerSide*j);
				Vector2 point(center.x + 0.5f*textScale*cos(currentRadian), center.y + 0.5f*textScale*sin(currentRadian));
				currentRadian = (float)(radianPerSide*(j+1));
				Vector2 point2(center.x + 0.5f*textScale*cos(currentRadian), center.y + 0.5f*textScale*sin(currentRadian));
				verts.push_back(Vertex3D_PCT(Vector3(point.x, point.y, 0.0f), Vector2(0.0f, 0.0f), edgeColor));
				verts.push_back(Vertex3D_PCT(Vector3(center.x, center.y, 0.0f), Vector2(0.0f, 1.0f), edgeColor));
				verts.push_back(Vertex3D_PCT(Vector3(point2.x, point2.y, 0.0f), Vector2(1.0f, 1.0f), edgeColor));

			}
			center.y -= textScale*GAPSCALE;
		}
	}
	
	int finalSize = verts.size();
	int textSize = 120;
	Vertex3D_PCT edgeVerts[120];
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

void CheckBox::GetEdgeVerts(Vertex3D_PCT* edgeVerts)
{
	Vector2 offset = GetOffSet();
	switch (m_checkBoxStyle)
	{
		case RADIO_SINGLE_WIDGET:
		{
			if (m_selectedIndexes.size() == 0)
			{
				return;
			}
			float textScale;
			GetValueInCurrentState("textScale", textScale);
			Vector2 position;			
			GetValueInCurrentState("position", position);
			position.y = position.y - m_selectedIndexes[0] * textScale * GAPSCALE;
			
			RGBA BGColor;
			GetValueInCurrentState("BGColor", BGColor);
			float edgeThickness;
			GetValueInCurrentState("edgeThickness", edgeThickness);
			const int numSides = 24;
			std::vector<Vector2> vertices;
			float radianPerSide = 2.0f * PI / (float)numSides;
			Vector2 center = Vector2(position.x - 1.5f*textScale, position.y - 0.5f *textScale) + offset;
			float radius = 0.3*(textScale - edgeThickness);
			for (unsigned int i = 0; i < numSides; i++)
			{
				float currentRadian = (float)(radianPerSide*i);
				Vector2 point(center.x + radius*cos(currentRadian), center.y + radius*sin(currentRadian));
				currentRadian = (float)(radianPerSide*(i + 1));
				Vector2 point2(center.x + radius*cos(currentRadian), center.y + radius*sin(currentRadian));
				edgeVerts[i * 3] = Vertex3D_PCT(Vector3(point.x, point.y, -1.0f), Vector2(0.0f, 0.0f), BGColor);
				edgeVerts[i * 3 + 1] = Vertex3D_PCT(Vector3(center.x, center.y, -1.0f), Vector2(0.0f, 1.0f), BGColor);
				edgeVerts[i * 3 + 2] = Vertex3D_PCT(Vector3(point2.x, point2.y, -1.0f), Vector2(1.0f, 1.0f), BGColor);
			}
			return;
		}
		case CHECKBOX_MULTIPLE:
		{
			if (m_selectedIndexes.size() == 0)
			{
				return;
			}
			float textScale;
			GetValueInCurrentState("textScale", textScale);
			Vector2 position;
			GetValueInCurrentState("position", position);
			for (unsigned int i = 0; i < m_selectedIndexes.size(); i++)
			{
				float y = position.y - m_selectedIndexes[i] * textScale * GAPSCALE;

				RGBA BGColor;
				GetValueInCurrentState("BGColor", BGColor);
				float edgeThickness;
				GetValueInCurrentState("edgeThickness", edgeThickness);
				Vector2 mins = Vector2(position.x - 2 * textScale, y - textScale) +offset;
				Vector2 maxs = Vector2(position.x - textScale, y) + offset;
				edgeVerts[i*6] = Vertex3D_PCT(Vector3(mins.x + edgeThickness, maxs.y - edgeThickness, -1.0f), Vector2(0.0f, 0.0f), BGColor);
				edgeVerts[i * 6 + 1] = Vertex3D_PCT(Vector3(mins.x + edgeThickness, mins.y + edgeThickness, -1.0f), Vector2(0.0f, 1.0f), BGColor);
				edgeVerts[i * 6 + 2] = Vertex3D_PCT(Vector3(maxs.x - edgeThickness, mins.y + edgeThickness, -1.0f), Vector2(1.0f, 1.0f), BGColor);
				edgeVerts[i * 6 + 3] = Vertex3D_PCT(Vector3(mins.x + edgeThickness, maxs.y - edgeThickness, -1.0f), Vector2(0.0f, 0.0f), BGColor);
				edgeVerts[i * 6 + 4] = Vertex3D_PCT(Vector3(maxs.x - edgeThickness, mins.y + edgeThickness, -1.0f), Vector2(1.0f, 1.0f), BGColor);
				edgeVerts[i * 6 + 5] = Vertex3D_PCT(Vector3(maxs.x - edgeThickness, maxs.y - edgeThickness, -1.0f), Vector2(1.0f, 0.0f), BGColor);
			}
			
			break;
		}
		case NUM_CHECKBOX_STYLE:
			break;
		default:
			break;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vertex3D_PCT* CheckBox::GetTextVerts(int& size)
{
	Vector2 position;
	GetValueInCurrentState("position", position);
	float textScale;
	GetValueInCurrentState("textScale", textScale);
	RGBA color;
	GetValueInCurrentState("textColor", color);
	Vector2 offset = GetOffSet();
	Vertex3D_PCT* passOutVerts = new Vertex3D_PCT[1000];
	int currentSize = 0;
	for (unsigned int i = 0; i < m_options.size(); i++)
	{
		int vertSize;
		Vertex3D_PCT* currentOptionVerts = s_font->CreateCharactersVerts(Vector3(position.x + offset.x, position.y + offset.y, -1.0f), m_options[i], textScale, color, vertSize);
		memcpy(&passOutVerts[currentSize], currentOptionVerts, vertSize*sizeof(Vertex3D_PCT));
		position.y -= textScale*GAPSCALE;
		currentSize += vertSize;
	}
	size = currentSize;
	return passOutVerts;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void CheckBox::AddOption(std::string newOption)
{
	m_options.push_back(newOption);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void CheckBox::SetOptionByIndex(const std::string& option, int index)
{
	if (index>=(int)m_options.size())
		m_options.push_back(option);
	else
		m_options[index] = option;
}

void CheckBox::SetStyle(CheckBoxStyle style)
{
	m_checkBoxStyle = style;
}

void CheckBox::AddSelection(int selection)
{
	bool canAdd = true;
	unsigned int i = 0;
	for (; i < m_selectedIndexes.size(); i++)
	{
		if (m_selectedIndexes[i] == (unsigned int)selection)
		{
			canAdd = false;
			break;
		}
	}
	if (canAdd)
		m_selectedIndexes.push_back(selection);
	else
		m_selectedIndexes.erase(m_selectedIndexes.begin() + i);
}
