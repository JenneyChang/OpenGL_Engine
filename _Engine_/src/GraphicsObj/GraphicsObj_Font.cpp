#include "GraphicsObj_Font.h"
#include "GlyphMan.h"
#include "Camera2DMan.h"

using namespace Azul;

//-----------------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------------

GraphicsObj_Font::GraphicsObj_Font(Mesh* mesh, ShaderObj* shaderobj)
	: GraphicsObj2D(mesh, shaderobj)
{
	assert(mesh);
	assert(shaderobj);

	this->pGlyph = nullptr;
	this->message = "null";
	this->x = 0.0f;
	this->y = 0.0f;

	this->texID = 0;

	this->poRect = new Rect();
	assert(this->poRect);
}

GraphicsObj_Font::~GraphicsObj_Font()
{
	delete this->poRect;
}


//-----------------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------------

void GraphicsObj_Font::Set(Glyph::Name _glyph, std::string mssg, float _x, float _y)
{
	assert(!mssg.empty());
	
	this->message = mssg;
	this->x = _x;
	this->y = _y;

	//save ref to glyph
	pGlyph = GlyphMan::Find(_glyph);
	assert(pGlyph);

	//save associated texture ID
	this->texID = pGlyph->GetTexID();
}

void GraphicsObj_Font::UpdateMessage(std::string mssg)
{
	assert(!mssg.empty());
	this->message = mssg;
}

void GraphicsObj_Font::Render()
{
	assert(!message.empty());

	Camera* cam = Camera2DMan::GetCurrCam();	//get 2d camera
	assert(cam);

	Texture* pTexture = pGlyph->GetTexture();	//get texture ref

	//set state--------------------------------------------------------
	glActiveTexture(GL_TEXTURE0);	//set active
	glBindTexture(GL_TEXTURE_2D, texID);	//bind texture

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

	//------------------------------------------------------------------

	glBindVertexArray(this->pMesh->GetVAO());	//set vao
	this->pShaderObj->SetActive();	//activate shader

	float tempx = x;
	float tempy = y;
	float tempxEnd = x;
	for (unsigned int i = 0; i < message.length(); ++i)
	{
		int key = message[i];	//grab first letter in message
		Rect pGlyphRect = pGlyph->GetKey(key);	//grab glyph rect values

		//set font rect
		tempx = tempxEnd + (pGlyphRect.w / 2);
		this->poRect->Set(tempx, tempy, pGlyphRect.w, pGlyphRect.h);

		//update matrix uv & scale
		float w = pGlyphRect.w / (float)pTexture->width;
		float h = pGlyphRect.h / (float)pTexture->height;
		float u = pGlyphRect.x / (float)pTexture->width;
		float v = pGlyphRect.y / (float)pTexture->height;

		Mat4 scaleuv(Mat4::Scale::XYZ, w, h, 1.0f);
		Mat4 transuv(Mat4::Trans::XYZ, u, v, 0.0f);
		*this->poMatrix_uv = scaleuv * transuv;

		Mat4 scale(Mat4::Scale::XYZ, pGlyphRect.w, pGlyphRect.h, 1.0f);
		*this->poMatrix_orig = scale;

		//create world mat
		Mat4 s(Mat4::Scale::XYZ, 1.0f, 1.0f, 1.0f);
		Mat4 r(Mat4::Rot1::Z, 0.0f);
		Mat4 t(Mat4::Trans::XYZ, tempx, tempy, 0.0f);
		Mat4 tmp = s * r * t;
		*this->poWorld = tmp;

		//set uniforms
		Mat4 TransToOriginLowerLeft(Mat4::Trans::XYZ, (float)-cam->GetScreenWidth() / 2.0f, (float)-cam->GetScreenHeight() / 2.0f, 0.0f);
		Mat4 tmpMatrix = *this->poMatrix_orig * this->GetWorldMat() * TransToOriginLowerLeft;

		glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&cam->GetProjMatrix());
		glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&cam->GetViewMatrix());
		glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&tmpMatrix);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("uv_matrix"), 1, GL_FALSE, (float*)this->poMatrix_uv);

		glDrawElements(GL_TRIANGLES, 3 * this->pMesh->GetTris(), GL_UNSIGNED_INT, 0);

		//adv to next letter
		tempxEnd = pGlyphRect.w / 2 + tempx;
	}

	//reset
	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}