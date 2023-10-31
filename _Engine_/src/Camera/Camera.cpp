#include "Camera.h"

using namespace Azul;


//-----------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------

Camera::Camera()
	: name(Camera::Name::UNINITIALIZED)
{ }

Camera::~Camera()
{ }


//-----------------------------------------------------------------------------
//	CAMERA SETUP
//-----------------------------------------------------------------------------

void Camera::SetViewport(const int inX, const int inY, const int w, const int h)
{
	this->view_x = inX;
	this->view_y = inY;
	this->view_w = w;
	this->view_h = h;

	//set opengl viewport
	this->prSetView();
}

void Camera::SetOrient_Pos(const Vec3& up, const Vec3& lookAt, const Vec3& pos)
{
	//unit vectors: up, look at, right (perpendicular)
	this->vLookat = lookAt;

	//screen --> eye
	this->vDir = pos - lookAt;
	this->vDir.norm();

	//get right (up x vdir)
	this->vRight = up.cross(this->vDir);
	this->vRight.norm();

	//get up (vdir x vright)
	this->vUp = this->vDir.cross(this->vRight);
	this->vUp.norm();

	this->vPos = pos;
}

void Camera::GetHelper(Vec3& up, Vec3& tar, Vec3& pos, Vec3& upNorm, Vec3& fwdNorm, Vec3& rghtNorm)
{
	this->GetPos(pos);
	this->GetLookat(tar);
	this->GetUp(upNorm);

	up = pos + upNorm;
	fwdNorm = tar - pos;
	fwdNorm.norm();

	this->GetRight(rghtNorm);
}

void Camera::SetHelper(Vec3& up, Vec3& tar, Vec3& pos)
{
	Vec3 upVect = up - pos;
	this->SetOrient_Pos(upVect, tar, pos);
}

bool Camera:: Compare(Node* pNode)
{
	assert(pNode != nullptr);
	Camera* pInNode = (Camera*)pNode;

	if (this->name == pInNode->name)
	{
		return true;
	}

	return false;
}


//-----------------------------------------------------------------------------
//	PRIVATE METHODS
//-----------------------------------------------------------------------------

void Camera::prSetView(void)
{
	glViewport(this->view_x, this->view_y, this->view_w, this->view_h);
}

void Camera::prUpdateViewMatrix(void)
{
	//assumes up, right, dir are unit vects (perpendicular to each other)
	//view = Rot(orient) * trans(-(eye.basis))

	this->viewMatrix[m0] = this->vRight.x();
	this->viewMatrix[m1] = this->vUp.x();
	this->viewMatrix[m2] = this->vDir.x();
	this->viewMatrix[m3] = 0.0f;

	this->viewMatrix[m4] = this->vRight.y();
	this->viewMatrix[m5] = this->vUp.y();
	this->viewMatrix[m6] = this->vDir.y();
	this->viewMatrix[m7] = 0.0f;

	this->viewMatrix[m8] = this->vRight.z();
	this->viewMatrix[m9] = this->vUp.z();
	this->viewMatrix[m10] = this->vDir.z();
	this->viewMatrix[m11] = 0.0f;

	//change of basis
	this->viewMatrix[m12] = -vPos.dot(this->vRight);
	this->viewMatrix[m13] = -vPos.dot(this->vUp);
	this->viewMatrix[m14] = -vPos.dot(this->vDir);
	this->viewMatrix[m15] = 1.0f;
}