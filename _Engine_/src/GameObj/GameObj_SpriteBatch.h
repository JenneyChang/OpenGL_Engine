#pragma once
#ifndef GAMEOBJ_SPRITE_BATCH_H
#define GAMEOBJ_SPRITE_BATCH_H

#include "GameObj2D.h"

class GameObj_SpriteBatch : public GameObj2D
{
public:
	GameObj_SpriteBatch() = delete;
	GameObj_SpriteBatch(const GameObj_SpriteBatch&) = delete;
	GameObj_SpriteBatch& operator=(const GameObj_SpriteBatch&) = delete;

	GameObj_SpriteBatch(GameObj2D::Name name);
	virtual ~GameObj_SpriteBatch();


};
#endif // !GAMEOBJ_SPRITE_BATCH_H
