#pragma once
#ifndef GAMEOBJ_DYNAMIC_H
#define GAMEOBJ_DYNAMIC_H

#include "GameObj3D.h"
#include "GraphicsObj3D.h"

using namespace Azul;

class GameObj_Dynamic : public GameObj3D
{
public:
	int mIndex;	//model index 
	int eIndex;	//engine index (tree)

	GameObj_Dynamic() = delete;
	GameObj_Dynamic(const GameObj_Dynamic&) = delete;
	GameObj_Dynamic& operator=(const GameObj_Dynamic&) = delete;

	GameObj_Dynamic(GraphicsObj3D* graphicsobj)
		: GameObj3D(graphicsobj), mIndex(-1), eIndex(-1) { }
	virtual ~GameObj_Dynamic() { }

	virtual void SetIndexM(int) { }
	virtual void SetIndexE(int) { }


};
#endif // !GAMEOBJ_DYNAMIC_H
