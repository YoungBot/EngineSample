//==========================================================
//Fonts.cpp
//==========================================================

#include "Fonts.hpp"



Fonts* s_font = NULL;
std::string s_text = "";
static float fadeScale = 1.0f;
const float FADE_TIME = 2.0f;

static bool s_isClear = false;
static bool s_isHelp = false;
static bool s_doPrint = false;
static int checkLineNum = 0;
static unsigned int curserPositionInString = 0;
Fonts::Fonts(const char* fileName, const char* textureFileName)
{
	m_fontName = "";
	m_characters.clear();
	m_fileName = fileName;
	m_fontTextureFileName = textureFileName;
	m_startType = false;
	m_doShowConsole = false;
	m_doFade = false;
	m_scale = 30.0f;
	m_consoleStartPoint = Vector3(0.0f,m_scale,0.0f);
	m_curserPos = Vector3(0.0f,0.0f,0.0f);
	m_log.push_back("");
	StartUp();
}

bool Fonts::LoadTxtFontFile(const char* fileName)
{
	size_t fileSize;
	float scaleW;
	float scaleH;
	int charactCount;
	unsigned char* buff = Utility::FileReadAll(fileName,&fileSize);
	if (buff==nullptr)
	{
		return false;
	}

	std::string buffString = "";
	for (size_t i = 0; i < fileSize; i++)
	{
		buffString += buff[i];
	}

	std::string res = CutString(buffString, '"');
	m_fontName =CutString(buffString, '"');
	res = CutString(buffString, '\r');
	//res = CutString(buffString, '=');
	//res = CutString(buffString, ' ');
	res = CutDoubleString(buffString, '=', ' ');
	m_lineHeight = (float)atof(res.c_str());
	res = CutDoubleString(buffString, '=', ' ');
	m_base = (float)atof(res.c_str());
	res = CutDoubleString(buffString, '=', ' ');
	scaleW = (float)atof(res.c_str());
	res = CutDoubleString(buffString, '=', ' ');
	scaleH = (float)atof(res.c_str());
	res = CutString(buffString, '\r');
	res = CutString(buffString, '\r');
	res = CutDoubleString(buffString, '=', ' ');
	charactCount = (int)atof(res.c_str());

	for (int i = 0; i < charactCount; i++)
	{
		short ID;
		Vector2 XY;
		Vector2 WH;
		Vector2 OffsetXY;
		Vector2 GLYPHWH;
		float XAdvance;
		res = CutDoubleString(buffString, '=', ' ');		
		ID = (short)atof(res.c_str());
		res = CutDoubleString(buffString, '=', ' ');
		XY.x = (float)atof(res.c_str()) / scaleW;
		res = CutDoubleString(buffString, '=', ' ');
		XY.y = (float)atof(res.c_str()) / scaleH;
		res = CutDoubleString(buffString, '=', ' ');
		WH.x = (float)atof(res.c_str()) / scaleW;
		GLYPHWH.x = (float)atof(res.c_str()) / m_lineHeight;
		res = CutDoubleString(buffString, '=', ' ');
		WH.y = (float)atof(res.c_str()) / scaleH;
		GLYPHWH.y = (float)atof(res.c_str()) / m_lineHeight;
		res = CutDoubleString(buffString, '=', ' ');
		OffsetXY.x = (float)atof(res.c_str()) / m_lineHeight;
		res = CutDoubleString(buffString, '=', ' ');
		OffsetXY.y = (float)atof(res.c_str()) / m_lineHeight;
		res = CutDoubleString(buffString, '=', ' ');
		XAdvance = (float)atof(res.c_str()) / m_lineHeight;
		res = CutString(buffString, '\r');
		Character newCharacter(ID, XY, WH,GLYPHWH, OffsetXY, XAdvance);
		m_characters.push_back(newCharacter);
	}	
	return true;
}

