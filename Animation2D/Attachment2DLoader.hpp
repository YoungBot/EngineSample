//==========================================================
//OutAttachmentLoader.hpp
//==========================================================
#pragma once

#ifndef _ATTACHMENT2DLOADER_HPP_
#define _ATTACHMENT2DLOADER_HPP_


#include <string>
class AttachmentLoaderImplementation;

class Attachment2DLoader
{
public:
	Attachment2DLoader();
	~Attachment2DLoader();
	AttachmentLoaderImplementation* GetAttachmentLoaderImplementation(){ return m_implementation; }
	void* GetImplementationSpecificAttachementLoader()const; 
protected:
	AttachmentLoaderImplementation* m_implementation;
};

#endif