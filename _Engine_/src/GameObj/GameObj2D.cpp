#include "GameObj2D.h"


//--------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------

GameObj2D::GameObj2D(GameObj2D::Name _name)
	: GameObj(nullptr)
{
	this->name = _name;
	this->sx = 1.0f;
	this->sy = 1.0f;
	this->angle = 0.0f;
	this->posx = 0.0f;
	this->posy = 0.0f;
}

GameObj2D::GameObj2D(GameObj2D::Name _name, GraphicsObj2D* graphicsobj)
	: GameObj(graphicsobj)
{
	assert(graphicsobj);

	this->name = _name;
	this->sx = 1.0f;
	this->sy = 1.0f;
	this->angle = 0.0f;

	graphicsobj->GetPos(posx, posy);
}

GameObj2D::~GameObj2D()
{ }


//--------------------------------------------------------------------------
//	PUBLIC METHODS
//--------------------------------------------------------------------------

void GameObj2D::SetPos(float x, float y)
{
	this->posx = x;
	this->posy = y;
}

void GameObj2D::SetScale(float _sx, float _sy)
{
	this->sx = _sx;
	this->sy = _sy;
}

void GameObj2D::SetAngle(float a)
{
	this->angle = a;
}

GameObj2D::Name GameObj2D::GetBatchName()
{
	return this->name;
}


//--------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//--------------------------------------------------------------------------

void GameObj2D::Update(AnimTime t)
{
	AZUL_UNUSED_VAR(t);

	//update world mat
	Mat4 Scale(Mat4::Scale::XYZ, sx, sy, 1.0f);
	Mat4 Trans(Mat4::Trans::XYZ, posx, posy, 0.0f);
	Mat4 Rot(Mat4::Rot1::Z, angle);

	*this->poWorld = Scale * Rot * Trans;

	//update grpahics obj
	if (this->poGraphicsObj)
	{
		this->poGraphicsObj->SetWorldMat(*this->poWorld);
	}
}