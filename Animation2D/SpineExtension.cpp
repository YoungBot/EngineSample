#include "SpineExtension.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Engine/Renderer/Texture.hpp"
#include <spine/Atlas.h>

bool LoadBinaryFileToExistingBuffer(const std::string& filePath, char* buffer, size_t existingBufferSize)
{
	FILE* file;// = fopen(filePath.c_str(),"rb");
	fopen_s(&file, filePath.c_str(), "rb");
	if (!file)
		return false;

	size_t count = fread(buffer, 1, existingBufferSize, file);
	count;
	fclose(file);
	return true;
}

void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
{
	Texture* newTexture = Texture::CreateOrGetTexture(path);
	self->rendererObject = newTexture;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void _spAtlasPage_disposeTexture(spAtlasPage* self)
{
	self;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

char* _spUtil_readFile(const char* path, int* length)
{
	*length = 0;
	FILE* file;
	fopen_s(&file, path, "rb"); // cFile_Read);
	if (file == NULL) {
		return nullptr;
	}
	fseek(file, 0, SEEK_END);
	size_t file_len = ftell(file);

	rewind(file);
	fclose(file);

	char *buffer = (char*)malloc(file_len + 1);
	if (buffer != nullptr)
	{
		LoadBinaryFileToExistingBuffer(path, buffer, file_len);
		buffer[file_len] = NULL;
		*length = file_len;
	}


	return buffer;
}