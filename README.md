# OpenGL_Engine
## Description
A game engine prototype using custom set of static libraries, a conversion tool, and OpenGL. 
## Demos
The engine has 3 predefined demos. The demos can be activated by setting the #define value to true in the Game.cpp file. 
```cpp
#define DEMO1 1
#define DEMO2 0
#define DEMO3 0
```
1. Demo 1: 2D Sprite and Font system
2. Demo 2: 3D System
3. Demo 3: Skinned Animations

## Instructions
1. Download converted data from google drive: https://drive.google.com/drive/folders/1OyBEGHnjmBhas2M6Qef55FK0_YezYSsy?usp=sharing
2. Place converted data into OpenGL\Data folder.
3. Open project solution, set desired demo to true, and Run.

## Documentation
### Table of Contents
* [Engine Loop](#engine-loop)
* [Camera](#camera)
* [Shader Objects](#shader-objects)
* [Game Objects](#game-objects)
* [Graphics Objects](#graphics-objects)
* [Models](#models)
* [Animation](#animation)

#### Engine Loop
Upon startup, a Game Manager singleton creates an instance of the Game. The Game class in turn instantiates the Engine singleton class. The Game instance loads all relevant content through various singleton Managers (textures, game objects, animation, etc). The Engine class loops to update and draw all game events. Once the user exits, the content is cleanly unloaded by their respective singleton Managers.
```cpp
void Engine::Run()
{
  this->privInitialize();          // set up window and OpenGL
  Initialize();                    // virtual, Game side initializes content
  this->privPreLoadContent();
  setVsync(true);                  // force graphics to wait for vSync
  LoadContent();                   // virtual, Game side loads content

  while((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) && (glfwWindowShouldClose(window) != GL_TRUE))
  {
    Update((float)glfwGetTime());  // virtual, game move objects
    ClearBufferFunct();            // clear screen
    Draw();                        // virtual, render objects

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  // exiting game, now clean up
  UnloadContent();

  glfwDestroyWindow(window);
  glfwTerminate();
}
```
### Camera
Engine allows for the use of multiple cameras; all cameras are created and managed through managers.
1. Orthogrpahic (Camera 2D)<br>
>```cpp
>void Game::LoadContent()
>{
>  // Singleton Manager is loaded by Game
>  Camera2DMan::Create();
>}
>
>void Demo1::Load()
>{
>  // Setup camera for specific demo
>  Camera2D* pCam1 = Camera2DMan::Add(Camera::Name::CAMERA_1);
>  pCam1->SetViewport(0, 0, width, height);
>  pCam1->SetOrthographic((float)-pCam1->GetScreenWidth() / 2.0f, (float)pCam1->GetScreenWidth() / 2.0f,
>    (float)-pCam1->GetScreenHeight() / 2.0f, (float)pCam1->GetScreenHeight() / 2.0f, 1.0f, 1000.0f);
>  pCam1->SetOrient_Pos(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 0.0f, 2.0f));
>  pCam1->UpdateCamera();
>  Camera2DMan::SetCurrCam(pCam1);
>}
>```
2. Perspective (Camera 3D)<br>
>```cpp
>void Game::LoadContent()
>{
>  // Singleton Manager is loaded by Game
>  Camera3DMan::Create();
>}
>
>void Demo4::Load()
>{
>  // Camera Setup
>  Camera3D* pCam0 = Camera3DMan::Add(Camera::Name::CAMERA_0);
>  pCam0->SetViewport(0, 0, width, height);
>  pCam0->SetPerspective(35.0f, float(pCam0->GetScreenWidth()) / float(pCam0->GetScreenHeight()), 1.0f, 10000.0f);
>  pCam0->SetOrient_Pos(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 8.0f));
>  pCam0->UpdateCamera();
>  Camera3DMan::SetCurrCam(pCam0);
>}
>```
### Shader Objects
Shaders are loaded into the engine upon startup and associated with Graphics Objects that utilize them for render. This engine utilizes both graphic and compute shaders. 
>```cpp
>void Game::LoadContent()
>{
>  // Singleton Manager is loaded by Game
>  ShaderMan::Create();
>
>  // Read in shaders and create object
>  ShaderObj* pSpriteShader = new ShaderGraphics(ShaderObj::Name::SPRITE, "sprite");
>  ShaderMan::Add(pWireframeShader);
>
>  ShaderObj* pSkinShader = new ShaderGraphics(ShaderObj::Name::SKIN_TEXTURE, "skinTexture");
>  ShaderMan::Add(pSkinShader);
>
>  ShaderObj* pComputeMixer = new ShaderCompute(ShaderObj::Name::COMPUTE_MIXER, "mixer");
>  ShaderMan::Add(pComputeMixer);
>}
>
>void Demo1::Load()
>{
>  // Load Sprites Graphic Object
>  GraphicsObj_Sprite* pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSMWalking0, Rect(250, 1550, 54, 65));
>  GameObj2D* pSMWalkObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
>  pSMWalkObj->SetName("SM_Walk");
>  pSMWalkObj->SetScale(6.5f, 6.5f);
>  GameObjMan::Add(pSMWalkObj, pMainBatch);
>}
>```
### Game Objects
All active objects in a scene are represented as a Game Object. The Game Object holds reference to its graphical counter part (Graphics Object). A Game Object can be considered as 2D or 3D object. 3D Game Objects can further be broken down into dynamic (animated) objects or rigid (static) objects.
1. 2D Game Objects
>2D objects (Sprites) are created and associated to a batch to allow for layered rendering.
>```cpp
>void Demo::Load()
>{
>  // Create a batch for text and main sprites
>  GameObj_SpriteBatch* pTextBatch = new GameObj_SpriteBatch(GameObj2D::Name::TextBatch);
>  pTextBatch->SetName("TextBatch");
>  GameObjMan::Add(pTextBatch, GameObjMan::GetRoot());
>
>  GameObj_SpriteBatch* pMainBatch = new GameObj_SpriteBatch(GameObj2D::Name::MainBatch);
>  pMainBatch->SetName("MainBatch");
>  GameObjMan::Add(pMainBatch, GameObjMan::GetRoot());
>
>  // Create Font Objects
>  GraphicsObj_Font* pGraphicsFont = new GraphicsObj_Font(pSprite, pSpriteShader);
>  GameObj2D* pConsolasText = new GameObj2D(GameObj2D::Name::TextBatch, pGraphicsFont);
>  GameObjMan::Add(pConsolasText, pTextBatch);
>  FontMan::Add(pGraphicsFont, FontName::Demo1A, Glyph::Name::CONSOLAS36PT, "Consolas Font : 36pt", 1900, 525);
>
>  // Create Sprite Objects
>  GraphicsObj_Sprite* pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSMWalking0, Rect(250, 1550, 54, 65));
>  GameObj2D* pSMWalkObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
>  pSMWalkObj->SetName("SM_Walk");
>  pSMWalkObj->SetScale(6.5f, 6.5f);
>  GameObjMan::Add(pSMWalkObj, pMainBatch);
>}
>```  
2. 3D Game Objects
### Graphics Objects
### Models
### Animation
