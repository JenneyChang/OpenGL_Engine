#include "Timer.h"

using namespace Azul;

//---------------------------------------------------------------------------
//	CONSTRUCTION
//---------------------------------------------------------------------------

Timer::Timer(AnimTime delta, AnimTime min, AnimTime max)
	: currt(AnimTime::Duration::ZERO), deltat(delta), maxt(max), mint(min)
{ }


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void Timer::Update()
{
	currt += deltat;

	//protection for looping
	if (currt < mint)
	{
		currt = maxt;
	}
	else if (currt > maxt)
	{
		currt = mint;
	}
	else
	{
		//do nothing
	}
}

void Timer::SetCurrTime(const AnimTime t)
{
	this->currt = t;
}

AnimTime Timer::GetCurrTime() const
{
	return this->currt;
}

void Timer::SetDelta(const AnimTime t)
{
	this->deltat = t;
}

AnimTime Timer::GetDelta() const
{
	return this->deltat;
}