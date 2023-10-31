#pragma once
#ifndef CAMERA2D_MAN_H
#define CAMERA2D_MAN_H

#include "Manager.h"
#include "Camera2D.h"

using namespace Azul;

class Camera2DMan : public Manager
{
public:
	Camera2DMan() = delete;
	Camera2DMan(const Camera2DMan&) = delete;
	Camera2DMan& operator=(const Camera2DMan&) = delete;

	static void Create(int toReserve = 1, int toGrow = 1);
	static void Destroy();

	static void SetCurrCam(Camera2D* cam);
	static void SetCurrCam(Camera::Name _name);
	static Camera2D* GetCurrCam();

	static Camera2D* Add(Camera::Name _name);
	static Camera2D* Find(Camera::Name _name);
	static void Remove(Camera::Name _name);
	static void Print();


protected:
	Node* derivedCreateNode() override;


private:
	Camera2D* poComparison;
	Camera2D* pCurrCam;

	static Camera2DMan* poInstance;
	static Camera2DMan* prInstance();

	Camera2DMan(int toReserve = 1, int toGrow = 1);
	virtual ~Camera2DMan();


};
#endif // !CAMERA2D_MAN_H
