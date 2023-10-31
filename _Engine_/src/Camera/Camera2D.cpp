#include "Camera2D.h"

using namespace Azul;

//-----------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------

Camera2D::Camera2D()
	: Camera()
{ }

Camera2D::~Camera2D()
{ }

//-----------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------

void Camera2D::SetOrthographic(const float _xmin, const float _xmax, const float _ymin, const float _ymax, const float _zmin, const float _zmax)
{
	this->xmin = _xmin;
	this->ymin = _ymin;
	this->zmin = _zmin;

	this->xmax = _xmax;
	this->ymax = _ymax;
	this->zmax = _zmax;
}

void Camera2D::UpdateCamera()
{
	//update projection
	this->prUpdateProjMatrix();

	//update view
	this->prUpdateViewMatrix();
}

//-----------------------------------------------------------------------------
//	PROTECTED METHODS
//-----------------------------------------------------------------------------

void Camera2D::prUpdateProjMatrix()
{
	this->projMatrix[m0] = 2.0f / (xmax - xmin);
	this->projMatrix[m1] = 0.0f;
	this->projMatrix[m2] = 0.0f;
	this->projMatrix[m3] = 0.0f;

	this->projMatrix[m4] = 0.0f;
	this->projMatrix[m5] = 2.0f / (ymax - ymin);
	this->projMatrix[m6] = 0.0f;
	this->projMatrix[m7] = 0.0f;

	this->projMatrix[m8] = 0.0f;
	this->projMatrix[m9] = 0.0f;
	this->projMatrix[m10] = -2.0f / (zmax - zmin);
	this->projMatrix[m11] = 0.0f;

	this->projMatrix[m12] = 0;
	this->projMatrix[m13] = 0;
	this->projMatrix[m14] = -(zmax + zmin) / (zmax - zmin);
	this->projMatrix[m15] = 1.0f;
}