void Fonts::StartUp()
{
	LoadTxtFontFile(m_fileName);
	m_fontTexture = Texture::CreateOrGetTexture(m_fontTextureFileName);
}
std::string Fonts::CutString(std::string& ori, const char delim)
{
	std::string result="";
	for (int i = 0; i <= (int)ori.length(); i++)
	{
		if (i == (int)ori.length())
		{
			ori = "";
			break;
		}
		if (ori[i]==delim)
		{		
			if (i+1<(int)ori.length())
			{
				ori = ori.substr(i+1, ori.length() - i-1);
				break;
			}
			
			break;
		}
		result += ori[i];
	}
	
	return result;
}

std::string Fonts::CutDoubleString(std::string& ori, const char delim1, const char delim2)
{
	std::string res;
	CutString(ori, delim1);
	res = CutString(ori, delim2);
	return res;
}
//////////////////////////////////////////////////////////////////////////
Vertex3D_PCT* Fonts::CreateCharactersVerts(Vector3 startPos, std::string words, float scale, RGBA& color, int& size)
{
	size_t wordsLength = words.length();
	Vertex3D_PCT* verts = new Vertex3D_PCT[wordsLength*6];
	float startPosX = startPos.x;
	float startPosY = startPos.y;
	for (size_t i = 0; i < wordsLength; i++)
	{
		for (unsigned int j = 0; j<m_characters.size(); j++)
		{
			if (m_characters[j].m_ID != words[i])
			{
				continue;
			}
			Vector2 mins(startPosX + scale*m_characters[j].m_OffsetXY.x, startPosY - scale*(m_characters[j].m_OffsetXY.y + m_characters[j].m_GLYPHWH.y));
			Vector2 maxs(startPosX + scale*(m_characters[j].m_OffsetXY.x + m_characters[j].m_GLYPHWH.x), startPosY - scale*(m_characters[j].m_OffsetXY.y));
			verts[i*6] = Vertex3D_PCT(Vector3(mins.x, maxs.y, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y), color);
			verts[i*6+1] = Vertex3D_PCT(Vector3(mins.x, mins.y, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), color);
			verts[i*6+2] = Vertex3D_PCT(Vector3(maxs.x, mins.y, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), color);
															
			verts[i * 6 + 3] = Vertex3D_PCT(Vector3(mins.x, maxs.y, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y), color);
			verts[i * 6 + 4] = Vertex3D_PCT(Vector3(maxs.x, mins.y, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), color);
			verts[i * 6 + 5] = Vertex3D_PCT(Vector3(maxs.x, maxs.y, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y), color);


			startPosX += scale*m_characters[j].m_XAdvance;
			break;
		}
	}
	size = wordsLength*6;
	return verts;
}
//////////////////////////////////////////////////////////////////////////

