#include "Demo5.h"
#include "InputMan.h"
#include "Camera3DMan.h"
#include "Camera2DMan.h"
#include "ShaderMan.h"
#include "TextureMan.h"
#include "MeshNodeMan.h"
#include "GameObjMan.h"
#include "GlyphMan.h"
#include "FontMan.h"
#include "SkeletonMan.h"
#include "ClipMan.h"
#include "AnimMan.h"

#include "ProtoMesh.h"
#include "GameObj_SpriteBatch.h"


Demo5::Demo5(const int w, const int h)
	: width(w), height(h)
{ }

Demo5::~Demo5()
{ }

void Demo5::Load()	
{
	//CAMERA SETUP-------------------------------------------------------------
	//Camera2D* pCam1 = Camera2DMan::Add(Camera::Name::CAMERA_1);
	//pCam1->SetViewport(0, 0, width, height);
	//pCam1->SetOrthographic((float)-pCam1->GetScreenWidth() / 2.0f, (float)pCam1->GetScreenWidth() / 2.0f,
	//	(float)-pCam1->GetScreenHeight() / 2.0f, (float)pCam1->GetScreenHeight() / 2.0f, 1.0f, 1000.0f);
	//pCam1->SetOrient_Pos(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 0.0f, 2.0f));
	//pCam1->UpdateCamera();
	//Camera2DMan::SetCurrCam(pCam1);

	Camera3D* pCam0 = Camera3DMan::Add(Camera::Name::CAMERA_0);
	pCam0->SetViewport(0, 0, width, height);
	pCam0->SetPerspective(35.0f, float(pCam0->GetScreenWidth()) / float(pCam0->GetScreenHeight()), 1.0f, 10000.0f);
	pCam0->SetOrient_Pos(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 8.0f));
	pCam0->UpdateCamera();
	Camera3DMan::SetCurrCam(pCam0);


	//SHADER -----------------------------------------------------------------
	//ShaderObj* pSpriteShader = ShaderMan::Find(ShaderObj::Name::SPRITE);


	//LOAD TEXTURE---------------------------------------------------------------
	Texture* pMouseyTex = TextureMan::Add("Data\\Mouse_Diffuse_tex.proto.azul", Texture::Name::MOUSEY);


	//LOAD MESH----------------------------------------------------------------
	//ProtoMesh* pSprite = new ProtoMesh("Data\\sprite.proto.azul");
	//MeshNodeMan::Add(Mesh::Name::SPRITE, pSprite);

	Mesh* pMouseyMesh = new ProtoMesh("Data\\Mouse_JoyfulJump.proto.azul", pMouseyTex);
	MeshNodeMan::Add(Mesh::Name::MOUSEY, pMouseyMesh);


	//LOAD FONTS----------------------------------------------------------------
	//GlyphMan::Add(Glyph::Name::CAIYUN_80PT, "Data\\StCaiyun80pt_font.proto.azul", Texture::Name::CAIYUN);

	//GameObj_SpriteBatch* pTextBatch = new GameObj_SpriteBatch(GameObj2D::Name::TextBatch);
	//pTextBatch->SetName("TextBatch");
	//GameObjMan::Add(pTextBatch, GameObjMan::GetRoot());

	//GraphicsObj_Font* pGraphicsFont = new GraphicsObj_Font(pSprite, pSpriteShader);
	//GameObj2D* pAnimText = new GameObj2D(GameObj2D::Name::TextBatch, pGraphicsFont);
	//GameObjMan::Add(pAnimText, pTextBatch);
	//FontMan::Add(pGraphicsFont, FontName::Tester, Glyph::Name::CAIYUN_80PT, "ANIMATION TRANSITIONS", 800, 1700);


	//LOAD ANIMATIONS----------------------------------------------------------

	// Mousey: Walking
	Quat tmp = Quat(Mat4(Mat4::Rot1::Y, MATH_PI2));
	SkeletonMan::Add(Skeleton::Name::MOUSEY_WALK, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_WALK, "Data\\Mouse_Walking_anim.proto.azul");
	Anim* pMouseWalkAnim = AnimMan::Add(Anim::Name::MOUSEY_WALK, Clip::Name::MOUSEY_WALK, Skeleton::Name::MOUSEY_WALK);
	pMouseWalkAnim->LinkAnim(Mesh::Name::MOUSEY, Vec3(-2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(1.75f, 1.75f, 1.75f), Vec3(-2.0f, -1.3f, 0.0f), tmp);

	// Mousey: Running
	SkeletonMan::Add(Skeleton::Name::MOUSEY_RUN, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_RUN, "Data\\Mouse_Running_anim.proto.azul");
	AnimMan::Add(Anim::Name::MOUSEY_RUNNING, Clip::Name::MOUSEY_RUN, Skeleton::Name::MOUSEY_RUN);

	// Mousey Font Flip
	SkeletonMan::Add(Skeleton::Name::MOUSEY_FLIP, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_FLIP, "Data\\Mouse_FrontFlip_anim.proto.azul");
	AnimMan::Add(Anim::Name::MOUSEY_FLIP, Clip::Name::MOUSEY_FLIP, Skeleton::Name::MOUSEY_FLIP);


	//SET TRANSITIONS----------------------------------------------------------
	pMouseWalkAnim->SetBlend(Clip::Name::MOUSEY_RUN);

}

void Demo5::Update()
{
	// update cameras
	Camera* cam = Camera3DMan::GetCurrCam();
	cam->UpdateCamera();

	//cam = Camera2DMan::GetCurrCam();
	//cam->UpdateCamera();

	//initiate blends
	Keyboard* pKey = InputMan::GetKeyboard();
	bool currKey1 = pKey->GetKeyState(Keyboard::KEY_1);
	if ( currKey1 && !prevKey1)
	{
		Anim* pAnim = AnimMan::Find(Anim::Name::MOUSEY_WALK);
		pAnim->blending = true; 
	}
	prevKey1 = currKey1;

	bool currKey2 = pKey->GetKeyState(Keyboard::KEY_2);
	if (currKey2 && !prevKey2)
	{
		Anim* pAnim = AnimMan::Find(Anim::Name::MOUSEY_WALK);
		pAnim->SetBlend(Clip::Name::MOUSEY_FLIP);

		pAnim->blending = true;
	}

	// reset transitions
	//bool currKey0 = pKey->GetKeyState(Keyboard::KEY_0);
	//if (currKey0 && !prevKey0)
	//{
	//	//hard reset
	//	Anim* pAnim = AnimMan::Find(Anim::Name::MOUSEY_WALK);
	//	pAnim->SwitchClip(Clip::Name::MOUSEY_WALK);
	//}
	//prevKey0 = currKey0;
}

void Demo5::Unload()
{}