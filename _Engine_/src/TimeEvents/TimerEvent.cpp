#include "TimerEvent.h"
#include "TimerEventMan.h"


//---------------------------------------------------------------------------
//	CONSTRUCTION
//---------------------------------------------------------------------------

TimerEvent::TimerEvent()
	: DLink(), name(TimerEvent::Name::UNINITIALIZED), poCommand(nullptr), 
	  triggerTime(AnimTime::Duration::ZERO), deltaTime(AnimTime::Duration::ZERO)
{ }

TimerEvent::~TimerEvent()
{
	delete this->poCommand;
}


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void TimerEvent::Set(TimerEvent::Name _name, Command* command, AnimTime delta)
{
	assert(command != nullptr);

	this->name = _name;
	this->poCommand = command;
	this->deltaTime = delta;

	this->triggerTime = TimerEventMan::GetCurrTime() + delta;
}

void TimerEvent::Set(TimerEvent::Name _name)
{
	this->name = _name;
}

AnimTime TimerEvent::GetTriggerTime()
{
	return this->triggerTime;
}

void TimerEvent::Update()
{
	assert(this->poCommand);
	this->poCommand->Execute(deltaTime);
}


//---------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//---------------------------------------------------------------------------

bool TimerEvent::Compare(Node* pNode)
{
	assert(pNode != nullptr);
	TimerEvent* pTmp = (TimerEvent*)pNode;

	if (this->name == pTmp->name)
	{
		return true;
	}

	return false;
}

bool TimerEvent::ComparePriority(Node* pNode)
{
	assert(pNode != nullptr);
	TimerEvent* pTmp = (TimerEvent*)pNode;

	if (this->triggerTime >= pTmp->triggerTime)
	{
		return true;
	}

	return false;
}

void TimerEvent::ResetLink()
{
	DLink::ResetLink();

	this->name = TimerEvent::Name::UNINITIALIZED;
	this->poCommand = nullptr;
	this->triggerTime = AnimTime(AnimTime::Duration::ZERO);
	this->deltaTime = AnimTime(AnimTime::Duration::ZERO);
}