//==========================================================
//Utility.cpp
//==========================================================
#define WINDOWS_LEAN_AND_MEAN
#include "Utility.hpp"
#include <io.h>
#include <stdio.h>
#include <windows.h>
#include "Engine/Math/MathUtils.hpp"
#include <atlstr.h>
#include <algorithm>


bool s_isRunning = true;
bool Utility::WriteBufferToBinaryFile(const unsigned char* buffer,size_t bufferSize, const std::string& filePath)
{
	FILE* file;
	fopen_s(&file,filePath.c_str(),"wb");
	if(!file)
	{
		return false;
	}

	fwrite(buffer,1,bufferSize,file);
	fclose(file);
	return true;
}
///------------------------------------------------------
///
///------------------------------------------------------
bool Utility::WriteVectorBufferToBinaryFile(const std::vector<unsigned char> vectorBuffer, const std::string& filePath)
{
	FILE* file;
	fopen_s(&file, filePath.c_str(), "wb");
	if (!file)
	{
		return false;
	}
	size_t bufferSize = vectorBuffer.size()*sizeof(unsigned char);
	
	fwrite(vectorBuffer.data(), 1, bufferSize, file);
	fclose(file);
	return true;
}
///------------------------------------------------------
///
///------------------------------------------------------
bool Utility::WriteBufferToASCIIFile(const char* buffer, size_t bufferSize, const std::string& filePath)
{
	FILE* file;
	fopen_s(&file, filePath.c_str(), "wb");
	if (!file)
	{
		return false;
	}

	fwrite(buffer, 1, bufferSize, file);
	fclose(file);
	return true;
}
///------------------------------------------------------
///
///------------------------------------------------------
bool Utility::WriteStringToASCIIFile(const std::string stringBuffer,const std::string& filePath)
{
	FILE* file;
	fopen_s(&file, filePath.c_str(), "wb");
	if (!file)
	{
		return false;
	}
	size_t bufferSize = stringBuffer.size()*sizeof(char);	
	fwrite(stringBuffer.data(), 1, bufferSize-1, file);
	fclose(file);
	return true;
}
///------------------------------------------------------
///
///------------------------------------------------------
unsigned char* Utility::LoadBinaryFileToNewBuffer(const std::string& filePath)
{
	FILE* file;// = fopen_s(filePath.c_str(),"rb");
	fopen_s(&file,filePath.c_str(),"rb");
	if(!file)
	{
		return false;
	}

	fseek( file, 0, SEEK_END );
	size_t numBytesInFile = ftell( file );
	rewind( file );
	unsigned char* buffer = new unsigned char[numBytesInFile];

	fread(buffer,1,numBytesInFile,file);
	fclose( file );
	return buffer;
}
///------------------------------------------------------
///
///------------------------------------------------------

bool Utility::LoadBinaryFileToExistingBuffer(const std::string& filePath, unsigned char* buffer, size_t existingBufferSize)
{
	FILE* file;// = fopen(filePath.c_str(),"rb");
	fopen_s(&file,filePath.c_str(),"rb");
	if(!file)
		return false;

	size_t count = fread(buffer,1,existingBufferSize,file);
	count;
	fclose( file );
	return true;
}
///------------------------------------------------------
///
///------------------------------------------------------
bool Utility::LoadBinaryFileToExistingVectorByteBuffer(const std::string& filePath, std::vector<unsigned char>& vectorBuffer)
{
	FILE* file;// = fopen(filePath.c_str(),"rb");
	fopen_s(&file, filePath.c_str(), "rb");
	if (!file)
		return false;

	fseek(file, 0, SEEK_END);
	size_t numBytesInFile = ftell(file);
	rewind(file);
	vectorBuffer.resize(numBytesInFile);	
	size_t count = fread(vectorBuffer.data(), 1, numBytesInFile, file);//can I do this?
	count;
	fclose(file);
	return true;
}
///------------------------------------------------------
///
///------------------------------------------------------

unsigned char* Utility::FileReadAll(char const *filename, size_t *out_len)
{
	*out_len = 0;
	FILE* file;
	fopen_s(&file, filename, "rb"); // cFile_Read);
	if (file == NULL) {
		return nullptr;
	}
	fseek(file, 0, SEEK_END);
	size_t file_len = ftell(file);
	        
	rewind(file);
	fclose(file);

	unsigned char *buffer = (unsigned char*)malloc(file_len + 1);
	if (buffer != nullptr) 
	{
		LoadBinaryFileToExistingBuffer(filename, buffer, file_len);
		buffer[file_len] = NULL;
		*out_len = file_len;
	}
	

	return buffer;
}
//////////////////////////////////////////////////////////////////////////
TiXmlDocument* Utility::LoadAndGetXMLFile(const char* filename)
{
	TiXmlDocument* doc = new TiXmlDocument(filename);
	bool loadOkay = doc->LoadFile();
	// faile to load 'phonebookdata.xml'.  
	if (!loadOkay) {
		return nullptr;
	}
	return doc;
}
//////////////////////////////////////////////////////////////////////////

