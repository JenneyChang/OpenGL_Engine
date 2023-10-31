#include "GraphicsObj_Skin.h"
#include "Camera3DMan.h"

using namespace Azul;


//-----------------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------------

GraphicsObj_Skin::GraphicsObj_Skin(Mesh* mesh, ShaderObj* shader, Texture* texture, GameObj_Rigid* pivot,
	Vec4& color, Vec3& pos) : GraphicsObj3D(mesh, shader), textureID(texture->GetID()), pPivot(pivot), 
	pSSBO_WorldResult(nullptr)
{
	assert(mesh);
	assert(shader);
	assert(textureID > 0);
	assert(pivot);

	this->poLightColor = new Vec4(color);
	assert(this->poLightColor);

	this->poLightPos = new Vec3(pos);
	assert(this->poLightPos);
}

GraphicsObj_Skin::~GraphicsObj_Skin()
{ 
	delete this->poLightColor;
	delete this->poLightPos;
}


//-----------------------------------------------------------------------------------
//	PUBLIC  METHODS
//-----------------------------------------------------------------------------------

void GraphicsObj_Skin::SetSSBOWorldResult(SSBO* pSSBOIn)
{
	assert(pSSBOIn);
	this->pSSBO_WorldResult = pSSBOIn;
}

void GraphicsObj_Skin::SetLightColor(Vec4* color)
{
	assert(color);
	this->poLightColor = color;
}

void GraphicsObj_Skin::SetLighPosition(Vec3* pos)
{
	assert(pos);
	this->poLightPos = pos;
}



//-----------------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//-----------------------------------------------------------------------------------

void GraphicsObj_Skin::SetState()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textureID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphicsObj_Skin::SetGPUData()
{
	Camera3D* cam = Camera3DMan::GetCurrCam();
	assert(cam);

	//set shader
	this->pShaderObj->SetActive();

	//set vao
	glBindVertexArray(this->pMesh->GetVAO());

	//set uniforms
	Mat4 view = cam->GetViewMatrix();
	Mat4 proj = cam->GetProjMatrix();
	Mat4 inverse = pPivot->GetWorldMat()->getInv();

	Vec4 color = *this->poLightColor;
	Vec3 light = *this->poLightPos;
	Vec3 camPos;
	cam->GetPos(camPos);

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("pivotTRS"), 1, GL_FALSE, (float*)pPivot->GetWorldMat());

	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)&color);
	glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float*)&light);
	glUniform3fv(this->pShaderObj->GetLocation("vViewPos"), 1, (float*)&camPos);

	//bind ssbo
	pSSBO_WorldResult->Bind(0);
}

void GraphicsObj_Skin::Draw()
{
	//The starting point of the IBO index buffer object
	glDrawElements(GL_TRIANGLES, 3 * this->pMesh->GetTris(), GL_UNSIGNED_INT, 0);
}

void GraphicsObj_Skin::ResetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}