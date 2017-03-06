//==========================================================
//JobGroup.hpp
//==========================================================
#pragma once
#include "JobManager.hpp"
#include "Engine/Utility/Utility.hpp"
#include "Engine/Math/MathUtils.hpp"
class CTestJob : public CJob
{
private:
	unsigned int wait_ms;
	std::string m_name;

protected:
	virtual void Run()
	{
		ThreadSleep(wait_ms);
		MessageBoxA(NULL, m_name.c_str(), "", MB_OK);
	}

public:
	CTestJob(unsigned int ms, std::string name)
	{
		wait_ms = ms;
		m_name = name;
	}
};
//////////////////////////////////////////////////////////////////////////
class LoadFileJob : public CJob
{
private:
	unsigned int m_waitMS;
	unsigned char* m_buffer;
	size_t m_bufferSize;
	std::string m_filePath;

protected:
	virtual void Run()
	{
		ThreadSleep(m_waitMS);
		bool result = Utility::LoadBinaryFileToExistingBuffer(m_filePath, m_buffer, m_bufferSize);
		if (result)
			MessageBoxA(NULL, "File loaded successfully", "", MB_OK);
		else
			MessageBoxA(NULL, "File loaded failed", "", MB_OK);
	}

public:
	LoadFileJob(unsigned int ms, unsigned char* buffer, std::string FilePath, size_t bufferSize)
		:m_waitMS(ms)
		, m_bufferSize(bufferSize)
		, m_buffer(buffer)
		, m_filePath(FilePath)
	{
		
	}
};
//////////////////////////////////////////////////////////////////////////
class ReverseBufferJob : public CJob
{
private:
	unsigned int m_waitMS;
	unsigned char* m_buffer;
	size_t m_bufferSize;

protected:
	virtual void Run()
	{
		ThreadSleep(m_waitMS);
		int MaxCounter = m_bufferSize / 2;
		for (int i = 0; i < MaxCounter; ++i)
		{
			unsigned char currentChar = m_buffer[i];
			m_buffer[i] = m_buffer[m_bufferSize - 1 - i];
			m_buffer[m_bufferSize - 1 - i] = currentChar;
		}
		MessageBoxA(NULL, "Buffer reversed successfully", "", MB_OK);
	}

public:
	ReverseBufferJob(unsigned int ms, unsigned char* buffer, size_t bufferSize)
		:m_waitMS(ms)
		, m_bufferSize(bufferSize)
		, m_buffer(buffer)
	{
		
		//wait_ms = ms;
		//m_name = name;
	}
};
//////////////////////////////////////////////////////////////////////////
class HashBufferJob : public CJob
{
private:
	unsigned int m_waitMS;
	unsigned char* m_buffer;
	unsigned long m_hash;


protected:
	virtual void Run()
	{
		ThreadSleep(m_waitMS);
		m_hash = 5381;
		int c;

		while (c = *m_buffer++)
			m_hash = ((m_hash << 5) + m_hash) + c; /* hash * 33 + c */

		MessageBoxA(NULL, "HashBufferDone", "", MB_OK);
	}

public:
	HashBufferJob(unsigned int ms, unsigned char* buffer)
		:m_waitMS(ms)
		, m_buffer(buffer)
		, m_hash(0)
	{

	}
};
//////////////////////////////////////////////////////////////////////////
class SaveFileJob : public CJob
{
private:
	unsigned int m_waitMS;
	unsigned char* m_buffer;
	size_t m_bufferSize;
	std::string m_filePath;

protected:
	virtual void Run()
	{
		ThreadSleep(m_waitMS);
		bool result = Utility::WriteBufferToBinaryFile(m_buffer, m_bufferSize, m_filePath);
		if (result)
			MessageBoxA(NULL, "File saved successfully", "", MB_OK);
		else
			MessageBoxA(NULL, "File saved failed", "", MB_OK);
	}

public:
	SaveFileJob(unsigned int ms, unsigned char* buffer, std::string FilePath, size_t bufferSize)
		:m_waitMS(ms)
		, m_bufferSize(bufferSize)
		, m_buffer(buffer)
		, m_filePath(FilePath)
	{

	}
};
///----------------------------------------------------------
///
///----------------------------------------------------------

class CTestThread : public CThread
{
protected:
	virtual void Run()
	{
		Sleep(2000);
		MessageBoxA(NULL, "Thread Finished 2 Seconds Later.", "", MB_OK);
	}
};
///----------------------------------------------------------
///
///----------------------------------------------------------

class GenerateFileJob : public CJob
{
private:
	unsigned int m_waitMS;
	int m_numKiloBytes;
	int m_numFiles;


protected:
	virtual void Run()
	{
		ThreadSleep(m_waitMS);
		for (int i = 0; i < m_numFiles; i++)
		{
			std::string outputFilePath = "Data/CommandOutput/output";
			outputFilePath += Utility::ConvertIntToString(i);
			outputFilePath += ".dat";
			std::string outputString = "";
			int charCounter = 0;
			while (charCounter <= m_numKiloBytes * 1024)
			{
				outputString += (char)MathUtils::GetRandomIntInRange(33, 126);
				charCounter++;
			}
			Utility::WriteBufferToASCIIFile(outputString.c_str(), m_numKiloBytes*1024, outputFilePath);
		}

		MessageBoxA(NULL, "Files Generated", "", MB_OK);
	}

public:
	GenerateFileJob(unsigned int ms, int numKiloBytes,int numFiles)
		:m_waitMS(ms)
		, m_numKiloBytes(numKiloBytes)
		, m_numFiles(numFiles)
	{

	}
};