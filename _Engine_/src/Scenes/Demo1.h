#pragma once
#ifndef DEMO_1_H
#define DEMO_1_H

#include "Scene.h"

// 2D System (Font & Sprites)
class Demo1 : public Scene
{
public:
	// deleted functions
	Demo1() = delete;
	Demo1(const Demo1&) = delete;
	Demo1& operator=(const Demo1&) = delete;

	Demo1(const int w, const int h);
	~Demo1();

	void Load() override;
	void Update() override;
	void Unload() override;


private:
	const unsigned int width;
	const unsigned int height;


};
#endif // !DEMO_1_H                                                                                         
