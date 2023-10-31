#pragma once
#ifndef CLIP_H
#define CLIP_H

#include "DLink.h"
#include "AnimTime.h"
#include "Joint.h"
#include "SSBO.h"
#include "Mixer.h"

#include "clip_proto.h"

using namespace Azul;

class Clip : public DLink
{
public:
	struct Frames
	{
		Frames* pNext;
		Frames* pPrev;
		AnimTime keytime;
		SSBO* poSSBO_Joints;
		char pad[4];

		Frames() = default;
		~Frames() { delete this->poSSBO_Joints; }
	};

	enum class Name
	{
		CHICKENBOT_WALK,
		CHICKENBOT_RUN,
		CHICKENBOT_FRONT_HIT,
		CHICKENBOT_DIE_RIGHT,

		MOUSEY_JUMP,
		MOUSEY_WALK,
		MOUSEY_RUN,
		MOUSEY_FLIP,
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

		UNINITIALIZED
	};


	Clip();
	~Clip();
	Clip(const Clip&) = delete;
	Clip& operator=(const Clip&) = delete;

	void Set(Clip::Name _name);
	void Set(Clip::Name _name, clip_proto& cproto, int numjoints);

	AnimTime GetDuration();
	int GetNumJoints();

	void AnimateBones(AnimTime t, SSBO* pSSBOIn);

	bool Compare(Node* pNode) override;


private:
	Clip::Name name;
	Frames* poHead;
	AnimTime duration;
	int numFrames;
	unsigned int numJoints;

	Frames* prFindCurrFrame(AnimTime t);


};
#endif // !CLIP_H