void Fonts::UpdateTextInput(float deltaTime)
{
	deltaTime;
	PrintLogToFile();
	AddHelpText();
	ClearAllText();

	if (m_startType==false)
	{
		return;
	}
	if (s_theInputSystem->WasKeyJustDown(VK_ESCAPE))
	{
		s_text = "";
		m_log[m_log.size() - 1] = s_text;
		m_startType = false;
		m_doShowConsole = false;
		return;
	}
	if (s_theInputSystem->WasKeyJustDown(VK_UP))
	{
		if ((checkLineNum-1)>=0)
		{
			checkLineNum--;		
			
		}
		else
			checkLineNum = m_log.size()-1;
		if (m_log[checkLineNum][0]!='>')
		{
			s_text = ">" + m_log[checkLineNum];
		}
		
		m_log[m_log.size() - 1] = s_text;
	}
	if (s_theInputSystem->WasKeyJustDown(VK_LEFT))
	{
		if (curserPositionInString>0)
		{
			curserPositionInString--;
		}
	}
	if (s_theInputSystem->WasKeyJustDown(VK_RIGHT))
	{
		if (curserPositionInString < s_text.length()-1)
		{
			curserPositionInString++;
		}
	}
	if (s_theInputSystem->WasKeyJustDown(VK_DOWN))
	{
		if ((checkLineNum) < (int)m_log.size() - 1)
		{
			checkLineNum++;			
		}
		else
			checkLineNum = 0;
		if (m_log[checkLineNum][0] != '>')
		{
			s_text = ">" + m_log[checkLineNum];
		}
		m_log[m_log.size() - 1] = s_text;
	}
	if (s_theInputSystem->WasKeyJustDown(VK_BACK))
	{
		//if (s_text.length()>1)
		//{
		//	s_text = s_text.substr(0, s_text.length() - 1);
		//}
		//
		//m_log[m_log.size() - 1] = s_text;
		DeleteCharacter();
	}
	m_log[m_log.size() - 1] = s_text;
	if (s_theInputSystem->WasKeyJustDown(VK_RETURN))
	{
		if (s_text == ">")
		{
			s_text = "";
			m_startType = false;
			return;
		}
		else
		{
			m_log[m_log.size() - 1] = CutDoubleString(s_text,'>','\n');
			RunConsoleFromLine(m_log[m_log.size() - 1].c_str());
			m_log.push_back("");
			s_text = "";
			m_startType = false;
			checkLineNum = m_log.size()-1;
		}
		curserPositionInString = 0;
		return;
	}

	for (int i = 0; i < NUMBER_OF_VIRTUAL_KEYS; i++)
	{
		if (s_theInputSystem->WasKeyJustDown(i))
		{
			if (s_theInputSystem->IsKeyDown(VK_SHIFT))
			{
				if (i>=65 && i<=90)
				{
					//s_text += (char)i;
					//curserPositionInString++;
					InsertCharacter(i);
					return;
				}
				if (i == 57)
				{
					//s_text += 40;  //'('
					//curserPositionInString++;
					InsertCharacter(i);
					return;
				}
				if (i == 48)
				{
					//s_text += 41;  //')'
					//curserPositionInString++;
					InsertCharacter(i);
					return;
				}
			}
			if (i == 32)
			{
				InsertCharacter(i);
			}
			if (i >= 65 && i <= 90)
			{
				InsertCharacter(i+32);
				return;
			}
			if (i>=188 && i<=191)
			{
				InsertCharacter(i-144);
				return;
			}
			if (i == 186)
			{
				InsertCharacter(59);
				return;
			}
			if (i<=57 && i >=48)
			{
				InsertCharacter(i);
			}
			
		}
	}
}
//////////////////////////////////////////////////////////////////////////

