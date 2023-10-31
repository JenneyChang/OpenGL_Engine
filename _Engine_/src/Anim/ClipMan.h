#pragma once
#ifndef CLIPMAN_H
#define CLIPMAN_H

#include "Manager.h"
#include "Clip.h"

#include "anim_proto.h"

using namespace Azul;

class ClipMan : public Manager
{
public:
	ClipMan() = delete;
	ClipMan(const ClipMan&) = delete;
	ClipMan& operator=(const ClipMan&) = delete;

	static void Create(int toReserve = 2, int grow = 1);
	static void Destroy();

	static Clip* Add(Clip::Name name, const char* filename);
	static Clip* Find(Clip::Name name);
	static void Remove(Clip* clip);
	static void Print();


protected:
	Node* derivedCreateNode() override;


private:
	Clip* poComparison;

	static ClipMan* poInstance;
	static ClipMan* prInstance();

	ClipMan(int toReserve, int toGrow);
	~ClipMan();

	bool prLoadFile(const char* filename, anim_proto& aproto);

};
#endif // !CLIPMAN_H
