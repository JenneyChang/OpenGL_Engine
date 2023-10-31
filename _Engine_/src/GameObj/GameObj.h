#pragma once
#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include "PCSNode.h"
#include "AnimTime.h"
#include "GraphicsObj.h"
//#include "BoundingSphere.h"
#include "Mesh.h"

//using namespace Azul;

namespace Azul
{
	class GameObj : public PCSNode
	{
	public:
		GameObj() = delete;
		GameObj(const GameObj&) = delete;
		GameObj& operator=(const GameObj&) = delete;

		GameObj(GraphicsObj* graphicsObj);
		virtual ~GameObj();

		virtual void Update(AnimTime t) = 0;
		virtual void Draw();

		GraphicsObj* GetGraphicsObj();

		Mat4* GetWorldMat();
		void SetWorldMat(Mat4* pWorld);

		void SetDraw(bool draw);


	protected:
		Mat4* poWorld;
		GraphicsObj* poGraphicsObj;
		bool toDraw;

	
	};
}
#endif // !GAME_OBJ_H
