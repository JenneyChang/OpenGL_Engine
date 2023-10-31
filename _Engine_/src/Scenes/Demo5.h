#pragma once
#ifndef DEMO5_H
#define DEMO5_H

#include "Scene.h"

//Basic Clip Blending...HACKY
class Demo5 : public Scene
{
public:
	// deleted functions
	Demo5() = delete;
	Demo5(const Demo5&) = delete;
	Demo5& operator=(const Demo5&) = delete;

	Demo5(const int w, const int h);
	virtual ~Demo5();

	void Load() override;
	void Update() override;
	void Unload() override;


private:
	const unsigned int width;
	const unsigned int height;

	bool prevKey0 = false;
	bool prevKey1 = false;
	bool prevKey2 = false;


};
#endif // !DEMO5_H
