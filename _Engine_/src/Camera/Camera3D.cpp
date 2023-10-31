#include "Camera3D.h"

using namespace Azul;


//-----------------------------------------------------------------------------
//	CULL TEST
//-----------------------------------------------------------------------------

Camera3D::CullResult Camera3D::CullTest(const BoundingSphere& bs)
{
	Camera3D::CullResult result = Camera3D::CullResult::INSIDE;

	Vec3 A = bs.center - this->nearTopLeft;
	if ((A.dot(this->topNorm) > bs.radius) || (A.dot(this->leftNorm) > bs.radius) || (A.dot(this->frontNorm) > bs.radius))
	{
		result = Camera3D::CullResult::OUTSIDE;
	}
	else
	{
		Vec3 B = bs.center - this->farBottomRight;
		if ((B.dot(this->backNorm) > bs.radius) || (B.dot(this->rightNorm) > bs.radius) || (B.dot(this->bottomNorm) > bs.radius))
		{
			result = Camera3D::CullResult::OUTSIDE;
		}
	}

	return result;
}


//-----------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------

Camera3D::Camera3D()
	: Camera()
{ }

Camera3D::~Camera3D()
{ }


//-----------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------

void Camera3D::SetPerspective(const float _fov_y, const float _aspectRatio,
	const float _nearDist, const float _farDist)
{
	this->aspectRatio = _aspectRatio;
	this->fov_y = _fov_y;
	this->nearDist = _nearDist;
	this->farDist = _farDist;
}

void Camera3D::UpdateCamera()
{
	//find near & far height + width
	this->prCalcPlaneHeightWidth();

	//find frustum phys vertices
	this->prCalcFrustumVerts();

	//find frustum collision normals
	this->prCalcFrustumCollisionNorms();

	//update projection
	this->prUpdateProjMatrix();

	//update view
	this->prUpdateViewMatrix();
}


//-----------------------------------------------------------------------------
//	PROTECTED METHODS
//-----------------------------------------------------------------------------

void Camera3D::prUpdateProjMatrix()
{
	//note: matrix is invertable
	this->projMatrix[m0] = (2.0f * this->nearDist) / this->near_width;
	this->projMatrix[m1] = 0.0f;
	this->projMatrix[m2] = 0.0f;
	this->projMatrix[m3] = 0.0f;

	this->projMatrix[m4] = 0.0f;
	this->projMatrix[m5] = (2.0f * this->nearDist) / this->near_height;
	this->projMatrix[m6] = 0.0f;
	this->projMatrix[m7] = 0.0f;

	this->projMatrix[m8] = 0.0f;
	this->projMatrix[m9] = 0.0f;
	this->projMatrix[m10] = (this->farDist + this->nearDist) / (this->nearDist - this->farDist);
	this->projMatrix[m11] = -1.0f;

	this->projMatrix[m12] = 0.0f;
	this->projMatrix[m13] = 0.0f;
	this->projMatrix[m14] = (2.0f * this->farDist * this->nearDist) / (this->nearDist - this->farDist);
	this->projMatrix[m15] = 0.0f;
}


//-----------------------------------------------------------------------------
//	PRIVATE METHODS
//-----------------------------------------------------------------------------

void Camera3D::prCalcPlaneHeightWidth(void)
{
	//calclate near & far plane height + width
	this->near_height = 2.0f * tanf((this->fov_y * MATH_PI / 180.0f) * 0.5f) * this->nearDist;
	this->near_width = this->near_height * this->aspectRatio;

	this->far_height = 2.0f * tanf((this->fov_y * MATH_PI / 180.0f) * 0.5f) * this->farDist;
	this->far_width = this->far_height * this->aspectRatio;
}

void Camera3D::prCalcFrustumVerts(void)
{
	//calc points that create frustrum
	//vDir goes from scrren to EYE, distance from eye is -vDir
	this->nearTopLeft = this->vPos - this->vDir * this->nearDist + this->vUp *
		this->near_height * 0.5f - this->vRight * this->near_width * 0.5f;

	this->nearTopRight = this->vPos - this->vDir * this->nearDist + this->vUp *
		this->near_height * 0.5f + this->vRight * this->near_width * 0.5f;

	this->nearBottomLeft = this->vPos - this->vDir * this->nearDist - this->vUp *
		this->near_height * 0.5f - this->vRight * this->near_width * 0.5f;

	this->nearBottomRight = this->vPos - this->vDir * this->nearDist - this->vUp *
		this->near_height * 0.5f + this->vRight * this->near_width * 0.5f;

	this->farTopLeft = this->vPos - this->vDir * this->farDist + this->vUp *
		this->far_height * 0.5f - this->vRight * this->far_width * 0.5f;

	this->farTopRight = this->vPos - this->vDir * this->farDist + this->vUp *
		this->far_height * 0.5f + this->vRight * this->far_width * 0.5f;

	this->farBottomLeft = this->vPos - this->vDir * this->farDist - this->vUp *
		this->far_height * 0.5f - this->vRight * this->far_width * 0.5f;

	this->farBottomRight = this->vPos - this->vDir * this->farDist - this->vUp *
		this->far_height * 0.5f + this->vRight * this->far_width * 0.5f;
}

void Camera3D::prCalcFrustumCollisionNorms(void)
{
	//frustum normals around nearTopLeft
	//subract vects
	Vec3 A = this->nearBottomLeft - this->nearTopLeft;
	Vec3 B = this->nearTopRight - this->nearTopLeft;
	Vec3 C = this->farTopLeft - this->nearTopLeft;

	//front = a x b
	this->frontNorm = A.cross(B);
	this->frontNorm.norm();

	//left = c x a
	this->leftNorm = B.cross(A);
	this->leftNorm.norm();

	//top = b x c
	this->topNorm = B.cross(C);
	this->topNorm.norm();

	//frustum normals around farBottomRight
	A = this->farBottomLeft - this->farBottomRight;
	B = this->farTopRight - this->farBottomRight;
	C = this->nearBottomRight - this->farBottomRight;

	this->backNorm = A.cross(B);
	this->backNorm.norm();

	this->rightNorm = B.cross(C);
	this->rightNorm.norm();

	this->bottomNorm = C.cross(A);
	this->bottomNorm.norm();
}
