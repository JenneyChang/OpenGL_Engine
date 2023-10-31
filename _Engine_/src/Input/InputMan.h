//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef INPUT_MAN_H
#define INPUT_MAN_H

#include "Keyboard.h"
#include "Mouse.h"

namespace Azul
{
	class InputMan
	{
	public:
		InputMan(const InputMan &) = delete;
		InputMan &operator = (const InputMan &) = delete;

		static void Create();
		static void Destroy();

		static void Update();

		static Keyboard *GetKeyboard();
		static Mouse *GetMouse();


	private:
		InputMan();
		~InputMan();

		operator bool();

		static InputMan *privInstance();
		static void privCreate();

		// Data
		static InputMan *poInputMan;
		Keyboard *poKeyboard;
		Mouse *poMouse;

		//TODO: clean this up
		bool keyPressed;
		Keyboard::Key key1 = Keyboard::KEY_1;	//mouse walk -> run
		Keyboard::Key key2 = Keyboard::KEY_2;	//mouse run -> flip

		Keyboard::Key key0 = Keyboard::KEY_0;	//reset mouse to orig anim

	};

}

#endif

// --- End of File ---
