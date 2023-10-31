#pragma once
#ifndef GAME_OBJ_MAN_H
#define GAME_OBJ_MAN_H

#include "PCSTree.h"
#include "AnimTime.h"
#include "GameObj.h"
#include "GameObj2D.h"

using namespace Azul;

namespace Azul
{
	class GameObjMan
	{
	public:
		GameObjMan(const GameObjMan&) = delete;
		GameObjMan& operator=(const GameObjMan&) = delete;

		static void Create();
		static void Destroy();

		//add game obj to tree
		static void Add(GameObj* pObj, GameObj* pParent);

		static void Draw(void);
		static void Update(AnimTime t);

		static GameObj* GetRoot();
		static PCSTree* GetPCSTree();


	private:
		PCSTree* poRootTree;

		static GameObjMan* prInstance();

		GameObjMan();
		~GameObjMan();


	};
}
#endif // !GAME_OBJ_MAN_H
