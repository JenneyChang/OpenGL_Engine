#pragma once
#ifndef DEMO3_H
#define DEMO3_H

#include "Scene.h"

// 3D System: Various Models & Shaders
class Demo3 : public Scene
{
public:
	// deleted functions
	Demo3() = delete;
	Demo3(const Demo3&) = delete;
	Demo3& operator=(const Demo3&) = delete;

	Demo3(const int w, const int h);
	~Demo3();

	void Load() override;
	void Update() override;
	void Unload() override;


private:
	const unsigned int width;
	const unsigned int height;


};
#endif // !DEMO3_H
