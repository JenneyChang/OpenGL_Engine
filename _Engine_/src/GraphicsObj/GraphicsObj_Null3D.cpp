#include "GraphicsObj_Null3D.h"


//------------------------------------------------------------------------
//	CONSTRUCTION
//------------------------------------------------------------------------

GraphicsObj_Null3D::GraphicsObj_Null3D(Mesh* mesh, const ShaderObj* shaderobj)
	: GraphicsObj3D(mesh, shaderobj)
{
	//does nothing
}

GraphicsObj_Null3D::~GraphicsObj_Null3D()
{
	//does nothing
}


//------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//------------------------------------------------------------------------

void GraphicsObj_Null3D::Render()
{
	//does nothing
}