#include "GraphicsObj_Wireframe.h"
#include "Camera3DMan.h"

//-----------------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------------

GraphicsObj_Wireframe::GraphicsObj_Wireframe( Mesh* mesh, const ShaderObj* shaderobj, const Vec4& wirecolor)
	: GraphicsObj3D(mesh, shaderobj), poWirecolor(new Vec4(wirecolor))
{
	//check incoming
	assert(mesh);
	assert(shaderobj);

	//check new
	assert(this->poWirecolor);
}

GraphicsObj_Wireframe::~GraphicsObj_Wireframe()
{
	//clean up
	delete this->poWirecolor;
}


//-----------------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------------

void GraphicsObj_Wireframe::SetColor(const Vec4& color)
{
	this->poWirecolor->set(color);
}

void GraphicsObj_Wireframe::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphicsObj_Wireframe::SetGPUData()
{
	//get curr 3D cam
	Camera* cam = Camera3DMan::GetCurrCam();
	assert(cam);

	//set vao
	glBindVertexArray(this->pMesh->GetVAO());

	//set state
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	//set shader
	this->pShaderObj->SetActive();

	//set uniforms
	Mat4 world = this->GetWorldMat();
	Mat4 view = cam->GetViewMatrix();
	Mat4 proj = cam->GetProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);

	glUniform4fv(this->pShaderObj->GetLocation("wire_color"), 1, (float*)this->poWirecolor);
}

void GraphicsObj_Wireframe::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->pMesh->GetTris(), GL_UNSIGNED_INT, 0);
}

void GraphicsObj_Wireframe::ResetState()
{
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFrontFace(GL_CCW);
}