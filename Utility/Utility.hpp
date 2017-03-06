//==========================================================
//Utility.hpp
//==========================================================
#pragma once

#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "Engine/TinyXML/tinyxml.h"
#include "Engine/Thread/Command.hpp"
#include "Engine/EventSystem/EventSystem.hpp"

class EventSystem;
class NamedProperties;

#define FATAL_ERROR(errorText) Utility::FatalError(errorText,__FILE__,__FUNCTION__,__LINE__)
#define RECOVERABLE_ERROR(errorText) Utility::RecoverableError(errorText,__FILE__,__FUNCTION__,__LINE__)
#define FATAL_ASSERTION(condition,errorText) Utility::FatalAssertion(condition,errorText,__FILE__,__FUNCTION__,__LINE__)
#define RECOVERABLE_ASSERTION(condition,errorText) Utility::RecoverableAssertion(condition,errorText,__FILE__,__FUNCTION__,__LINE__)
typedef void(EventCallback)(NamedProperties& args);



class Utility
{
public:
	static bool WriteBufferToBinaryFile(const unsigned char* buffer,size_t bufferSize, const std::string& filePath);
	static bool WriteVectorBufferToBinaryFile(const std::vector<unsigned char> vectorBuffer, const std::string& filePath);
	static bool WriteBufferToASCIIFile(const char* buffer, size_t bufferSize, const std::string& filePath);
	static bool WriteStringToASCIIFile(const std::string stringBuffer,const std::string& filePath);
	static bool LoadBinaryFileToExistingBuffer(const std::string& filePath, unsigned char* buffer, size_t existingBufferSize);
	static bool LoadBinaryFileToExistingVectorByteBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);
	static unsigned char* LoadBinaryFileToNewBuffer(const std::string& filePath);

	static bool LoadASCIIFileToExistingBuffer(const std::string& filePath, char* buffer, size_t existingBufferSize);
	static bool LoadASCIIFileToExistingString(const std::string& filePath, std::string& stringBuffer);
	static char* LoadASCIIFileToNewBuffer(const std::string& filePath);

	static unsigned char* FileReadAll(const char* filename, size_t *out_len);
	static TiXmlDocument* LoadAndGetXMLFile(const char* filename);
	static FILE* ReadTXTFile(const char* filename);
	static unsigned char* CreateMeshFromC23File(const std::string& filePath,const std::string& fourChars);
	static bool TestFourChars(unsigned char* buffer, const std::string& fourChars);
	static std::string CutString(std::string& ori, const char delim);
	static bool FindAllFilesOfType(const std::string& directory, const std::string& searchString, std::vector<std::string>& filesFound_out);
	static std::string ConvertIntToString(const int number);

	static void FatalError(const char* errorText, const char* fileName, const char* functionName, const long lineNumber);
	static void RecoverableError(const char* errorText, const char* fileName, const char* functionName, const long lineNumber);
	static void FatalAssertion(bool condition, const char* errorText, const char* fileName, const char* functionName, const long lineNumber);
	static void RecoverableAssertion(bool condition, const char* errorText, const char* fileName, const char* functionName, const long lineNumber);
	static bool ProcessRawCommandLine(LPSTR lpCmdLine);
	static bool WriteToFileCommand(CCommand const *command);
	static int FireEvent(const std::string& eventName, NamedProperties* np=nullptr);
	static bool RegisterEventCallback(const std::string& eventName, EventCallback* cb);
	template<typename T_ObjType, typename T_MethodPtrType>
	static bool RegisterEventSubscribe(const std::string& eventName, T_ObjType& obj, T_MethodPtrType method);
	static bool UnregisterEventCallback(const std::string& eventName, EventCallback* cb);
	static bool EnumerateFiles(const std::string& basefolder, const std::string& filePattern, std::vector<std::string>& filesFound_out, bool recurseSubfolders);
	static void FireEventForEachFileFound(const std::string& eventToFire, const std::string& baseFolder, const std::string& filePattern, bool recurseSubfolders);
};

template<typename T_ObjType, typename T_MethodPtrType>
inline bool Utility::RegisterEventSubscribe(const std::string& eventName, T_ObjType& obj, T_MethodPtrType method)
{
	EventSystem& eventSys = EventSystem::GetInstance();
	return eventSys.RegisterEventSubscribe(eventName, obj, method);
}

extern bool s_isRunning;

#endif


//std::vector< std::string > EnumerateFiles(const std::string& basefolder,const std::string& filePattern, bool recurseSubfolders);
//
//which finds all files in folder(and will, if indicated, recurse into subfolders) which match filePattern(such as ¡°*.dat¡±),
//returning the list of results(as file / paths relative to the base folder).
