#pragma once
#ifndef GAME_OBJ_BSPHERE_H
#define GAME_OBJ_BSPHERE_H

#include "GameObj.h"
#include "GameObj_Static.h"
#include "MathEngine.h"
#include "AnimTime.h"

using namespace Azul;

class GameObj_BSphere : public GameObj_Static
{
public:
	GameObj_BSphere() = delete;
	GameObj_BSphere(const GameObj_BSphere&) = delete;
	GameObj_BSphere& operator=(const GameObj_BSphere&) = delete;

	GameObj_BSphere(GraphicsObj3D* graphicsobj);
	virtual ~GameObj_BSphere();

	void Update(AnimTime t) override;
	void SetBSphereRef(GameObj* gameobj);


private:
	GameObj* pGameObjRef;
	Vec3* poScale;
	Vec3* poTrans;

	void prUpdate(AnimTime t);
	void prUpdateBSphereRef(AnimTime t);


};
#endif // !GAME_OBJ_BSPHERE_H
