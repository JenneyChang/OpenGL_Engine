#include "Skeleton.h"

#include "TextureMan.h"
#include "ShaderMan.h"
#include "MeshNodeMan.h"
#include "ProtoMesh.h"
#include "GraphicsObj_Null3D.h"
#include "GraphicsObj_Skin.h"
#include "GraphicsObj_Texture.h"
#include "GraphicsObj_Wireframe.h"
#include "GameObj_Rigid.h"
#include "GameObj_Skin.h"
#include "GameObjMan.h"
#include "GameObj_BSphere.h"

#include "PCSNode.h"
#include "PCSTreeForwardIterator.h"
#include "PCSTreeReverseIterator.h"

using namespace Azul;


//-----------------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------------

Skeleton::Skeleton()
	: pOrigList(nullptr), pOrderedList(nullptr), name(Skeleton::Name::UNINITIALIZED), 
	  numJoints(0), pFirstBone(nullptr), poSSBO_HierarchyTable(new SSBO()), hierarchyDepth(-1)
{ 
	assert(this->poSSBO_HierarchyTable);
}

Skeleton::~Skeleton()
{ 
	delete[] this->pOrigList;
	delete[] this->pOrderedList;

	delete this->poSSBO_HierarchyTable;
}


//-----------------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------------

void Skeleton::Set(Skeleton::Name _name)
{
	this->name = _name;
}

void Skeleton::Set(Skeleton::Name _name, hierarchy_proto& hproto)
{
	this->name = _name;
	this->numJoints = hproto.skelSize;

	//original joint list
	this->pOrigList = new SkelData[(unsigned int)numJoints]();
	assert(this->pOrigList);

	for (unsigned int i = 0; i < (unsigned int)numJoints; ++i)
	{
		pOrigList[i].index = hproto.origList[i].nodeIndex;
		pOrigList[i].parentIndex = hproto.origList[i].parentIndex;

		memcpy(pOrigList[i].name, hproto.origList[i].nodeName.c_str(), hproto.origList[i].nodeName.length());
	}

	//ordered joint list
	this->pOrderedList = new SkelData[(unsigned int)numJoints]();
	assert(this->pOrderedList);

	for (unsigned int i = 0; i < (unsigned int)numJoints; ++i)
	{
		pOrderedList[i].index = hproto.orderedList[i].nodeIndex;
		pOrderedList[i].parentIndex = hproto.orderedList[i].parentIndex;

		memcpy(pOrderedList[i].name, hproto.orderedList[i].nodeName.c_str(), hproto.orderedList[i].nodeName.length());
	}

	//hierarchy table
	this->hierarchyDepth = hproto.hierarchyDepth;
	this->poSSBO_HierarchyTable->Set(hproto.tableSize, sizeof(int), hproto.hierarchyTable.data());
}

SSBO* Skeleton::GetSSBOTable()
{
	assert(this->poSSBO_HierarchyTable);
	return this->poSSBO_HierarchyTable;
}

void Skeleton::SetHierarchy(SSBO* pSSBOIn, Mesh* mesh, Vec3 lightPos, Vec4 lightColor, Vec3 scale, Vec3 trans, Quat rot)
{
	assert(pSSBOIn);
	assert(mesh);

	//std::string pivotName = "Pivot_" + GetSkeletonName(this->name);
	//std::string skinName = GetSkeletonName(this->name) + "_Skin";
	//std::string sphereName = skinName + "_BSphere";

	//setup pivot node
	ShaderObj* pNullShader = ShaderMan::Find(ShaderObj::Name::NULL_SHADER);
	ShaderObj* pSkinShader = ShaderMan::Find(ShaderObj::Name::SKIN_TEXTURE);
	ShaderObj* pWireframeShader = ShaderMan::Find(ShaderObj::Name::WIREFRAME);

	Mesh* pNullMesh = MeshNodeMan::Find(Mesh::Name::NULL_MESH);
	assert(pNullShader);
	assert(pSkinShader);
	assert(pWireframeShader);
	assert(pNullMesh);

		GraphicsObj3D* pGraphicsObj = new GraphicsObj_Null3D(pNullMesh, pNullShader);
		GameObj_Rigid* pPivot = new GameObj_Rigid(pGraphicsObj);
		//pPivot->SetName(pivotName.c_str());
		pPivot->SetScale(scale);
		pPivot->SetTrans(trans);
		pPivot->SetRot(rot);
		GameObjMan::Add(pPivot, GameObjMan::GetRoot());

	// Skinned Object
	GraphicsObj_Skin* pGraphicsSkin = new GraphicsObj_Skin(mesh, pSkinShader, ((ProtoMesh*)mesh)->GetTexture(), pPivot, lightColor, lightPos);
	GameObj_Skin* pGameObjSkin = new GameObj_Skin(pGraphicsSkin, this, this->numJoints, pSSBOIn);
	pGraphicsSkin->SetSSBOWorldResult(pGameObjSkin->GetSSBOWorldResult());
	//pGameObjSkin->SetName(skinName.c_str());
	GameObjMan::Add(pGameObjSkin, pPivot);

	// Bounding Volume
	/*pGraphicsObj = new GraphicsObj_Wireframe(mesh, pWireframeShader, Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	GameObj_BSphere* pBSphereObj = new GameObj_BSphere(pGraphicsObj);
	pBSphereObj->SetName(sphereName.c_str());
	pBSphereObj->SetBSphereRef(pPivot);
	GameObjMan::Add(pBSphereObj, pPivot);*/
}

int Skeleton::GetHierarchyDepth()
{
	assert(hierarchyDepth);
	return this->hierarchyDepth;
}


//-----------------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//-----------------------------------------------------------------------------------

void Skeleton::ResetLink()
{
	DLink::ResetLink();

	this->name = Skeleton::Name::UNINITIALIZED;
	this->numJoints = 0;
	this->pFirstBone = nullptr;
}

bool Skeleton::Compare(Node* pNode)
{
	assert(pNode);
	Skeleton* pTemp = (Skeleton*)pNode;

	if (this->name == pTemp->name)
	{
		return true;
	}

	return false;
}
