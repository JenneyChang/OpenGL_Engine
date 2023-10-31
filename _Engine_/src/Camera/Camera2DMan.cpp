#include "Camera2DMan.h"

using namespace Azul;

Camera2DMan* Camera2DMan::poInstance = nullptr;

//--------------------------------------------------------------------------
//	PRIVATE CONSTRUCTOR
//--------------------------------------------------------------------------

Camera2DMan::Camera2DMan(int toReserve, int toGrow)
	: Manager(toGrow)
{
	//prefill reserve pool
	this->FillReserve(toReserve);

	//create comparison node
	this->poComparison = new Camera2D();
	assert(this->poComparison);

	this->pCurrCam = nullptr;
}

Camera2DMan::~Camera2DMan()
{ }


//--------------------------------------------------------------------------
//	PUBLIC STATIC METHODS
//--------------------------------------------------------------------------

void Camera2DMan::Create(int toReserve, int toGrow)
{
	if (Camera2DMan::poInstance == nullptr)
	{
		Camera2DMan::poInstance = new Camera2DMan(toReserve, toGrow);
		assert(Camera2DMan::poInstance != nullptr);
	}
}

void Camera2DMan::Destroy()
{
	Camera2DMan* pManager = Camera2DMan::prInstance();
	assert(pManager);

	//comparison node
	delete pManager->poComparison;
	pManager->poComparison = nullptr;

	//active list
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		Camera2D* temp = (Camera2D*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	//reserve list
	it = pManager->baseGetReserveIterator();
	pNode = it->First();
	while (!it->IsDone())
	{
		Camera2D* temp = (Camera2D*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	//instance
	delete Camera2DMan::poInstance;
	Camera2DMan::poInstance = nullptr;
}

void Camera2DMan::SetCurrCam(Camera2D* cam)
{
	assert(cam);

	Camera2DMan* pManager = Camera2DMan::prInstance();
	pManager->pCurrCam = cam;
}

void Camera2DMan::SetCurrCam(Camera::Name _name)
{
	Camera2DMan* pManager = Camera2DMan::prInstance();

	Camera2D* pNode = Camera2DMan::Find(_name);
	assert(pNode);

	pManager->pCurrCam = pNode;
}

Camera2D* Camera2DMan::GetCurrCam()
{
	Camera2DMan* pManager = Camera2DMan::prInstance();
	assert(pManager->pCurrCam);

	return pManager->pCurrCam;
}

Camera2D* Camera2DMan::Add(Camera::Name _name)
{
	Camera2DMan* pManager = Camera2DMan::prInstance();
	
	//grab node from pool
	Camera2D* pNode = (Camera2D*)pManager->baseAddToFront();
	assert(pNode);

	pNode->SetName(_name);

	return pNode;
}

Camera2D* Camera2DMan::Find(Camera::Name _name)
{
	Camera2DMan* pManager = Camera2DMan::prInstance();
	pManager->poComparison->SetName(_name);

	Camera2D* pNode = (Camera2D*)pManager->baseFind(pManager->poComparison);
	assert(pNode);

	return pNode;
}

void Camera2DMan::Remove(Camera::Name _name)
{
	Camera2DMan* pManager = Camera2DMan::prInstance();
	
	Camera2D* pNode = Camera2DMan::Find(_name);
	assert(pNode);

	pManager->baseRemove(pNode);
}

void Camera2DMan::Print()
{
	Camera2DMan* pManager = Camera2DMan::prInstance();

	Trace::out("\n------------Camera2D Manager------------\n");
	pManager->basePrint();
}


//--------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//--------------------------------------------------------------------------

Node* Camera2DMan::derivedCreateNode()
{
	DLink* pNode = new Camera2D();
	assert(pNode);

	return pNode;
}

//--------------------------------------------------------------------------
//	PRIVATE METHODS
//--------------------------------------------------------------------------

Camera2DMan* Camera2DMan::prInstance()
{
	assert(Camera2DMan::poInstance);
	return Camera2DMan::poInstance;
}