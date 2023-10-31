#include "Demo2.h"
#include "Camera3DMan.h"
#include "TextureMan.h"
#include "MeshNodeMan.h"
#include "ShaderMan.h"
#include "ProtoMesh.h"
#include "GraphicsObj3D.h"
#include "GraphicsObj_Texture.h"
#include "GraphicsObj_Wireframe.h"
#include "GameObjMan.h"
#include "GameObj_BSphere.h"



Demo2::Demo2(const int w, const int h)
	: width(w), height(h)
{ }

Demo2::~Demo2()
{ }


void Demo2::Load()   
{
	//CAMERA SETUP-------------------------------------------------------------
	// inside frustum (front--> to back)
	Camera3D* pFrustum = Camera3DMan::Add(Camera::Name::FRUSTRUM);
	pFrustum->SetViewport(0, 0, width, height);
	pFrustum->SetPerspective(35.0f, float(pFrustum->GetScreenWidth()) / float(pFrustum->GetScreenHeight()), 4.0f, 10.0f);
	pFrustum->SetOrient_Pos(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 8.0f));
	pFrustum->UpdateCamera();
	Camera3DMan::SetCurrCam(pFrustum);

	// frustum side view & back view...
	Camera3D* pFrustum_Side = Camera3DMan::Add(Camera::Name::FRUSTRUM_SIDE);
	pFrustum_Side->SetViewport(0, 0, width, height);
	pFrustum_Side->SetPerspective(1.0f, float(pFrustum->GetScreenWidth()) / float(pFrustum->GetScreenHeight()), 1.0f, 1000.0f);
	pFrustum_Side->SetOrient_Pos(Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 2.0f), Vec3(0.0f, -700.0f, 2.0f));
	pFrustum_Side->UpdateCamera();

	Camera3D* pFrustum_Back = Camera3DMan::Add(Camera::Name::FRUSTRUM_BACK);
	pFrustum_Back->SetViewport(0, 0, width, height);
	pFrustum_Back->SetPerspective(1.0f, float(pFrustum->GetScreenWidth()) / float(pFrustum->GetScreenHeight()), 1.0f, 1000.0f);
	pFrustum_Back->SetOrient_Pos(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 2.0f), Vec3(0.0f, 0.0f, 700.0f));
	pFrustum_Back->UpdateCamera();


	//SHADER -----------------------------------------------------------------
	ShaderObj* pTextureShader = ShaderMan::Find(ShaderObj::Name::TEXTURE);
	assert(pTextureShader);

	ShaderObj* pWireframeShader = ShaderMan::Find(ShaderObj::Name::WIREFRAME);
	assert(pWireframeShader);


	//LOAD 3D MODELS----------------------------------------------------------
	Mesh* pBSphere = new ProtoMesh("Data\\sphere.proto.azul");
	MeshNodeMan::Add(Mesh::Name::SPHERE, pBSphere);

	//wooden crate
	Texture* pCrateTex = TextureMan::Add("Data\\crate_BaseColor_tex.proto.azul", Texture::Name::CRATE);
	Mesh* pCrateMesh = new ProtoMesh("Data\\wooden crate.proto.azul", pCrateTex);
	MeshNodeMan::Add(Mesh::Name::CRATE, pCrateMesh);
	GraphicsObj3D* pGraphicsObj = new GraphicsObj_Texture(pCrateMesh, pTextureShader, pCrateTex);
	/*GameObj_Rigid**/ pCrateObj = new GameObj_Rigid(pGraphicsObj);
	pCrateObj->SetScale(0.25f, 0.25f, 0.25f);
	pCrateObj->SetDeltaY(0.003f);
	pCrateObj->SetTrans(0.0f, 0.0f, 1.0f);
	GameObjMan::Add(pCrateObj, GameObjMan::GetRoot());

	pGraphicsObj = new GraphicsObj_Wireframe(pBSphere, pWireframeShader, Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	GameObj_BSphere* pBSphereObj = new GameObj_BSphere(pGraphicsObj);
	pBSphereObj->SetName("Crate_BSphere");
	pBSphereObj->SetBSphereRef(pCrateObj);
	GameObjMan::Add(pBSphereObj, pCrateObj);

	//space frigate
	Texture* pFrigateTex = TextureMan::Add("Data\\space_frigate_tex.proto.azul", Texture::Name::FRIGATE);
	Mesh* pFrigateMesh = new ProtoMesh("Data\\space_frigate.proto.azul", pFrigateTex);
	MeshNodeMan::Add(Mesh::Name::FRIGATE, pFrigateMesh);
	pGraphicsObj = new GraphicsObj_Texture(pFrigateMesh, pTextureShader, pFrigateTex);
	/*GameObj_Rigid**/ pFrigateObj = new GameObj_Rigid(pGraphicsObj);
	pFrigateObj->SetScale(0.015f, 0.015f, 0.015f);
	pFrigateObj->SetTrans(2.0f, -2.0f, 0.0f);
	pFrigateObj->SetRot(-0.25f, 0.5f, 0.15f, 1.0f);
	pFrigateObj->SetDeltaZ(-0.02f);
	pFrigateObj->SetDeltaX(0.003f);
	GameObjMan::Add(pFrigateObj, GameObjMan::GetRoot());

	pGraphicsObj = new GraphicsObj_Wireframe(pBSphere, pWireframeShader, Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	pBSphereObj = new GameObj_BSphere(pGraphicsObj);
	pBSphereObj->SetName("Frigate_BSphere");
	pBSphereObj->SetBSphereRef(pFrigateObj);
	GameObjMan::Add(pBSphereObj, pFrigateObj);
		
	//R2D2
	Texture* pR2D2Tex = TextureMan::Add("Data\\R2D2_BaseColor_tex.proto.azul", Texture::Name::R2);
	Mesh* pR2D2Mesh = new ProtoMesh("Data\\R2D2.proto.azul", pR2D2Tex);
	MeshNodeMan::Add(Mesh::Name::R2D2, pR2D2Mesh);
	pGraphicsObj = new GraphicsObj_Texture(pR2D2Mesh, pTextureShader, pR2D2Tex);
	/*GameObj_Rigid* */pR2D2Obj = new GameObj_Rigid(pGraphicsObj);
	pR2D2Obj->SetScale(30.0f, 30.0f, 30.0f);
	//pR2D2Obj->SetTrans(-2.7f, 1.5f, 0.0f);
	pR2D2Obj->SetTrans(0.0f, 1.5f, -3.0f);
	pR2D2Obj->SetRot(-0.57f, 0.0f, 0.0f, 1.0f);
	GameObjMan::Add(pR2D2Obj, GameObjMan::GetRoot());
		
	pGraphicsObj = new GraphicsObj_Wireframe(pBSphere, pWireframeShader, Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	pBSphereObj = new GameObj_BSphere(pGraphicsObj);
	pBSphereObj->SetName("R2D2_BSphere");
	pBSphereObj->SetBSphereRef(pR2D2Obj);
	GameObjMan::Add(pBSphereObj, pR2D2Obj);

	pGraphicsObj = new GraphicsObj_Wireframe(pR2D2Mesh, pWireframeShader, Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	pR2D2Obj2 = new GameObj_Rigid(pGraphicsObj);
	pR2D2Obj2->SetScale(30.0f, 30.0f, 30.0f);
	pR2D2Obj2->SetRot(-0.57f, 0.0f, 0.0f, 1.0f);
	pR2D2Obj2->SetTrans(-1.8f, 1.5f, 0.0f);
	GameObjMan::Add(pR2D2Obj2, GameObjMan::GetRoot());
}

void Demo2::Update() 
{
	//move camera
	//camctrl.Update();

	//update camera
	Camera* cam = Camera3DMan::GetCurrCam();
	cam->UpdateCamera();
}

void Demo2::Unload() 
{
	pCrateObj->SetDraw(false);
	pFrigateObj->SetDraw(false);
	pR2D2Obj->SetDraw(false);
	pR2D2Obj2->SetDraw(false);
}
			  