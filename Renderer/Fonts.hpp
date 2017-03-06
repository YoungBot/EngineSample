//==========================================================
//Fonts.hpp
//==========================================================


#pragma once

#include "Engine/Utility/Utility.hpp"
#include "Engine/Renderer/Character.hpp"
#include "Engine/Renderer/Texture.hpp"
#include "Engine/Renderer/OpenGLRenderer.hpp"
#include "Engine/Input/InputSystem.hpp"
#include "Engine/Console/console_command.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
class Fonts
{
public:
	Fonts(const char* fileName, const char* texturePath);
	bool LoadTxtFontFile(const char* fileName);
	void StartUp();
	static std::string CutString(std::string& ori,const char delim);
	static std::string CutDoubleString(std::string& ori, const char delim1, const char delim2);
	Vertex3D_PCT* CreateCharactersVerts(Vector3 startPos, std::string words, float scale, RGBA& color, int& size);
	Vertex3D_PCT* CreateConsoleCharactersVerts(Vector3 startPos, float scale, RGBA& color, int& size);
	Vertex3D_PCT* CreateVertsFromStringVector(Vector3 startPos,std::vector<std::string>& currentStringVec, float scale, RGBA& color, int& size);
	NTBVertex3D_PCT* CreateNTBVertsFromStringVector(Vector3 startPos, std::vector<std::string>& currentStringVec, float scale, RGBA& color, int& size);
	void UpdateTextInput(float deltaTime);
	void UpdateConsoleRender(float deltaTime);
	void AddHelpText();
	void ClearAllText();
	Vector3 CalcTextWidth(std::string text);
	Vector3 GetCursorPosition(std::string text);
	void DrawCurser(OpenGLRenderer* renderer, float deltaTime);
	void PrintLogToFile();
	void InsertCharacter(int ascii);
	void DeleteCharacter();
	std::string m_fontName;
	const char* m_fontTextureFileName;
	const char* m_fileName;
	float m_lineHeight;
	float m_base;
	float m_scale;
	Vector3 m_consoleStartPoint;
	std::vector<Character> m_characters;
	bool m_startType;
	bool m_doShowConsole;
	bool m_doFade;
	Vector3 m_curserPos;
	std::vector <std::string> m_log;
	Texture* m_fontTexture;
};
extern std::string s_text;
extern Fonts* s_font;
