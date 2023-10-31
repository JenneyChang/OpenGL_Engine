#include "MeshNodeMan.h"
#include "MeshNull.h"

MeshNodeMan* MeshNodeMan::poInstance = nullptr;

//-----------------------------------------------------------------------------------
//	PRIVATE CONSTRUCTOR
//-----------------------------------------------------------------------------------

MeshNodeMan::MeshNodeMan(int numReserve, int numGrow)
	: Manager(numGrow)
{
	//load reserve list
	this->FillReserve(numReserve);

	//setup comparison node
	Mesh* pMesh = new MeshNull();
	assert(pMesh);

	this->poComparison = new MeshNode();
	assert(this->poComparison);

	this->poComparison->Set(Mesh::Name::NULL_MESH, pMesh);
}

MeshNodeMan::~MeshNodeMan()
{ }


//-----------------------------------------------------------------------------------
//	STATIC METHODS
//-----------------------------------------------------------------------------------

void MeshNodeMan::Create(int toReserve, int toGrow)
{
	if (MeshNodeMan::poInstance == nullptr)
	{
		MeshNodeMan::poInstance = new MeshNodeMan(toReserve, toGrow);
		assert(MeshNodeMan::poInstance);
	}
}

void MeshNodeMan::Destroy()
{
	MeshNodeMan* pManager = MeshNodeMan::prInstance();
	assert(pManager);

	//delete comparison node
	delete pManager->poComparison;
	pManager->poComparison = nullptr;

	//delete active & reserve
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		MeshNode* temp = (MeshNode*)it->Curr();
		pNode = it->Next();
		
		delete temp;
	}

	it = pManager->baseGetReserveIterator();
	pNode = it->First();
	while (!it->IsDone())
	{
		MeshNode* temp = (MeshNode*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	//instance
	delete MeshNodeMan::poInstance;
	MeshNodeMan::poInstance = nullptr;
}

MeshNode* MeshNodeMan::Add(Mesh::Name name, Mesh* pMesh)
{
	assert(pMesh);
	MeshNodeMan* pManager = MeshNodeMan::prInstance();

	//grab node from pool
	MeshNode* pNode = (MeshNode*)pManager->baseAddToFront();
	assert(pNode);

	pNode->Set(name, pMesh);

	return pNode;
}

Mesh* MeshNodeMan::Find(Mesh::Name name)
{
	MeshNodeMan* pManager = MeshNodeMan::prInstance();
	pManager->poComparison->GetMesh()->SetName(name);

	MeshNode* pNode = (MeshNode*)pManager->baseFind(pManager->poComparison);
	assert(pNode);

	return pNode->GetMesh();
}

void MeshNodeMan::Remove(MeshNode* pNode)
{
	assert(pNode);
	MeshNodeMan* pManager = MeshNodeMan::prInstance();

	pManager->baseRemove(pNode);
}

void MeshNodeMan::Remove(Mesh::Name name)
{
	MeshNodeMan* pManager = MeshNodeMan::prInstance();
	assert(pManager);

	pManager->poComparison->GetMesh()->SetName(name);
	MeshNode* pNode = (MeshNode*)pManager->baseFind(pManager->poComparison);
	assert(pNode);

	pManager->baseRemove(pNode);
}

void MeshNodeMan::Print()
{
	MeshNodeMan* pManager = MeshNodeMan::prInstance();

	Trace::out("\n----------MeshNodeMan Manager----------\n");
	pManager->basePrint();
}


//-----------------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//-----------------------------------------------------------------------------------

Node* MeshNodeMan::derivedCreateNode()
{
	DLink* pNode = new MeshNode();
	assert(pNode);

	return pNode;
}


//-----------------------------------------------------------------------------------
//	PRIVATE METHODS
//-----------------------------------------------------------------------------------

MeshNodeMan* MeshNodeMan::prInstance()
{
	assert(MeshNodeMan::poInstance != nullptr);
	return MeshNodeMan::poInstance;
}