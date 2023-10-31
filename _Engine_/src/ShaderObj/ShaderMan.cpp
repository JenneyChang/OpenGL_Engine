#include "ShaderMan.h"
#include "ShaderGraphics.h"


ShaderMan* ShaderMan::poInstance = nullptr;

//---------------------------------------------------------------------------
//	PRIVATE CONSTRUCTOR
//---------------------------------------------------------------------------

ShaderMan::ShaderMan(int toReserve, int toGrow)
	: Manager(toGrow)
{
	//prefill reserve
	this->FillReserve(toReserve);

	//create & setup comparison node
	ShaderObj* pNullShader = new ShaderGraphics(ShaderObj::Name::NULL_SHADER, "null");
	assert(pNullShader);

	this->poComparison = new ShaderNode();
	assert(this->poComparison);

	this->poComparison->Set(pNullShader);
}

ShaderMan::~ShaderMan()
{ }


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void ShaderMan::Create(int toReserve, int toGrow)
{
	if (ShaderMan::poInstance == nullptr)
	{
		ShaderMan::poInstance = new ShaderMan(toReserve, toGrow);
		assert(ShaderMan::poInstance != nullptr);
	}
}

void ShaderMan::Destroy()
{
	ShaderMan* pManager = ShaderMan::prInstance();

	//delete active & reserve lists 
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		ShaderNode* temp = (ShaderNode*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	it = pManager->baseGetReserveIterator();
	pNode = it->First();
	while (!it->IsDone())
	{
		ShaderNode* temp = (ShaderNode*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	//delete comparison node
	delete pManager->poComparison;
	pManager->poComparison = nullptr;

	//delete instance
	delete ShaderMan::poInstance;
	ShaderMan::poInstance = nullptr;
}

ShaderObj* ShaderMan::Add(ShaderObj* shaderobj)
{
	assert(shaderobj);
	ShaderMan* pManager = ShaderMan::prInstance();

	//grab node from pool
	ShaderNode* pNode = (ShaderNode*)pManager->baseAddToFront();
	assert(pNode);

	//set data
	pNode->Set(shaderobj);

	return pNode->Get();
}

ShaderObj* ShaderMan::Find(ShaderObj::Name _type)
{
	ShaderMan* pManager = ShaderMan::prInstance();

	pManager->poComparison->Get()->Set(_type);
	ShaderNode* pData = (ShaderNode*)pManager->baseFind(pManager->poComparison);

	return pData->Get();
}

void ShaderMan::Remove(ShaderObj::Name name)
{
	ShaderMan* pManager = ShaderMan::prInstance();

	pManager->poComparison->Get()->Set(name);
	ShaderNode* pData = (ShaderNode*)pManager->baseFind(pManager->poComparison);
	assert(pData);

	pManager->baseRemove(pData);
}

void ShaderMan::Print()
{
	ShaderMan* pManager = ShaderMan::prInstance();
	
	Trace::out("\n--------Shader Manager--------------\n");
	pManager->basePrint();
}


//---------------------------------------------------------------------------
//	OVERRIDDEN METHOD
//---------------------------------------------------------------------------

Node* ShaderMan::derivedCreateNode()
{
	DLink* pNode = new ShaderNode();
	assert(pNode != nullptr);

	return pNode;
}


//---------------------------------------------------------------------------
//	PRIVATE METHOD
//---------------------------------------------------------------------------

ShaderMan* ShaderMan::prInstance()
{
	assert(ShaderMan::poInstance != nullptr);
	return ShaderMan::poInstance;
}
