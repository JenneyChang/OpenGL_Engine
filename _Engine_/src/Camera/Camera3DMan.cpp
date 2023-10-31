#include "Camera3DMan.h"

using namespace Azul;

Camera3DMan* Camera3DMan::poInstance = nullptr;

//--------------------------------------------------------------------------
//	PRIVATE CONSTRUCTOR
//--------------------------------------------------------------------------

Camera3DMan::Camera3DMan(int toReserve, int toGrow)
	: Manager(toGrow)
{
	//prefill reserve pool
	this->FillReserve(toReserve);

	//create comparison node
	this->poComparison = new Camera3D();
	assert(this->poComparison);

	this->pCurrCam = nullptr;
}

Camera3DMan::~Camera3DMan()
{ }


//--------------------------------------------------------------------------
//	PUBLIC STATIC METHODS
//--------------------------------------------------------------------------

void Camera3DMan::Create(int toReserve, int toGrow)
{
	if (Camera3DMan::poInstance == nullptr)
	{
		Camera3DMan::poInstance = new Camera3DMan(toReserve, toGrow);
		assert(Camera3DMan::poInstance != nullptr);
	}
}

void Camera3DMan::Destroy()
{
	Camera3DMan* pManager = Camera3DMan::prInstance();
	assert(pManager);

	//delete comparison node
	delete pManager->poComparison;
	pManager->poComparison = nullptr;

	//active and reserve list
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		Camera3D* temp = (Camera3D*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	it = pManager->baseGetReserveIterator();
	pNode = it->First();
	while (!it->IsDone())
	{
		Camera3D* temp = (Camera3D*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	//delete instance
	delete Camera3DMan::poInstance;
	Camera3DMan::poInstance = nullptr;
}

void Camera3DMan::SetCurrCam(Camera3D* cam)
{
	assert(cam);

	Camera3DMan* pManager = Camera3DMan::prInstance();
	pManager->pCurrCam = cam;
}

void Camera3DMan::SetCurrCam(Camera::Name _name)
{
	Camera3DMan* pManager = Camera3DMan::prInstance();

	Camera3D* pNode = Camera3DMan::Find(_name);
	assert(pNode);

	pManager->pCurrCam = pNode;
}

Camera3D* Camera3DMan::GetCurrCam()
{
	Camera3DMan* pManager = Camera3DMan::prInstance();
	assert(pManager->pCurrCam);

	return pManager->pCurrCam;
}

Camera3D* Camera3DMan::Add(Camera::Name _name)
{
	Camera3DMan* pManager = Camera3DMan::prInstance();

	//grab node from pool
	Camera3D* pNode = (Camera3D*)pManager->baseAddToFront();
	assert(pNode);

	pNode->SetName(_name);

	return pNode;
}

Camera3D* Camera3DMan::Find(Camera::Name _name)
{
	Camera3DMan* pManager = Camera3DMan::prInstance();
	pManager->poComparison->SetName(_name);

	Camera3D* pNode = (Camera3D*)pManager->baseFind(pManager->poComparison);
	assert(pNode);

	return pNode;
}

void Camera3DMan::Remove(Camera::Name _name)
{
	Camera3DMan* pManager = Camera3DMan::prInstance();

	Camera3D* pNode = Camera3DMan::Find(_name);
	assert(pNode);

	pManager->baseRemove(pNode);
}

void Camera3DMan::Print()
{
	Camera3DMan* pManager = Camera3DMan::prInstance();

	Trace::out("\n------------Camera3D Manager------------\n");
	pManager->basePrint();
}


//--------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//--------------------------------------------------------------------------

Node* Camera3DMan::derivedCreateNode()
{
	DLink* pNode = new Camera3D();
	assert(pNode);

	return pNode;
}


//--------------------------------------------------------------------------
//	PRIVATE METHODS
//--------------------------------------------------------------------------

Camera3DMan* Camera3DMan::prInstance()
{
	assert(Camera3DMan::poInstance);
	return Camera3DMan::poInstance;
}