FILE* Utility::ReadTXTFile(const char* filename)
{
	FILE* file;
	fopen_s(&file, filename, "rb"); // cFile_Read);
	if (file == NULL) {
		return nullptr;
	}
	else
		return file;
}

bool Utility::LoadASCIIFileToExistingBuffer(const std::string& filePath, char* buffer, size_t existingBufferSize)
{
	FILE* file;// = fopen(filePath.c_str(),"rb");
	fopen_s(&file, filePath.c_str(), "rb");
	if (!file)
		return false;												//Do I need to add +1 here?
	size_t count = fread(buffer, 1, existingBufferSize, file);									
	buffer[count] = '\0';
	fclose(file);
	return true;
}
///------------------------------------------------------
///
///------------------------------------------------------
char* Utility::LoadASCIIFileToNewBuffer(const std::string& filePath)
{
	FILE* file;// = fopen_s(filePath.c_str(),"rb");
	fopen_s(&file, filePath.c_str(), "rb");
	if (!file)
	{
		return false;
	}

	fseek(file, 0, SEEK_END);
	size_t numBytesInFile = ftell(file);
	rewind(file);
	char* buffer = new char[numBytesInFile];

	fread(buffer, 1, numBytesInFile, file);
	buffer[numBytesInFile] = '\0';
	fclose(file);
	return buffer;
}
///------------------------------------------------------
///
///------------------------------------------------------
bool Utility::LoadASCIIFileToExistingString(const std::string& filePath, std::string& stringBuffer)
{
	FILE* file;// = fopen(filePath.c_str(),"rb");
	fopen_s(&file, filePath.c_str(), "rb");
	if (!file)
		return false;
	fseek(file, 0, SEEK_END);
	size_t numBytesInFile = ftell(file);
	rewind(file);
	stringBuffer.resize(numBytesInFile);
	size_t count = fread((void*)stringBuffer.data(), 1, numBytesInFile, file);
	count;
	fclose(file);
	return true;
}
///------------------------------------------------------
///
///------------------------------------------------------

