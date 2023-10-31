#pragma once
#ifndef SCENE_MAN_H
#define SCENE_MAN_H

#include "Scene.h"

class SceneMan
{
public:
	//deleted functions
	SceneMan(const SceneMan&) = delete;
	SceneMan& operator=(const SceneMan&) = delete;

	static void Create(/*const int w, const int h*/);

	static void SetScene(Scene* scene);
	static Scene* GetScene();


private:
	static SceneMan* Instance();

	SceneMan();
	~SceneMan();

	Scene* pCurrScene;


};
#endif // !SCENE_MAN_H
