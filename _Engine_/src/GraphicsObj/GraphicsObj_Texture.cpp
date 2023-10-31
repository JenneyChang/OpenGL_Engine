#include "GraphicsObj_Texture.h"
#include "Camera3DMan.h"

using namespace Azul;

//-----------------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------------

GraphicsObj_Texture::GraphicsObj_Texture(Mesh* mesh, ShaderObj* shaderobj, Texture* texture)
	: GraphicsObj3D(mesh, shaderobj), pTexture(texture)
{
	assert(mesh);
	assert(shaderobj);
	assert(texture);
}

GraphicsObj_Texture::~GraphicsObj_Texture()
{ }


//-----------------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//-----------------------------------------------------------------------------------

void GraphicsObj_Texture::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	//bind texture
	glBindTexture(GL_TEXTURE_2D, this->pTexture->GetID());

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphicsObj_Texture::SetGPUData()
{
	//get 3D camera
	Camera* cam = Camera3DMan::GetCurrCam();
	assert(cam);

	//set vao
	glBindVertexArray(this->pMesh->GetVAO());

	//set shader
	this->pShaderObj->SetActive();

	//set uniforms
	Mat4 world = this->GetWorldMat();
	Mat4 view = cam->GetViewMatrix();
	Mat4 proj = cam->GetProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);
}

void GraphicsObj_Texture::Draw()
{
	glDrawElements(GL_TRIANGLES, (3 * this->pMesh->GetTris()), GL_UNSIGNED_INT, 0);
}

void GraphicsObj_Texture::ResetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

