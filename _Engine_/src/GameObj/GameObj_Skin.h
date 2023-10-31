#pragma once
#ifndef GAME_OBJ_SKN_H
#define GAME_OBJ_SKN_H

#include "GameObj_Dynamic.h"
#include "GraphicsObj3D.h"
#include "MathEngine.h"
#include "Skeleton.h"

#include "SSBO.h"

using namespace Azul;

class GameObj_Skin : public GameObj_Dynamic
{
public:
	GameObj_Skin() = delete;
	GameObj_Skin(const GameObj_Skin&) = delete;
	GameObj_Skin& operator=(const GameObj_Skin&) = delete;

	GameObj_Skin(GraphicsObj3D* graphicsobj, Skeleton* skel, unsigned int numJoints, SSBO* pSSBO_JointsIn);
	virtual ~GameObj_Skin();

	void Update(AnimTime t) override;

	SSBO* GetSSBOWorldResult();


private:
	Skeleton* pSkeleton;
	unsigned int numBones;

	SSBO* pSSBO_JointLocal;
	SSBO* poSSBO_WorldResult;	//calculated world matrices	

	void prUpdate(AnimTime t);


};
#endif // !GAME_OBJ_SKN_H
