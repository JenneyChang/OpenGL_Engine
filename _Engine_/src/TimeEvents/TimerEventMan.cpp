#include "TimerEventMan.h"

TimerEventMan* TimerEventMan::poInstance = nullptr;

//---------------------------------------------------------------------------
//	PRIVATE CONSTRUCTION
//---------------------------------------------------------------------------

TimerEventMan::TimerEventMan(int toReserve, int toGrow)
	: Manager(toGrow)
{
	//prefill reserve
	this->FillReserve(toReserve);

	//create comparison node
	this->poCompare = new TimerEvent();
	assert(this->poCompare);

	this->currTime = AnimTime(AnimTime::Duration::ZERO);
}

TimerEventMan::~TimerEventMan()
{ }


//---------------------------------------------------------------------------
//	PUBLIC STATIC METHODS
//---------------------------------------------------------------------------

void TimerEventMan::Create(int toReserve, int toGrow)
{
	if (TimerEventMan::poInstance == nullptr)
	{
		TimerEventMan::poInstance = new TimerEventMan(toReserve, toGrow);
		assert(TimerEventMan::poInstance != nullptr);
	}
}

void TimerEventMan::Destroy()
{
	TimerEventMan* pManager = TimerEventMan::prInstance();
	assert(pManager != nullptr);

	//remove comparison 
	delete pManager->poCompare;
	pManager->poCompare = nullptr;

	//remove time events
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		TimerEvent* temp = (TimerEvent*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	it = pManager->baseGetReserveIterator();
	pNode = it->First();
	while (!it->IsDone())
	{
		TimerEvent* temp = (TimerEvent*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	//remove instance
	delete pManager->poInstance;
	pManager->poInstance = nullptr;
}

TimerEvent* TimerEventMan::Add(TimerEvent::Name name, Command* cmd, AnimTime delta)
{
	assert(cmd != nullptr);
	TimerEventMan* pManager = TimerEventMan::prInstance();

	//grab from reserve
	TimerEvent* pEvent = (TimerEvent*)pManager->baseGetReserve();
	assert(pEvent != nullptr);
	
	//set event & add by priority
	pEvent->Set(name, cmd, delta);
	pManager->baseAddByPriority(pEvent);

	return pEvent;
}

TimerEvent* TimerEventMan::Find(TimerEvent::Name name)
{
	TimerEventMan* pManager = TimerEventMan::prInstance();
	pManager->poCompare->Set(name);
	
	//the find
	TimerEvent* pEvent = (TimerEvent*)pManager->baseFind(pManager->poCompare);

	return pEvent;
}

void TimerEventMan::Remove(TimerEvent* event)
{
	assert(event != nullptr);
	TimerEventMan* pManager = TimerEventMan::prInstance();
	pManager->baseRemove(event);
}

AnimTime TimerEventMan::GetCurrTime()
{
	TimerEventMan* pManager = TimerEventMan::prInstance();
	return pManager->currTime;
}

void TimerEventMan::Update(AnimTime t)
{
	TimerEventMan* pManager = TimerEventMan::prInstance();

	//update time
	pManager->currTime = t;

	//trigger events
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		TimerEvent* tmp = (TimerEvent*)pNode;
		if (pManager->currTime >= tmp->GetTriggerTime())
		{
			tmp->Update();
			pManager->baseRemove(tmp);
		}

		pNode = it->Next();
	}
}


//---------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//---------------------------------------------------------------------------

Node* TimerEventMan::derivedCreateNode()
{
	TimerEvent* pNode = new TimerEvent();
	assert(pNode != nullptr);

	return pNode;
}


//---------------------------------------------------------------------------
//	PRIVATE METHODS
//---------------------------------------------------------------------------

TimerEventMan* TimerEventMan::prInstance()
{
	assert(TimerEventMan::poInstance != nullptr);
	return TimerEventMan::poInstance;
}