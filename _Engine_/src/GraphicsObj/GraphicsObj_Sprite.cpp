#include "GraphicsObj_Sprite.h"
#include "Camera2DMan.h"

using namespace Azul;

//-----------------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------------

GraphicsObj_Sprite::GraphicsObj_Sprite(Mesh* mesh, ShaderObj* shaderobj, Image* img, Rect rect)
	: GraphicsObj2D(mesh, shaderobj)
{
	assert(img != nullptr);
	assert(mesh != nullptr);
	assert(shaderobj != nullptr);

	this->pImage = img;

	this->origWidth = rect.w;
	this->origHeight = rect.h;
	this->origPosx = rect.x;
	this->origPosy = rect.y;

	// Create the UV matrix
	float w = pImage->pRect.w / (float)pImage->pTexture->width;
	float h = pImage->pRect.h / (float)pImage->pTexture->height;
	float u = pImage->pRect.x / (float)pImage->pTexture->width;
	float v = pImage->pRect.y / (float)pImage->pTexture->height;
	Mat4 ScaleUV(Mat4::Scale::XYZ, w, h, 1.0f);
	Mat4 TransUV(Mat4::Trans::XYZ, u, v, 0.0f);
	*this->poMatrix_uv = ScaleUV * TransUV;

	// Create the orig Matrix 
	// The initial sprite setup, after this point standard world will adjust
	Mat4 Scale(Mat4::Scale::XYZ, this->origWidth, this->origHeight, 1.0f);
	*this->poMatrix_orig = Scale;

	texID = pImage->pTexture->GetID();
	assert(texID);
}

GraphicsObj_Sprite::~GraphicsObj_Sprite()
{ }

//-----------------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------------

void GraphicsObj_Sprite::SwapImage(Image* img)
{
	assert(img != nullptr);
	this->pImage = img;

	//update matrices
	// Create the UV matrix
	float w = pImage->pRect.w / (float)pImage->pTexture->width;
	float h = pImage->pRect.h / (float)pImage->pTexture->height;
	float u = pImage->pRect.x / (float)pImage->pTexture->width;
	float v = pImage->pRect.y / (float)pImage->pTexture->height;
	Mat4 ScaleUV(Mat4::Scale::XYZ, w, h, 1.0f);
	Mat4 TransUV(Mat4::Trans::XYZ, u, v, 0.0f);
	*this->poMatrix_uv = ScaleUV * TransUV;

	Mat4 Scale(Mat4::Scale::XYZ, this->origWidth, this->origHeight, 1.0f);
	*this->poMatrix_orig = Scale;

	//render it
	this->Render();
}

void GraphicsObj_Sprite::Render()
{
	this->SetState();
	this->SetGPUData();
	this->Draw();
	this->ResetState();
}


//-----------------------------------------------------------------------------------
//	PRIVATE METHODS
//-----------------------------------------------------------------------------------

void GraphicsObj_Sprite::SetState()
{
	//set active
	glActiveTexture(GL_TEXTURE0);

	//bind texture
	glBindTexture(GL_TEXTURE_2D, this->texID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	//blend for sprites
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
}

void GraphicsObj_Sprite::SetGPUData()	
{
	//get 2d camera
	Camera* cam = Camera2DMan::GetCurrCam();
	assert(cam);

	//set vao
	glBindVertexArray(this->pMesh->GetVAO());

	//activate shader
	this->pShaderObj->SetActive();

	//set uniforms
	Mat4 TransToOriginLowerLeft(Mat4::Trans::XYZ, (float)-cam->GetScreenWidth() / 2.0f, (float)-cam->GetScreenHeight() / 2.0f, 0.0f);
	Mat4 tmpMatrix = *this->poMatrix_orig * this->GetWorldMat() * TransToOriginLowerLeft;

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&cam->GetProjMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&cam->GetViewMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&tmpMatrix);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("uv_matrix"), 1, GL_FALSE, (float*)this->poMatrix_uv);
}

void GraphicsObj_Sprite::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->pMesh->GetTris(), GL_UNSIGNED_INT, 0);
}

void GraphicsObj_Sprite::ResetState()
{
	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}