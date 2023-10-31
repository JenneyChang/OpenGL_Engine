#include "Anim.h"
#include "MathEngine.h"
#include "ClipMan.h"
#include "SkeletonMan.h"
#include "MeshNodeMan.h"

using namespace Azul;

//---------------------------------------------------------------------------
//	CONSTRUCTION
//---------------------------------------------------------------------------

Anim::Anim()
	: DLink(), name(Anim::Name::UNINITIALIZED), pClip(nullptr), pSkeleton(nullptr),
	  poTimer(nullptr), poSSBO_JointResult(new SSBO()), speed(0.0f)
{ 
	assert(poSSBO_JointResult);

	this->poResultA = new SSBO();
	assert(this->poResultA);

	this->poResultB = new SSBO();
	assert(this->poResultB);
}

Anim::~Anim()
{ 
	delete this->poTimer;
	delete this->poSSBO_JointResult;
	
	delete this->poResultA;
	delete this->poResultB;
}


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void Anim::Set(Anim::Name _name)
{
	this->name = _name;
}

void Anim::Set(Anim::Name _name, AnimTime delta, Clip::Name clip, Skeleton::Name skel)
{
	this->name = _name;

	this->pClip = ClipMan::Find(clip);
	assert(this->pClip);

	this->pSkeleton = SkeletonMan::Find(skel);
	assert(this->pSkeleton);

	//set up ssbo --> add 1 to account for hierarchy  table
	unsigned int numJoints = (unsigned int)pClip->GetNumJoints();
	Joint* poResult = new Joint[numJoints + 1]();
	assert(poResult);

	poSSBO_JointResult->Set(numJoints + 1, sizeof(Joint), poResult);

	//set timer
	AnimTime min = AnimTime(AnimTime::Duration::ZERO);
	AnimTime max = this->pClip->GetDuration();
	this->poTimer = new Timer(delta, min, max);
	assert(this->poTimer);

	//clean up
	delete[] poResult;
}

void Anim::SetBlend(Clip::Name _clipB, float duration, float blendfactor)
{
	//set up clip we want to blend with, duration of blend, and start blend %
	this->pClipB = ClipMan::Find(_clipB);
	assert(this->pClipB);

	this->t_duration = duration;
	this->blendFactor = blendfactor;
	this->t_elapsed = 0.0f;

	unsigned int numJoints = (unsigned int)pClip->GetNumJoints();
	Joint* pResultA = new Joint[numJoints];
	Joint* pResultB = new Joint[numJoints];


	poResultA->Set(numJoints, sizeof(Joint), pResultA);
	poResultB->Set(numJoints, sizeof(Joint), pResultB);

	delete[] pResultA;
	delete[] pResultB;
}

SSBO* Anim::GetSSBOJointResult()
{
	assert(this->poSSBO_JointResult);
	return this->poSSBO_JointResult;
}

void Anim::Animate()
{
	this->poTimer->Update();
	this->pClip->AnimateBones(this->poTimer->GetCurrTime(), this->poSSBO_JointResult);
}

void Anim::Blend()
{
	float fps = (AnimTime(AnimTime::Duration::ONE_SECOND) / AnimTime(AnimTime::Duration::FILM_24_FRAME));
	float tic = 1.0f / fps;
	float incrBlend = 1.0f / (t_duration * fps);

	this->poTimer->SetDelta(0.00001f * AnimTime(AnimTime::Duration::FILM_24_FRAME));

	//blend till elapsed time = duration
	if (!Util::isEqual(t_elapsed, t_duration, MATH_TOLERANCE))
	{
		//note: clips may have diff playback rates...should be synced based on blend
		this->poTimer->Update();
		this->pClip->AnimateBones(poTimer->GetCurrTime(), poResultA);
		pClipB->AnimateBones(poTimer->GetCurrTime(), poResultB);

		//blend two results
		Mixer::Blend(this->poSSBO_JointResult, poResultA, poResultB, blendFactor, pClip->GetNumJoints());

		//update blend factor & elapsed time
		if (!Util::isOne(blendFactor, MATH_TOLERANCE))
		{
			this->blendFactor += incrBlend;
		}
		else
		{
			this->blendFactor = 1.0f;
		}

		t_elapsed += tic;
	}
	else
	{
		blending = false;
		this->pClip = pClipB;

		//save previous time
		AnimTime currTime = poTimer->GetCurrTime();
		delete this->poTimer;

		//reset timer
		AnimTime delta = 0.01f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		AnimTime min = AnimTime(AnimTime::Duration::ZERO);
		AnimTime max = pClipB->GetDuration();
		this->poTimer = new Timer(delta, min, max);
		this->poTimer->SetCurrTime(currTime);
	}
}

void Anim::Play()
{
	AnimTime delta = 0.01f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
	this->poTimer->SetDelta(delta);
}

void Anim::Pause()
{
	AnimTime delta = 0.0f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
	this->poTimer->SetDelta(delta);
}

void Anim::SpeedUp()
{	
	if (speed <= 0.1f)
	{
		speed += 0.002f;
	}

	AnimTime delta = speed * AnimTime(AnimTime::Duration::FILM_24_FRAME);
	this->poTimer->SetDelta(delta);
}

void Anim::SlowDown()
{
	if (speed <= -0.1f)
	{
		speed += -0.002f;
	}
	
	AnimTime delta = speed * AnimTime(AnimTime::Duration::FILM_24_FRAME);
	this->poTimer->SetDelta(delta);
}

void Anim::SwitchClip(Clip::Name clipName)
{
	this->pClip = ClipMan::Find(clipName);
	assert(this->pClip);
}

void Anim::LinkAnim(Mesh::Name meshName, Vec3 lightPos, Vec4 lightColor, Vec3 scale, Vec3 trans, Quat rot)
{
	Mesh* pMesh = MeshNodeMan::Find(meshName);
	assert(pMesh);
	assert(this->pSkeleton);

	this->pSkeleton->SetHierarchy(this->poSSBO_JointResult, pMesh, lightPos, lightColor, scale, trans, rot);
}


//---------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//---------------------------------------------------------------------------

void Anim::ResetLink()
{
	this->pPrev = nullptr;
	this->pNext = nullptr;

	this->name = Anim::Name::UNINITIALIZED;
	this->pClip = nullptr;
	this->pSkeleton = nullptr;

	delete this->poTimer;
}

bool Anim::Compare(Node* pNode)
{
	assert(pNode);
	Anim* pTemp = (Anim*)pNode;

	if (this->name == pTemp->name)
	{
		return true;
	}

	return false;
}