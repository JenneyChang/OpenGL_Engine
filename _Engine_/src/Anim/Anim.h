#pragma once
#ifndef ANIM_H
#define ANIM_H

#include "DLink.h"
#include "Timer.h"
#include "AnimTimer.h"
#include "Clip.h"
#include "Skeleton.h"
#include "Joint.h"
#include "SSBO.h"

#include "GameObj_Skin.h"

using namespace Azul;

class Anim : public DLink
{
public:
	enum class Name
	{
		CHICKENBOT_WALK,
		CHICKENBOT_RUN,
		CHICKENBOT_HIT_FRONT,
		CHICKENBOT_DIE_RIGHT,

		MOUSEY,
		MOUSEY_WALK,
		MOUSEY_RUNNING,
		MOUSEY_TPOSE,
		MOUSEY_SHUFFLE,
		MOUSEY_GANGNAM_STYLE,
		MOUSEY_HAPPY_WALK,
		MOUSEY_HIPHOP_DANCE,
		MOUSEY_SOULSPIN2,
		MOUSEY_RUMBA,
		MOUSEY_RUNFWD,
		MOUSEY_SAMBA,
		MOUSEY_SILLYDANCE,
		MOUSEY_TUT_HIPHOP,
		MOUSEY_TWIST_DANCE,
		
		MOUSEY_ANGRY,
		MOUSEY_ZOMBIEWALK,
		MOUSEY_GUITAR_PLAYING,
		MOUSEY_KNEELING_POINTING,
		MOUSEY_CROUCH_STAND,
		MOUSEY_FRONT_DEATH,
		MOUSEY_DRUNK_WALK,
		MOUSEY_MMA_KICK,
		MOUSEY_SITTING,
		MOUSEY_STAND_CLAP,
		MOUSEY_FLIP,

		UNINITIALIZED
	};

	Anim();
	~Anim();
	Anim(const Anim&) = delete;
	Anim& operator=(const Anim&) = delete;

	void Set(Anim::Name _name);
	void Set(Anim::Name _name, AnimTime delta, Clip::Name clip, Skeleton::Name skel);
	void SetBlend(Clip::Name clipB, float duration = 1.5f, float blendfactor = 0.0f);

	SSBO* GetSSBOJointResult();

	void Animate();
	void Blend();	//TODO: push this into its own class

	void Play();
	void Pause();
	void SpeedUp();
	void SlowDown();

	void SwitchClip(Clip::Name clipName);

	void LinkAnim(Mesh::Name meshName, Vec3 lightPos, Vec4 lightColor, Vec3 scale = Vec3(1, 1, 1),
			Vec3 trans = Vec3(0, 0, 0), Quat rot = Quat(0, 0, 0, 1));

	void ResetLink() override;
	bool Compare(Node* pNode) override;
	

private:
	Anim::Name name;
	Clip* pClip;
	Skeleton* pSkeleton;
	Timer* poTimer;

	SSBO* poSSBO_JointResult;
	float speed;

	//TODO: blending can be on its own mini sys
	Clip* pClipB;
	float t_elapsed;
	float t_duration;
	float blendFactor;

	SSBO* poResultA;
	SSBO* poResultB;


public:
	bool blending = false;


};
#endif // !ANIM_H
