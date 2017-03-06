//==========================================================
//Console.cpp
//==========================================================
#include "Console.hpp"
#include <stdio.h>
#include <stdarg.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <sstream>
#include <iostream>
#include <fstream>


std::string ConsolePrintf(const char* messageFormat,...)
{
	static const int BUFFER_SIZE = 2048;
	static char message[BUFFER_SIZE];

	va_list argumentList;
	va_start(argumentList,messageFormat);
		_vsnprintf_s(message,BUFFER_SIZE,BUFFER_SIZE-1,messageFormat,argumentList);
	va_end(argumentList);

	//windows specific
	OutputDebugStringA(message);
	return message;
}
///----------------------------------------------------------
///
///----------------------------------------------------------
void LogPrintf(const char* messageFormat, ...)
{
	std::ofstream outputToFile;
	outputToFile.open("../debugLog.txt", std::ios::app);
	if (!outputToFile)
		MessageBoxA(NULL, "File Not Found!", "No file available for output.", MB_OK);
	static const size_t BUFFER_SIZE = 2048;
	static char message[BUFFER_SIZE];
	va_list argumentList;
	va_start(argumentList, messageFormat);
	_vsnprintf_s(message, BUFFER_SIZE, BUFFER_SIZE - 1, messageFormat, argumentList);
	va_end(argumentList);
	outputToFile << message;
	outputToFile.close();
}