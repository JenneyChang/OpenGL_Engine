#include "GameObj3D.h"

using namespace Azul;

//-----------------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------------

GameObj3D::GameObj3D(GraphicsObj3D* graphicsobj)
	: GameObj(graphicsobj), pBSphere(nullptr)
{ }

GameObj3D::~GameObj3D()
{ }


//-----------------------------------------------------------------------------------
//	PRIVATE METHODS
//-----------------------------------------------------------------------------------

void GameObj3D::baseUpdateBSphere()
{
	BoundingSphere* sphereRef = this->poGraphicsObj->GetMesh()->GetSphere();
	assert(sphereRef);

	//get curr sphere
	BoundingSphere* currSphere = ((GraphicsObj3D*)this->poGraphicsObj)->GetSphere();
	assert(currSphere);

	//update center w/ uniform scaling
	Vec3 radius(1.0f, 0.0f, 0.0f);
	Vec3 A = sphereRef->center;
	Vec3 B = A + radius;

	Vec3 A_out;
	A_out = A * (*this->poWorld);

	Vec3 B_out;
	B_out = B * (*this->poWorld);

	currSphere->radius = (B_out - A_out).len() * sphereRef->radius;
	currSphere->center = A_out;
}