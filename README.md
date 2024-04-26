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
>
>void Game::UnloadContent()
>{
>  // Manager removes and deletes all objects contained in its pool
>  Camera3DMan::Destroy();
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
>* Rigid Objects
>>```cpp
>>void Demo3::Load()
>>{
>>  // Loads a Crate Rigid Object
>>  GraphicsObj3D* pGraphicsObj = new GraphicsObj_Texture(pCrateMesh, pTextureShader, pCrateTex);
>>  GameObj_Rigid* pCrateObj = new GameObj_Rigid(pGraphicsObj);
>>  pCrateObj->SetName("Crate3D");
>>  pCrateObj->SetScale(0.35f, 0.35f, 0.35f);
>>  pCrateObj->SetDeltaY(0.003f);
>>  pCrateObj->SetTrans(-2.7f, 1.9f, 0.0f);
>>  GameObjMan::Add(pCrateObj, GameObjMan::GetRoot());
>>}
>>```
>* Dynamic Objects
>>```cpp
>>void Skeleton::SetHierarchy(SSBO* pSSBOIn, Mesh* mesh, Vec3 lightPos, Vec4 lightColor, Vec3 scale, Vec3 trans, Quat rot)
>>{
>>  // Set object pivot node (root)
>>  // (1) grab related shaders
>>  ShaderObj* pNullShader = ShaderMan::Find(ShaderObj::Name::NULL_SHADER);
>>  ShaderObj* pSkinShader = ShaderMan::Find(ShaderObj::Name::SKIN_TEXTURE);
>>  ShaderObj* pWireframeShader = ShaderMan::Find(ShaderObj::Name::WIREFRAME);
>>
>>  // (2) define game object
>>  Mesh* pNullMesh = MeshNodeMan::Find(Mesh::Name::NULL_MESH);
>>  GraphicsObj3D* pGraphicsObj = new GraphicsObj_Null3D(pNullMesh, pNullShader);
>>  GameObj_Rigid* pPivot = new GameObj_Rigid(pGraphicsObj);
>>  pPivot->SetScale(scale);
>>  pPivot->SetTrans(trans);
>>  pPivot->SetRot(rot);
>>  GameObjMan::Add(pPivot, GameObjMan::GetRoot());
>>
>>  // Set associated skinned object
>>  GraphicsObj_Skin* pGraphicsSkin = new GraphicsObj_Skin(mesh, pSkinShader, ((ProtoMesh*)mesh)->GetTexture(), pPivot, lightColor, lightPos);
>>  GameObj_Skin* pGameObjSkin = new GameObj_Skin(pGraphicsSkin, this, this->numJoints, pSSBOIn);
>>  pGraphicsSkin->SetSSBOWorldResult(pGameObjSkin->GetSSBOWorldResult());
>>  GameObjMan::Add(pGameObjSkin, pPivot);
>>}
>>```
### Graphics Objects
Engine allows for a set of 2D and 3D graphical objects. Graphical Objects hold information on relevant mesh, texture, colors, and shader resources.
1. Graphics Object 2D
>* Sprites
>* Font
2. Graphics Object 3D
>* Wireframe
>* Texture
>* Skin

>  Code Snippet
>  ```cpp
>  void Demo1::Load()
>  {
>    // Sprite Shader
>    ShaderObj* pSpriteShader = ShaderMan::Find(ShaderObj::Name::SPRITE);
>
>    // Mesh loaded from file
>    ProtoMesh* pSprite = new ProtoMesh("Data\\sprite.proto.azul");
>    MeshNodeMan::Add(Mesh::Name::SPRITE, pSprite);
>
>    // Loaded Texture
>    Texture* pAlienTex = TextureMan::Add("Data\\Aliens_tex.proto.azul", Texture::Name::ALIENS);
>
>    // Create image from texture
>    Image* pSquid0 = ImageMan::Add(Image::Name::SQUID_OPEN, pAlienTex, Rect(370, 200, 60, 65));
>
>    // Tie created data to graphical object
>    GraphicsObj_Sprite* pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSquid0, Rect(2250, 150, 80, 65));
>  }
>  ```
### Animation
1. Sprite Animations
>* Sprites are animated by creating a animate sprite command and associating the command to a timer event.
>* The timer event determines the rate of image swaps for the sprites.
>```cpp
>void Demo1::Load()
>{
>  AnimTime delta = AnimTime(AnimTime::Duration::ONE_SECOND) * 0.5f;
>  AnimateSprite* pCrabAnim = new AnimateSprite(pCrabObj, TimerEvent::Name::CRAB);
>  pCrabAnim->AttachImage(pCrab1);
>  pCrabAnim->AttachImage(pCrab0);
>  TimerEventMan::Add(TimerEvent::Name::CRAB, pCrabAnim, delta);
>}
>```
2. Skinned Animations
>* Composed of a character skeleton, clips, and an anim object.
>> Anim object ties the skeleton and clip information together, essentially linking them to a Game Object.
>  ```cpp
>  void Demo4::Load()
>  {
>    // Load in converted Model data
>    Mesh* pMouseyMesh = new ProtoMesh("Data\\Mouse_JoyfulJump.proto.azul", pMouseyTex);
>    MeshNodeMan::Add(Mesh::Name::MOUSEY, pMouseyMesh);
>
>    // Load in skeleton and clip
>    SkeletonMan::Add(Skeleton::Name::MOUSEY, "Data\\Mouse_JoyfulJump_skel.proto.azul");
>    ClipMan::Add(Clip::Name::MOUSEY_JUMP, "Data\\Mouse_JoyfulJump_anim.proto.azul");
>
>    // Create Anim object and associate skeleton and clip
>    Anim* pMouseyAnim = AnimMan::Add(Anim::Name::MOUSEY, Clip::Name::MOUSEY_JUMP, Skeleton::Name::MOUSEY);
>    pMouseyAnim->LinkAnim(Mesh::Name::MOUSEY, Vec3(-2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(-2.9f, 1.3f, 0.0f));
>  }
>  ```
>* Skeleton holds a table of joints and their depth within the skeletal hierarchy.
>> hierarchy table is passed as a SSBO (shader storage buffer objects) and stored on the GPU
>* A clip has a duration and a list of frames which specify the orientation of skeletal joints at a time t.
>> frames are loaded in and stored in SSBO on the GPU
>>  ```cpp
>>  void Clip::Set(Clip::Name _name, clip_proto& cproto, int numjoints)
>>  {
>>    //...
>>
>>    // Load frames from proto file
>>    Joint* poJoint = new Joint[numJoints]();
>>
>>    Frames* curr = nullptr;
>>    Frames* prev = nullptr;
>>    for (size_t i = 0; i < (unsigned int)numFrames; ++i)
>>    {
>>      // grab 1 frame from file
>>      auto& f = cproto.frames[i];
>>      if (this->poHead == nullptr)
>>      {
>>          // case: empty list
>>          // create new frame and add to list
>>          curr = new Frames();
>>          curr->keytime = f.keytime * AnimTime(AnimTime::Duration::FILM_24_FRAME);
>>          curr->poSSBO_Joints = new SSBO();
>>
>>          this->poHead = curr;
>>          prev = curr;	
>>      }
>>      else
>>      {
>>        // add to end of list
>>      }
>>
>>      // grab joint (bone) data for each frame
>>      for (size_t j = 0; j < numJoints; ++j)
>>      {
>>        auto& b = cproto.frames[i].bones[j];
>>        poJoint[j].Trans.set(b.trans.x, b.trans.y, b.trans.z);
>>			  poJoint[j].Rot.set(b.rot.x, b.rot.y, b.rot.z, b.rot.w);
>>			  poJoint[j].Scale.set(b.scale.x, b.scale.y, b.scale.z);
>>      }
>>
>>      // pass list to GPU
>>      prev->poSSBO_Joints->Set(numJoints, sizeof(Joint), poJoint);
>>    }
>>    delete[] poJoint;
>>  }
>>  ```
>> frames are interpolated using compute shader called COMPUTE_MIXER on the GPU
>>  ```cpp
>>  void Mixer::Blend(SSBO* pSSBOIn, SSBO* pA, SSBO* pB, const float ts, const int numJoints)
>>  {
>>    // Grab compute shader for blending
>>    ShaderObj* pComputeMixer = ShaderMan::Find(ShaderObj::Name::COMPUTE_MIXER);
>>    pComputeMixer->SetActive();
>>
>>    // Bind relevant input frame data and output buffer
>>    pA->Bind(0);
>>	  pB->Bind(1);
>>	  pSSBOIn->Bind(2);
>>
>>    // Set uniforms
>>    glUniform1f(pComputeMixer->GetLocation("ts"), ts);
>>    glUniform1i(pComputeMixer->GetLocation("numJoints"), numJoints);
>>  
>>    // Dispatch Shader and set sync barrier
>>    ((ShaderCompute*)pComputeMixer)->Dispatch((unsigned int)numJoints/8, 1, 1);
>>    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
>>  }
>>  ```

