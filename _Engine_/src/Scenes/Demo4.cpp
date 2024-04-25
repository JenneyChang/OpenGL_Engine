#include "Demo4.h"

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


Demo4::Demo4(const int w, const int h)
	: width(w), height(h)
{ }

Demo4::~Demo4()
{ }

void Demo4::Load()	
{
	//CAMERA SETUP-------------------------------------------------------------
	Camera3D* pCam0 = Camera3DMan::Add(Camera::Name::CAMERA_0);
	pCam0->SetViewport(0, 0, width, height);
	pCam0->SetPerspective(35.0f, float(pCam0->GetScreenWidth()) / float(pCam0->GetScreenHeight()), 1.0f, 10000.0f);
	pCam0->SetOrient_Pos(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 8.0f));
	pCam0->UpdateCamera();
	Camera3DMan::SetCurrCam(pCam0);

	//LOAD TEXTURE---------------------------------------------------------------
	Texture* pMouseyTex = TextureMan::Add("Data\\Mouse_Diffuse_tex.proto.azul", Texture::Name::MOUSEY);


	//LOAD MESH----------------------------------------------------------------
	Mesh* pMouseyMesh = new ProtoMesh("Data\\Mouse_JoyfulJump.proto.azul", pMouseyTex);
	MeshNodeMan::Add(Mesh::Name::MOUSEY, pMouseyMesh);

	//LOAD ANIMATIONS----------------------------------------------------------

	// Mousey: Joyful Jump
	SkeletonMan::Add(Skeleton::Name::MOUSEY, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_JUMP, "Data\\Mouse_JoyfulJump_anim.proto.azul");
	Anim* pMouseyAnim = AnimMan::Add(Anim::Name::MOUSEY, Clip::Name::MOUSEY_JUMP, Skeleton::Name::MOUSEY);
	pMouseyAnim->LinkAnim(Mesh::Name::MOUSEY, Vec3(-2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(-2.9f, 1.3f, 0.0f));

	// Mousey: Walking
	SkeletonMan::Add(Skeleton::Name::MOUSEY_WALK, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_WALK, "Data\\Mouse_Walking_anim.proto.azul");
	Anim* pMouseWalkAnim = AnimMan::Add(Anim::Name::MOUSEY_WALK, Clip::Name::MOUSEY_WALK, Skeleton::Name::MOUSEY_WALK);
	pMouseWalkAnim->LinkAnim(Mesh::Name::MOUSEY, Vec3(-2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(-2.0f, 1.3f, 0.0f));

	// Mousey: Running
	SkeletonMan::Add(Skeleton::Name::MOUSEY_RUN, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_RUN, "Data\\Mouse_Running_anim.proto.azul");
	Anim* pMouseRunAnim = AnimMan::Add(Anim::Name::MOUSEY_RUNNING, Clip::Name::MOUSEY_RUN, Skeleton::Name::MOUSEY_RUN);
	pMouseRunAnim->LinkAnim(Mesh::Name::MOUSEY, Vec3(-2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(-1.0f, 1.3f, 0.0f));

	// Mousey: Shuffling
	SkeletonMan::Add(Skeleton::Name::MOUSEY_SHUFFLE, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_SHUFFLE, "Data\\Mousey_Shuffling_anim.proto.azul");
	Anim* pMouseShuffle = AnimMan::Add(Anim::Name::MOUSEY_SHUFFLE, Clip::Name::MOUSEY_SHUFFLE, Skeleton::Name::MOUSEY_SHUFFLE);
	pMouseShuffle->LinkAnim(Mesh::Name::MOUSEY, Vec3(0.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(-0.1f, 1.3f, 0.0f));

	// Guitar Playing
	SkeletonMan::Add(Skeleton::Name::MOUSEY_GUITAR_PLAYING, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_GUITAR_PLAYING, "Data\\Mousey_GuitarPlaying_anim.proto.azul");
	Anim* pMouseGuitarPlay = AnimMan::Add(Anim::Name::MOUSEY_GUITAR_PLAYING, Clip::Name::MOUSEY_GUITAR_PLAYING, Skeleton::Name::MOUSEY_GUITAR_PLAYING);
	pMouseGuitarPlay->LinkAnim(Mesh::Name::MOUSEY, Vec3(0.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(0.9f, 1.3f, 0.0f));

	// Hip hop dancing
	SkeletonMan::Add(Skeleton::Name::MOUSEY_HIPHOP_DANCE, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_HIPHOP_DANCE, "Data\\Mousey_Hip_Hop_Dancing_anim.proto.azul");
	Anim* pMouseHiphopDance = AnimMan::Add(Anim::Name::MOUSEY_HIPHOP_DANCE, Clip::Name::MOUSEY_HIPHOP_DANCE, Skeleton::Name::MOUSEY_HIPHOP_DANCE);
	pMouseHiphopDance->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(1.9f, 1.3f, 0.0f));

	// MMA Kick
	SkeletonMan::Add(Skeleton::Name::MOUSEY_MMA_KICK, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_MMA_KICK, "Data\\Mousey_MmaKick_anim.proto.azul");
	Anim* pMouseKick = AnimMan::Add(Anim::Name::MOUSEY_MMA_KICK, Clip::Name::MOUSEY_MMA_KICK, Skeleton::Name::MOUSEY_MMA_KICK);
	pMouseKick->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(2.7f, 1.3f, 0.0f));

	// Angry
	SkeletonMan::Add(Skeleton::Name::MOUSEY_ANGRY, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_ANGRY, "Data\\Mousey_Angry_anim.proto.azul");
	Anim* pMouseAngry = AnimMan::Add(Anim::Name::MOUSEY_ANGRY, Clip::Name::MOUSEY_ANGRY, Skeleton::Name::MOUSEY_ANGRY);
	pMouseAngry->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(-2.9f, 0.0f, 0.0f));

	// Crouch To Stand
	SkeletonMan::Add(Skeleton::Name::MOUSEY_CROUCH_STAND, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_CROUCH_STAND, "Data\\Mousey_CrouchToStand_anim.proto.azul");
	Anim* pMouseCrouchStand = AnimMan::Add(Anim::Name::MOUSEY_CROUCH_STAND, Clip::Name::MOUSEY_CROUCH_STAND, Skeleton::Name::MOUSEY_CROUCH_STAND);
	pMouseCrouchStand->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(-1.5f, 0.0f, 0.0f));

	// Silly Dancing
	SkeletonMan::Add(Skeleton::Name::MOUSEY_SILLYDANCE, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_SILLYDANCE, "Data\\Mousey_Silly_Dancing_anim.proto.azul");
	Anim* pMouseSillyDance = AnimMan::Add(Anim::Name::MOUSEY_SILLYDANCE, Clip::Name::MOUSEY_SILLYDANCE, Skeleton::Name::MOUSEY_SILLYDANCE);
	pMouseSillyDance->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(-0.1f, 0.0f, 0.0f));

	// Death From The Front
	SkeletonMan::Add(Skeleton::Name::MOUSEY_FRONT_DEATH, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_FRONT_DEATH, "Data\\Mousey_DeathFromTheFront_anim.proto.azul");
	Anim* pMouseFrontDeath = AnimMan::Add(Anim::Name::MOUSEY_FRONT_DEATH, Clip::Name::MOUSEY_FRONT_DEATH, Skeleton::Name::MOUSEY_FRONT_DEATH);
	pMouseFrontDeath->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(1.3f, 0.0f, 0.0f));

	// Rumba Dancing
	SkeletonMan::Add(Skeleton::Name::MOUSEY_RUMBA, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_RUMBA, "Data\\Mousey_Rumba_Dancing_anim.proto.azul");
	Anim* pMouseRumba = AnimMan::Add(Anim::Name::MOUSEY_RUMBA, Clip::Name::MOUSEY_RUMBA, Skeleton::Name::MOUSEY_RUMBA);
	pMouseRumba->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(2.6f, 0.0f, 0.0f));

	// Sitting
	SkeletonMan::Add(Skeleton::Name::MOUSEY_SITTING, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_SITTING, "Data\\Mousey_Sitting_anim.proto.azul");
	Anim* pMouseSitting = AnimMan::Add(Anim::Name::MOUSEY_SITTING, Clip::Name::MOUSEY_SITTING, Skeleton::Name::MOUSEY_SITTING);
	pMouseSitting->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(-2.8f, -1.3f, 0.0f));

	// Twist Dance
	SkeletonMan::Add(Skeleton::Name::MOUSEY_TWIST_DANCE, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_TWIST_DANCE, "Data\\Mousey_Twist_Dance_anim.proto.azul");
	Anim* pMouseTwist = AnimMan::Add(Anim::Name::MOUSEY_TWIST_DANCE, Clip::Name::MOUSEY_TWIST_DANCE, Skeleton::Name::MOUSEY_TWIST_DANCE);
	pMouseTwist->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(-1.5f, -1.3f, 0.0f));

	// Zombie Walk
	SkeletonMan::Add(Skeleton::Name::MOUSEY_ZOMBIEWALK, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_ZOMBIEWALK, "Data\\Mousey_ZombieWalk_anim.proto.azul");
	Anim* pMouseZombie = AnimMan::Add(Anim::Name::MOUSEY_ZOMBIEWALK, Clip::Name::MOUSEY_ZOMBIEWALK, Skeleton::Name::MOUSEY_ZOMBIEWALK);
	pMouseZombie->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(-0.1f, -1.3f, 0.0f));

	// Tut Hiphop Dance
	SkeletonMan::Add(Skeleton::Name::MOUSEY_TUT_HIPHOP, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_TUT_HIPHOP, "Data\\Mousey_Tut_Hip_Hop_Dance_anim.proto.azul");
	Anim* pMouseTut = AnimMan::Add(Anim::Name::MOUSEY_TUT_HIPHOP, Clip::Name::MOUSEY_TUT_HIPHOP, Skeleton::Name::MOUSEY_TUT_HIPHOP);
	pMouseTut->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(1.3f, -1.3f, 0.0f));

	// Kneeling Pointing
	SkeletonMan::Add(Skeleton::Name::MOUSEY_KNEELING_POINTING, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_KNEELING_POINTING, "Data\\Mousey_KneelingPointing_anim.proto.azul");
	Anim* pMouseTut1 = AnimMan::Add(Anim::Name::MOUSEY_KNEELING_POINTING, Clip::Name::MOUSEY_KNEELING_POINTING, Skeleton::Name::MOUSEY_KNEELING_POINTING);
	pMouseTut1->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.75f, 0.75f, 0.75f), Vec3(2.6f, -1.3f, 0.0f));

	// Soul Spin
	SkeletonMan::Add(Skeleton::Name::MOUSEY_SOULSPIN2, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_SOULSPIN2, "Data\\Mousey_Northern_Soul_Spin2_anim.proto.azul");
	Anim* pMouseSoulSpin = AnimMan::Add(Anim::Name::MOUSEY_SOULSPIN2, Clip::Name::MOUSEY_SOULSPIN2, Skeleton::Name::MOUSEY_SOULSPIN2);
	pMouseSoulSpin->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.65f, 0.65f, 0.65f), Vec3(-2.7f, -2.4f, 0.0f));

	// Run Foward
	Quat tmp = Quat(Mat4(Mat4::Rot1::Y, MATH_PI2));
	SkeletonMan::Add(Skeleton::Name::MOUSEY_RUNFWD, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_RUNFWD, "Data\\Mousey_Run_Forward_anim.proto.azul");
	Anim* pMouseRunFwd = AnimMan::Add(Anim::Name::MOUSEY_RUNFWD, Clip::Name::MOUSEY_RUNFWD, Skeleton::Name::MOUSEY_RUNFWD);
	pMouseRunFwd->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.65f, 0.65f, 0.65f), Vec3(-1.9f, -2.4f, 0.0f), tmp);

	// Standing Clap
	SkeletonMan::Add(Skeleton::Name::MOUSEY_STAND_CLAP, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_STAND_CLAP, "Data\\Mousey_StandingClap_anim.proto.azul");
	Anim* pMouseStandClap = AnimMan::Add(Anim::Name::MOUSEY_STAND_CLAP, Clip::Name::MOUSEY_STAND_CLAP, Skeleton::Name::MOUSEY_STAND_CLAP);
	pMouseStandClap->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.65f, 0.65f, 0.65f), Vec3(-0.1f, -2.4f, 0.0f));

	// Drunk Walk
	SkeletonMan::Add(Skeleton::Name::MOUSEY_DRUNK_WALK, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_DRUNK_WALK, "Data\\Mousey_DrunkWalk_anim.proto.azul");
	Anim* pMouseDrunkWalk = AnimMan::Add(Anim::Name::MOUSEY_DRUNK_WALK, Clip::Name::MOUSEY_DRUNK_WALK, Skeleton::Name::MOUSEY_DRUNK_WALK);
	pMouseDrunkWalk->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.65f, 0.65f, 0.65f), Vec3(1.3f, -2.4f, 0.0f));

	// Happy Walk
	SkeletonMan::Add(Skeleton::Name::MOUSEY_HAPPY_WALK, "Data\\Mouse_JoyfulJump_skel.proto.azul");
	ClipMan::Add(Clip::Name::MOUSEY_HAPPY_WALK, "Data\\Mousey_Happy_Walk_anim.proto.azul");
	Anim* pMouseHappyWalk = AnimMan::Add(Anim::Name::MOUSEY_HAPPY_WALK, Clip::Name::MOUSEY_HAPPY_WALK, Skeleton::Name::MOUSEY_HAPPY_WALK);
	pMouseHappyWalk->LinkAnim(Mesh::Name::MOUSEY, Vec3(2.0f, 1.5f, 1.2f), Vec4(1, 1, 1, 1), Vec3(0.65f, 0.65f, 0.65f), Vec3(2.6f, -2.4f, 0.0f));

}

void Demo4::Update()
{
	Camera* cam = Camera3DMan::GetCurrCam();
	cam->UpdateCamera();
}

void Demo4::Unload()
{

}
