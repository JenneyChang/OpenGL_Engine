//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"

#include "InputMan.h"
#include "Camera3DMan.h"
#include "Camera2DMan.h"
#include "GameObjMan.h"
#include "MeshNodeMan.h"
#include "ShaderMan.h"
#include "ShaderGraphics.h"
#include "ShaderCompute.h"
#include "TextureMan.h"
#include "ImageMan.h"
#include "GlyphMan.h"
#include "FontMan.h"
#include "AnimMan.h"
#include "SkeletonMan.h"
#include "ClipMan.h"
#include "TimerEventMan.h"
#include "SceneMan.h"

#include "Demo1.h"
#include "Demo3.h"
#include "Demo4.h"
#include "Demo5.h"

using namespace Azul;

#define DEMO1 0
#define DEMO2 0
#define DEMO3 1

Scene* pDemo = nullptr;


//-----------------------------------------------------------------------------
//  Game::Game()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
Game::Game(const char *const pWindowName, const int Width, const int Height)
	:Engine(pWindowName, Width, Height)
{
	assert(pWindowName);
	this->globalTimer.Tic();
	this->intervalTimer.Tic();
}


//-----------------------------------------------------------------------------
//  Game::~Game()
//		Game Engine destructor
//-----------------------------------------------------------------------------
Game::~Game()
{ }


//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{ }


//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{
	//LOAD MANAGERS------------------------------------------------------------
	{
		InputMan::Create();
		Camera3DMan::Create();
		Camera2DMan::Create();
		ShaderMan::Create();
		TextureMan::Create();
		ImageMan::Create();
		GlyphMan::Create();
		FontMan::Create();
		MeshNodeMan::Create();
		GameObjMan::Create();
		ClipMan::Create();
		SkeletonMan::Create();
		AnimMan::Create();
		TimerEventMan::Create();
		SceneMan::Create();
	}


	//CREATE & LOAD SHADERS----------------------------------------------------
	{
		//2D shader
		ShaderObj* pSpriteShader = new ShaderGraphics(ShaderObj::Name::SPRITE, "sprite");
		ShaderMan::Add(pSpriteShader);

		//3D shaders
		ShaderObj* pWireframeShader = new ShaderGraphics(ShaderObj::Name::WIREFRAME, "wireframe");
		ShaderMan::Add(pWireframeShader);

		ShaderObj* pTextureShader = new ShaderGraphics(ShaderObj::Name::TEXTURE, "texture");
		ShaderMan::Add(pTextureShader);

		ShaderObj* pSkinShader = new ShaderGraphics(ShaderObj::Name::SKIN_TEXTURE, "skinTexture");
		ShaderMan::Add(pSkinShader);


		//Compute shaders
		ShaderObj* pComputeMixer = new ShaderCompute(ShaderObj::Name::COMPUTE_MIXER, "mixer");
		ShaderMan::Add(pComputeMixer);

		ShaderObj* pComputeWorld = new ShaderCompute(ShaderObj::Name::COMPUTE_WORLD, "worldMatrix");
		ShaderMan::Add(pComputeWorld);
	}


	//LOAD TEXTURES------------------------------------------------------------
	TextureMan::Add("Data\\HotPink_tex.proto.azul", Texture::Name::HOTPINK);


#if DEMO1 
	// 2D System (Fonts & Sprites)
	pDemo = new Demo1(info.windowWidth, info.windowHeight);
	SceneMan::SetScene(pDemo);
#elif DEMO2
	// 3D System
	pDemo = new Demo3(info.windowWidth, info.windowHeight);
	SceneMan::SetScene(pDemo);
#elif DEMO3
	// Skinned Animations
	pDemo = new Demo4(info.windowWidth, info.windowHeight);
	SceneMan::SetScene(pDemo);
#else
	// Animation Transitions
	pDemo = new Demo5(info.windowWidth, info.windowHeight);
	SceneMan::SetScene(pDemo);
#endif // DEMO1 1
	
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------

//int count = 0;
void Game::Update(float )
{
	// Timer update
	this->intervalTimer.Toc(); 
	this->intervalTimer.Tic(); 

	Scene* pScene = SceneMan::GetScene();
	pScene->Update();

	TimerEventMan::Update(globalTimer.Toc());

	// Animate Models
	AnimMan::Update();

	// Update Game Objs
	GameObjMan::Update(this->globalTimer.Toc());
}


//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{
	// Render Graphics objs
	GameObjMan::Draw();
}


//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	delete pDemo;

	InputMan::Destroy();
	Camera3DMan::Destroy();
	Camera2DMan::Destroy();
	ShaderMan::Destroy();
	TextureMan::Destroy();
	ImageMan::Destroy();
	GlyphMan::Destroy();
	FontMan::Destroy();
	MeshNodeMan::Destroy();
	GameObjMan::Destroy();
	ClipMan::Destroy();
	SkeletonMan::Destroy();
	AnimMan::Destroy();
	TimerEventMan::Destroy();
}


//------------------------------------------------------------------
// Game::ClearBufferFunc()
// Allows user to change the way the clear buffer function works
//------------------------------------------------------------------
void Game::ClearBufferFunc()
{
#ifdef _DEBUG	
	const GLfloat color[] = { 0.2f, 0.2f, 0.2f, 1.0f };
#else
	const GLfloat color[] = { 0.85f, 0.7f, 0.7f, 1.0f };
#endif
	const GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, color);
	glClearBufferfv(GL_DEPTH, 0, &one);
}


// --- End of File ---
