//==========================================================
//DropdownWidget.cpp
//==========================================================
#include "DropdownWidget.hpp"
#include "Engine/Renderer/GLMeshRenderer.hpp"
#include "Engine/Renderer/Fonts.hpp"
#include "Engine/Math/Math2D.hpp"
DropdownWidget::DropdownWidget()
	:BaseWidget2()
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
	, m_isExpend(false)
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("BGColor", RGBA(0.0F, 0.0F, 0.0F, 1.0F));
		m_forStates[i].fromCode.Set("edgeColor", RGBA(1.0F, 1.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("position", Vector2(200.0f, 500.0f));
		//m_forStates[i].fromCode.Set("mins", Vector2(200.0f, 500.0f));
		m_forStates[i].fromCode.Set("textColor", RGBA(1.0F, 1.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("textScale", 25.0f);
		m_forStates[i].fromCode.Set("edgeThickness", 3.0f);
		m_forStates[i].fromCode.Set("length", 100.0f);
		m_forStates[i].fromCode.Set("height", 40.0f);
	}
	m_currentStateProperty = m_forStates[0];
	//AddNewOption("option1");
	//AddNewOption("option1");
	//AddNewOption("option2");
	//AddNewOption("option3");
	//AddNewOption("option4");
}
///----------------------------------------------------------
///
///----------------------------------------------------------

DropdownWidget::DropdownWidget(const XMLNode& node)
	:BaseWidget2(node)
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
	, m_isExpend(false)
{
	//m_currentStateProperty = m_forStates[1];
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromCode.Set("BGColor", RGBA(0.0F, 0.0F, 0.0F, 1.0F));
		m_forStates[i].fromCode.Set("edgeColor", RGBA(1.0F, 1.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("position", Vector2(200.0f, 500.0f));
		//m_forStates[i].fromCode.Set("mins", Vector2(200.0f, 500.0f));
		m_forStates[i].fromCode.Set("textColor", RGBA(1.0F, 1.0F, 1.0F, 1.0F));
		m_forStates[i].fromCode.Set("textScale", 25.0f);
		m_forStates[i].fromCode.Set("edgeThickness", 3.0f);
		m_forStates[i].fromCode.Set("length", 100.0f);
		m_forStates[i].fromCode.Set("height", 40.0f);
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
			//////////////////////////////////////////////////////////////////////////
		const char* maxs = stateNode.getAttribute("position");
		if(maxs != NULL)
		{
			std::string str = maxs;
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
			m_forStates[currentState].fromWidget.Set("position", currentMaxs);

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
		//////////////////////////////////////////////////////////////////////////
		const char* length = stateNode.getAttribute("length");
		if (length != NULL)
		{
			float lengthf = (float)atof(length);
			m_forStates[currentState].fromWidget.Set("length", lengthf);
		}
		const char* height = stateNode.getAttribute("height");
		if (height != NULL)
		{
			float heightf = (float)atof(height);
			m_forStates[currentState].fromWidget.Set("height", heightf);
		}
		//////////////////////////////////////////////////////////////////////////
		const char* options = stateNode.getAttribute("options");
		if (options != NULL)
		{
			m_currentStateProperty = m_forStates[1];
			std::string t = options;
			//m_forStates[currentState].fromWidget.Set("text", t);
			std::string option = Utility::CutString(t, ',');
			while (option != "")
			{
				AddNewOption(option);
				if (m_options.size()==1)
				{
					AddNewOption(option);
				}
				option = Utility::CutString(t, ',');

			}
		}
		j++;
		stateNode = node.getChildNode(j);
	}
	m_currentStateProperty = m_forStates[1];
}
///----------------------------------------------------------
///
///----------------------------------------------------------

DropdownWidget::DropdownWidget(DropdownWidget* widget)
	:BaseWidget2(*widget)
	, m_renderer(nullptr)
	, m_textRenderer(nullptr)
{
	
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void DropdownWidget::Draw(const Matrix4x4& Ortho, const Matrix4x4& I)
{
	if (m_options.size() == 0)
	{
		return;
	}
	if (!m_isExpend)
	{
		m_options[0]->Draw(Ortho, I);
	}
	else
	{
		for (unsigned int i = 0; i < m_options.size(); i++)
		{
			m_options[i]->Draw(Ortho, I);
		}
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void DropdownWidget::Update(float deltaSecond, Vector2& mousePosition)
{
	m_currentStateProperty = m_forStates[m_currentState];
	Vector2 offset = GetOffSet();
	for (unsigned int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_forStates[i].fromWidget.Set("parentsOffset", offset);
		if (m_options.size()>0)
		{
			m_options[0]->m_forStates[i].fromWidget.Set("parentsOffset", offset);
		}
	}
	if (m_isExpend)
	{
		for (unsigned int i = 0; i < m_options.size(); i++)
		{
			NamedProperties properties;
			properties.Set("widget", this, "index", i);
			m_options[i]->Update(deltaSecond, mousePosition, &properties);
			if (i>=1)
			{
				m_options[i]->SetDragable(false);
			}
		}
	}
	else
	{
		NamedProperties properties;
		properties.Set("widget", this, "index", 0);
		m_options[0]->Update(deltaSecond, mousePosition, &properties);

	}
	
	
	if (!m_isExpend)
	{
		Vector2 currentOffset(0.0f, 0.0f);
		currentOffset = m_options[0]->GetOffSet();
		Vector2 mins;
		Vector2 maxs;
		m_options[0]->GetValueInCurrentState("mins", mins);
		m_options[0]->GetValueInCurrentState("maxs", maxs);
		AABB2D box(mins+ currentOffset, maxs+ currentOffset);
		if (box.IsPointInside(mousePosition))
		{
			m_isExpend = true;
		}
	}
	else
	{
		Vector2 currentOffset(0.0f, 0.0f);
		currentOffset = m_options[0]->GetOffSet();
		Vector2 mins;
		Vector2 maxs;
		m_options.back()->GetValueInCurrentState("mins", mins);
		m_options[0]->GetValueInCurrentState("maxs", maxs);
		AABB2D box(mins+ currentOffset, maxs+ currentOffset);
		if (!box.IsPointInside(mousePosition))
		{
			m_isExpend = false;
		}
		//for (unsigned int i = 0; i < m_options.size(); i++)
		//{
		//	m_options[i]->GetValueInCurrentState("mins", mins);
		//	m_options[i]->GetValueInCurrentState("maxs", maxs);
		//	box = AABB2D(mins, maxs);
		//	if (box.IsPointInside(mousePosition) && s_theInputSystem->WasMouseButtonJustReleased(VK_LBUTTON))
		//	{
		//		NamedProperties properties;
		//		properties.Set("widget", this, "index", i);
		//		m_options[i]->CallEvent(&properties);
		//		//SwitchOption(i);
		//	}
		//}
			
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void DropdownWidget::AddNewOption(const std::string& optionStr)
{
	Vector2 offset = GetOffSet();
	Vector2 position;
	GetValueInCurrentState("position", position);
	float length;
	GetValueInCurrentState("length", length);
	float height;
	GetValueInCurrentState("height", height);
	float textScale;
	GetValueInCurrentState("textScale", textScale);
	unsigned int num = m_options.size();
	Vector2 mins = Vector2(position.x,position.y-(num+1)*height)+offset;
	Vector2 maxs = Vector2(position.x+length,mins.y+height)+offset;
	RectButton* newButton = new RectButton();
	newButton->SetEvent("Dropdown");
	if (m_options.size() == 0)
	{
		newButton->m_parent = this;
	}
	else
		newButton->m_parent = m_options[0];
	
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		newButton->m_forStates[i] = m_forStates[i];
		newButton->m_forStates[i].fromCode.Set("text", optionStr);
		newButton->m_forStates[i].fromCode.Set("mins", mins);
		newButton->m_forStates[i].fromCode.Set("maxs", maxs);
		newButton->m_forStates[i].fromCode.Set("offset", Vector2(0.0f,0.0f));
		newButton->m_forStates[i].fromCode.Set("textScale", textScale);
	}
	newButton->m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("BGColor", RGBA(0.5f, 0.5f, 0.5f, 1.0f));
	newButton->m_forStates[WIDGET_STATE_SELECT_].fromCode.Set("edgeColor", RGBA(1.0f, 1.0f, 1.0f, 1.0f));
	newButton->Init();
	//newButton->m_currentState = WIDGET_STATE_ENABLE_;
	m_options.push_back(newButton);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void DropdownWidget::SwitchOption(int index)
{
	std::string text;
	m_options[index]->m_currentStateProperty.fromCode.Get("text", text);
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_options[0]->m_forStates[i].fromWidget.Set("text", text);
	}
}

///----------------------------------------------------------
///
///----------------------------------------------------------

//Vertex3D_PCT* DropdownWidget::CreateVerts(int& size)
//{
//
//}
/////----------------------------------------------------------
/////
/////----------------------------------------------------------
//
//void DropdownWidget::GetEdgeVerts(Vertex3D_PCT* edgeVerts)
//{
//
//}
/////----------------------------------------------------------
/////
/////----------------------------------------------------------
//
//Vertex3D_PCT* DropdownWidget::GetTextVerts(int& size)
//{
//
//}

