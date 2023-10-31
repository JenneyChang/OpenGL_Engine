#include "GameObj.h"

namespace Azul
{
	//-----------------------------------------------------------------------------------
	//	CONSTRUCTION
	//-----------------------------------------------------------------------------------

	GameObj::GameObj(GraphicsObj* graphicsObj)
		: poWorld(new Mat4(Mat4::Special::Identity)), poGraphicsObj(graphicsObj), /*pBSphere(nullptr),*/
		toDraw(true)
	{
		assert(this->poWorld);
	}

	GameObj::~GameObj()
	{
		delete this->poWorld;

		if (this->poGraphicsObj)
		{
			delete this->poGraphicsObj;
		}
	}


	//-----------------------------------------------------------------------------------
	//	PUBLIC METHODS
	//-----------------------------------------------------------------------------------

	void GameObj::Draw()
	{
		if (this->toDraw && this->poGraphicsObj != nullptr)
		{
			this->poGraphicsObj->Render();
		}
	}

	GraphicsObj* GameObj::GetGraphicsObj()
	{
		return this->poGraphicsObj;
	}

	Mat4* GameObj::GetWorldMat()
	{
		return this->poWorld;
	}

	void GameObj::SetWorldMat(Mat4* pWorld)
	{
		assert(pWorld);
		*this->poWorld = *pWorld;
	}

	void GameObj::SetDraw(bool draw)
	{
		this->toDraw = draw;
	}


}