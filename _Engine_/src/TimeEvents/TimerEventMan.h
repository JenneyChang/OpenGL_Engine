#pragma once
#ifndef TIMER_EVENT_MAN_H
#define TIMER_EVENT_MAN_H

#include "Manager.h"
#include "TimerEvent.h"
#include "AnimTime.h"

using namespace Azul;

class TimerEventMan : public Manager
{
public:
	TimerEventMan() = delete;
	TimerEventMan(const TimerEventMan&) = delete;
	TimerEventMan& operator=(const TimerEventMan&) = delete;

	static void Create(int toReserve = 2, int toGrow = 1);
	static void Destroy();

	static TimerEvent* Add(TimerEvent::Name name, Command* cmd, AnimTime delta);
	static TimerEvent* Find(TimerEvent::Name name);
	static void Remove(TimerEvent* event);

	static AnimTime GetCurrTime();

	static void Update(AnimTime t);

protected:
	Node* derivedCreateNode() override;


private:
	TimerEvent* poCompare;
	AnimTime currTime;

	static TimerEventMan* poInstance;
	static TimerEventMan* prInstance();

	TimerEventMan(int toReserve, int toGrow);
	virtual ~TimerEventMan();


};
#endif // !TIMER_EVENT_MAN_H