Vertex3D_PCT* Fonts::CreateConsoleCharactersVerts(Vector3 startPos, float scale, RGBA& color, int& size)
{
	size = 0;
	std::vector<Vertex3D_PCT> verts;
	RGBA fadeColor = RGBA(color.GetRed(), color.GetGreen(), color.GetBlue(), fadeScale);
	for (int k = (int)m_log.size()-1; k >= 0; k--)
	{
		size_t wordsLength = m_log[k].length();
		
		float startPosX = startPos.x;
		float startPosY = startPos.y;
		m_curserPos.x = startPosX;
		for (size_t i = 0; i < wordsLength; i++)
		{
			for (unsigned int j = 0; j < m_characters.size(); j++)
			{
				if (m_characters[j].m_ID != m_log[k][i])
				{
					continue;
				}
				Vector2 mins(startPosX + scale*m_characters[j].m_OffsetXY.x, startPosY - scale*(m_characters[j].m_OffsetXY.y + m_characters[j].m_GLYPHWH.y));
				Vector2 maxs(startPosX + scale*(m_characters[j].m_OffsetXY.x + m_characters[j].m_GLYPHWH.x), startPosY - scale*(m_characters[j].m_OffsetXY.y));
				mins += Vector2(0.0f, m_scale * (m_log.size() - k - 1));
				maxs += Vector2(0.0f, m_scale * (m_log.size() - k - 1));
				verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y), fadeColor));
				verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), fadeColor));
				verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), fadeColor));
					 
				verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y), fadeColor));
				verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), fadeColor));
				verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y), fadeColor));
				startPosX += scale*m_characters[j].m_XAdvance;
				
				break;
			}
			
		}
	}
	Vertex3D_PCT* passOutVerts = new Vertex3D_PCT[verts.size()];
	memcpy(passOutVerts,verts.data(),verts.size()*sizeof(Vertex3D_PCT));
	size = verts.size();
	return passOutVerts;
}
//////////////////////////////////////////////////////////////////////////
void Fonts::UpdateConsoleRender(float deltaTime)
{
	static float totalFadeTime = 0.0f;

	if (!m_startType)
	{
		if (m_doShowConsole)
		{
			fadeScale = 1.0f - totalFadeTime / FADE_TIME;
			totalFadeTime += deltaTime;
			if (totalFadeTime >= FADE_TIME)
			{
				m_doShowConsole = false;
				totalFadeTime = 0.0f;
				fadeScale = 1.0f;
			}
		}
		return;
	}

	totalFadeTime = 0.0f;
	fadeScale = 1.0f;
}
//////////////////////////////////////////////////////////////////////////

void Fonts::AddHelpText()
{
	if (s_isHelp == false)
	{
		return;
	}
	s_text = "HELP to Open help menu";
	m_log.push_back(s_text);
	s_text = "QUIT to exit app";
	m_log.push_back(s_text);
	s_text = "Clear to clean console command";
	m_log.push_back(s_text);
	s_text = ">";
	m_log.push_back(s_text);
	s_isHelp = false;
}
//////////////////////////////////////////////////////////////////////////
void Fonts::ClearAllText()
{
	if (s_isClear == false)
	{
		return;
	}
	//m_log.clear();
	std::vector<std::string>().swap(m_log);
	s_text = ">";
	m_log.push_back(s_text);
	s_isClear = false;
	checkLineNum = 0;
}
//////////////////////////////////////////////////////////////////////////

