#pragma once
#ifndef GAME_OBJ_NULL_H
#define GAME_OBJ_NULL_H

#include "GameObj.h"
#include "GraphicsObj_Null3D.h"
#include "AnimTime.h"

using namespace Azul;

class GameObj_Null : GameObj
{
public:
	GameObj_Null() = delete;
	GameObj_Null(const GameObj_Null&) = delete;
	GameObj_Null& operator=(const GameObj_Null&) = delete;

	GameObj_Null(GraphicsObj_Null3D* graphicsobj);
	~GameObj_Null();

	void Update(AnimTime t) override;

};
#endif // !GAME_OBJ_NULL_H
