#pragma once
#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Load() = 0;
	virtual void Update() = 0;
	virtual void Unload() = 0;

};
#endif // !SCENE_H
