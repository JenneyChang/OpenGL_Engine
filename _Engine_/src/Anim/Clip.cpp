#include "Clip.h"

using namespace Azul;

//---------------------------------------------------------------------------
//	CONSTRUCTION
//---------------------------------------------------------------------------

Clip::Clip()
	: name(Clip::Name::UNINITIALIZED), poHead(nullptr), duration(AnimTime::Duration::ZERO),
	  numFrames(0), numJoints(0)
{ }

Clip::~Clip()
{
	//clean up frame list
	Frames* temp = this->poHead;
	while (temp != nullptr)
	{
		Frames* deleteIt = temp;
		temp = temp->pNext;

		delete deleteIt;
	}
}


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void Clip::Set(Clip::Name _name)
{
	this->name = _name;
}

void Clip::Set(Clip::Name _name, clip_proto& cproto, int numjoints)
{
	this->name = _name;
	this->numJoints = numjoints;
	this->numFrames = (unsigned int)cproto.numFrames;
	this->duration = cproto.duration * AnimTime(AnimTime::Duration::FILM_24_FRAME);

	//load frames from proto
	Joint* poJoint = new Joint[numJoints]();
	assert(poJoint);

	Frames* curr = nullptr;
	Frames* prev = nullptr;
	for (size_t i = 0; i < (unsigned int)numFrames; ++i)
	{
		auto& f = cproto.frames[i];
		if (this->poHead == nullptr)
		{
			//empty list
			//create new frame & add to list
			curr = new Frames();
			curr->pPrev = nullptr;
			curr->pNext = nullptr;
			curr->keytime = f.keytime * AnimTime(AnimTime::Duration::FILM_24_FRAME);
			curr->poSSBO_Joints = new SSBO();

			this->poHead = curr;
			prev = curr;	
		}
		else
		{
			//add to end list
			curr = new Frames();
			curr->pPrev = prev;
			curr->pNext = nullptr;
			curr->keytime = f.keytime * AnimTime(AnimTime::Duration::FILM_24_FRAME);
			curr->poSSBO_Joints = new SSBO();

			prev->pNext = curr;
			prev = curr;
		}

		//grab bone data
		//Trace::out("\nFrame[%d]\t\t Keytime[%f] \n", i, f.keytime);
		for (size_t j = 0; j < numJoints; ++j)
		{
			auto& b = cproto.frames[i].bones[j];

			poJoint[j].Trans.set(b.trans.x, b.trans.y, b.trans.z);
			poJoint[j].Rot.set(b.rot.x, b.rot.y, b.rot.z, b.rot.w);
			poJoint[j].Scale.set(b.scale.x, b.scale.y, b.scale.z);

		/*	Trace::out("Joint %d\n", j);
			Trace::out("[Trans] = Vect( %ff, %ff, %ff )\n", prev->poJoint[j].Trans[x], prev->poJoint[j].Trans[y], prev->poJoint[j].Trans[z]);
			Trace::out("[ Quat] = Quat( %ff, %ff, %ff, %ff )\n", prev->poJoint[j].Rot[x], prev->poJoint[j].Rot[y], prev->poJoint[j].Rot[z], prev->poJoint[j].Rot[w]);
			Trace::out("[Scale] = Vect( %ff, %ff, %ff )\n", prev->poJoint[j].Scale[x], prev->poJoint[j].Scale[y], prev->poJoint[j].Scale[z]);*/
		}

		//TODO: clean up
		prev->poSSBO_Joints->Set(numJoints, sizeof(Joint), poJoint);
	}

	delete[] poJoint;
}

AnimTime Clip::GetDuration()
{
	return this->duration;
}

int Clip::GetNumJoints()
{
	return this->numJoints;
}

void Clip::AnimateBones(AnimTime t, SSBO* pSSBOIn)
{
	Frames* temp = this->prFindCurrFrame(t);

	//pA = prev frame & pB is curr key frame (temp)
	Frames* pA = temp->pPrev;
	Frames* pB = temp;

	float ts = (t - pA->keytime) / (pB->keytime - pA->keytime);
	Mixer::Blend( pSSBOIn, pA->poSSBO_Joints, pB->poSSBO_Joints, ts, this->numJoints);
}

bool Clip::Compare(Node* pNode)
{
	assert(pNode != nullptr);
	Clip* pTemp = (Clip*)pNode;

	if (this->name == pTemp->name)
	{
		return true;
	}

	return false;
}


//---------------------------------------------------------------------------
//	PRIVATE METHODS
//---------------------------------------------------------------------------

Clip::Frames* Clip::prFindCurrFrame(AnimTime t)
{
	//grab first frame
	Frames* temp = this->poHead;

	//find which key frames we're in
	while (t >= temp->keytime && temp->pNext != nullptr)
	{
		temp = temp->pNext;
	}

	return temp;
}