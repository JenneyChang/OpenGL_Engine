#pragma once
#ifndef DEMO4_H
#define DEMO4_H

#include "Scene.h"


//3D Skinned Model Anims 
class Demo4 : public Scene
{
public:
	// deleted functions
	Demo4() = delete;
	Demo4(const Demo4&) = delete;
	Demo4& operator=(const Demo4&) = delete;

	Demo4(const int w, const int h);
	virtual ~Demo4();

	void Load() override;
	void Update() override;
	void Unload() override;


private:
	const unsigned int width;
	const unsigned int height;


};
#endif // !DEMO4_H
