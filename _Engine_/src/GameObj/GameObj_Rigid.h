#pragma once
#ifndef GAME_OBJ_RIGID_H
#define GAME_OBJ_RIGID_H

#include "GameObj_Static.h"
#include "GraphicsObj3D.h"
#include "MathEngine.h"

using namespace Azul;

class GameObj_Rigid : public GameObj_Static
{
public:
	enum Direction
	{
		move_x,
		move_y,
		move_z,
		standby
	};

	//deleted function
	GameObj_Rigid() = delete;
	GameObj_Rigid(const GameObj_Rigid&) = delete;
	GameObj_Rigid& operator=(const GameObj_Rigid&) = delete;

	GameObj_Rigid(GraphicsObj3D* graphicsobj);
	~GameObj_Rigid();

	void Update(AnimTime t) override;

	void SetScale(float sx, float sy, float sz);
	void SetTrans(float x, float y, float z);
	void SetRot(float x, float y, float z, float w);

	void SetScale(Vec3& r);
	void SetTrans(Vec3& r);
	void SetRot(Quat& r);

	void SetDeltaX(float x);
	void SetDeltaY(float y);
	void SetDeltaZ(float z);

	void SetDirX(Direction dir, float x);
	void SetDirY(Direction dir, float y);
	void SetDirZ(Direction dir, float z);


private:
	Vec3* poScale;
	Vec3* poTrans;
	Quat* poRot;

	float deltax;
	float deltay;
	float deltaz;

	float currx;
	float curry;
	float currz;

	float dirx;
	float diry;
	float dirz;

	Direction moveDir;

	void prUpdate(AnimTime t);


};
#endif // !GAME_OBJ_RIGID_H
