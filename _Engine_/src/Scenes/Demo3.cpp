#include "Demo3.h"

#include "Camera3DMan.h"
#include "Camera2DMan.h"
#include "ShaderMan.h"
#include "TextureMan.h"
#include "MeshNodeMan.h"
#include "GameObjMan.h"
#include "GlyphMan.h"
#include "FontMan.h"

#include "ProtoMesh.h"
#include "GraphicsObj_Wireframe.h"
#include "GraphicsObj_Font.h"
#include "GraphicsObj_Texture.h"
#include "GameObj_Rigid.h"
#include "GameObj_SpriteBatch.h"


Demo3::Demo3(const int w, const int h)
	: width(w), height(h)
{ }

Demo3::~Demo3()
{ }

void Demo3::Load()   
{
	//CAMERA SETUP-------------------------------------------------------------
	Camera2D* pCam1 = Camera2DMan::Add(Camera::Name::CAMERA_1);
	pCam1->SetViewport(0, 0, width, height);
	pCam1->SetOrthographic((float)-pCam1->GetScreenWidth() / 2.0f, (float)pCam1->GetScreenWidth() / 2.0f,
		(float)-pCam1->GetScreenHeight() / 2.0f, (float)pCam1->GetScreenHeight() / 2.0f, 1.0f, 1000.0f);
	pCam1->SetOrient_Pos(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 0.0f, 2.0f));
	pCam1->UpdateCamera();
	Camera2DMan::SetCurrCam(pCam1);

	Camera3D* pCam0 = Camera3DMan::Add(Camera::Name::CAMERA_0);
	pCam0->SetViewport(0, 0, width, height);
	pCam0->SetPerspective(35.0f, float(pCam0->GetScreenWidth()) / float(pCam0->GetScreenHeight()), 1.0f, 10000.0f);
	pCam0->SetOrient_Pos(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 8.0f));
	pCam0->UpdateCamera();
	Camera3DMan::SetCurrCam(pCam0);


	//SHADER -----------------------------------------------------------------
	//ShaderObj* pSpriteShader = ShaderMan::Find(ShaderObj::Name::SPRITE);
	ShaderObj* pTextureShader = ShaderMan::Find(ShaderObj::Name::TEXTURE);
	ShaderObj* pWireframeShader = ShaderMan::Find(ShaderObj::Name::WIREFRAME);
	assert(pWireframeShader);

	//LOAD TEXTURE---------------------------------------------------------------
	Texture* pCrateTex = TextureMan::Add("Data\\wooden_crate_tex.proto.azul", Texture::Name::CRATE);
	assert(pCrateTex);
	Texture* pFrigateTex = TextureMan::Add("Data\\space_frigate_tex.proto.azul", Texture::Name::FRIGATE);
	assert(pFrigateTex);
	Texture* pWatchTowerTex = TextureMan::Add("Data\\Wood_Tower_Col_tex.proto.azul", Texture::Name::WATCH_TOWER);
	assert(pWatchTowerTex);
	Texture* pFishTex = TextureMan::Add("Data\\BarramundiFish_tex.proto.azul", Texture::Name::BARRAMUNDI_FISH);
	assert(pFishTex);
	Texture* pAvocadoTex = TextureMan::Add("Data\\Avocado_tex.proto.azul", Texture::Name::AVOCADO);
	assert(pAvocadoTex);
	Texture* pSneakerTex = TextureMan::Add("Data\\sneaker_tex.proto.azul", Texture::Name::SNEAKER);
	assert(pSneakerTex);
	Texture* pDogeTex = TextureMan::Add("Data\\doge_tex.proto.azul", Texture::Name::DOGE);
	assert(pDogeTex);

	Texture* pCameraTex = TextureMan::Add("Data\\AntiqueCamera0_tex.proto.azul", Texture::Name::ANTIQUE_CAMERA);
	Texture* pCameraTex2 = TextureMan::Add("Data\\AntiqueCamera1_tex.proto.azul", Texture::Name::ANTIQUE_CAMERA);
	Texture* pSnowman0Tex = TextureMan::Add("Data\\snowman_finish0_tex.proto.azul", Texture::Name::SNOWMAN);
	Texture* pSnowman1Tex = TextureMan::Add("Data\\snowman_finish1_tex.proto.azul", Texture::Name::SNOWMAN);
	Texture* pShiva0Tex = TextureMan::Add("Data\\LordShiva0_tex.proto.azul", Texture::Name::LORD_SHIVA);
	Texture* pShiva1Tex = TextureMan::Add("Data\\LordShiva1_tex.proto.azul", Texture::Name::LORD_SHIVA);

	Texture* pR2D2Tex = TextureMan::Add("Data\\R2D2_BaseColor_tex.proto.azul", Texture::Name::R2);
	assert(pR2D2Tex);
	Texture* pChickenBotTex = TextureMan::Add("Data\\Chickenbot_walk_tex.proto.azul", Texture::Name::CHICKEN_BOT);
	assert(pChickenBotTex);
	Texture* pMouseyTex = TextureMan::Add("Data\\Mouse_Diffuse_tex.proto.azul", Texture::Name::MOUSEY);
	assert(pMouseyTex);
	Texture* pCorsetTex = TextureMan::Add("Data\\Corset_tex.proto.azul", Texture::Name::CORSET);
	assert(pCorsetTex);


	//LOAD MESH----------------------------------------------------------------
	//ProtoMesh* pSprite = new ProtoMesh("Data\\sprite.proto.azul");
	//MeshNodeMan::Add(Mesh::Name::SPRITE, pSprite);

	/*Mesh* pCubeMesh = new ProtoMesh("Data\\cube.proto.azul");
	MeshNodeMan::Add(Mesh::Name::CUBE, pCubeMesh);

	Mesh* pSphereMesh = new ProtoMesh("Data\\sphere.proto.azul");
	MeshNodeMan::Add(Mesh::Name::SPHERE, pSphereMesh);*/

	Mesh* pCrateMesh = new ProtoMesh("Data\\wooden_crate.proto.azul", pCrateTex);
	MeshNodeMan::Add(Mesh::Name::CRATE, pCrateMesh);

	Mesh* pFrigateMesh = new ProtoMesh("Data\\space_frigate.proto.azul", pFrigateTex);
	MeshNodeMan::Add(Mesh::Name::FRIGATE, pFrigateMesh);

	Mesh* pWatchTowerMesh = new ProtoMesh("Data\\WatchTower.proto.azul", pWatchTowerTex);
	MeshNodeMan::Add(Mesh::Name::WATCH_TOWER, pWatchTowerMesh);

	Mesh* pFishMesh = new ProtoMesh("Data\\BarramundiFish.proto.azul");
	MeshNodeMan::Add(Mesh::Name::BARRAMUNDI_FISH, pFishMesh);
	
	Mesh* pAvocadoMesh = new ProtoMesh("Data\\Avocado.proto.azul");
	MeshNodeMan::Add(Mesh::Name::AVOCADO, pAvocadoMesh);

	Mesh* pDogeMesh = new ProtoMesh("Data\\doge.proto.azul");
	MeshNodeMan::Add(Mesh::Name::DOGE, pDogeMesh);

	Mesh* pSneakerMesh = new ProtoMesh("Data\\sneaker.proto.azul");
	MeshNodeMan::Add(Mesh::Name::SNEAKER, pSneakerMesh);

	Mesh* pCameraMesh0 = new ProtoMesh("Data\\AntiqueCamera0.proto.azul", pCameraTex);
	Mesh* pCameraMesh1 = new ProtoMesh("Data\\AntiqueCamera1.proto.azul", pCameraTex2);
	MeshNodeMan::Add(Mesh::Name::ANTIQUE_CAMERA, pCameraMesh0);
	MeshNodeMan::Add(Mesh::Name::ANTIQUE_CAMERA, pCameraMesh1);
		
	Mesh* pSnowmanMesh0 = new ProtoMesh("Data\\snowman_finish0.proto.azul");
	Mesh* pSnowmanMesh1 = new ProtoMesh("Data\\snowman_finish1.proto.azul");
	MeshNodeMan::Add(Mesh::Name::SNOWMAN, pSnowmanMesh0);
	MeshNodeMan::Add(Mesh::Name::SNOWMAN, pSnowmanMesh1);

	Mesh* pShiva0Mesh = new ProtoMesh("Data\\LordShiva0.proto.azul");
	Mesh* pShiva1Mesh = new ProtoMesh("Data\\LordShiva1.proto.azul");
	MeshNodeMan::Add(Mesh::Name::LORD_SHIVA, pShiva0Mesh);
	MeshNodeMan::Add(Mesh::Name::LORD_SHIVA, pShiva1Mesh);

	Mesh* pR2D2Mesh = new ProtoMesh("Data\\R2D2.proto.azul", pR2D2Tex);
	MeshNodeMan::Add(Mesh::Name::R2D2, pR2D2Mesh);

	Mesh* pChickenBotMesh = new ProtoMesh("Data\\Chickenbot_walk.proto.azul", pChickenBotTex);
	MeshNodeMan::Add(Mesh::Name::CHICKEN_BOT, pChickenBotMesh);

	Mesh* pMouseyMesh = new ProtoMesh("Data\\Mouse_JoyfulJump.proto.azul", pMouseyTex);
	MeshNodeMan::Add(Mesh::Name::MOUSEY, pMouseyMesh);

	Mesh* pCorsetMesh = new ProtoMesh("Data\\Corset.proto.azul");
	MeshNodeMan::Add(Mesh::Name::CORSET, pCorsetMesh);


	//LOAD FONTS----------------------------------------------------------------
	//GlyphMan::Add(Glyph::Name::CAIYUN_80PT, "Data\\StCaiyun80pt_font.proto.azul", Texture::Name::CAIYUN);

	//GameObj_SpriteBatch* pTextBatch = new GameObj_SpriteBatch(GameObj2D::Name::TextBatch);
	//pTextBatch->SetName("TextBatch");
	//GameObjMan::Add(pTextBatch, GameObjMan::GetRoot());

	//GraphicsObj_Font* pGraphicsFont = new GraphicsObj_Font(pSprite, pSpriteShader);
	//GameObj2D* pAnimText = new GameObj2D(GameObj2D::Name::TextBatch, pGraphicsFont);
	//GameObjMan::Add(pAnimText, pTextBatch);
	//FontMan::Add(pGraphicsFont, FontName::Tester, Glyph::Name::CAIYUN_80PT, "3D SYSTEM", 950, 1650);

	
	//LOAD MODEL---------------------------------------------------------------
	GraphicsObj3D* pGraphicsObj = nullptr;
	Quat tmp;

	// Cube 
	//pGraphicsObj = new GraphicsObj_Wireframe(pCubeMesh, pWireframeShader, Vec4(1, 1, 1, 1));
	//GameObj_Rigid* pCubeObj = new GameObj_Rigid(pGraphicsObj);
	//pCubeObj->SetName("Cube3D");
	//pCubeObj->SetTrans(-2.7f, 2.0f, 0);
	//pCubeObj->SetScale(1.2f, 1.2f, 1.2f);
	//pCubeObj->SetDeltaY(0.01f);
	//GameObjMan::Add(pCubeObj, GameObjMan::GetRoot());
	//
	//// Sphere
	//pGraphicsObj = new GraphicsObj_Wireframe(pSphereMesh, pWireframeShader, Vec4(0, 0.5f, 0.5f, 1.0f));
	//GameObj_Rigid* pSphereObj = new GameObj_Rigid(pGraphicsObj);
	//pSphereObj->SetName("Sphere3D");
	//pSphereObj->SetScale(0.45f, 0.45f, 0.45f);
	//pSphereObj->SetTrans(-1.5f, 2.0f, 0);
	//pSphereObj->SetDeltaZ(0.01f);
	//GameObjMan::Add(pSphereObj, GameObjMan::GetRoot());
	
	// Crate
	//pGraphicsObj = new GraphicsObj_Wireframe(pCrateMesh, pWireframeShader, Vec4(1, 1, 1, 1));
	pGraphicsObj = new GraphicsObj_Texture(pCrateMesh, pTextureShader, pCrateTex);
	GameObj_Rigid* pCrateObj = new GameObj_Rigid(pGraphicsObj);
	pCrateObj->SetName("Crate3D");
	pCrateObj->SetScale(0.35f, 0.35f, 0.35f);
	pCrateObj->SetDeltaY(0.003f);
	pCrateObj->SetTrans(-2.7f, 1.9f, 0.0f);
	GameObjMan::Add(pCrateObj, GameObjMan::GetRoot());
	
	// Space Frigate
	tmp = Quat(Mat4(Mat4::Rot1::X, MATH_PI2) * Mat4(Mat4::Rot1::Z, -MATH_PI2));
	//pGraphicsObj = new GraphicsObj_Wireframe(pFrigateMesh, pWireframeShader, Vec4(1, 1, 1, 1));
	pGraphicsObj = new GraphicsObj_Texture(pFrigateMesh, pTextureShader, pFrigateTex);
	GameObj_Rigid* pFrigateObj = new GameObj_Rigid(pGraphicsObj);
	pFrigateObj->SetName("Frigate");
	pFrigateObj->SetScale(0.015f, 0.015f, 0.015f);
	pFrigateObj->SetDeltaY(0.006f);
	pFrigateObj->SetTrans(-1.6f, 1.9f, 0.0f);
	pFrigateObj->SetRot(tmp);
	GameObjMan::Add(pFrigateObj, GameObjMan::GetRoot());

	// Avocado 
	tmp = Quat(Mat4(Mat4::Rot1::Y, MATH_PI));
	//pGraphicsObj = new GraphicsObj_Wireframe(pAvocadoMesh, pWireframeShader, Vec4(1, 1, 1, 1));
	pGraphicsObj = new GraphicsObj_Texture(pAvocadoMesh, pTextureShader, pAvocadoTex);
	GameObj_Rigid* pAvocadoObj = new GameObj_Rigid(pGraphicsObj);
	pAvocadoObj->SetName("Avocado");
	pAvocadoObj->SetScale(16, 16, 16);
	pAvocadoObj->SetRot(tmp);
	pAvocadoObj->SetTrans(-0.6f, 1.4f, 0.0f);
	GameObjMan::Add(pAvocadoObj, GameObjMan::GetRoot());

	// Barramundi Fish
	tmp = Quat(Mat4(Mat4::Rot1::Z, MATH_PI2) * Mat4(Mat4::Rot1::X, MATH_PI2));
	//pGraphicsObj = new GraphicsObj_Wireframe(pFishMesh, pWireframeShader, Vec4(1, 1, 1, 1));
	pGraphicsObj = new GraphicsObj_Texture(pFishMesh, pTextureShader, pFishTex);
	GameObj_Rigid* pFishObj = new GameObj_Rigid(pGraphicsObj);
	pFishObj->SetName("Barramundi Fish");
	pFishObj->SetScale(1.5f, 1.5f, 1.5f);
	pFishObj->SetRot(tmp);
	pFishObj->SetTrans(0.4f, 1.9f, 0.0f);
	GameObjMan::Add(pFishObj, GameObjMan::GetRoot());

	// Watch Tower
	tmp = Quat(Mat4(Mat4::Rot1::X, -MATH_PI2));
	//pGraphicsObj = new GraphicsObj_Wireframe(pWatchTowerMesh, pWireframeShader, Vec4(1, 1, 1, 1));
	pGraphicsObj = new GraphicsObj_Texture(pWatchTowerMesh, pTextureShader, pWatchTowerTex);
	GameObj_Rigid* pWatchTowerObj = new GameObj_Rigid(pGraphicsObj);
	pWatchTowerObj->SetName("WatchTower");
	pWatchTowerObj->SetScale(12.5f, 12.5f, 12.5f);
	pWatchTowerObj->SetTrans(1.0f, 1.4f, 0.0f);
	pWatchTowerObj->SetRot(tmp);
	pWatchTowerObj->SetDeltaY(0.009f);
	GameObjMan::Add(pWatchTowerObj, GameObjMan::GetRoot());
	
	//Sneaker
	tmp = Quat(Mat4(Mat4::Rot1::Z, -MATH_PI2));
	//pGraphicsObj = new GraphicsObj_Wireframe(pSneakerMesh, pWireframeShader, Vec4(1, 1, 1, 1));
	pGraphicsObj = new GraphicsObj_Texture(pSneakerMesh, pTextureShader, pSneakerTex);
	GameObj_Rigid* pSneakerObj = new GameObj_Rigid(pGraphicsObj);
	pSneakerObj->SetName("Sneaker");
	pSneakerObj->SetScale(3, 3, 3);
	pSneakerObj->SetTrans(1.9f, 1.9f, 0.0f);
	pSneakerObj->SetRot(tmp);
	pSneakerObj->SetDeltaY(0.02f);
	GameObjMan::Add(pSneakerObj, GameObjMan::GetRoot());

	// Doge
	tmp = Quat(Mat4(Mat4::Rot1::Z, MATH_PI) * Mat4(Mat4::Rot1::Y, MATH_PI2) * Mat4(Mat4::Rot1::Z, MATH_PI2));
	//pGraphicsObj = new GraphicsObj_Wireframe(pDogeMesh, pWireframeShader, Vec4(1, 1, 1, 1));
	pGraphicsObj = new GraphicsObj_Texture(pDogeMesh, pTextureShader, pDogeTex);
	GameObj_Rigid* pDogeObj = new GameObj_Rigid(pGraphicsObj);
	pDogeObj->SetName("Doge");
	pDogeObj->SetScale(0.4f, 0.4f, 0.4f);
	pDogeObj->SetRot(tmp);
	pDogeObj->SetTrans(2.9f, 1.5f, 0.0f);
	GameObjMan::Add(pDogeObj, GameObjMan::GetRoot());

	// Antique Camera (multi-mesh) : tripod + cam
	tmp = Quat(Mat4(Mat4::Rot1::Y, -MATH_PI4));
	pGraphicsObj = new GraphicsObj_Texture(pCameraMesh0, pTextureShader, pCameraTex);
	GameObj_Rigid* pCamera0Obj = new GameObj_Rigid(pGraphicsObj);
	pCamera0Obj->SetName("Antique_Camera0");
	pCamera0Obj->SetScale(0.12f, 0.12f, 0.12f);
	pCamera0Obj->SetTrans(-2.4f,/* -0.5f*/-0.4f, 0.0f);
	pCamera0Obj->SetRot(tmp);
	GameObjMan::Add(pCamera0Obj, GameObjMan::GetRoot());
	
	pGraphicsObj = new GraphicsObj_Texture(pCameraMesh1, pTextureShader, pCameraTex);
	GameObj_Rigid* pCamera1Obj = new GameObj_Rigid(pGraphicsObj);
	pCamera1Obj->SetName("Antique_Camera1");
	pCamera1Obj->SetScale(0.12f, 0.12f, 0.12f);
	pCamera1Obj->SetTrans(-2.4f, -0.4f/*-0.3f*/, 0.0f);
	pCamera1Obj->SetRot(tmp);
	GameObjMan::Add(pCamera1Obj, pCamera0Obj);
	
	// Snowman (multi-mesh)
	tmp = Quat(Mat4(Mat4::Rot1::X, -MATH_PI2));
	pGraphicsObj = new GraphicsObj_Texture(pSnowmanMesh0, pTextureShader, pSnowman0Tex);
	GameObj_Rigid* pSnowman0Obj = new GameObj_Rigid(pGraphicsObj);
	pSnowman0Obj->SetName("Snowman 0");
	pSnowman0Obj->SetScale(80, 80, 80);
	pSnowman0Obj->SetRot(tmp);
	pSnowman0Obj->SetTrans(0.0f, 0.2f, 0.0f);
	GameObjMan::Add(pSnowman0Obj, GameObjMan::GetRoot());
	
	pGraphicsObj = new GraphicsObj_Texture(pSnowmanMesh1, pTextureShader, pSnowman1Tex);
	GameObj_Rigid* pSnowman1Obj = new GameObj_Rigid(pGraphicsObj);
	pSnowman1Obj->SetName("Snowman 1");
	pSnowman1Obj->SetScale(80, 80, 80);
	pSnowman1Obj->SetRot(tmp);
	pSnowman1Obj->SetTrans(-0.9f, -0.1f, 0.0f);
	GameObjMan::Add(pSnowman1Obj, pSnowman0Obj);

	// Lord Shiva
	tmp = Quat(Mat4(Mat4::Rot1::X, -MATH_PI2));
	pGraphicsObj = new GraphicsObj_Texture(pShiva0Mesh, pTextureShader, pShiva0Tex);
	GameObj_Rigid* pShiva0Obj = new GameObj_Rigid(pGraphicsObj);
	pShiva0Obj->SetName("Lord_Shiva0");
	pShiva0Obj->SetScale(50, 50, 50);
	pShiva0Obj->SetRot(tmp);
	pShiva0Obj->SetTrans(1.9f, -0.1f, 0.0f);
	GameObjMan::Add(pShiva0Obj, GameObjMan::GetRoot());

	pGraphicsObj = new GraphicsObj_Texture(pShiva1Mesh, pTextureShader, pShiva1Tex);
	GameObj_Rigid* pShiva1Obj = new GameObj_Rigid(pGraphicsObj);
	pShiva1Obj->SetName("Lord_Shiva1");
	pShiva1Obj->SetScale(50, 50, 50);
	pShiva1Obj->SetRot(tmp);
	pShiva1Obj->SetTrans(1.9f, -0.3f, 0.0f);
	GameObjMan::Add(pShiva1Obj, pShiva0Obj);


	// R2D2 
	tmp = Quat(Mat4(Mat4::Rot1::X, -MATH_PI2));
	pGraphicsObj = new GraphicsObj_Wireframe(pR2D2Mesh, pWireframeShader, Vec4(1, 1, 1, 1));
	//pGraphicsObj = new GraphicsObj_Texture(pR2D2Mesh, pTextureShader, pR2D2Tex);
	GameObj_Rigid* pR2D2Obj = new GameObj_Rigid(pGraphicsObj);
	pR2D2Obj->SetName("R2D2");
	pR2D2Obj->SetScale(40.0f, 40.0f, 40.0f);
	pR2D2Obj->SetTrans(-2.4f, -1.6f, 0.0f);
	pR2D2Obj->SetRot(tmp);
	GameObjMan::Add(pR2D2Obj, GameObjMan::GetRoot());
	
	// Corset
	pGraphicsObj = new GraphicsObj_Wireframe(pCorsetMesh, pWireframeShader, Vec4(1, 1, 1, 1));
	//pGraphicsObj = new GraphicsObj_Texture(pCorsetMesh, pTextureShader, pCorsetTex);
	GameObj_Rigid* pCorsetObj = new GameObj_Rigid(pGraphicsObj);
	pCorsetObj->SetName("Corset");
	pCorsetObj->SetScale(25, 25, 25);
	pCorsetObj->SetTrans(-0.9f, -2.2f, 0.0f);
	pCorsetObj->SetDeltaY(-0.01f);
	GameObjMan::Add(pCorsetObj, GameObjMan::GetRoot());
		
	// Chicken Bot
	tmp = Quat(Mat4(Mat4::Rot1::X, -MATH_PI2));
	pGraphicsObj = new GraphicsObj_Wireframe(pChickenBotMesh, pWireframeShader, Vec4(1, 1, 1, 1));
	//pGraphicsObj = new GraphicsObj_Texture(pChickenBotMesh, pTextureShader, pChickenBotTex);
	GameObj_Rigid* pChickenBotObj = new GameObj_Rigid(pGraphicsObj);
	pChickenBotObj->SetName("Chicken Bot");
	pChickenBotObj->SetScale(40, 40, 40);
	pChickenBotObj->SetRot(tmp);
	pChickenBotObj->SetTrans(1.2f, -2.2f, 0.0f);
	GameObjMan::Add(pChickenBotObj, GameObjMan::GetRoot());
	
	// Mouse
	pGraphicsObj = new GraphicsObj_Wireframe(pMouseyMesh, pWireframeShader, Vec4(1, 1, 1, 1));
	//pGraphicsObj = new GraphicsObj_Texture(pMouseyMesh, pTextureShader, pMouseyTex);
	GameObj_Rigid* pMouseObj = new GameObj_Rigid(pGraphicsObj);
	pMouseObj->SetName("Mousey");
	pMouseObj->SetTrans(2.5f, -2.2f, 0.0f);
	GameObjMan::Add(pMouseObj, GameObjMan::GetRoot());
}

void Demo3::Update() 
{
	Camera* cam = Camera3DMan::GetCurrCam();
	cam->UpdateCamera();

	cam = Camera2DMan::GetCurrCam();
	cam->UpdateCamera();
}

void Demo3::Unload() 
{

}