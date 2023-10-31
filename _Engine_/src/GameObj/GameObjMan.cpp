#include "GameObjMan.h"
#include "MeshNull.h"
#include "MeshNodeMan.h"
#include "ShaderMan.h"
#include "ShaderGraphics.h"
#include "GraphicsObj_Null3D.h"
#include "GameObj_Null.h"

#include "PCSTreeForwardIterator.h"

using namespace Azul;

namespace Azul
{
	//-----------------------------------------------------------------------------------
	//	PRIVATE CONSTRUCTOR
	//-----------------------------------------------------------------------------------

	GameObjMan::GameObjMan()
	{
		//create & setup tree root
		MeshNull* pMesh = new MeshNull();
		MeshNodeMan::Add(Mesh::Name::NULL_MESH, pMesh);

		ShaderObj* pShader = new ShaderGraphics(ShaderObj::Name::NULL_SHADER, "null");
		ShaderMan::Add(pShader);
		assert(pShader);

		GraphicsObj_Null3D* pGraphicsObj = new GraphicsObj_Null3D(pMesh, pShader);
		GameObj_Null* pRootObj = new GameObj_Null(pGraphicsObj);
		((PCSNode*)pRootObj)->SetName("GameObj_Root");

		//create tree
		this->poRootTree = new PCSTree();
		assert(this->poRootTree);

		//attach root
		this->poRootTree->Insert((PCSNode*)pRootObj, this->poRootTree->GetRoot());
	}

	GameObjMan::~GameObjMan()
	{
		delete this->poRootTree;
	}


	//-----------------------------------------------------------------------------------
	//	PUBLIC METHODS
	//-----------------------------------------------------------------------------------

	void GameObjMan::Create()
	{
		GameObjMan* pManager = GameObjMan::prInstance();
		assert(pManager != nullptr);
	}

	void GameObjMan::Destroy()
	{
		GameObjMan* pManager = GameObjMan::prInstance();

		//delete tree
		PCSTree* pTree = pManager->poRootTree;
		PCSNode* pNode = nullptr;

		PCSTreeForwardIterator fwdIt(pTree->GetRoot());
		pNode = fwdIt.First();
		PCSNode* temp = nullptr;

		while (!fwdIt.IsDone())
		{
			temp = fwdIt.CurrentItem();
			pNode = fwdIt.Next();

			delete temp;
		}
	}

	void GameObjMan::Add(GameObj* pObj, GameObj* pParent)
	{
		assert(pObj);
		assert(pParent);

		//get instance
		GameObjMan* pManager = GameObjMan::prInstance();

		//insert into tree
		pManager->poRootTree->Insert(pObj, pParent);
	}

	void GameObjMan::Draw(void)
	{
		GameObjMan* pManager = GameObjMan::prInstance();

		//get root
		PCSNode* pRootNode = pManager->poRootTree->GetRoot();
		assert(pRootNode);

		//draw ea node
		PCSTreeForwardIterator fwdIt(pRootNode);
		GameObj* pNode = (GameObj*)fwdIt.First();
		while (!fwdIt.IsDone())
		{
			assert(pNode);

			pNode->Draw();
			pNode = (GameObj*)fwdIt.Next();
		}
	}

	void GameObjMan::Update(AnimTime currTime)
	{
		GameObjMan* pManager = GameObjMan::prInstance();

		//get root
		PCSNode* pRootNode = pManager->poRootTree->GetRoot();
		assert(pRootNode);

		//update ea node
		PCSTreeForwardIterator fwdIt(pRootNode);
		GameObj* pNode = (GameObj*)fwdIt.First();
		while (!fwdIt.IsDone())
		{
			assert(pNode);

			pNode->Update(currTime);
			pNode = (GameObj*)fwdIt.Next();
		}
	}

	GameObj* GameObjMan::GetRoot()
	{
		GameObjMan* pManager = GameObjMan::prInstance();

		GameObj* gameobj = (GameObj*)pManager->poRootTree->GetRoot();
		assert(gameobj);

		return gameobj;
	}

	PCSTree* GameObjMan::GetPCSTree()
	{
		GameObjMan* pManager = GameObjMan::prInstance();
		return pManager->poRootTree;
	}


	//-----------------------------------------------------------------------------------
	//	PRIVATE METHODS
	//-----------------------------------------------------------------------------------

	GameObjMan* GameObjMan::prInstance()
	{
		static GameObjMan poInstance;
		return &poInstance;
	}

	
}