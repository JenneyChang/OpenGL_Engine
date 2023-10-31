//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "InputMan.h"
#include "AnimMan.h"

namespace Azul
{
	InputMan *InputMan::poInputMan = nullptr;

	//---------------------------------------------------------------------------
	//	PRIVATE CONSTRUCTION
	//---------------------------------------------------------------------------

	InputMan::InputMan()
	{
		this->poKeyboard = new Keyboard();
		assert(this->poKeyboard);

		this->poMouse = new Mouse();
		assert(this->poMouse);

		this->keyPressed = false;
	}

	InputMan::~InputMan()
	{ }


	//---------------------------------------------------------------------------
	//	PUBLIC STATIC METHODS
	//---------------------------------------------------------------------------

	void InputMan::Create()
	{
		InputMan::privCreate();
	}

	void InputMan::Destroy()
	{
		InputMan *pMan = InputMan::privInstance();
		assert(pMan);

		delete pMan->poMouse;
		delete pMan->poKeyboard;

		delete pMan->poInputMan;
	}

	void Azul::InputMan::Update()
	{
		//InputMan* pManager = InputMan::privInstance();

		//if (pManager->poKeyboard->GetKeyState(pManager->key1))
		//{
		//	Anim* pAnim = AnimMan::Find(Anim::Name::MOUSEY_WALK);
		//	assert(pAnim);

		//	//pAnim->SetBlend(Clip::Name::MOUSEY_RUN);
		//	pAnim->blending = true;
		//}

		//if (pManager->poKeyboard->GetKeyState(pManager->key2))
		//{
		//	Anim* pAnim = AnimMan::Find(Anim::Name::MOUSEY_RUNNING);
		//	assert(pAnim);

		//	//pAnim->SetBlend(Clip::Name::MOUSEY_FLIP);
		//	pAnim->blending = true;
		//}

		//if (pManager->poKeyboard->GetKeyState(pManager->key0))
		//{
		//	Anim* pAnim1 = AnimMan::Find(Anim::Name::MOUSEY_WALK);
		//	assert(pAnim1);

		//	pAnim1->SetBlend(Clip::Name::MOUSEY_WALK);
		//	pAnim1->blending = true;

		//	Anim* pAnim = AnimMan::Find(Anim::Name::MOUSEY_RUNNING);
		//	assert(pAnim);
		//	pAnim->SetBlend(Clip::Name::MOUSEY_RUN);
		//	pAnim->blending = true;
		//}
	}

	Keyboard *InputMan::GetKeyboard()
	{
		InputMan *pMan = InputMan::privInstance();
		return pMan->poKeyboard;
	}

	Mouse *InputMan::GetMouse()
	{
		InputMan *pMan = InputMan::privInstance();
		return pMan->poMouse;
	}


	//---------------------------------------------------------------------------
	//	PRIVATE METHODS
	//---------------------------------------------------------------------------

	void InputMan::privCreate()
	{
		InputMan::poInputMan = new InputMan();
		assert(poInputMan);
	}

	InputMan *InputMan::privInstance()
	{
		assert(poInputMan);
		return poInputMan;
	}

	Azul::InputMan::operator bool()
	{
		InputMan* pManager = InputMan::privInstance();

		if (pManager->poKeyboard->GetKeyState(key1))
		{
			pManager->keyPressed = true;
		}
		if (pManager->keyPressed && pManager->poKeyboard->GetKeyState(key1))
		{
			pManager->keyPressed = false;
			return true;
		}

		if (pManager->poKeyboard->GetKeyState(key2))
		{
			pManager->keyPressed = true;
		}
		if (pManager->keyPressed && pManager->poKeyboard->GetKeyState(key2))
		{
			pManager->keyPressed = false;
			return true;
		}

		if (pManager->poKeyboard->GetKeyState(key0))
		{
			pManager->keyPressed = true;
		}
		if (pManager->keyPressed && pManager->poKeyboard->GetKeyState(key0))
		{
			pManager->keyPressed = false;
			return true;
		}

		return false;
	}

}

// --- End of File ---
