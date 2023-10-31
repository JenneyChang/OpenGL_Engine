#include "GameObj_Null.h"

using namespace Azul;

//-----------------------------------------------------------------------------------
//	PRIVATE CONSTRUCTOR
//-----------------------------------------------------------------------------------

GameObj_Null::GameObj_Null(GraphicsObj_Null3D* graphicsobj)
	: GameObj(graphicsobj)
{ }

GameObj_Null::~GameObj_Null()
{ }


//-----------------------------------------------------------------------------------
//	OVERRIDDEN FUNCTION
//-----------------------------------------------------------------------------------

void GameObj_Null::Update(AnimTime t)
{
	AZUL_UNUSED_VAR(t);

	Mat4 Identity(Mat4::Special::Identity);
	*this->poWorld = Identity;

	this->poGraphicsObj->SetWorldMat(*this->poWorld);
}