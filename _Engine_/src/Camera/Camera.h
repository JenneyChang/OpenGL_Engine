#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "sb7.h"
#include "MathEngine.h"
#include "DLink.h"

using namespace Azul;

class Camera : public Align16 , public DLink
{
public:
	enum class Name
	{
		CAMERA_0,
		CAMERA_1,
		CAMERA_2,
		CAMERA_3,

		FRUSTRUM,
		FRUSTRUM_SIDE,
		FRUSTRUM_BACK,

		UNINITIALIZED
	};

	Camera();
	virtual ~Camera();
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;


	//camera setup
	void SetViewport(const int inX, const int inY, const int w, const int h);
	void SetOrient_Pos(const Vec3& up, const Vec3& lookAt, const Vec3& pos);
	
	//update camera
	virtual void UpdateCamera() = 0;

	void GetHelper(Vec3& up, Vec3& tar, Vec3& pos, Vec3& upNorm, Vec3& fwdNorm, Vec3& rghtNorm);
	void SetHelper(Vec3& up, Vec3& tar, Vec3& pos);

	//accessors
	void SetName(Camera::Name _name) { this->name = _name; }
	
	//rendering matrices
	Mat4& GetViewMatrix() { return this->viewMatrix; }
	Mat4& GetProjMatrix() { return this->projMatrix; }

	//Note: pos, dir, up, lookat, right are set (<--private) together 
	void GetPos(Vec3& outPos) const { outPos = this->vPos; }
	void GetDir(Vec3& outDir) const { outDir = this->vDir; }
	void GetUp(Vec3& outUp) const { outUp = this->vUp; }

	void GetLookat(Vec3& outLookat) const { outLookat = this->vLookat; }
	void GetRight(Vec3& outRight) const { outRight = this->vRight; }

	int GetScreenWidth() const { return this->view_w; }
	int GetScreenHeight() const { return this->view_h; }

	bool Compare(Node* pNode) override;


private:
	void prSetView(void);


protected:
	virtual void prUpdateProjMatrix() = 0;
	void prUpdateViewMatrix(void);


protected:
	// 16-bit ALIGNED DATA ------------------------------------------- 

	//projection
	Mat4 projMatrix;	//2D or 3D
	Mat4 viewMatrix;

	//camera unit vectors
	Vec3 vUp;
	Vec3 vDir;
	Vec3 vRight;	//up x dir
	Vec3 vPos;

	Vec3 vLookat;

	// UNALIGNED DATA ------------------------------------------------------

	//viewports
	int view_x;
	int view_y;
	int view_w;
	int view_h;

	Camera::Name name;


};
#endif // !CAMERA_H
