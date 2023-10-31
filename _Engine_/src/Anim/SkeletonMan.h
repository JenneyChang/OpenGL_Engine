#pragma once
#ifndef SKELETON_MAN_H
#define SKELETON_MAN_H

#include "Manager.h"
#include "Skeleton.h"
#include "hierarchy_proto.h"

using namespace Azul;

class SkeletonMan : public Manager
{
public:
	SkeletonMan() = delete;
	SkeletonMan(const SkeletonMan&) = delete;
	SkeletonMan& operator=(const SkeletonMan&) = delete;

	static void Create(int toReserve = 2, int toGrow = 1);
	static void Destroy();

	static Skeleton* Add(Skeleton::Name name, const char* filename);
	static Skeleton* Find(Skeleton::Name name);
	static void Remove(Skeleton* skeleton);
	static void Print();


protected:
	Node* derivedCreateNode() override;


private:
	Skeleton* poComparison;

	static SkeletonMan* poInstance;
	static SkeletonMan* prInstance();

	SkeletonMan(int toReserve, int toGrow);
	~SkeletonMan();

	bool prLoadFile(const char* filename, hierarchy_proto& hproto);


};
#endif // !SKELETON_MAN_H
