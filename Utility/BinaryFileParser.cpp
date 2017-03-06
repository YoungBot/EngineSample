//==========================================================
//BinaryFileParser.cpp
//==========================================================
#include "BinaryFileParser.hpp"

BinaryFileParser::BinaryFileParser(std::string fileName) 
{
	Utility::LoadBinaryFileToExistingVectorByteBuffer(fileName,m_buffer);
	m_bufferStart = m_buffer.data();
	m_bufferSize = m_buffer.size();
	m_nextByteToRead = m_bufferStart;
}
BinaryFileParser::BinaryFileParser()
{

}
BinaryFileParser::~BinaryFileParser()
{

}