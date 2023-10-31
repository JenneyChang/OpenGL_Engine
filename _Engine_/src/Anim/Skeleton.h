#pragma once
#ifndef SKELETON_H
#define SKELETON_H

#include "DLink.h"
#include "Joint.h"
#include "SSBO.h"
#include "GameObj_Dynamic.h"
#include "MathEngine.h"

#include "hierarchy_proto.h"

using namespace Azul;

class Skeleton : public DLink
{
public:
	enum class Name
	{
		CHICKENBOT_WALK,
		CHICKENBOT_RUN,
		CHICKENBOT_FRONT_HIT,
		CHICKENBOT_DIE_RIGHT,

		MOUSEY,
		MOUSEY_WALK,
		MOUSEY_RUN,
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

	struct SkelData
	{
		int index = -1;
		int parentIndex = -1;
		char name[64] = { 0 };
	};
	SkelData* pOrigList;
	SkelData* pOrderedList;

	Skeleton(const Skeleton&) = delete;
	Skeleton& operator=(const Skeleton&) = delete;
	Skeleton();
	~Skeleton();

	void Set(Skeleton::Name _name);
	void Set(Skeleton::Name _name, hierarchy_proto& hproto);
	
	SSBO* GetSSBOTable();

	void SetHierarchy(SSBO* pSSBOIn, Mesh* mesh, Vec3 lightPos, Vec4 lightColor, Vec3 scale, Vec3 trans, Quat rot);
	int GetHierarchyDepth();

	void ResetLink() override;
	bool Compare(Node* pNode) override;


private:
	Skeleton::Name name;
	int numJoints;
	GameObj_Dynamic* pFirstBone;

	SSBO* poSSBO_HierarchyTable;
	int hierarchyDepth;

	//std::string GetSkeletonName(Skeleton::Name _name);


};
#endif // !SKELETON_H
