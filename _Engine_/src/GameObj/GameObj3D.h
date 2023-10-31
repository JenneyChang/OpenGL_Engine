#pragma once
#ifndef GAMEOBJ_3D_H
#define GAMEOBJ_3D_H

#include "GameObj.h"
#include "GraphicsObj3D.h"
#include "BoundingSphere.h"

class GameObj3D : public GameObj
{
public:
	GameObj3D() = delete;
	GameObj3D(const GameObj3D&) = delete;
	GameObj3D& operator=(const GameObj3D&) = delete;

	GameObj3D(GraphicsObj3D* graphicsobj);
	virtual ~GameObj3D();


protected:
	BoundingSphere* pBSphere;	//todo: move to 3d obj

	void baseUpdateBSphere();


};
#endif // !GAMEOBJ_3D_H
