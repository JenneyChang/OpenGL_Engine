#pragma once
#ifndef TIMER_H
#define TIMER_H

#include "AnimTimer.h"

using namespace Azul;

class Timer
{
public:
	Timer() = delete;
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

	Timer(AnimTime delta, AnimTime min, AnimTime max);
	~Timer() = default;

	void Update();

	void SetCurrTime(const AnimTime t);
	AnimTime GetCurrTime() const;

	void SetDelta(const AnimTime t);
	AnimTime GetDelta() const;


private:
	AnimTime currt;
	AnimTime deltat;
	AnimTime maxt;
	AnimTime mint;


};
#endif // !TIMER_H
