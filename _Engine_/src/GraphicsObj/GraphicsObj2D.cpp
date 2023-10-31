#include "GraphicsObj2D.h"

using namespace Azul;

//--------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------

GraphicsObj2D::GraphicsObj2D(Mesh* mesh, ShaderObj* shaderobj)
	: GraphicsObj(mesh, shaderobj)
{
	this->poMatrix_uv = new Mat4();
	this->poMatrix_orig = new Mat4();
	assert(poMatrix_uv);
	assert(poMatrix_orig);
}

GraphicsObj2D::~GraphicsObj2D()
{
	delete this->poMatrix_uv;
	delete this->poMatrix_orig;
}

//--------------------------------------------------------------------------
//	PUBLIC METHODS
//--------------------------------------------------------------------------

void GraphicsObj2D::GetPos(float& x, float& y)
{
	x = origPosx;
	y = origPosy;
}
