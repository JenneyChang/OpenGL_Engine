#pragma once
#ifndef CAMERA3D_MAN_H
#define CAMERA3D_MAN_H

#include "Manager.h"
#include "Camera3D.h"

using namespace Azul;

class Camera3DMan : public Manager
{
public:
	Camera3DMan() = delete;
	Camera3DMan(const Camera3DMan&) = delete;
	Camera3DMan& operator = (const Camera3DMan&) = delete;

	static void Create(int toReserve = 2, int toGrow = 1);
	static void Destroy();

	static void SetCurrCam(Camera3D* cam);
	static void SetCurrCam(Camera::Name _name);
	static Camera3D* GetCurrCam();

	static Camera3D* Add(Camera::Name _name);
	static Camera3D* Find(Camera::Name _name);
	static void Remove(Camera::Name _name);
	static void Print();


protected:
	Node* derivedCreateNode() override;


private:
	Camera3D* poComparison;
	Camera3D* pCurrCam;

	static Camera3DMan* poInstance;
	static Camera3DMan* prInstance();

	Camera3DMan(int toReserve = 2, int toGrow = 1);
	virtual ~Camera3DMan();


};
#endif // !CAMERA3D_MAN_H
