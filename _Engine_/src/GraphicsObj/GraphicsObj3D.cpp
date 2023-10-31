#include "GraphicsObj3D.h"

using namespace Azul;

//--------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------

GraphicsObj3D::GraphicsObj3D(Mesh* mesh, const ShaderObj* shaderobj)
	: GraphicsObj(mesh, shaderobj)
{
	assert(mesh);
	assert(shaderobj);

	this->poCurrSphere = new BoundingSphere();
	assert(this->poCurrSphere);
}

GraphicsObj3D::~GraphicsObj3D()
{ 
	delete this->poCurrSphere;
}

//--------------------------------------------------------------------------
//	PUBLIC METHODS
//--------------------------------------------------------------------------

BoundingSphere* GraphicsObj3D::GetSphere()
{
	return this->poCurrSphere;
}

void GraphicsObj3D::Render()
{
	this->SetState();
	this->SetGPUData();
	this->Draw();
	this->ResetState();
}