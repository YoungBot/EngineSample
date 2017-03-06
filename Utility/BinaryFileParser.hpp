//==========================================================
//BinaryFileParser.hpp
//==========================================================
#pragma once
#ifndef _BINARY_FILE_PARSER_
#define _BINARY_FILE_PARSER_
#include"BinaryBufferParser.hpp"
#include"Utility.hpp"

class BinaryFileParser : public BinaryBufferParser
{
public:
	BinaryFileParser();
	BinaryFileParser (std::string fileName);
	~BinaryFileParser ();

	std::vector<unsigned char> m_buffer;
};


#endif

