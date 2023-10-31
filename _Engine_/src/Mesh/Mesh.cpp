#include "Mesh.h"

using namespace Azul;

//-----------------------------------------------------------------------------------
//	CONSTRUCTOR
//-----------------------------------------------------------------------------------

Mesh::Mesh()
	: name(Mesh::Name::UNINITIALIZED), poSphere(new BoundingSphere()), numVerts(0), numTris(0),
	  vao(0), vbo_verts(0), vbo_norms(0), vbo_texcoords(0), vbo_color(0), vbo_index(0),
	  poSSBO_InvBind(new SSBO()), basecolor(new Vec4(1, 1, 1, 1))
{ 
	assert(this->poSphere);
}

Mesh::~Mesh()
{
	delete this->poSphere;
	delete this->poSSBO_InvBind;
	delete this->basecolor;
}


//-----------------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------------

void Mesh::SetName(Mesh::Name _name)
{
	this->name = _name;
}

Mesh::Name Mesh::GetName()
{
	return this->name;
}

int Mesh::GetTris()
{
	return this->numTris;
}

GLuint Mesh::GetVAO()
{
	return this->vao;
}

SSBO* Mesh::GetSSBOInvbind()
{
	assert(this->poSSBO_InvBind);
	return this->poSSBO_InvBind;
}

BoundingSphere* Mesh::GetSphere()
{
	return this->poSphere;
}

Vec4* Mesh::GetBaseColor()
{
	return this->basecolor;
}