bool Utility::FindAllFilesOfType(const std::string& directory, const std::string& searchPattern, std::vector<std::string>& filesFound_out)
{
	struct _finddata_t fileData;
	intptr_t searchHandle;
	std::string searchPath;
	searchPath = directory + searchPattern;
	searchHandle = _findfirst(searchPath.c_str(), &fileData);
	if (searchHandle != -1)
	{
		do
		{
			filesFound_out.push_back(fileData.name);
		} while (_findnext(searchHandle, &fileData) == 0);
	}
	else
		return false;
	if (_findclose(searchHandle) == 0 && filesFound_out.size()!=0)
	{
		return true;
	}
	else
		return false;	
}
///------------------------------------------------------
///
///------------------------------------------------------
bool Utility::TestFourChars(unsigned char* buffer, const std::string& fourChars)
{
	for (int i = 0; i < 4; i++)
	{
		if (buffer[i]!=fourChars[i])
		{
			return false;
		}
	}
	return true;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

std::string Utility::CutString(std::string& ori, const char delim)
{
	std::string result = "";
	for (int i = 0; i <= (int)ori.length(); i++)
	{
		if (i == (int)ori.length())
		{
			ori = "";
			break;
		}
		if (ori[i] == delim)
		{
			if (i + 1 < (int)ori.length())
			{
				ori = ori.substr(i + 1, ori.length() - i - 1);
				break;
			}

			break;
		}
		result += ori[i];
	}

	return result;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

std::string Utility::ConvertIntToString(const int number)
{
	int value = number;
	std::string outputString = "";
	if (value < 0)
	{
		value *= -1;
	}
	do
	{
		unsigned int num = value % 10;		
		char numChar = (char)(num + 48);
		outputString.insert(outputString.begin(), numChar);
		value /= 10;
	}while (value != 0);
	
	if (number<0)
	{
		outputString.insert(outputString.begin(), '-');
	}
	return outputString;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Utility::FatalError(const char* errorText, const char* fileName, const char* functionName, const long lineNumber)
{
	std::string errorMessage = "";
	errorMessage += "File Name: ";
	errorMessage += fileName;
	errorMessage += " \n\rFunction Name: ";
	errorMessage += functionName;
	errorMessage += " \n\rLine Number: ";
	char numString[5];
	_itoa(lineNumber, numString, 5);
	errorMessage += numString;
	errorMessage += " \n\rPossible Reason: ";
	errorMessage += errorText;
	int output = MessageBoxA(NULL, errorMessage.c_str(), "Fatal Error", MB_OK | MB_ICONSTOP);
	if (output == IDOK)
	{
		s_isRunning = false;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Utility::RecoverableError(const char* errorText, const char* fileName, const char* functionName, const long lineNumber)
{

	std::string errorMessage = "";
	errorMessage += "File Name: ";
	errorMessage += fileName;
	errorMessage += " \n\rFunction Name: ";
	errorMessage += functionName;
	errorMessage += " \n\rLine Number: ";
	char numString[5];
	_itoa(lineNumber, numString, 5);
	errorMessage += numString;
	errorMessage += " \n\rPossible Reason: ";
	errorMessage += errorText;
	errorMessage += "\n\rPress OK to Quit, Press Cancel to Continue.";
	int output = MessageBoxA(NULL, errorMessage.c_str(), "Recoverable Error", MB_OKCANCEL | MB_ICONSTOP);
	if (output == IDOK)
	{
		s_isRunning = false;
	}
}

void Utility::FatalAssertion(bool condition, const char* errorText, const char* fileName, const char* functionName, const long lineNumber)
{
	if (condition==true)
	{
		return;
	}
	std::string errorMessage = "";
	errorMessage += "File Name: ";
	errorMessage += fileName;
	errorMessage += " \n\rFunction Name: ";
	errorMessage += functionName;
	errorMessage += " \n\rLine Number: ";
	char numString[5];
	_itoa(lineNumber, numString, 5);
	errorMessage += numString;
	errorMessage += " \n\rPossible Reason: ";
	errorMessage += errorText;
	int output = MessageBoxA(NULL, errorMessage.c_str(), "Fatal Assertion", MB_OK | MB_ICONWARNING);
	if (output == IDOK)
	{
		s_isRunning = false;
	}
}

void Utility::RecoverableAssertion(bool condition, const char* errorText, const char* fileName, const char* functionName, const long lineNumber)
{
	if (condition == true)
	{
		return;
	}
	std::string errorMessage = "";
	errorMessage += "File Name: ";
	errorMessage += fileName;
	errorMessage += " \n\rFunction Name: ";
	errorMessage += functionName;
	errorMessage += " \n\rLine Number: ";
	char numString[5];
	_itoa(lineNumber, numString, 5);
	errorMessage += numString;
	errorMessage += " \n\rPossible Reason: ";
	errorMessage += errorText;
	errorMessage += "\n\rPress OK to Quit, Press Cancel to Continue.";
	int output = MessageBoxA(NULL, errorMessage.c_str(), "Recoverable Error", MB_OKCANCEL | MB_ICONWARNING);
	if (output == IDOK)
	{
		s_isRunning = false;
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool Utility::ProcessRawCommandLine(LPSTR lpCmdLine)
{
	if (lpCmdLine == nullptr) {
		return true;
	}

	// Conver to ASCII if we're using Unicode
	std::string command_line;
	command_line = (char const*)lpCmdLine;


	//if (sizeof(TCHAR) == sizeof(wchar_t)) {
	//	std::wstring temp = (wchar_t const*)lpCmdLine;
	//	command_line.assign(temp.begin(), temp.end());
	//}
	//else {
	//	// this conversion does nothing if we're in wchar_t mode
	//	command_line = (char const*)lpCmdLine;
	//}

	CCommandList commands = ParseCommands(command_line);
	bool result = ProcessCommands(commands);
	FreeCommands(commands);
	return result;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool Utility::WriteToFileCommand(CCommand const *command)
{
	int arg0;
	int arg1;
	if (!command->GetInt(0, &arg0) || !command->GetInt(1, &arg1)) {
		return false;
	}

	for (int i = 0; i < arg0; i++)
	{
		std::string outputFilePath = "Data/CommandOutput/output";		
		outputFilePath += ConvertIntToString(i);
		outputFilePath += ".dat";
		std::string outputString = "";
		int charCounter = 0;
		while (charCounter<=arg1*1024)
		{
			outputString += (char)MathUtils::GetRandomIntInRange(33, 126);
			charCounter++;
		}
		WriteBufferToASCIIFile(outputString.c_str(),arg1*1024,outputFilePath);
	}

	int output = MessageBoxA(NULL, "WriteToFileCommand Succeeded. Continue?", "", MB_YESNO);
	if (output == IDYES)
		return true;
	else
		return false;
}

int Utility::FireEvent(const std::string& eventName, NamedProperties* np)
{
	EventSystem& eventSys = EventSystem::GetInstance();
	return eventSys.FireEvent(eventName, *np);
	
}

bool Utility::RegisterEventCallback(const std::string& eventName, EventCallback* cb)
{
	EventSystem& eventSys = EventSystem::GetInstance();
	return eventSys.RegisterEvent(eventName,cb);
}

bool Utility::UnregisterEventCallback(const std::string& eventName, EventCallback* cb)
{
	EventSystem& eventSys = EventSystem::GetInstance();
	return eventSys.UnRegisterEvent(eventName, cb);
}
///----------------------------------------------------------
///
///----------------------------------------------------------
bool CheckPattern(const std::string& name, const std::string& pattern)
{
	std::string patt = "*.";
	for (unsigned int i = name.size() - 1; i >= 0;i--)
	{
		if (name[i]=='.')
			break;
		else
			patt += name[i];
	}
	int result = strcmp(patt.c_str(), pattern.c_str());
	if (result == 0)
		return true;
	else
		return false;
}
bool Utility::EnumerateFiles(const std::string& baseFolder, const std::string& filePattern, std::vector<std::string>& filesFound_out, bool recurseSubfolders)
{
	struct _finddata_t fileData;
	intptr_t searchHandle;
	std::string searchPath;
	
	searchPath = baseFolder + "*.*";
	searchHandle = _findfirst(searchPath.c_str(), &fileData);
	if (searchHandle != -1)
	{
		do
		{
			if (fileData.attrib==32 && CheckPattern(fileData.name,filePattern))
			{
				filesFound_out.push_back(baseFolder + fileData.name);
			}
			else if (fileData.attrib == 16 && fileData.name[0] != '.' && recurseSubfolders)
			{
				EnumerateFiles(baseFolder + fileData.name+"/", filePattern, filesFound_out, recurseSubfolders);
			}
		} while (_findnext(searchHandle, &fileData) == 0);
	}
	else
		return false;
	if (_findclose(searchHandle) == 0 && filesFound_out.size() != 0)
	{
		return true;
	}
	else
		return false;
}
///----------------------------------------------------------
///
///----------------------------------------------------------
std::string RemovePattern(const std::string& fileName)
{
	std::string name = fileName;
	for (unsigned int i = name.size() - 1; i >= 0; i--)
	{
		if (name[i] == '.')
		{
			name[i] = '\0';
			break;
		}
		else
			name[i] = '\0';
	}
	return name;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

bool ChangeBackSlashToSlash(std::string& fileName)
{
	std::replace(fileName.begin(), fileName.end(), '\\', '/');
	return true;
}
//////////////////////////////////////////////////////////////////////////
std::string GetFullFilePath(std::string& relativePath)
{
	TCHAR  absolutePath[300] = TEXT("");
	TCHAR  relative[300] = TEXT("");
	_tcscpy_s(relative, CA2T(relativePath.c_str()));
	GetFullPathName(relative, 300, absolutePath, NULL);
	std::wstring convert(&absolutePath[0]); //convert to wstring
	std::string absolute(convert.begin(), convert.end());
	ChangeBackSlashToSlash(absolute);
	return absolute;
}
void Utility::FireEventForEachFileFound(const std::string& eventToFire, const std::string& baseFolder, const std::string& filePattern, bool recurseSubfolders)
{
		//¡°FileName¡±				¡°ExplosionSprites.png¡±
		//¡°FileExtension¡±			¡°.png¡±
		//¡°FileNameWithoutExtension¡±		¡°ExplosionSprites¡±
		//¡°FileRelativePath¡±			¡°Images / ExplosionSprites.png¡±
		//¡°FileAbsolutePath¡±			¡°C : / Guildhall / Projects / Tanks / Data / Images / ExplosionSprites.png¡±
	NamedProperties np;
	struct _finddata_t fileData;
	intptr_t searchHandle;
	std::string searchPath;

	searchPath = baseFolder + "*.*";
	searchHandle = _findfirst(searchPath.c_str(), &fileData);
	if (searchHandle != -1)
	{
		do
		{
			if (fileData.attrib == 32 && CheckPattern(fileData.name, filePattern))
			{
				std::string relativePath = baseFolder + fileData.name;
				np.Set("FileName", fileData.name);
				np.Set("FileExtension", filePattern);
				np.Set("FileNameWithoutExtension", RemovePattern(fileData.name));
				np.Set("FileRelativePath", relativePath);
				np.Set("FileAbsolutePath", GetFullFilePath(relativePath));
				Utility::FireEvent(eventToFire, &np);
			}
			else if (fileData.attrib == 16 && fileData.name[0] != '.' && recurseSubfolders)
			{
				FireEventForEachFileFound(eventToFire, baseFolder + fileData.name + "/", filePattern, recurseSubfolders);
			}
		} while (_findnext(searchHandle, &fileData) == 0);
	}
}
