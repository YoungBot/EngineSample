//==========================================================
//WidgetStyle.cpp
//==========================================================
#include "WidgetStyle.hpp"
#include "Engine/Utility/Utility.hpp"
#include "Engine/Utility/xmlParser.h"

std::map<std::string, WidgetStyle*> WidgetStyle::s_styles;
WidgetStyle::WidgetStyle()
{
	for (int i = 0; i < NUM_WIDGET_STATE_; i++)
	{
		m_nameProperties[i] = NamedProperties();
	}
}

int WidgetStyle::LoadAllStyleFromXML()
{
	std::vector<std::string> allUIFiles;
	Utility::FindAllFilesOfType("Data/UIs/Styles/", "*.xml", allUIFiles);
	for (unsigned int i = 0; i < allUIFiles.size(); i++)
	{
		std::string dir = "Data/UIs/Styles/";
		dir += allUIFiles[i];
		XMLNode WidgetParser = XMLNode::parseFile(dir.c_str(), "Style");
		std::string styleName = WidgetParser.getAttribute("name");
		XMLNode stateNode;
		stateNode = WidgetParser.getChildNode("States");
		CreateAndSaveStyles(styleName, stateNode);
		//CreateAndSaveBaseWidget2(widgetType, stateNode);
		//StringTable::GetIDByName(currentNPC->m_prototype->m_name);
	}
	return allUIFiles.size();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

WidgetStyle* WidgetStyle::GetStyleByName(const std::string& name)
{
	std::map<std::string, WidgetStyle*>::iterator styleProperties = s_styles.find(name);
	if (styleProperties != s_styles.end())
	{
		return new WidgetStyle(*styleProperties->second);
	}
	return nullptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void WidgetStyle::CreateAndSaveStyles(const std::string name, const XMLNode& node)
{
	WidgetStyle* newStyle = new WidgetStyle();
	int j = 0;
	XMLNode currentState = node.getChildNode(j);
	while (!currentState.isEmpty())
	{
		const char* stateNum = currentState.getAttribute("state");
		int currentStateNum;
		if (stateNum != NULL)
			currentStateNum = atoi(stateNum);
		else
			continue;
		RGBA edgeColor = GetRGBAFromXMLbyName("edgeColor", currentState);
		if (edgeColor!=RGBA(0.0f,0.0f,0.0f,0.0f))
		{
			newStyle->m_nameProperties[currentStateNum].Set("edgeColor", edgeColor);
		}		
		RGBA textColor = GetRGBAFromXMLbyName("textColor", currentState);
		if (textColor != RGBA(0.0f, 0.0f, 0.0f, 0.0f))
		{
			newStyle->m_nameProperties[currentStateNum].Set("textColor", textColor);
		}
		RGBA BGColor = GetRGBAFromXMLbyName("BGColor", currentState);
		if (BGColor != RGBA(0.0f, 0.0f, 0.0f, 0.0f))
		{
			newStyle->m_nameProperties[currentStateNum].Set("BGColor", BGColor);
		}
		const char* edgeThicknessChar = currentState.getAttribute("edgeThickness");
		float edgeThickness;
		if (edgeThicknessChar != NULL)
			edgeThickness = (float)atof(edgeThicknessChar);
		newStyle->m_nameProperties[currentStateNum].Set("edgeThickness", edgeThickness);
		j++;
		currentState = node.getChildNode(j);
	}
	s_styles.insert(std::pair<std::string, WidgetStyle*>(name, newStyle));
}
///----------------------------------------------------------
///
///----------------------------------------------------------

RGBA WidgetStyle::GetRGBAFromXMLbyName(const std::string& name, const XMLNode& node)
{
	const char* colorStr = node.getAttribute(name.c_str());
	if (colorStr != NULL)
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
		return RGBA(colorChar[0], colorChar[1], colorChar[2], colorChar[3]);
	}
	else
	{
		return RGBA(0.0F, 0.0F, 0.0F, 0.0F);
	}
}
