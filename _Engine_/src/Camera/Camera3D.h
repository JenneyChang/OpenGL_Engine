#pragma once
#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include "Camera.h"
#include "BoundingSphere.h"

using namespace Azul;

class Camera3D final : public Camera
{
public:
	enum class CullResult
	{
		INSIDE,
		OUTSIDE
	};

	Camera3D::CullResult CullTest(const BoundingSphere& bs);

	Camera3D();
	virtual ~Camera3D();
	Camera3D(const Camera3D&) = delete;
	Camera3D& operator=(const Camera3D&) = delete;

	//camera setup
	void SetPerspective(const float fov_y, const float aspectRatio, const float nearDist, const float farDist);

	//update camera
	void UpdateCamera() override;

	//accessors
	void GetFOV(float& val) const	{ val = this->aspectRatio; }
	void SetFOV(const float val)	{ this->aspectRatio = val; }

	void GetNearDist(float& val) const	{ val = this->nearDist; }
	void SetNearDist(const float val)	{ this->nearDist = val; }

	void GetNearTopLeft(Vec3& vOut) const		{ vOut = this->nearTopLeft; }
	void GetNearTopRight(Vec3& vOut) const		{ vOut = this->nearTopRight; }
	void GetNearBottomLeft(Vec3& vOut) const	{ vOut = this->nearBottomLeft; }
	void GetNearBottomRight(Vec3& vOut) const	{ vOut = this->nearBottomRight; }

	void GetFarTopLeft(Vec3& vOut) const		{ vOut = this->farTopLeft; }
	void GetFarTopRight(Vec3& vOut) const		{ vOut = this->farTopRight; }
	void GetFarBottomLeft(Vec3& vOut) const		{ vOut = this->farBottomLeft; }
	void GetFarBottomRight(Vec3& vOut) const	{ vOut = this->farBottomRight; }


protected:
	void prUpdateProjMatrix() override;


private:
	//world space coordinates for viewing frustum 
	Vec3 nearTopLeft;
	Vec3 nearTopRight;
	Vec3 nearBottomLeft;
	Vec3 nearBottomRight;

	Vec3 farTopLeft;
	Vec3 farTopRight;
	Vec3 farBottomLeft;
	Vec3 farBottomRight;

	//frustum inputs
	float nearDist;
	float farDist;
	float fov_y;
	float aspectRatio;

	//screen size in world space
	float near_height;
	float near_width;
	float far_height;
	float far_width;

	//frustum normals
	Vec3 frontNorm;
	Vec3 backNorm;
	Vec3 rightNorm;
	Vec3 leftNorm;
	Vec3 topNorm;
	Vec3 bottomNorm;

	void prCalcPlaneHeightWidth(void);
	void prCalcFrustumVerts(void);
	void prCalcFrustumCollisionNorms(void);


};
#endif // !CAMERA_3D_H
