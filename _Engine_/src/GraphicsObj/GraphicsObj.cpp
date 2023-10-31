#include "GraphicsObj.h"

using namespace Azul;

//-----------------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------------

GraphicsObj::GraphicsObj(Mesh* mesh, const ShaderObj* shaderobj)
	: Material(), pMesh(mesh), poWorld(new Mat4(Mat4::Special::Identity)),
	  pShaderObj(shaderobj)/*, poCurrSphere(new BoundingSphere())*/
{
	//check incoming
	/*assert(mesh);
	assert(shaderobj);*/

	//check news
	assert(this->poWorld);
	//assert(this->poCurrSphere);
}

GraphicsObj::~GraphicsObj()
{
	delete this->poWorld;
	//delete this->poCurrSphere;
}

//-----------------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------------

void GraphicsObj::SetWorldMat(Azul::Mat4& world)
{
	*this->poWorld = world;
}

Azul::Mat4& GraphicsObj::GetWorldMat()
{
	return *this->poWorld;
}

Mesh* GraphicsObj::GetMesh() const
{
	return this->pMesh;
}

//BoundingSphere* GraphicsObj::GetSphere()
//{
//	return this->poCurrSphere;
//}

