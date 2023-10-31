#include "AnimateSprite.h"
#include "ImageMan.h"
#include "ImageNode.h"
#include "GraphicsObj_Sprite.h"
#include "TimerEventMan.h"


//---------------------------------------------------------------------------
//	CONSTRUCTION
//---------------------------------------------------------------------------

AnimateSprite::AnimateSprite(GameObj2D* sprite, TimerEvent::Name eventName)
{
	assert(sprite != nullptr);
	this->pSprite = sprite;

	this->pImageList = new SLinkMan();
	assert(pImageList);

	this->it = pImageList->GetIterator();
	assert(it != nullptr);

	this->name = eventName;
	//this->count = 0;
}

AnimateSprite::~AnimateSprite()
{
	//remove attached nodes
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		ImageNode* tmp = (ImageNode*)pNode;
		pNode = it->Next();

		delete tmp;
	}

	delete this->pImageList;
}


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void AnimateSprite::AttachImage(Image::Name _name)
{
	Image* pImage = ImageMan::Find(_name);
	assert(pImage != nullptr);

	//create node
	ImageNode* pNode = new ImageNode(pImage);
	assert(pNode);

	//attach
	this->pImageList->AddToFront(pNode);
	this->it = pImageList->GetIterator();
}

void AnimateSprite::AttachImage(Image* img)
{
	assert(img != nullptr);

	//create node
	ImageNode* pNode = new ImageNode(img);
	assert(pNode);

	//attach
	this->pImageList->AddToFront(pNode);
	this->it = pImageList->GetIterator();
}


//---------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//---------------------------------------------------------------------------

void AnimateSprite::Execute(AnimTime delta)
{
	ImageNode* pNode = (ImageNode*)it->Curr();
	
	//if reach the end
	if (it->Next() == nullptr)
	{
		//go back to beginning
		it->First();
	}

	//change image rendered
	GraphicsObj_Sprite* sprite = (GraphicsObj_Sprite*)this->pSprite->GetGraphicsObj();
	sprite->SwapImage(pNode->Get());

	//add back to timer
	TimerEventMan::Add(name, this, delta);
}