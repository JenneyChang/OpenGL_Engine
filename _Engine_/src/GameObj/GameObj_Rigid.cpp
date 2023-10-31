#include "GameObj_Rigid.h"

using namespace Azul;

//-----------------------------------------------------------------------------------
//	 CONSTRUCTION
//-----------------------------------------------------------------------------------

GameObj_Rigid::GameObj_Rigid(GraphicsObj3D* graphicsobj)
	: GameObj_Static(graphicsobj), poScale(new Vec3(1.0f, 1.0f, 1.0f)), poTrans(new Vec3(0.0f, 0.0f, 0.0f)),
	  poRot(new Quat(0.0f, 0.0f, 0.0f, 1.0f)), deltax(0.0f), deltay(0.0f), deltaz(0.0f), currx(0.0f), curry(0.0f), currz(0.0f)
{
	assert(graphicsobj);

	assert(this->poTrans);
	assert(this->poScale);
	assert(this->poRot);
}

GameObj_Rigid::~GameObj_Rigid()
{
	delete this->poTrans;
	delete this->poScale;
	delete this->poRot;
}


//-----------------------------------------------------------------------------------
//	 PUBLIC METHODS
//-----------------------------------------------------------------------------------

void GameObj_Rigid::Update(AnimTime t)
{
	//update world matrix
	this->prUpdate(t);

	//base update: bounding vol using world mat
	this->baseUpdateBSphere();

	//update graphics obj world mat
	this->poGraphicsObj->SetWorldMat(*this->poWorld);
}

void GameObj_Rigid::SetScale(float sx, float sy, float sz)
{
	this->poScale->set(sx, sy, sz);
}

void GameObj_Rigid::SetTrans(float x, float y, float z)
{
	this->poTrans->set(x, y, z);
}

void GameObj_Rigid::SetRot(float x, float y, float z, float w)
{
	this->poRot->set(x, y, z, w);
}

void GameObj_Rigid::SetScale(Vec3& s)
{
	*this->poScale = s;
}

void GameObj_Rigid::SetTrans(Vec3& r)
{
	*this->poTrans = r;
}

void GameObj_Rigid::SetRot(Quat& r)
{
	*this->poRot = r;
}

void GameObj_Rigid::SetDeltaX(float x)
{
	this->deltax = x;
}

void GameObj_Rigid::SetDeltaY(float y)
{
	this->deltay = y;
}

void GameObj_Rigid::SetDeltaZ(float z)
{
	this->deltaz = z;
}

void GameObj_Rigid::SetDirX(Direction dir, float x)
{
	this->moveDir = dir;
	this->dirx = x;
}

void GameObj_Rigid::SetDirY(Direction dir, float y)
{
	this->moveDir = dir;
	this->diry = y;
}

void GameObj_Rigid::SetDirZ(Direction dir, float z)
{
	this->moveDir = dir;
	this->dirz = z;
}


//-----------------------------------------------------------------------------------
//	 PRIVATE METHODS
//-----------------------------------------------------------------------------------

void GameObj_Rigid::prUpdate(AnimTime t)
{
	AZUL_UNUSED_VAR(t);
	//float delta = 0.01f;

	Mat4 Scale(Mat4::Scale::XYZ, *this->poScale);
	Mat4 Trans(Mat4::Trans::XYZ, *this->poTrans);
	Quat Rot(*this->poRot);

	/*switch (this->moveDir)
	{
	case move_x:
		float tmp;
		poTrans->x(tmp);

		tmp += (delta * dirx);
		if (tmp > 6.0f || tmp < -6.0f)
		{
			dirx *= -1.0f;
		}
		break;
	case move_y:
		break;
	case move_z:
		break;
	case standby:
		break;
	}*/

	currx += deltax;
	curry += deltay;
	currz += deltaz;

	Mat4 Rx(Mat4::Rot1::X, currx);
	Mat4 Ry(Mat4::Rot1::Y, curry);
	Mat4 Rz(Mat4::Rot1::Z, currz);

	*this->poWorld = Scale * Rot * Rx * Ry * Rz * Trans;
}
