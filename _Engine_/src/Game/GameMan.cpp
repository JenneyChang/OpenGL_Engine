//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "GameMan.h"

namespace Azul
{
	GameMan *GameMan::pInstance = nullptr;

	//-----------------------------------------------------------------------------
	//	PRIVATE CONSTRUCTION
	//-----------------------------------------------------------------------------

	GameMan::GameMan(Game* poGame)
	{
		assert(poGame);
		this->poGame = poGame;
	}

	GameMan::~GameMan()
	{
		assert(this->poGame == nullptr);
	}


	//-----------------------------------------------------------------------------
	//	PUBLIC METHODS
	//-----------------------------------------------------------------------------

	void GameMan::Create(const char *windowName, const int Width, const int Height)
	{
		GameMan::privCreate(windowName, Width, Height);
	}

	void GameMan::Destroy()
	{
		GameMan *pMan = GameMan::privInstance();
		assert(pMan);

		assert(pMan->poGame);
		delete pMan->poGame;
		pMan->poGame = nullptr;
	}

	Game* GameMan::GetGame()
	{
		GameMan* pMan = GameMan::privInstance();
		assert(pMan);
		assert(pMan->poGame);
		return pMan->poGame;
	}


	//-----------------------------------------------------------------------------
	//	PRIVATE METHODS
	//-----------------------------------------------------------------------------

	void GameMan::privCreate(const char *windowName, const int Width, const int Height)
	{
		Game *poGame = new Game(windowName, Width, Height);

		// Storage
		static GameMan gameMan(poGame);
		GameMan::pInstance = &gameMan;
	}

	GameMan *GameMan::privInstance()
	{
		assert(GameMan::pInstance);
		return GameMan::pInstance;
	}
}

// --- End of File ---