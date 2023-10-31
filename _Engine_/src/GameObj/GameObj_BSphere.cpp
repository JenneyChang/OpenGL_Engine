#include "GameObj_BSphere.h"
#include "Camera3DMan.h"
#include "GraphicsObj_Wireframe.h"

using namespace Azul;

//--------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------

GameObj_BSphere::GameObj_BSphere(GraphicsObj3D* graphicsobj)
	: GameObj_Static(graphicsobj), pGameObjRef(nullptr), poScale(new Vec3()), 
	  poTrans(new Vec3())
{
	assert(graphicsobj);
	assert(this->poScale);
	assert(this->poTrans);
}

GameObj_BSphere::~GameObj_BSphere()
{
	delete this->poScale;
	delete this->poTrans;
}


//--------------------------------------------------------------------------
//	PUBLIC METHODS
//--------------------------------------------------------------------------

void GameObj_BSphere::Update(AnimTime t)
{
	//set values from ref
	this->prUpdateBSphereRef(t);

	//update world mat
	this->prUpdate(t);

	//update graphics obj
	this->poGraphicsObj->SetWorldMat(*this->poWorld);
}

void GameObj_BSphere::SetBSphereRef(GameObj* gameobj)
{
	assert(gameobj);
	this->pGameObjRef = gameobj;
}


//--------------------------------------------------------------------------
//	PRIVATE METHODS
//--------------------------------------------------------------------------

void GameObj_BSphere::prUpdate(AnimTime t)
{
	//update world mat
	Mat4 Scale(Mat4::Scale::XYZ, *this->poScale);
	Mat4 Trans(Mat4::Trans::XYZ, *this->poTrans);
	*this->poWorld = Scale * Trans;

	//flip color based on camera (culling)
	//Camera3D* cam = Camera3DMan::Find(Camera::Name::FRUSTRUM);	//create default god cam?
	Camera3D* cam = Camera3DMan::GetCurrCam();
	BoundingSphere* sphere = ((GraphicsObj3D*)this->poGraphicsObj)->GetSphere();

	//TODO
	GraphicsObj_Wireframe* pWireframe = (GraphicsObj_Wireframe*)this->poGraphicsObj;
	if (cam->CullTest(*sphere) == Camera3D::CullResult::OUTSIDE)
	{
		pWireframe->SetColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		pWireframe->SetColor(Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	}
}

void GameObj_BSphere::prUpdateBSphereRef(AnimTime t)
{
	//call update just in case
	this->pGameObjRef->Update(t);

	//set center & scale of bounding box base on ref obj world coords
	GraphicsObj3D* pGraphicsObj = (GraphicsObj3D*)this->pGameObjRef->GetGraphicsObj();
	BoundingSphere* sphereRef = pGraphicsObj->GetSphere();
	this->poScale->set(sphereRef->radius, sphereRef->radius, sphereRef->radius);
	this->poTrans->set(sphereRef->center);

	BoundingSphere* sphereCurr = ((GraphicsObj3D*)this->poGraphicsObj)->GetSphere();
	*sphereCurr = *sphereRef;
}