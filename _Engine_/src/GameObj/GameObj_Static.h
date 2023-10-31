#pragma once
#ifndef GAMEOBJ_STATIC_H
#define GAMEOBJ_STATIC_H

#include "GameObj3D.h"
#include "GraphicsObj3D.h"

using namespace Azul;

class GameObj_Static : public GameObj3D
{
public:
	GameObj_Static() = delete;
	GameObj_Static(const GameObj_Static&) = delete;
	GameObj_Static& operator=(const GameObj_Static&) = delete;

	GameObj_Static(GraphicsObj3D* graphicsobj) : GameObj3D(graphicsobj) { }
	virtual ~GameObj_Static() { }


};
#endif // !GAMEOBJ_STATIC_H
