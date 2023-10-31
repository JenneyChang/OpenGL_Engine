#include "MeshNode.h"


//-----------------------------------------------------------------------------------
//	CONSTRUCTOR
//-----------------------------------------------------------------------------------

MeshNode::MeshNode()
	: DLink(), poMesh(nullptr)
{ }

MeshNode::~MeshNode()
{
	if (poMesh)
	{
		delete this->poMesh;
	}
}


//-----------------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------------

void MeshNode::Set(Mesh::Name name, Mesh* pMesh)
{
	assert(pMesh);

	this->poMesh = pMesh;
	this->poMesh->SetName(name);
}

Mesh* MeshNode::GetMesh()
{
	assert(this->poMesh);
	return this->poMesh;
}


//-----------------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//-----------------------------------------------------------------------------------

bool MeshNode::Compare(Node* pNode)
{
	assert(pNode);
	MeshNode* pTemp = (MeshNode*)pNode;

	assert(pTemp->poMesh);
	assert(this->poMesh);

	if (this->poMesh->GetName() == pTemp->poMesh->GetName())
	{
		return true;
	}

	return false;
}