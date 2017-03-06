//==========================================================
//Skeleton2D.cpp
//==========================================================

#include "Skeleton2D.hpp"
#include "Skeleton2DData.hpp"
#include "Skeleton2DAnimation.hpp"
#include <spine/Skeleton.h>
#include "Engine/Math/Vector3.hpp"
#include "Engine/Renderer/OpenGLRenderer.hpp"
#include "Engine/Console/Console.hpp"
#include <spine/RegionAttachment.h>
#include <spine/MeshAttachment.h>
#include "Engine/Renderer/GLMaterial.hpp"
#include "Engine/Renderer/GLMesh.hpp"
#include "Engine/Renderer/GLMeshRenderer.hpp"
const int WORLD_VERTS_SIZE = 100;
struct SkeletonRenderer
{
	int m_numOfVerts;
	NTBVertex3D_PCT* m_verts;
	GLMeshRenderer* m_meshRenderer;
	GLShader m_skeletonShader;
	GLSampler m_skeletonSampler;
	GLMaterial m_skeletonMaterial;
	Texture* m_texture;
	std::vector<GLMeshRenderer*> m_meshRenderers;
	SkeletonRenderer(Texture* texture);
	void Init(int numOfSlots);
	void UpdateMeshRenderer(NTBVertex3D_PCT* verts,int numberOfVerts);
	void DrawSkeleton(const Matrix4x4& transformMatrix);
};
///----------------------------------------------------------
///
///----------------------------------------------------------
SkeletonRenderer::SkeletonRenderer(Texture* texture)
	:m_numOfVerts(0)
	, m_verts(nullptr)
	, m_meshRenderer(nullptr)
{
	m_skeletonShader = GLShader("Data/Shaders/basic.vert", "Data/Shaders/basic.frag");
	m_skeletonSampler.CreateSampler(GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
	m_skeletonSampler.gTexDiffuse = texture;
	m_skeletonMaterial = GLMaterial(m_skeletonShader, m_skeletonSampler);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void SkeletonRenderer::Init(int numOfSlots)
{
	GLMesh mesh(nullptr, 6 * sizeof(NTBVertex3D_PCT));
	m_meshRenderer = new GLMeshRenderer(mesh, m_skeletonMaterial);
	GLMeshRenderer* currentMeshRenderer = new GLMeshRenderer(mesh, m_skeletonMaterial);
	for (int i = 0; i < numOfSlots; i++)
	{
		m_meshRenderers.push_back(currentMeshRenderer);
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void SkeletonRenderer::UpdateMeshRenderer(NTBVertex3D_PCT* verts, int numberOfVerts)
{
	m_meshRenderer->m_mesh.UpdateVBO(verts, sizeof(NTBVertex3D_PCT)*numberOfVerts);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void SkeletonRenderer::DrawSkeleton(const Matrix4x4& transformMatrix)
{
	Matrix4x4 I;
	I.MakeIdentity();
	glDisable(GL_DEPTH_TEST);
	for (unsigned int i = 0; i < m_meshRenderers.size();++i)
	{
		m_meshRenderers[i]->DrawShaderPolygon(0.0f, transformMatrix, I);
	}
	
}

//////////////////////////////////////////////////////////////////////////
float scale = 0.8f;
class Skeleton2DImplementation
{
public:
	Skeleton2DImplementation(Skeleton2DDataImplementation* skeletonData);
	Skeleton2DImplementation::Skeleton2DImplementation(spSkeletonData* skeletonData);
	spSkeleton* GetSkeleton(){ return m_skeleton; }
	NTBVertex3D_PCT* GetBoneData();
	void DebugSkeleton();
	void DebugDrawSkeletonBone(OpenGLRenderer* renderer);
	void DebugDrawRectSlot(OpenGLRenderer* renderer);
	void DrawRectSlot(const Matrix4x4& transformMatrix);
	void Update(float deltaSecond);
	void OneTextureInitMeshRenderer();
	void UpdateVerts();
	void SetScaleSize(float scale);
	void SetPosition(const Vector2& newPosition);
	const Vector2& GetPosition(){ return m_position; }
	void FlipSkeletonX(bool isFlip);
	void FlipSkeletonY(bool isFlip);
	void SetBoneRotation(const std::string& targetBoneName, float rotationDegree);
	void UpdateBoneRotation();
	Vector2 GetBonePositionByName(const std::string& boneName);
	Vector2 GetSlotPositionByName(const std::string& slotName);
	void SetBonePositionByName(const Vector2& newPosition, const std::string& boneName);
	AABB2D GetSkeletonBox();
protected:
	spSkeleton* m_skeleton;
	std::vector<SkeletonRenderer*> m_meshRenderers;
	SkeletonRenderer* skeletonRenderer;
	Vector2 m_position;
	AABB2D m_skeletonBox;
	std::vector<std::pair<spBone*, float>> m_rotationList;
};
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DImplementation::Skeleton2DImplementation(Skeleton2DDataImplementation* skeletonData)
	:skeletonRenderer(nullptr)
	, m_position(Vector2(0.0f,0.0f))
	
{
	m_skeletonBox = (AABB2D(Vector2(0.0f, 0.0f), 0.0F, 0.0F));
	m_rotationList.clear();
	m_meshRenderers.clear();
	if (skeletonData == nullptr)
		m_skeleton = nullptr;
	//else
		//m_skeleton = spSkeleton_create(skeletonData->GetSkeletonData());
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2DImplementation::Skeleton2DImplementation(spSkeletonData* skeletonData)
	:skeletonRenderer(nullptr)
	, m_position(Vector2(0.0f, 0.0f))
	,m_skeletonBox(AABB2D(Vector2(0.0f, 0.0f), 0.0F, 0.0F))
{
	m_rotationList.clear();
	m_meshRenderers.clear();
	if (skeletonData == nullptr)
		m_skeleton = nullptr;
	else
		m_skeleton = spSkeleton_create(skeletonData);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DImplementation::Update(float deltaSecond)
{
	spSkeleton_update(m_skeleton, deltaSecond);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

NTBVertex3D_PCT* Skeleton2DImplementation::GetBoneData()
{
	
	for (int i = 0; i < m_skeleton->bonesCount; i++)
	{
		float x, y;
		x = m_skeleton->bones[i]->x;
		y = m_skeleton->bones[i]->y;
		Vector3 fp(x, y,0.0f);
		float length = 10;
		float rotationDegree = m_skeleton->bones[i]->rotation * RAD2DEG;
		
		Vector3 lp(x + length*cos(rotationDegree), y+ length* sin(rotationDegree),0.0f);
		RGBA white(1.0f, 1.0f, 1.0f, 1.0f);		
	}
	return nullptr;
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DImplementation::DebugSkeleton()
{
	ConsolePrintf("------------------------------------------\n");
	for (int boneIndex = 0; boneIndex < m_skeleton->bonesCount; boneIndex++)
	{
		float x, y;
		spBone* currentBone = m_skeleton->bones[boneIndex];
		spBoneData* currentBoneData = currentBone->data;
		spBoneData* parentBoneData = currentBoneData->parent;
		std::string currentBoneName = currentBoneData->name;
		std::string parentBoneName = "No Parent.";
		if (parentBoneData != nullptr)
		{
			parentBoneName = parentBoneData->name;
		}
		x = m_skeleton->bones[boneIndex]->worldX;
		y = m_skeleton->bones[boneIndex]->worldY;
		
		ConsolePrintf("Bone: %s , Parent: %s , %3.2f , %3.2f\n",currentBoneName.c_str(),parentBoneName.c_str(),x,y);
		
		//Vector3 fp(x, y, 0.0f);
		//float length = 10;
		//float rotationDegree = m_skeleton->bones[i]->rotation * RAD2DEG;
		//
		//Vector3 lp(x + length*cos(rotationDegree), y + length* sin(rotationDegree), 0.0f);
		//RGBA white(1.0f, 1.0f, 1.0f, 1.0f);
	}
	ConsolePrintf("------------------------------------------\n");
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DImplementation::DebugDrawSkeletonBone(OpenGLRenderer* renderer)
{
	RGBA purple(1.0f, 0.0f, 1.0f, 1.0f);
	RGBA green(0.0f, 1.0f, 0.0f, 1.0f);
	for (int boneIndex = 0; boneIndex < m_skeleton->bonesCount; boneIndex++)
	{
		spBone* currentBone = m_skeleton->bones[boneIndex];
		spBone* parentBone = currentBone->parent;
		Vector3 offset = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 fp = Vector3(currentBone->worldX, currentBone->worldY, 0.0f)*scale;
		renderer->DrawDisc(Vector2(currentBone->worldX*scale + offset.x, currentBone->worldY*scale + offset.y), 2.0f, green);
		if (parentBone!=nullptr)
		{	
			Vector3 lp = Vector3(parentBone->worldX, parentBone->worldY, 0.0f)*scale;
			renderer->DrawLineSegment(fp, lp, purple, 0);
		}
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DImplementation::DebugDrawRectSlot(OpenGLRenderer* renderer)
{
	float worldVerts[8];
	std::vector<Vector2> slotPolygon;
	std::vector<Vector2> uvs;
	Vector2 offset = Vector2(800.0f, 300.0f);
	RGBA yellow(1.0f, 1.0f, 0.0f, 1.0f);
	RGBA white(1.0f, 1.0f, 1.0f, 1.0f);
	Texture* texture = nullptr;
	for (int slotIndex = 0; slotIndex < m_skeleton->slotsCount; slotIndex++)
	{
		slotPolygon.clear();
		uvs.clear();
		spSlot* currentSlot = m_skeleton->slots[slotIndex];
		spAttachment* currentAttachment = currentSlot->attachment;
		if (currentAttachment==nullptr)
		{
			continue;
		}
		if (currentAttachment->type == SP_ATTACHMENT_REGION)
		{
			spRegionAttachment* regionAttachment = (spRegionAttachment*)currentAttachment;		
			spRegionAttachment_computeWorldVertices(regionAttachment, currentSlot->bone, worldVerts);
			
			for (int worldVertsIndex = 0; worldVertsIndex < 8; worldVertsIndex+=2)
			{
				float x = worldVerts[worldVertsIndex];
				float y = worldVerts[worldVertsIndex+1];
				float u = regionAttachment->uvs[worldVertsIndex];
				float v = regionAttachment->uvs[worldVertsIndex+1];
				slotPolygon.push_back(Vector2(x, y)*scale + offset);
				uvs.push_back(Vector2(u, v));
			}
			spAtlasRegion* currentAtlasRegion = (spAtlasRegion*)(regionAttachment->rendererObject);
			spAtlasPage* currentAtlasPage = currentAtlasRegion->page;
			texture = (Texture*)currentAtlasPage->rendererObject;
			//texture = Texture::CreateOrGetTexture("Data/Spine2D/TestSpineBoy/spineboy.png");
		}
		renderer->DrawTexturedQuad(*texture, slotPolygon, uvs, white);
		
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DImplementation::UpdateVerts()
{
	if (skeletonRenderer == nullptr)
	{
		OneTextureInitMeshRenderer();
	}
	m_skeletonBox = (AABB2D(Vector2(0.0f, 0.0f), 0.0F, 0.0F));
	float worldVerts[WORLD_VERTS_SIZE];
	std::vector <NTBVertex3D_PCT> verts;
	std::vector<Vector2> uvs;
	RGBA yellow(1.0f, 1.0f, 0.0f, 1.0f);
	RGBA white(1.0f, 1.0f, 1.0f, 1.0f);
	Texture* texture = nullptr;

	for (int slotIndex = 0; slotIndex < m_skeleton->slotsCount; slotIndex++)
	{
		uvs.clear();
		spSlot* currentSlot = m_skeleton->slots[slotIndex];
		spAttachment* currentAttachment = currentSlot->attachment;
		if (currentAttachment == nullptr)
		{
			continue;
		}
		switch (currentAttachment->type)
		{
		case SP_ATTACHMENT_REGION:
		{
			spRegionAttachment* regionAttachment = (spRegionAttachment*)currentAttachment;
			spRegionAttachment_computeWorldVertices(regionAttachment, currentSlot->bone, worldVerts);
			
			for (int worldVertsIndex = 0; worldVertsIndex < 8; worldVertsIndex += 2)
			{
				float x = worldVerts[worldVertsIndex];
				float y = worldVerts[worldVertsIndex + 1];
				float u = regionAttachment->uvs[worldVertsIndex];
				float v = regionAttachment->uvs[worldVertsIndex + 1];
				uvs.push_back(Vector2(u, v));
				//Vector3 position(x+x*m_scaleSize, y+y*m_scaleSize, 0.0f);
				//Vector3 position(m_position.x + x*m_scaleSize, m_position.y + y*m_scaleSize, 0.0f);
				//Vector3 position(m_position.x + x*m_scaleSize, m_position.y + y*m_scaleSize, 0.0f);
				Vector3 position(x, y, 0.0f);
				Vector2 texCo(u, v);
				Vector3 zero(0.0f, 0.0f, 0.0f);
				NTBVertex3D_PCT currentVert(position, texCo, zero, zero, zero, white);
				verts.push_back(currentVert);
				if (x<m_skeletonBox.mins.x || m_skeletonBox.mins.x == 0.0f)
				{
					m_skeletonBox.mins.x = x;
				}
				if (x>m_skeletonBox.maxs.x || m_skeletonBox.maxs.x == 0.0f)
				{
					m_skeletonBox.maxs.x = x;
				}
				if (y < m_skeletonBox.mins.y || m_skeletonBox.mins.y == 0.0f)
				{
					m_skeletonBox.mins.y = y;
				}
				if (y > m_skeletonBox.maxs.y || m_skeletonBox.maxs.y == 0.0f)
				{
					m_skeletonBox.maxs.y = y;
				}
			}
			break;
		}
		case SP_ATTACHMENT_MESH:
		{
			spMeshAttachment* meshAttachment = (spMeshAttachment*)currentAttachment;
			spMeshAttachment_computeWorldVertices(meshAttachment, currentSlot, worldVerts);

			for (int worldVertsIndex = 0; worldVertsIndex < meshAttachment->verticesCount/2; worldVertsIndex+=2)
			{
				float x = worldVerts[worldVertsIndex];
				float y = worldVerts[worldVertsIndex + 1];
				float u = meshAttachment->uvs[worldVertsIndex];
				float v = meshAttachment->uvs[worldVertsIndex + 1];
				uvs.push_back(Vector2(u, v));
				Vector3 position(x, y, 0.0f);
				Vector2 texCo(u, v);
				Vector3 zero(0.0f, 0.0f, 0.0f);
				NTBVertex3D_PCT currentVert(position, texCo, zero, zero, zero, white);
				verts.push_back(currentVert);
			}
			break;
		}
		default:
			break;
		}
		
		skeletonRenderer->m_meshRenderers[slotIndex]->m_mesh.UpdateVBO(verts.data(), sizeof(NTBVertex3D_PCT)*verts.size());
	}
	//NTBVertex3D_PCT* passOutVerts = new NTBVertex3D_PCT[verts.size()];
	//memcpy(passOutVerts, verts.data(), verts.size()*sizeof(NTBVertex3D_PCT));
	//testRenderer->UpdateMeshRenderer(verts.data(), verts.size());

	return;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DImplementation::OneTextureInitMeshRenderer()
{
	spSlot* currentSlot = m_skeleton->slots[1];
	spAttachment* currentAttachment = currentSlot->attachment;
	spRegionAttachment* regionAttachment = (spRegionAttachment*)currentAttachment;
	spAtlasRegion* currentAtlasRegion = (spAtlasRegion*)(regionAttachment->rendererObject);
	spAtlasPage* currentAtlasPage = currentAtlasRegion->page;
	Texture* currentTexture = (Texture*)currentAtlasPage->rendererObject;
	skeletonRenderer = new SkeletonRenderer(currentTexture);
	skeletonRenderer->Init(m_skeleton->slotsCount);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DImplementation::DrawRectSlot(const Matrix4x4& transformMatrix)
{
	skeletonRenderer->DrawSkeleton(transformMatrix);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DImplementation::FlipSkeletonX(bool isFlip)
{
	m_skeleton->flipX = isFlip;
}

void Skeleton2DImplementation::FlipSkeletonY(bool isFlip)
{
	m_skeleton->flipY= isFlip;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DImplementation::SetBoneRotation(const std::string& targetName,float rotationDegree)
{
	spBone* targetBone;
	for (int i = 0; i < m_skeleton->bonesCount;i++)
	{
		targetBone = m_skeleton->bones[i];
		std::string currentBoneName = targetBone->data->name;
		if (targetName == currentBoneName)
		{
			break;
		}
	}
	m_rotationList.push_back(std::pair<spBone*,float>(targetBone, rotationDegree));
}

void Skeleton2DImplementation::UpdateBoneRotation()
{
	for (std::vector<std::pair<spBone*, float>>::iterator rotationIter = m_rotationList.begin(); rotationIter != m_rotationList.end();++rotationIter)
	{
		spBone* currentBone = rotationIter->first;
		currentBone->rotation = rotationIter->second;
	}
	m_rotationList.clear();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vector2 Skeleton2DImplementation::GetBonePositionByName(const std::string& boneName)
{
	spBone* currentBone = spSkeleton_findBone(m_skeleton, boneName.c_str());
	if (currentBone != nullptr)
		return Vector2(currentBone->worldX, currentBone->worldY);
	else
		return Vector2(0.0f, 0.0f);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vector2 Skeleton2DImplementation::GetSlotPositionByName(const std::string& slotName)
{
	spSlot* currentSlot = spSkeleton_findSlot(m_skeleton, slotName.c_str());
	if (currentSlot != nullptr)
		return Vector2(currentSlot->bone->worldX, currentSlot->bone->worldY);
	else
		return Vector2(0.0f, 0.0f);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DImplementation::SetPosition(const Vector2& newPosition)
{
	//m_position = newPosition;
	m_skeleton->x = newPosition.x;
	m_skeleton->y = newPosition.y;
	//SetBonePositionByName(newPosition, "torso");
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2DImplementation::SetBonePositionByName(const Vector2& newPosition, const std::string& boneName)
{

	spBone* currentBone = spSkeleton_findBone(m_skeleton, boneName.c_str());
	if (currentBone != nullptr)
	{
		currentBone->x = newPosition.x;
		currentBone->y = newPosition.y;
	}
	else
		return;
}

void Skeleton2DImplementation::SetScaleSize(float scale)
{
	m_skeleton->root->data->scaleX = scale;
	m_skeleton->root->data->scaleY = scale;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

AABB2D Skeleton2DImplementation::GetSkeletonBox()
{
	return m_skeletonBox;
}

///----------------------------------------------------------
///
///----------------------------------------------------------


///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2D::Skeleton2D(Skeleton2DData* skeletonData)
	:m_implementation(nullptr)
{
	m_activeAnimations.clear();
	m_implementation = new Skeleton2DImplementation((spSkeletonData*)skeletonData->GetSkeleton2DData());
	m_skeletonData = skeletonData;
}
///----------------------------------------------------------
///
///----------------------------------------------------------


///----------------------------------------------------------
///
///----------------------------------------------------------

Skeleton2D::~Skeleton2D()
{

}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::Update(float deltaSecond)
{
	//SetScaleSize(0.5f);
	m_implementation->Update(deltaSecond);	
	UpdateAnimations(deltaSecond);	
	UpdateBoneRotation();
	spSkeleton_updateWorldTransform(m_implementation->GetSkeleton());	
	m_implementation->UpdateVerts();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::PlayAnimation(const std::string& animationName, bool isBaseAnimation, bool isLooping, float blendingchangingDuration, float changeScale, float expectBlending, float startBlending)
{
	for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
	{
		if (m_activeAnimations[i]->GetName() == animationName)
		{
			return;
		}
	}
	Skeleton2DAnimation* newAnim = new Skeleton2DAnimation(animationName, m_skeletonData, isBaseAnimation,isLooping,blendingchangingDuration,changeScale,expectBlending,startBlending);
	m_activeAnimations.push_back(newAnim);
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::DebugDrawSkeletonBone(OpenGLRenderer* renderer)
{
	m_implementation->DebugDrawSkeletonBone(renderer);

}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::DebugDrawRectSlot(OpenGLRenderer* renderer)
{
	m_implementation->DebugDrawRectSlot(renderer);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::DrawSlot(const Matrix4x4& transformMatrix)
{
	m_implementation->DrawRectSlot(transformMatrix);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::SetScaleSize(float scale)
{
	m_implementation->SetScaleSize(scale);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::SetPosition(const Vector2& newPosition)
{
	m_implementation->SetPosition(newPosition);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

const Vector2& Skeleton2D::GetPosition()
{
	return m_implementation->GetPosition();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::UpdateAnimations(float deltaSecond)
{
	if (m_activeAnimations.size() == 0)
	{
		//PlayAnimation("idle", true, true);
		//m_activeAnimations[m_activeAnimations.size() - 1]->SetStartBlending(0.8f);
	}
	ProcessUpdatedAnimations();
	DeleteCompletedAnimation();
	
	for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
	{
		if (i == 0)
		{
			m_activeAnimations[i]->BaseUpdate(deltaSecond, m_implementation->GetSkeleton());
			continue;
		}
		m_activeAnimations[i]->MixUpdate(deltaSecond, m_implementation->GetSkeleton());
	}
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::ProcessUpdatedAnimations()
{
	for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
	{
		if (i!=0 && m_activeAnimations[i]->IsFinishBlending() && m_activeAnimations[i]->GetIsBaseAnimation())
		{
			delete m_activeAnimations[0];
			m_activeAnimations[0] = m_activeAnimations[i]; 
			m_activeAnimations.erase(m_activeAnimations.begin() + i);
			break;
		}
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::DeleteCompletedAnimation()
{
	for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
	{
		if (!m_activeAnimations[i]->GetIsLooping() && m_activeAnimations[i]->GetIsComplete())
		{
			m_activeAnimations.erase(m_activeAnimations.begin() + i);
			continue;
		}
	}
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::FlipSkeletonX(bool isFlip)
{
	m_implementation->FlipSkeletonX(isFlip);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::FlipSkeletonY(bool isFlip)
{
	m_implementation->FlipSkeletonY(isFlip);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::SetBoneRotation(const std::string& targetBoneName, float rotationDegree)
{
	m_implementation->SetBoneRotation(targetBoneName, rotationDegree);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::UpdateBoneRotation()
{
	m_implementation->UpdateBoneRotation();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vector2 Skeleton2D::GetBonePositionByName(const std::string& boneName)
{
	return m_implementation->GetBonePositionByName(boneName);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::ResetAnimations()
{
	m_activeAnimations.clear();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

Vector2 Skeleton2D::GetSlotPositionByName(const std::string& slotName)
{
	return m_implementation->GetSlotPositionByName(slotName);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void Skeleton2D::SetBonePositionByName(const Vector2& newPosition, const std::string& boneName)
{
	m_implementation->SetBonePositionByName(newPosition, boneName);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

AABB2D Skeleton2D::GetSkeletonBox()
{
	return m_implementation->GetSkeletonBox();
}

///----------------------------------------------------------
///
///----------------------------------------------------------


///----------------------------------------------------------
///
///----------------------------------------------------------


