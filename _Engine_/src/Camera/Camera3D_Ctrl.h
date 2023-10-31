#pragma once
#ifndef CAMERA_3D_CTRL_H
#define CAMERA_3D_CTRL_H

#include "GameObj.h"

class CameraCtrl
{
public:
	//deleted functions
	CameraCtrl(const CameraCtrl&) = delete;
	CameraCtrl& operator=(const CameraCtrl&) = delete;

	CameraCtrl() = default;
	~CameraCtrl() = default;

	void SetCamObj(GameObj* camobj);

	//bsc like a god cam...
	void Update();

private:
	GameObj* pCameraMeshObj;

	//just used to reset camera
	Vec3 up0;
	Vec3 tar0;
	Vec3 pos0;
	Vec3 upNorm0;
	Vec3 fwdNorm0;
	Vec3 rightNorm0;

	// target object
	Vec3 obj;


};
#endif // !CAMERA_3D_CTRL_H
