#include "Demo1.h"
#include "Camera2DMan.h"
#include "MeshNodeMan.h"
#include "ProtoMesh.h"
#include "GameObjMan.h"
#include "GlyphMan.h"
#include "FontMan.h"
#include "GraphicsObj_Font.h"
#include "GraphicsObj_Sprite.h"
#include "TextureMan.h"
#include "ImageMan.h"
#include "AnimateSprite.h"
#include "TimerEventMan.h"
#include "GameObj_SpriteBatch.h"

#include "ShaderMan.h"
#include "GameObj2D.h"
#include "AnimateSprite.h"

Demo1::Demo1(const int w, const int h)
	: width(w), height(h)
{ }

Demo1::~Demo1()
{ }


void Demo1::Load()	 
{
	//CAMERA SETUP-------------------------------------------------------------
	Camera2D* pCam1 = Camera2DMan::Add(Camera::Name::CAMERA_1);
	pCam1->SetViewport(0, 0, width, height);
	pCam1->SetOrthographic((float)-pCam1->GetScreenWidth() / 2.0f, (float)pCam1->GetScreenWidth() / 2.0f,
		(float)-pCam1->GetScreenHeight() / 2.0f, (float)pCam1->GetScreenHeight() / 2.0f, 1.0f, 1000.0f);
	pCam1->SetOrient_Pos(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 0.0f, 2.0f));
	pCam1->UpdateCamera();
	Camera2DMan::SetCurrCam(pCam1);


	//GRAB SHADERS-------------------------------------------------------------
	ShaderObj* pSpriteShader = ShaderMan::Find(ShaderObj::Name::SPRITE);
	assert(pSpriteShader);


	//LOAD MESH----------------------------------------------------------------
	ProtoMesh* pSprite = new ProtoMesh("Data\\sprite.proto.azul");
	MeshNodeMan::Add(Mesh::Name::SPRITE, pSprite);


	//LOAD TEXTURE---------------------------------------------------------------
	Texture* pAlienTex = TextureMan::Add("Data\\Aliens_tex.proto.azul", Texture::Name::ALIENS);
	Texture* pMoonTex = TextureMan::Add("Data\\SailorMoon_tex.proto.azul", Texture::Name::SAILORMOON);
	Texture* pVegaTex = TextureMan::Add("Data\\Vega0_tex.proto.azul", Texture::Name::SFVEGA);
	Texture* pLinkTex = TextureMan::Add("Data\\Link0_tex.proto.azul", Texture::Name::LINK);
	Texture* pLink1Tex = TextureMan::Add("Data\\Link1_tex.proto.azul", Texture::Name::LINK1);


	//LOAD IMAGE----------------------------------------------------------------
	// Space Invaders
	Image* pSquid0 = ImageMan::Add(Image::Name::SQUID_OPEN, pAlienTex, Rect(370, 200, 60, 65));
	Image* pSquid1 = ImageMan::Add(Image::Name::SQUID_CLOSED, pAlienTex, Rect(456, 200, 60, 65));
	Image* pCrab0 = ImageMan::Add(Image::Name::CRAB_OPEN, pAlienTex, Rect(25, 334, 80, 65));
	Image* pCrab1 = ImageMan::Add(Image::Name::CRAB_OPEN, pAlienTex, Rect(135, 334, 80, 66));
	Image* pOctopus0 = ImageMan::Add(Image::Name::OCTOPUS_OPEN, pAlienTex, Rect(245, 335, 70, 70));
	Image* pOctopus1 = ImageMan::Add(Image::Name::OCTOPUS_OPEN, pAlienTex, Rect(339, 335, 68, 68));


	// Sailor Moon Images
	Image* pSMWalking0 = ImageMan::Add(Image::Name::SM_WALKING0, pMoonTex, Rect(7, 94, 54, 65));
	Image* pSMWalking1 = ImageMan::Add(Image::Name::SM_WALKING1, pMoonTex, Rect(88, 95, 54, 67));
	Image* pSMWalking2 = ImageMan::Add(Image::Name::SM_WALKING2, pMoonTex, Rect(166, 94, 56, 69));
	Image* pSMWalking4 = ImageMan::Add(Image::Name::SM_WALKING4, pMoonTex, Rect(328, 94, 54, 67));
	Image* pSMWalking5 = ImageMan::Add(Image::Name::SM_WALKING5, pMoonTex, Rect(408, 94, 54, 67));
	Image* pSMWalking7 = ImageMan::Add(Image::Name::SM_WALKING7, pMoonTex, Rect(567, 94, 54, 67));

	Image* pSMRunning0 = ImageMan::Add(Image::Name::SM_RUNNING0, pMoonTex, Rect(1, 574, 64, 63));
	Image* pSMRunning1 = ImageMan::Add(Image::Name::SM_RUNNING1, pMoonTex, Rect(82, 574, 64, 63));
	Image* pSMRunning2 = ImageMan::Add(Image::Name::SM_RUNNING2, pMoonTex, Rect(161, 577, 64, 63));
	Image* pSMRunning4 = ImageMan::Add(Image::Name::SM_RUNNING4, pMoonTex, Rect(338, 575, 64, 63));
	Image* pSMRunning5 = ImageMan::Add(Image::Name::SM_RUNNING5, pMoonTex, Rect(417, 575, 64, 63));

	Image* pSMPogo0 = ImageMan::Add(Image::Name::SM_POGOSTICK0, pMoonTex, Rect(288, 671, 60, 84));
	Image* pSMPogo1 = ImageMan::Add(Image::Name::SM_POGOSTICK1, pMoonTex, Rect(367, 671, 60, 84));
	Image* pSMPogo2 = ImageMan::Add(Image::Name::SM_POGOSTICK2, pMoonTex, Rect(446, 671, 60, 84));

	Image* pSMJump0 = ImageMan::Add(Image::Name::SM_JUMPING0, pMoonTex, Rect(419, 870, 66, 70));
	Image* pSMJump1 = ImageMan::Add(Image::Name::SM_JUMPING1, pMoonTex, Rect(497, 870, 66, 75));
	Image* pSMJump2 = ImageMan::Add(Image::Name::SM_JUMPING2, pMoonTex, Rect(563, 870, 66, 70));
	Image* pSMJump3 = ImageMan::Add(Image::Name::SM_JUMPING3, pMoonTex, Rect(658, 870, 75, 70));

	Image* pSMFall0 = ImageMan::Add(Image::Name::SM_FALLING0, pMoonTex, Rect(3, 1213, 80, 75));
	Image* pSMFall1 = ImageMan::Add(Image::Name::SM_FALLING1, pMoonTex, Rect(96, 1213, 80, 75));
	Image* pSMFall2 = ImageMan::Add(Image::Name::SM_FALLING2, pMoonTex, Rect(193, 1213, 80, 75));
	Image* pSMFall3 = ImageMan::Add(Image::Name::SM_FALLING3, pMoonTex, Rect(289, 1213, 80, 75));
	Image* pSMFall4 = ImageMan::Add(Image::Name::SM_FALLING4, pMoonTex, Rect(380, 1213, 80, 75));
	Image* pSMFall5 = ImageMan::Add(Image::Name::SM_FALLING5, pMoonTex, Rect(472, 1213, 80, 75));

	Image* pSMDice0 = ImageMan::Add(Image::Name::SM_DICE0, pMoonTex, Rect(0, 298, 64, 67));
	Image* pSMDice1 = ImageMan::Add(Image::Name::SM_DICE1, pMoonTex, Rect(85, 288, 64, 67));
	Image* pSMDice2 = ImageMan::Add(Image::Name::SM_DICE2, pMoonTex, Rect(170, 289, 70, 67));
	Image* pSMDice3 = ImageMan::Add(Image::Name::SM_DICE3, pMoonTex, Rect(263, 283, 70, 67));


	// Street Fighter: Vega
	Image* pSFKick0 = ImageMan::Add(Image::Name::SF_KICK0, pVegaTex, Rect(15, 891, 92, 64));
	Image* pSFKick1= ImageMan::Add(Image::Name::SF_KICK1, pVegaTex, Rect(106, 891, 88, 64));
	Image* pSFKick2= ImageMan::Add(Image::Name::SF_KICK2, pVegaTex, Rect(186, 891, 99, 64));
	Image* pSFKick3= ImageMan::Add(Image::Name::SF_KICK3, pVegaTex, Rect(282, 891, 126, 64));

	Image* pSFStab0 = ImageMan::Add(Image::Name::SF_STAB0, pVegaTex, Rect(0, 519, 87, 105));
	Image* pSFStab1 = ImageMan::Add(Image::Name::SF_STAB1, pVegaTex, Rect(86, 519, 96, 105));
	Image* pSFStab2 = ImageMan::Add(Image::Name::SF_STAB2, pVegaTex, Rect(182, 519, 150, 105));
	Image* pSFStab3 = ImageMan::Add(Image::Name::SF_STAB3, pVegaTex, Rect(335, 519, 95, 105));
	Image* pSFStab4 = ImageMan::Add(Image::Name::SF_STAB4, pVegaTex, Rect(424, 519, 95, 105));

	Image* pSFIdle0 = ImageMan::Add(Image::Name::SF_IDLE0, pVegaTex, Rect(10, 370, 75, 112));
	Image* pSFIdle1 = ImageMan::Add(Image::Name::SF_IDLE1, pVegaTex, Rect(84, 370, 75, 112));
	Image* pSFIdle2 = ImageMan::Add(Image::Name::SF_IDLE2, pVegaTex, Rect(160, 370, 75, 112));
	Image* pSFIdle3 = ImageMan::Add(Image::Name::SF_IDLE3, pVegaTex, Rect(240, 370, 75, 112));
	Image* pSFIdle4 = ImageMan::Add(Image::Name::SF_IDLE4, pVegaTex, Rect(315, 370, 75, 112));
	Image* pSFIdle5 = ImageMan::Add(Image::Name::SF_IDLE5, pVegaTex, Rect(394, 370, 75, 112));

	// Zelda Link
	Image* pLWalk0 = ImageMan::Add(Image::Name::LWALK0, pLinkTex, Rect(51, 49, 25, 25));
	Image* pLWalk1 = ImageMan::Add(Image::Name::LWALK1, pLinkTex, Rect(78, 49, 25, 25));
	Image* pLWalk2 = ImageMan::Add(Image::Name::LWALK2, pLinkTex, Rect(103, 47, 25, 25));
	Image* pLWalk3 = ImageMan::Add(Image::Name::LWALK3, pLinkTex, Rect(130, 47, 25, 25));
	Image* pLWalk4 = ImageMan::Add(Image::Name::LWALK4, pLinkTex, Rect(155, 47, 25, 25));
	Image* pLWalk5 = ImageMan::Add(Image::Name::LWALK5, pLinkTex, Rect(188, 47, 25, 25));
	Image* pLWalk6 = ImageMan::Add(Image::Name::LWALK6, pLinkTex, Rect(215, 47, 25, 25));
	Image* pLWalk7 = ImageMan::Add(Image::Name::LWALK7, pLinkTex, Rect(240, 47, 25, 25));
	Image* pLWalk8 = ImageMan::Add(Image::Name::LWALK8, pLinkTex, Rect(266, 47, 25, 25));
	Image* pLWalk9 = ImageMan::Add(Image::Name::LWALK9, pLinkTex, Rect(289, 47, 25, 25));

	Image* pLSwing0 = ImageMan::Add(Image::Name::LSWING0, pLink1Tex, Rect(0, 0, 35, 60));
	Image* pLSwing1 = ImageMan::Add(Image::Name::LSWING1, pLink1Tex, Rect(33, 0, 34, 60));
	Image* pLSwing2 = ImageMan::Add(Image::Name::LSWING2, pLink1Tex, Rect(67, 0, 39, 60));
	Image* pLSwing3 = ImageMan::Add(Image::Name::LSWING3, pLink1Tex, Rect(110, 0, 35, 60));
	Image* pLSwing4 = ImageMan::Add(Image::Name::LSWING4, pLink1Tex, Rect(147, 0, 35, 60));
	Image* pLSwing5 = ImageMan::Add(Image::Name::LSWING5, pLink1Tex, Rect(188, 0, 40, 60));
	Image* pLSwing6 = ImageMan::Add(Image::Name::LSWING6, pLink1Tex, Rect(237, 0, 35, 60));
	Image* pLSwing7 = ImageMan::Add(Image::Name::LSWING7, pLink1Tex, Rect(279, 0, 35, 60));
	Image* pLSwing8 = ImageMan::Add(Image::Name::LSWING8, pLink1Tex, Rect(322, 0, 41, 60));
	Image* pLSwing9 = ImageMan::Add(Image::Name::LSWING9, pLink1Tex, Rect(371, 0, 35, 60));
	Image* pLSwing10 = ImageMan::Add(Image::Name::LSWING10, pLink1Tex, Rect(413, 0, 35, 60));
	Image* pLSwing11 = ImageMan::Add(Image::Name::LSWING11, pLink1Tex, Rect(454, 0, 35, 60));
	Image* pLSwing12 = ImageMan::Add(Image::Name::LSWING12, pLink1Tex, Rect(491, 0, 33, 60));


	//LOAD FONTS----------------------------------------------------------------
	GlyphMan::Add(Glyph::Name::CONSOLAS36PT, "Data\\Consolas36pt_font.proto.azul", Texture::Name::CONSOLAS36PT);
	GlyphMan::Add(Glyph::Name::CAIYUN_80PT, "Data\\StCaiyun80pt_font.proto.azul", Texture::Name::CAIYUN);
	GlyphMan::Add(Glyph::Name::COMICSANS_55PT, "Data\\ComicSans55pt_font.proto.azul", Texture::Name::COMICSANS);
	GlyphMan::Add(Glyph::Name::MAGNETO_45PT, "Data\\Magneto45pt_font.proto.azul", Texture::Name::MAGNETO);


	//LOAD SPRITE BATCH---------------------------------------------------------
	GameObj_SpriteBatch* pTextBatch = new GameObj_SpriteBatch(GameObj2D::Name::TextBatch);
	pTextBatch->SetName("TextBatch");
	GameObjMan::Add(pTextBatch, GameObjMan::GetRoot());

	GameObj_SpriteBatch* pMainBatch = new GameObj_SpriteBatch(GameObj2D::Name::MainBatch);
	pMainBatch->SetName("MainBatch");
	GameObjMan::Add(pMainBatch, GameObjMan::GetRoot());


	//ADD FONT OBJECTS---------------------------------------------------------
	GraphicsObj_Font* pGraphicsFont = nullptr;

	//pGraphicsFont = new GraphicsObj_Font(pSprite, pSpriteShader);
	//GameObj2D* pAnimText = new GameObj2D(GameObj2D::Name::TextBatch, pGraphicsFont);
	//GameObjMan::Add(pAnimText, pTextBatch);
	//FontMan::Add(pGraphicsFont, FontName::Tester, Glyph::Name::CAIYUN_80PT, "2D SYSTEM", 950, 1650);

	pGraphicsFont = new GraphicsObj_Font(pSprite, pSpriteShader);
	GameObj2D* pConsolasText = new GameObj2D(GameObj2D::Name::TextBatch, pGraphicsFont);
	GameObjMan::Add(pConsolasText, pTextBatch);
	FontMan::Add(pGraphicsFont, FontName::Demo1A, Glyph::Name::CONSOLAS36PT, "Consolas Font : 36pt", 1900, 525);

	pGraphicsFont = new GraphicsObj_Font(pSprite, pSpriteShader);
	GameObj2D* pComicSansText = new GameObj2D(GameObj2D::Name::TextBatch, pGraphicsFont);
	GameObjMan::Add(pComicSansText, pTextBatch);
	FontMan::Add(pGraphicsFont, FontName::Demo1B, Glyph::Name::COMICSANS_55PT, "Comic Sans Font : 55pt", 1810, 450);

	pGraphicsFont = new GraphicsObj_Font(pSprite, pSpriteShader);
	GameObj2D* pMagnetoText = new GameObj2D(GameObj2D::Name::TextBatch, pGraphicsFont);
	GameObjMan::Add(pMagnetoText, pTextBatch);
	FontMan::Add(pGraphicsFont, FontName::Demo1C, Glyph::Name::MAGNETO_45PT, "Magneto Font : 45pt", 1810, 375);

	pGraphicsFont = new GraphicsObj_Font(pSprite, pSpriteShader);
	GameObj2D* pCaiyunText = new GameObj2D(GameObj2D::Name::TextBatch, pGraphicsFont);
	GameObjMan::Add(pCaiyunText, pTextBatch);
	FontMan::Add(pGraphicsFont, FontName::Demo1D, Glyph::Name::CAIYUN_80PT, "Caiyun Font : 80pt", 1710, 290);


	//LOAD SPRITES-----------------------------------------------------------
	GraphicsObj_Sprite* pGraphicsSprite = nullptr;

	// Sailor Moon Walking
	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSMWalking0, Rect(250, 1550, 54, 65));
	GameObj2D* pSMWalkObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pSMWalkObj->SetName("SM_Walk");
	pSMWalkObj->SetScale(6.5f, 6.5f);
	GameObjMan::Add(pSMWalkObj, pMainBatch);

	// Sailor Moon Running
	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSMRunning0, Rect(900, 1550, 54, 63));
	GameObj2D* pSMRunObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pSMRunObj->SetName("SM_Run");
	pSMRunObj->SetScale(6.5f, 6.5f);
	GameObjMan::Add(pSMRunObj, pMainBatch);

	// Sailor Moon Jumping
	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSMJump0, Rect(1500, 1550, 57, 59));
	GameObj2D* pSMJumpObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pSMJumpObj->SetName("SM_Jump");
	pSMJumpObj->SetScale(7.5f, 7.5f);
	GameObjMan::Add(pSMJumpObj, pMainBatch);

	// Sailor Moon Sighing
	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSMDice0, Rect(2100, 1550, 55, 67));
	GameObj2D* pSMDiceObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pSMDiceObj->SetName("SM_Dice");
	pSMDiceObj->SetScale(6.5f, 6.5f);
	GameObjMan::Add(pSMDiceObj, pMainBatch);
	
	// Sailor Moon Pogo stick
	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSMPogo2, Rect(400, 970, 60, 82));
	GameObj2D* pSMPogoObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pSMPogoObj->SetName("SM_PogoStick");
	pSMPogoObj->SetScale(6.5f, 6.5f);
	GameObjMan::Add(pSMPogoObj, pMainBatch);

	// Sailor Moon Falling
	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSMFall0, Rect(1100, 970, 73, 64));
	GameObj2D* pSMFallObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pSMFallObj->SetName("SM_Fall");
	pSMFallObj->SetScale(6.5f, 6.5f);
	GameObjMan::Add(pSMFallObj, pMainBatch);

	//Zelda Link
	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pLSwing0, Rect(1650, 970, 25, 30));
	GameObj2D* pLSwingObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pLSwingObj->SetName("Link_Swing");
	pLSwingObj->SetScale(12.5f, 12.5f);
	GameObjMan::Add(pLSwingObj, pMainBatch);

	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pLWalk0, Rect(2150, 970, 25, 25));
	GameObj2D* pLWalkObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pLWalkObj->SetName("Link_Walk");
	pLWalkObj->SetScale(9.5f, 9.5f);
	GameObjMan::Add(pLWalkObj, pMainBatch);

	// Street Fighter Vega Side-kick
	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSFKick0, Rect(300, 370, 92, 64));
	GameObj2D* pSFVegaObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pSFVegaObj->SetName("SF_Vega");
	pSFVegaObj->SetScale(5.5f, 5.5f);
	GameObjMan::Add(pSFVegaObj, pMainBatch);
	
	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSFStab0, Rect(950, 370, 87, 105));
	GameObj2D* pSFVega2Obj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pSFVega2Obj->SetName("SF_Vega2");
	pSFVega2Obj->SetScale(5.5f, 5.5f);
	GameObjMan::Add(pSFVega2Obj, pMainBatch);

	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSFIdle0, Rect(1550, 370, 87, 105));
	GameObj2D* pSFVega3Obj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pSFVega3Obj->SetName("SF_Vega3");
	pSFVega3Obj->SetScale(5.0f, 5.0f);
	GameObjMan::Add(pSFVega3Obj, pMainBatch);

	// Space Invaders Crab, Squid, 
	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pCrab0, Rect(1950, 150, 80, 65));
	GameObj2D* pCrabObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pCrabObj->SetName("Alien_Crab");
	pCrabObj->SetScale(2.0f, 2.0f);
	GameObjMan::Add(pCrabObj, pMainBatch);

	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pSquid0, Rect(2250, 150, 80, 65));
	GameObj2D* pSquidObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pSquidObj->SetName("Alien_Squid");
	pSquidObj->SetScale(1.5f, 1.5f);
	pSquidObj->SetAngle(MATH_PI4);
	GameObjMan::Add(pSquidObj, pMainBatch);

	pGraphicsSprite = new GraphicsObj_Sprite(pSprite, pSpriteShader, pOctopus0, Rect(2070, 670, 80, 65));
	GameObj2D* pOctopusObj = new GameObj2D(GameObj2D::Name::MainBatch, pGraphicsSprite);
	pOctopusObj->SetName("Alien_Squid");
	pOctopusObj->SetScale(2.5f, 2.5f);
	GameObjMan::Add(pOctopusObj, pMainBatch);


	//LOAD ANIMATIONS-----------------------------------------------------------
	AnimTime delta;

	// Sailor Moon Walk 
	delta = AnimTime(AnimTime::Duration::ONE_SECOND) * 0.25f;
	AnimateSprite* pSMWalkAnim = new AnimateSprite(pSMWalkObj, TimerEvent::Name::SM_WALKING);
	pSMWalkAnim->AttachImage(pSMWalking7);	
	pSMWalkAnim->AttachImage(pSMWalking5);
	pSMWalkAnim->AttachImage(pSMWalking4);
	pSMWalkAnim->AttachImage(pSMWalking2);
	pSMWalkAnim->AttachImage(pSMWalking1);
	TimerEventMan::Add(TimerEvent::Name::SM_WALKING, pSMWalkAnim, delta);

	// Sailor Moon Run
	delta = AnimTime(AnimTime::Duration::ONE_SECOND) * 0.15f;
	AnimateSprite* pSMRunAnim = new AnimateSprite(pSMRunObj, TimerEvent::Name::SM_RUNNING);
	pSMRunAnim->AttachImage(pSMRunning5);
	pSMRunAnim->AttachImage(pSMRunning4);
	pSMRunAnim->AttachImage(pSMRunning2);
	pSMRunAnim->AttachImage(pSMRunning1);
	pSMRunAnim->AttachImage(pSMRunning0);
	TimerEventMan::Add(TimerEvent::Name::SM_RUNNING, pSMRunAnim, delta);

	// Sailor Moon Pogo
	delta = AnimTime(AnimTime::Duration::ONE_SECOND) * 0.25f;
	AnimateSprite* pSMPogoAnim = new AnimateSprite(pSMPogoObj, TimerEvent::Name::SM_POGO);
	pSMPogoAnim->AttachImage(pSMPogo2);
	pSMPogoAnim->AttachImage(pSMPogo1);
	pSMPogoAnim->AttachImage(pSMPogo0);
	TimerEventMan::Add(TimerEvent::Name::SM_POGO, pSMPogoAnim, delta);

	// Sailor Moon Jump
	delta = AnimTime(AnimTime::Duration::ONE_SECOND) * 0.27f;
	AnimateSprite* pSMJumpAnim = new AnimateSprite(pSMJumpObj, TimerEvent::Name::SM_JUMPING);
	pSMJumpAnim->AttachImage(pSMJump3);
	pSMJumpAnim->AttachImage(pSMJump2);
	pSMJumpAnim->AttachImage(pSMJump1);
	pSMJumpAnim->AttachImage(pSMJump0);
	TimerEventMan::Add(TimerEvent::Name::SM_JUMPING, pSMJumpAnim, delta);

	// Sailor Moon Fall
	delta = AnimTime(AnimTime::Duration::ONE_SECOND) * 0.23f;
	AnimateSprite* pSMFallAnim = new AnimateSprite(pSMFallObj, TimerEvent::Name::SM_FALLING);
	pSMFallAnim->AttachImage(pSMFall5);
	pSMFallAnim->AttachImage(pSMFall4);
	pSMFallAnim->AttachImage(pSMFall3);
	pSMFallAnim->AttachImage(pSMFall2);
	pSMFallAnim->AttachImage(pSMFall1);
	pSMFallAnim->AttachImage(pSMFall0);
	TimerEventMan::Add(TimerEvent::Name::SM_FALLING, pSMFallAnim, delta);

	// Sailor Moon Sigh
	delta = AnimTime(AnimTime::Duration::ONE_SECOND) * 0.3f;
	AnimateSprite* pSMDiceAnim = new AnimateSprite(pSMDiceObj, TimerEvent::Name::SM_SIGH);
	pSMDiceAnim->AttachImage(pSMDice3);
	pSMDiceAnim->AttachImage(pSMDice2);
	pSMDiceAnim->AttachImage(pSMDice1);
	pSMDiceAnim->AttachImage(pSMDice0);
	TimerEventMan::Add(TimerEvent::Name::SM_SIGH, pSMDiceAnim, delta);

	// Street Fighter Vega side kick
	delta = AnimTime(AnimTime::Duration::ONE_SECOND) * 0.2f;
	AnimateSprite* pSFVegaAnim = new AnimateSprite(pSFVegaObj, TimerEvent::Name::VEGA_KICK);
	pSFVegaAnim->AttachImage(pSFKick3);
	pSFVegaAnim->AttachImage(pSFKick2);
	pSFVegaAnim->AttachImage(pSFKick1);
	pSFVegaAnim->AttachImage(pSFKick0);
	TimerEventMan::Add(TimerEvent::Name::VEGA_KICK, pSFVegaAnim, delta);

	AnimateSprite* pSFVega2Anim = new AnimateSprite(pSFVega2Obj, TimerEvent::Name::VEGA_STAB);
	pSFVega2Anim->AttachImage(pSFStab4);
	pSFVega2Anim->AttachImage(pSFStab3);
	pSFVega2Anim->AttachImage(pSFStab2);
	pSFVega2Anim->AttachImage(pSFStab1);
	pSFVega2Anim->AttachImage(pSFStab0);
	TimerEventMan::Add(TimerEvent::Name::VEGA_STAB, pSFVega2Anim, delta);

	AnimateSprite* pSFVega3Anim = new AnimateSprite(pSFVega3Obj, TimerEvent::Name::VEGA_IDLE);
	pSFVega3Anim->AttachImage(pSFIdle0);
	pSFVega3Anim->AttachImage(pSFIdle1);
	pSFVega3Anim->AttachImage(pSFIdle2);
	pSFVega3Anim->AttachImage(pSFIdle3);
	pSFVega3Anim->AttachImage(pSFIdle4);
	pSFVega3Anim->AttachImage(pSFIdle5);
	TimerEventMan::Add(TimerEvent::Name::VEGA_IDLE, pSFVega3Anim, delta);

	//SpaceInvader Crab
	delta = AnimTime(AnimTime::Duration::ONE_SECOND) * 0.5f;
	AnimateSprite* pCrabAnim = new AnimateSprite(pCrabObj, TimerEvent::Name::CRAB);
	pCrabAnim->AttachImage(pCrab1);
	pCrabAnim->AttachImage(pCrab0);
	TimerEventMan::Add(TimerEvent::Name::CRAB, pCrabAnim, delta);

	AnimateSprite* pSquidAnim = new AnimateSprite(pSquidObj, TimerEvent::Name::SQUID);
	pSquidAnim->AttachImage(pSquid1);
	pSquidAnim->AttachImage(pSquid0);
	TimerEventMan::Add(TimerEvent::Name::SQUID, pSquidAnim, delta);

	AnimateSprite* pOctopusAnim = new AnimateSprite(pOctopusObj, TimerEvent::Name::OCTOPUS);
	pOctopusAnim->AttachImage(pOctopus1);
	pOctopusAnim->AttachImage(pOctopus0);
	TimerEventMan::Add(TimerEvent::Name::OCTOPUS, pOctopusAnim, delta);

	// Link Walking
	delta = AnimTime(AnimTime::Duration::ONE_SECOND) * 0.07f;
	AnimateSprite* pLWalkAnim = new AnimateSprite(pLWalkObj, TimerEvent::Name::LWALK);
	pLWalkAnim->AttachImage(pLWalk9);
	pLWalkAnim->AttachImage(pLWalk8);
	pLWalkAnim->AttachImage(pLWalk7);
	pLWalkAnim->AttachImage(pLWalk6);
	pLWalkAnim->AttachImage(pLWalk5);
	pLWalkAnim->AttachImage(pLWalk4);
	pLWalkAnim->AttachImage(pLWalk3);
	pLWalkAnim->AttachImage(pLWalk2);
	pLWalkAnim->AttachImage(pLWalk1);
	pLWalkAnim->AttachImage(pLWalk0);
	TimerEventMan::Add(TimerEvent::Name::LWALK, pLWalkAnim, delta);

	delta = AnimTime(AnimTime::Duration::ONE_SECOND) * 0.1f;
	AnimateSprite* pLSwingAnim = new AnimateSprite(pLSwingObj, TimerEvent::Name::LSWING);
	pLSwingAnim->AttachImage(pLSwing12);
	pLSwingAnim->AttachImage(pLSwing11);
	pLSwingAnim->AttachImage(pLSwing10);
	pLSwingAnim->AttachImage(pLSwing9);
	pLSwingAnim->AttachImage(pLSwing8);
	pLSwingAnim->AttachImage(pLSwing7);
	pLSwingAnim->AttachImage(pLSwing6);
	pLSwingAnim->AttachImage(pLSwing5);
	pLSwingAnim->AttachImage(pLSwing4);
	pLSwingAnim->AttachImage(pLSwing3);
	pLSwingAnim->AttachImage(pLSwing2);
	pLSwingAnim->AttachImage(pLSwing1);
	pLSwingAnim->AttachImage(pLSwing0);
	TimerEventMan::Add(TimerEvent::Name::LSWING, pLSwingAnim, delta);
}

void Demo1::Update() 
{
	Camera* cam = Camera2DMan::GetCurrCam();
	cam->UpdateCamera();
}

void Demo1::Unload() 
{

}
					 