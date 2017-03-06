//==========================================================
//OutAttachmentLoader.cpp
//==========================================================
#include "Attachment2DLoader.hpp"
#include <spine/AttachmentLoader.h>
#include <spine/extension.h>
#include <string>

std::string GetTypeNameString(spAttachmentType type)
{
	switch (type)
	{
	case SP_ATTACHMENT_REGION:
		return "REGION_ATTACHMENT";
	case SP_ATTACHMENT_BOUNDING_BOX:
		return "BOUNDINGBOX_ATTACHMENT";
	case SP_ATTACHMENT_MESH:
		return "MESH_ATTACHMENT";
	case  SP_ATTACHMENT_SKINNED_MESH:
		return "SKINNED_MESH_ATTACHMENT";
	default:
		return "";
	}
}

class AttachmentLoaderImplementation : public spAttachmentLoader
{
public:
	AttachmentLoaderImplementation();
	static spAttachment* newAttachment(spAttachmentLoader* self, spSkin* skin, spAttachmentType type, const char* name, const char* path);
};
///----------------------------------------------------------
///
///----------------------------------------------------------

AttachmentLoaderImplementation::AttachmentLoaderImplementation()
{
	_spAttachmentLoader_init(this, nullptr, &newAttachment);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

spAttachment* AttachmentLoaderImplementation::newAttachment(spAttachmentLoader* self, spSkin* skin, spAttachmentType type, const char* name, const char* path)
{
	self;
	skin;
	type;
	path;
	spAttachment* attachment = nullptr;
	
	switch (type)
	{
	case SP_ATTACHMENT_REGION:
	{
		spRegionAttachment* newRegionAttachment = spRegionAttachment_create(name);
		attachment = &(newRegionAttachment->super);
		
		newRegionAttachment->regionOriginalWidth = 100;
		newRegionAttachment->regionOriginalHeight = 100;
		newRegionAttachment->regionWidth = newRegionAttachment->regionOriginalHeight;
		newRegionAttachment->regionHeight = newRegionAttachment->regionOriginalWidth;
		break;
	}	
	case SP_ATTACHMENT_BOUNDING_BOX:
	{
		spBoundingBoxAttachment* newBoundingBoxAttachment = spBoundingBoxAttachment_create(name);
		attachment = &(newBoundingBoxAttachment->super);

		break;
	}
	case SP_ATTACHMENT_MESH:
	{
		spMeshAttachment* newMeshAttachment = spMeshAttachment_create(name);
		attachment = &(newMeshAttachment->super);
		break;
	}
	case  SP_ATTACHMENT_SKINNED_MESH:
	{
		spSkinnedMeshAttachment* newSkinnedMeshAttachment = spSkinnedMeshAttachment_create(name);
		attachment = &(newSkinnedMeshAttachment->super);
		break;
	}
	default:
		break;
	}
	return attachment;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Attachment2DLoader::Attachment2DLoader()
	: m_implementation(nullptr)
	
{
	m_implementation = new AttachmentLoaderImplementation();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void* Attachment2DLoader::GetImplementationSpecificAttachementLoader() const 
{
	return (void*)m_implementation;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Attachment2DLoader::~Attachment2DLoader()
{

}
