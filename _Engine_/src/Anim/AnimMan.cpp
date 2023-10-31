#include "AnimMan.h"
#include "File.h"

using namespace Azul;

AnimMan* AnimMan::poInstance = nullptr;

//---------------------------------------------------------------------------
//	PRIVATE CONSTRUCTION
//---------------------------------------------------------------------------

AnimMan::AnimMan(int toReserve, int toGrow)
	: Manager(toGrow)
{
	//prefill reserve
	this->FillReserve(toReserve);

	//create compparison node
	this->poComparison = new Anim();
	assert(this->poComparison);
}

AnimMan::~AnimMan()
{ }


//---------------------------------------------------------------------------
//	PUBLIC STATIC METHODS
//---------------------------------------------------------------------------

void AnimMan::Create(int toReserve, int toGrow)
{
	if (AnimMan::poInstance == nullptr)
	{
		AnimMan::poInstance = new AnimMan(toReserve, toGrow);
		assert(AnimMan::poInstance != nullptr);
	}
}

void AnimMan::Destroy()
{
	AnimMan* pManager = AnimMan::prInstance();
	assert(pManager);

	//remove active & reserve list
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		Anim* temp = (Anim*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	it = pManager->baseGetReserveIterator();
	pNode = it->First();
	while (!it->IsDone())
	{
		Anim* temp = (Anim*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	//remove comparison node
	delete pManager->poComparison;
	pManager->poComparison = nullptr;

	//remove instance
	delete pManager->poInstance;
	pManager->poInstance = nullptr;
}

Anim* AnimMan::Add(Anim::Name animName, Clip::Name clipName, Skeleton::Name skelName, float speed)
{
	AnimMan* pManager = AnimMan::prInstance();

	//grab node from pool
	Anim* pNode = (Anim*)pManager->baseAddToFront();
	assert(pNode);

	//set data
	AnimTime delta = speed * AnimTime(AnimTime::Duration::FILM_24_FRAME);
	pNode->Set(animName, delta, clipName, skelName);

	return pNode;
}

Anim* AnimMan::Find(Anim::Name name)
{
	AnimMan* pManager = AnimMan::prInstance();
	
	pManager->poComparison->Set(name);
	Anim* pNode = (Anim*)pManager->baseFind(pManager->poComparison);

	return pNode;
}

void AnimMan::Remove(Anim* anim)
{
	assert(anim);
	AnimMan* pManager = AnimMan::prInstance();

	pManager->baseRemove(anim);
}

void AnimMan::Print()
{
	AnimMan* pManager = AnimMan::prInstance();

	Trace::out("\n----------Anim Manager-------\n");
	pManager->basePrint();
}

void AnimMan::Update()
{
	//update all anims in active list
	Iterator* it = AnimMan::prInstance()->baseGetActiveIterator();

	Anim* pNode = (Anim*)it->First();
	while (!it->IsDone())
	{
		if (!pNode->blending)
		{
			//interpolate
			pNode->Animate();
		}
		else
		{
			//blending clips
			pNode->Blend();
		}
		
		//get next
		pNode = (Anim*)it->Next();
	}
}

void AnimMan::Play(Anim::Name name)
{
	AnimMan* pManager = AnimMan::prInstance();

	Anim* pAnim = pManager->Find(name);
	assert(pAnim);

	pAnim->Play();
}

void AnimMan::Pause(Anim::Name name)
{
	AnimMan* pManager = AnimMan::prInstance();

	Anim* pAnim = pManager->Find(name);
	assert(pAnim);

	pAnim->Pause();
}

void AnimMan::SpeedUp(Anim::Name name)
{
	AnimMan* pManager = AnimMan::prInstance();

	Anim* pAnim = pManager->Find(name);
	assert(pAnim);

	pAnim->SpeedUp();
}

void AnimMan::SlowDown(Anim::Name name)
{
	AnimMan* pManager = AnimMan::prInstance();

	Anim* pAnim = pManager->Find(name);
	assert(pAnim);

	pAnim->SlowDown();
}

void AnimMan::SwitchClip(Anim::Name animName, Clip::Name clipName)
{
	AnimMan* pManager = AnimMan::prInstance();

	Anim* pAnim = pManager->Find(animName);
	assert(pAnim);

	pAnim->SwitchClip(clipName);
}


//---------------------------------------------------------------------------
//	PROTECTED METHODS
//---------------------------------------------------------------------------

Node* AnimMan::derivedCreateNode()
{
	DLink* pNode = new Anim();
	assert(pNode);

	return pNode;
}


//---------------------------------------------------------------------------
//	PRIVATE METHODS
//---------------------------------------------------------------------------

AnimMan* AnimMan::prInstance()
{
	assert(AnimMan::poInstance != nullptr);
	return AnimMan::poInstance;
}

bool AnimMan::prLoadProto(const char* filename, anim_proto& aproto)
{
	assert(filename);

	bool status = false;
	File::Handle fh;
	File::Error err;

	err = File::Open(fh, filename, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	err = File::Seek(fh, File::Position::END, 0);
	assert(err == File::Error::SUCCESS);

	DWORD fileLength;
	err = File::Tell(fh, fileLength);
	assert(err == File::Error::SUCCESS);

	char* buffer = new char[fileLength]();
	assert(buffer);

	err = File::Seek(fh, File::Position::BEGIN, 0);
	assert(err == File::Error::SUCCESS);

	err = File::Read(fh, buffer, fileLength);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	anim_proto_mssg mssg;
	status = mssg.ParseFromArray(buffer, fileLength);
	aproto.deserialize(mssg);

	delete[] buffer;

	return status;
}