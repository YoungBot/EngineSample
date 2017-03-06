//==========================================================
//UISystem.cpp
//==========================================================
#include "UISystem.hpp"
#include "Engine/Utility/Utility.hpp"
#include "RectButton.hpp"
#include "SliderWidget.hpp"
#include "WidgetStyle.hpp"
#include "DropdownWidget.hpp"
#include "CheckBox.hpp"
#include "DropdownWidget.hpp"
#include "Label.hpp"
#include "EditableLabel.hpp"
#include "ProgressBar.hpp"
#include "Engine/Input/InputSystem.hpp"

UISystem* s_theUISystem = NULL;
UISystem::UISystem()
{
	RegistEvent();
}

int UISystem::LoadAllBaseWidgetXMLs()
{
	std::vector<std::string> allUIFiles;
	Utility::FindAllFilesOfType("Data/UIs/BaseWidgets/", "*.xml", allUIFiles);
	for (unsigned int i = 0; i < allUIFiles.size(); i++)
	{
		std::string dir = "Data/UIs/BaseWidgets/";
		dir += allUIFiles[i];
		XMLNode WidgetParser = XMLNode::parseFile(dir.c_str(), "BaseWidget");
		std::string widgetType = WidgetParser.getAttribute("name");
		XMLNode defaultNode;
		defaultNode = WidgetParser.getChildNode("Default");
		XMLNode stateNode;
		stateNode = WidgetParser.getChildNode("States");
		if (defaultNode.isEmpty())
			continue;
		else
			CreateAndSaveBaseWidget(widgetType, defaultNode,stateNode);
		//StringTable::GetIDByName(currentNPC->m_prototype->m_name);
	}
	return allUIFiles.size();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

int UISystem::LoadAllBaseWidget2XMLs()
{
	std::vector<std::string> allUIFiles;
	Utility::FindAllFilesOfType("Data/UIs/BaseWidgets/", "*.xml", allUIFiles);
	for (unsigned int i = 0; i < allUIFiles.size(); i++)
	{
		std::string dir = "Data/UIs/BaseWidgets/";
		dir += allUIFiles[i];
		XMLNode WidgetParser = XMLNode::parseFile(dir.c_str(), "BaseWidget");
		std::string widgetType = WidgetParser.getAttribute("name");
		XMLNode stateNode;
		stateNode = WidgetParser.getChildNode("States");
		CreateAndSaveBaseWidget2(widgetType, stateNode);
		//StringTable::GetIDByName(currentNPC->m_prototype->m_name);
	}
	return allUIFiles.size();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

int UISystem::LoadAllSpecificWidgetXMLs()
{
	std::vector<std::string> allUIFiles;
	Utility::FindAllFilesOfType("Data/UIs/SpecificWidgets/", "*.xml", allUIFiles);
	for (unsigned int i = 0; i < allUIFiles.size(); i++)
	{
		std::string dir = "Data/UIs/SpecificWidgets/";
		dir += allUIFiles[i];
		XMLNode WidgetParser = XMLNode::parseFile(dir.c_str(), "BaseWidget");
		std::string widgetType = WidgetParser.getAttribute("name");
		const char* styleType = WidgetParser.getAttribute("style");
		std::string styleTypeStr;
		if (styleType != NULL)
		{
			styleTypeStr = styleType;
		}
		XMLNode stateNode;
		stateNode = WidgetParser.getChildNode("States");
		CreateWidgetByTypeAndStyle(stateNode, widgetType, styleTypeStr);
		//StringTable::GetIDByName(currentNPC->m_prototype->m_name);
	}
	return allUIFiles.size();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void UISystem::Startup()
{
	LoadAllBaseWidget2XMLs();
	LoadAllSpecificWidgetXMLs();
	LoadAllBaseWidgetXMLs();
}

///----------------------------------------------------------
///
///----------------------------------------------------------

BaseWidget* UISystem::GetBaseWidgetByName(const std::string& name)
{
	std::map<std::string,BaseWidget*>::iterator baseWidget = m_baseWidgets.find(name);
	if (baseWidget != m_baseWidgets.end())
	{
		return new BaseWidget(*baseWidget->second);
	}
	return nullptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

BaseWidget2* UISystem::CreateWidgetByType(WidgetType2 type)
{
	switch (type)
	{
	case WIDGET_TYPE_DEFAULT_:
		return nullptr;
	case WIDGET_TYPE_RECTBUTTON_:
		return new RectButton();
	case NUM_WIDGET_TYPE_:
		return nullptr;
	default:
		return nullptr;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

BaseWidget2* UISystem::CreateWidgetByTypeAndStyle(const XMLNode& node,const std::string& widgetName, const std::string& styleName)
{
	BaseWidget2* widget = nullptr;
	if (widgetName == "RectButton")
	{
		widget = new RectButton(node);		
	}
	if (widgetName == "SliderWidget")
	{
		widget = new SliderWidget(node);
	}
	if (widgetName == "CheckBox")
	{
		CheckBox* checkBox = new CheckBox(node);
		checkBox->SetStyle(CHECKBOX_MULTIPLE);
		widget = checkBox;
	}
	if (widgetName == "RadioWidget")
	{
		CheckBox* radio = new CheckBox(node);
		radio->SetStyle(RADIO_SINGLE_WIDGET);
		widget = radio;
	}
	if (widgetName == "DropdownWidget")
	{
		widget = new DropdownWidget(node);
	}
	if (widgetName == "ProgressBar")
	{
		widget = new ProgressBar(node);
	}
	if (widgetName == "EditableLabel")
	{
		widget = new EditableLabel(node);
	}
	if (widgetName == "Label")
	{
		widget = new Label(node);
	}
	if (widgetName == "QuitButton")
	{
		RectButton* button = new RectButton(node);
		button->SetEvent("quit");
		widget = button;
	}
	if (widgetName == "TileButton" || widgetName == "NextButton")
	{
		RectButton* button = new RectButton(node);
		widget = button;
	}

	if (widgetName == "LayerDropdown")
	{
		DropdownWidget* button = new DropdownWidget(node);
		widget = button;
	}

	if (widget==nullptr)
	{
		return nullptr;
	}
	else
	{
		SetWidgetByStyle(styleName, widget);
		m_specificWidgets.insert(std::pair<std::string, BaseWidget2*>(widgetName, widget));
		return widget;
	}
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

BaseWidget2* UISystem::GetBaseWidget2ByName(const std::string& name)
{
	std::map<std::string, BaseWidget2*>::iterator baseWidget2 = m_newBaseWidgets.find(name);
	if (baseWidget2 != m_newBaseWidgets.end())
	{
		return baseWidget2->second;
	}
	return nullptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

BaseWidget2* UISystem::GetSpecificWidgetByName(const std::string& name)
{
	std::map<std::string, BaseWidget2*>::iterator baseWidget2 = m_specificWidgets.find(name);
	if (baseWidget2 != m_specificWidgets.end())
	{
		//return baseWidget2->second;
		//BaseWidget2* a = baseWidget2->second;
		//BaseWidget2* b = 
		return new RectButton(*baseWidget2->second);
		//need work
	}
	return nullptr;
}

///----------------------------------------------------------
///
///----------------------------------------------------------

void UISystem::SetWidgetByStyle(const std::string& styleName, BaseWidget2* widget)
{
	WidgetStyle* style = WidgetStyle::GetStyleByName(styleName);
	if (style!= nullptr)
	{
		for (int i = 0; i < NUM_WIDGET_STATE_; i++)
		{
			widget->m_forStates[i].fromStyle = style->m_nameProperties[i];
		}
	}
}



///----------------------------------------------------------
///
///----------------------------------------------------------

void UISystem::CreateAndSaveBaseWidget(const std::string& name, const XMLNode& widgetNode,const XMLNode& stateNode)
{
	BaseWidget* newWidget = new BaseWidget();
	newWidget->SetDefaultByXML(widgetNode);
	int j = 0;
	XMLNode statesNode = stateNode.getChildNode("State",j);
	
	while (statesNode.isEmpty())
	{
		const char* state = statesNode.getAttribute("name");
		if (state != NULL && std::string(state) == "Selecting")
		{
			newWidget->SetStateByXML(WIDGET_STATE_SELECTING, statesNode);
		}
		j++;
		statesNode = stateNode.getChildNode("State",j);
	}
	
	
	m_baseWidgets.insert(std::pair<std::string, BaseWidget*>(name, newWidget));
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void UISystem::CreateAndSaveBaseWidget2(const std::string& name, const XMLNode& stateNode)
{
	if (name == "RectButton")
	{
		BaseWidget2* newWidget = new RectButton(stateNode);
		m_newBaseWidgets.insert(std::pair<std::string, BaseWidget2*>(name, newWidget));
	}
	if (name == "SliderWidget")
	{
		BaseWidget2* newWidget = new SliderWidget(stateNode);
		m_newBaseWidgets.insert(std::pair<std::string, BaseWidget2*>(name, newWidget));
	}
	if (name == "CheckBox")
	{
		BaseWidget2* newWidget;
		CheckBox* checkBox = new CheckBox(stateNode);
		checkBox->SetStyle(CHECKBOX_MULTIPLE);
		newWidget = checkBox;
		m_newBaseWidgets.insert(std::pair<std::string, BaseWidget2*>(name, newWidget));
	}
	if (name == "RadioWidget")
	{
		BaseWidget2* newWidget;
		CheckBox* checkBox = new CheckBox(stateNode);
		checkBox->SetStyle(RADIO_SINGLE_WIDGET);
		newWidget = checkBox;
		m_newBaseWidgets.insert(std::pair<std::string, BaseWidget2*>(name, newWidget));
	}
	if (name == "DropdownWidget")
	{
		BaseWidget2* newWidget = new DropdownWidget(stateNode);
		m_newBaseWidgets.insert(std::pair<std::string, BaseWidget2*>(name, newWidget));
	}
	if (name == "EditableLabel")
	{
		BaseWidget2* newWidget = new EditableLabel(stateNode);
		m_newBaseWidgets.insert(std::pair<std::string, BaseWidget2*>(name, newWidget));
	}
	if (name == "Label")
	{
		BaseWidget2* newWidget = new Label(stateNode);
		m_newBaseWidgets.insert(std::pair<std::string, BaseWidget2*>(name, newWidget));
	}
	if (name == "ProgressBar")
	{
		BaseWidget2* newWidget = new ProgressBar(stateNode);
		m_newBaseWidgets.insert(std::pair<std::string, BaseWidget2*>(name, newWidget));
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------
void BEP(NamedProperties& np)
{
	np;
	Beep(1000, 1000);
}

void QuitEvent(NamedProperties& np)
{
	np;
	s_theInputSystem->SetSystemQuit();
}

void DropdownEvent(NamedProperties& np)
{
	np;
	DropdownWidget* currentWidget =nullptr;
	np.Get("widget", currentWidget);
	unsigned int index;
	np.Get("index", index);

	std::string text;
	currentWidget->m_options[index]->m_currentStateProperty.fromCode.Get("text", text);
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		currentWidget->m_options[0]->m_forStates[i].fromWidget.Set("text", text);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void UISystem::RegistEvent()
{
	Utility::RegisterEventCallback("testEvent", BEP);
	Utility::RegisterEventCallback("Dropdown", DropdownEvent);
	Utility::RegisterEventCallback("quit", QuitEvent);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void UISystem::AddNamedWidget(const std::string& name, BaseWidget2* widget)
{
	m_namedWidget.insert(std::pair<std::string, BaseWidget2*>(name, widget));
}
///----------------------------------------------------------
///
///----------------------------------------------------------

BaseWidget2* UISystem::GetNamedWidgetByName(const std::string& name)
{
	std::map<std::string, BaseWidget2*>::iterator baseWidget2 = m_namedWidget.find(name);
	if (baseWidget2 != m_namedWidget.end())
	{
		return baseWidget2->second;
	}
	return nullptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void UISystem::SetHiddenByName(const std::string& name,bool isHidden)
{
	std::map<std::string, BaseWidget2*>::iterator baseWidget2 = m_namedWidget.find(name);
	if (baseWidget2 != m_namedWidget.end())
	{
		baseWidget2->second->m_isHidden = isHidden;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