Vector3 Fonts::CalcTextWidth(std::string text)
{
	Vector3 pos = m_consoleStartPoint;
	for (int i = 0; i < (int)text.length(); i++)
	{
		for (unsigned int j = 0; j < m_characters.size(); j++)
		{
			if (m_characters[j].m_ID != text[i])
			{
				continue;
			}
			pos.x += m_characters[j].m_XAdvance*m_scale;
			pos.y = m_consoleStartPoint.y;
			pos.z = m_consoleStartPoint.y;
			
		}
	}
	pos.x *= 1.063f;
	return pos;
}
//////////////////////////////////////////////////////////////////////////
Vector3 Fonts::GetCursorPosition(std::string text)
{
	Vector3 pos = m_consoleStartPoint;
	for (unsigned int i = 0; i < curserPositionInString+1; i++)
	{
		for (unsigned int j = 0; j < m_characters.size(); j++)
		{
			if (m_characters[j].m_ID != text[i])
			{
				continue;
			}
			pos.x += m_characters[j].m_XAdvance*m_scale;
			pos.y = m_consoleStartPoint.y;
			pos.z = m_consoleStartPoint.y;

		}
	}
	pos.x *= 1.063f;
	return pos;
}
//////////////////////////////////////////////////////////////////////////
void Fonts::DrawCurser(OpenGLRenderer* renderer,float deltaTime)
{
	static float totalTime = 0;
	//Vector3 pos = CalcTextWidth(s_text);
	Vector3 pos = GetCursorPosition(s_text);
	//Vector3 pos = Vector3(100.0f,100.0f,10.0f);
	//Vector3 pos = m_curserPos;
	renderer->PushMatrix();
	renderer->SetOrthographicView();
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
	{
	
		glColor4f(1.0f,0.0f,0.0f,sin(totalTime*5));
		glVertex3f(pos.x, pos.y, 0.0f);
		glVertex3f(pos.x, pos.y-m_scale, 0.0f);
	
	}
	glEnd();
	glPopMatrix();
	totalTime += deltaTime;
}
//////////////////////////////////////////////////////////////////////////
void Fonts::PrintLogToFile()
{
	if (s_doPrint==false)
	{
		return;
	}
	std::ofstream fout;
	fout.open("Data/log.txt");
	if (!fout)
	{
		return;
	}
	for (unsigned int i = 0; i < m_log.size();i++)
	{
		fout << m_log[i];
	}
	fout.close();
	s_doPrint = false;
	return;
}
//////////////////////////////////////////////////////////////////////////
void Fonts::InsertCharacter(int ascii)
{
	std::string tmp1 = "";
	for (unsigned int i = 0; i <= curserPositionInString;i++)
	{
		tmp1 += s_text[i];
	}
	tmp1 += (char)ascii;
	for (unsigned int i = curserPositionInString+1; i < s_text.length(); i++)
	{
		tmp1 += s_text[i];
	}
	s_text = tmp1;
	curserPositionInString++;
}
//////////////////////////////////////////////////////////////////////////
void Fonts::DeleteCharacter()
{
	if (curserPositionInString<1)
	{
		return;
	}
	std::string tmp1 = "";
	for (unsigned int i = 0; i < curserPositionInString; i++)
	{
		tmp1 += s_text[i];
	}
	for (unsigned int i = curserPositionInString + 1; i < s_text.length(); i++)
	{
		tmp1 += s_text[i];
	}
	s_text = tmp1;
	curserPositionInString--;
}
///------------------------------------------------------
///
///------------------------------------------------------
Vertex3D_PCT* Fonts::CreateVertsFromStringVector(Vector3 startPos, std::vector<std::string>& currentStringVec, float scale, RGBA& color, int& size)
{
	size = 0;
	std::vector<Vertex3D_PCT> verts;
	RGBA fadeColor = RGBA(color.GetRed(), color.GetGreen(), color.GetBlue(), fadeScale);
	for (int k = (int)currentStringVec.size() - 1; k >= 0; k--)
	{
		size_t wordsLength = currentStringVec[k].length();

		float startPosX = startPos.x;
		float startPosY = startPos.y;
		float yOffsetFloat = 0.0f;
		m_curserPos.x = startPosX;
		for (size_t i = 0; i < wordsLength; i++)
		{
			for (unsigned int j = 0; j < m_characters.size(); j++)
			{
				if (m_characters[j].m_ID != currentStringVec[k][i])
				{
					continue;
				}
				Vector2 mins(startPosX + scale*m_characters[j].m_OffsetXY.x, startPosY - scale*(m_characters[j].m_OffsetXY.y + m_characters[j].m_GLYPHWH.y));
				Vector2 maxs(startPosX + scale*(m_characters[j].m_OffsetXY.x + m_characters[j].m_GLYPHWH.x), startPosY - scale*(m_characters[j].m_OffsetXY.y));
				mins += Vector2(0.0f, m_scale * (currentStringVec.size() - k - 1));
				maxs += Vector2(0.0f, m_scale * (currentStringVec.size() - k - 1));
				verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y-yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y), fadeColor));
				verts.push_back(Vertex3D_PCT(Vector3(mins.x, mins.y-yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), fadeColor));
				verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y-yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), fadeColor));
																   
				verts.push_back(Vertex3D_PCT(Vector3(mins.x, maxs.y-yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y), fadeColor));
				verts.push_back(Vertex3D_PCT(Vector3(maxs.x, mins.y-yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), fadeColor));
				verts.push_back(Vertex3D_PCT(Vector3(maxs.x, maxs.y-yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y), fadeColor));
				startPosX += scale*m_characters[j].m_XAdvance;

				break;
			}

		}
		yOffsetFloat += 000.0f;
	}
	Vertex3D_PCT* passOutVerts = new Vertex3D_PCT[verts.size()];
	memcpy(passOutVerts, verts.data(), verts.size()*sizeof(Vertex3D_PCT));
	size = verts.size();
	return passOutVerts;
}
NTBVertex3D_PCT* Fonts::CreateNTBVertsFromStringVector(Vector3 startPos, std::vector<std::string>& currentStringVec, float scale, RGBA& color, int& size)
{
	size = 0;
	std::vector<NTBVertex3D_PCT> verts;
	RGBA fadeColor = RGBA(color.GetRed(), color.GetGreen(), color.GetBlue(), fadeScale);
	for (int k = (int)currentStringVec.size() - 1; k >= 0; k--)
	{
		size_t wordsLength = currentStringVec[k].length();

		float startPosX = startPos.x;
		float startPosY = startPos.y;
		float yOffsetFloat = 0.0f;
		m_curserPos.x = startPosX;
		for (size_t i = 0; i < wordsLength; i++)
		{
			for (unsigned int j = 0; j < m_characters.size(); j++)
			{
				if (m_characters[j].m_ID != currentStringVec[k][i])
				{
					continue;
				}
				Vector2 mins(startPosX + scale*m_characters[j].m_OffsetXY.x, startPosY - scale*(m_characters[j].m_OffsetXY.y + m_characters[j].m_GLYPHWH.y));
				Vector2 maxs(startPosX + scale*(m_characters[j].m_OffsetXY.x + m_characters[j].m_GLYPHWH.x), startPosY - scale*(m_characters[j].m_OffsetXY.y));
				mins += Vector2(0.0f, m_scale * (currentStringVec.size() - k - 1));
				maxs += Vector2(0.0f, m_scale * (currentStringVec.size() - k - 1));
				verts.push_back(NTBVertex3D_PCT(Vector3(mins.x, maxs.y - yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), fadeColor));
				verts.push_back(NTBVertex3D_PCT(Vector3(mins.x, mins.y - yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), fadeColor));
				verts.push_back(NTBVertex3D_PCT(Vector3(maxs.x, mins.y - yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), fadeColor));
								
				verts.push_back(NTBVertex3D_PCT(Vector3(mins.x, maxs.y - yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x, m_characters[j].m_XY.y), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), fadeColor));
				verts.push_back(NTBVertex3D_PCT(Vector3(maxs.x, mins.y - yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y + m_characters[j].m_WH.y), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), fadeColor));
				verts.push_back(NTBVertex3D_PCT(Vector3(maxs.x, maxs.y - yOffsetFloat, startPos.z), Vector2(m_characters[j].m_XY.x + m_characters[j].m_WH.x, m_characters[j].m_XY.y), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), Vector3(0.0F, 0.0F, 0.0F), fadeColor));
				startPosX += scale*m_characters[j].m_XAdvance;

				break;
			}

		}
		yOffsetFloat += 0.0f;
	}
	NTBVertex3D_PCT* passOutVerts = new NTBVertex3D_PCT[verts.size()];
	memcpy(passOutVerts, verts.data(), verts.size()*sizeof(NTBVertex3D_PCT));
	size = verts.size();
	return passOutVerts;
}
//////////////////////////////////////////////////////////////////////////

CONSOLE_COMMAND(HELP)
{
	s_isHelp = true;
	(void)args;
}
CONSOLE_COMMAND(help)
{
	s_isHelp = true;
	(void)args;
}
CONSOLE_COMMAND(CLEAR)
{
	s_isClear = true;
	(void)args;
}
CONSOLE_COMMAND(clear)
{

	s_isClear = true;
	(void)args;
}
CONSOLE_COMMAND(printlog)
{
	s_doPrint = true;
	(void)args;
}

