#pragma once
#ifndef TIMER_EVENT_H
#define TIMER_EVENT_H

#include "DLink.h"
#include "Command.h"

using namespace Azul;

class TimerEvent : public DLink
{
public:
	enum class Name
	{
		OCTOPUS,
		CRAB,
		SQUID,

		SM_WALKING,
		SM_RUNNING,
		SM_JUMPING,
		SM_POGO,
		SM_FALLING,
		SM_SIGH,

		VEGA_KICK,
		VEGA_STAB,
		VEGA_IDLE,

		LWALK,
		LSWING,

		UNINITIALIZED
	};

	TimerEvent();
	virtual ~TimerEvent();
	
	void Set(TimerEvent::Name _name, Command* pCommand, AnimTime delta);
	void Set(TimerEvent::Name _name);

	AnimTime GetTriggerTime();

	void Update();

	bool Compare(Node* pNode) override;
	bool ComparePriority(Node* pNode) override;
	void ResetLink() override;

	
private:
	TimerEvent::Name name;
	Command* poCommand;
	AnimTime triggerTime;	//in global time	--> AnimTime?
	AnimTime deltaTime;	//secs til activate


};
#endif // !TIMER_EVENT_H
