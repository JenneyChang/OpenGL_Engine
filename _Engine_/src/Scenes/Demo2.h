#pragma once
#ifndef DEMO_2_H
#define DEMO_2_H

#include "Scene.h"
#include "Camera3D_Ctrl.h"
#include "GameObj_Rigid.h"

// Frustum Culling
class Demo2 : public Scene, public Align16
{
public:
	Demo2() = delete;
	Demo2(const Demo2&) = delete;
	Demo2& operator=(const Demo2&) = delete;

	Demo2(const int w, const int h);
	virtual ~Demo2();

	void Load() override;
	void Update() override;
	void Unload() override;


private:
	const unsigned int width;	
	const unsigned int height;	

	CameraCtrl camctrl;			
	GameObj_Rigid* pCrateObj;	
	GameObj_Rigid* pFrigateObj;
	GameObj_Rigid* pR2D2Obj;
	GameObj_Rigid* pR2D2Obj2;


};
#endif // !DEMO_2_H
