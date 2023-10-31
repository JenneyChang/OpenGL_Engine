#pragma once
#ifndef ANIM_MAN_H
#define ANIM_MAN_H

#include "Manager.h"
#include "Anim.h"

#include "anim_proto.h"

using namespace Azul;

class AnimMan : public Manager
{
public:
	AnimMan() = delete;
	AnimMan(const AnimMan&) = delete;
	AnimMan& operator=(const AnimMan&) = delete;

	static void Create(int toReserve = 2, int toGrow = 1);
	static void Destroy();

	static Anim* Add(Anim::Name animName, Clip::Name clipName, Skeleton::Name skelName, float speed = 0.01f);
	static Anim* Find(Anim::Name name);
	static void Remove(Anim* anim);
	static void Print();

	static void Update();

	static void Play(Anim::Name name);
	static void Pause(Anim::Name name);
	static void SpeedUp(Anim::Name name);
	static void SlowDown(Anim::Name name);

	//hard switch
	static void SwitchClip(Anim::Name animName, Clip::Name clipName);


protected:
	Node* derivedCreateNode() override;


private:
	Anim* poComparison;
	
	static AnimMan* poInstance;
	static AnimMan* prInstance();

	AnimMan(int toReserve, int toGrow);
	~AnimMan();

	bool prLoadProto(const char* filename, anim_proto& aproto);


};
#endif // !ANIM_MAN_H
