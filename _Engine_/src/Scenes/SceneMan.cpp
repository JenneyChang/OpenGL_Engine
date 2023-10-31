#include "SceneMan.h"

SceneMan::SceneMan()
	: pCurrScene(nullptr)
{ }

SceneMan::~SceneMan()
{ }

void SceneMan::Create(/*const int w, const int h*/)
{
	SceneMan* pManager = SceneMan::Instance();
	assert(pManager);
}

void SceneMan::SetScene(Scene* scene)
{
	SceneMan* pManager = SceneMan::Instance();
	assert(pManager);
	assert(scene);

	if (pManager->pCurrScene)
	{
		// unload active scene
		pManager->pCurrScene->Unload();

		// load new scene
		pManager->pCurrScene = scene;
		pManager->pCurrScene->Load();
	}
	else
	{
		pManager->pCurrScene = scene;
		pManager->pCurrScene->Load();
	}
}

Scene* SceneMan::GetScene()
{
	SceneMan* pManager = SceneMan::Instance();
	assert(pManager);

	return pManager->pCurrScene;
}

SceneMan* SceneMan::Instance()
{
	static SceneMan poInstance;
	return &poInstance;
}
