#pragma once
#ifndef GAMEOBJ_2D_H
#define GAMEOBJ_2D_H

#include "GameObj.h"
#include "GraphicsObj_Sprite.h"
#include "MathEngine.h"

using namespace Azul;

class GameObj2D : public GameObj
{
public:
	enum class Name
	{
		MainBatch,
		TextBatch,

		Uninitialized
	};

	GameObj2D() = delete;
	GameObj2D(const GameObj2D&) = delete;
	GameObj2D& operator=(const GameObj2D&) = delete;

	GameObj2D(GameObj2D::Name _name);
	GameObj2D(GameObj2D::Name _name , GraphicsObj2D* graphicsobj);
	virtual ~GameObj2D();

	void SetPos(float x, float y);
	void SetScale(float sx, float sy);
	void SetAngle(float a);

	GameObj2D::Name GetBatchName();

	void Update(AnimTime t) override;


protected:
	GameObj2D::Name name;

	float sx;
	float sy;
	float posx;
	float posy;
	float angle;

	//Todo: do I want ability to reset?
	/*float origWidth;
	float origHeight;
	float origAngle;*/


};
#endif // !GAMEOBJ_2D_H
