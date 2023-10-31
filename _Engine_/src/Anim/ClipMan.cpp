#include "ClipMan.h"
#include "File.h"

using namespace Azul;

ClipMan* ClipMan::poInstance = nullptr;

//---------------------------------------------------------------------------
//	PRIVATE CONSTRUCTION
//---------------------------------------------------------------------------

ClipMan::ClipMan(int toReserve, int toGrow)
	: Manager(toGrow)
{
	//prefill reserve
	this->FillReserve(toReserve);

	//setup comparison node
	this->poComparison = new Clip();
	assert(this->poComparison);
}

ClipMan::~ClipMan()
{ }


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void ClipMan::Create(int toReserve, int toGrow)
{
	if (ClipMan::poInstance == nullptr)
	{
		ClipMan::poInstance = new ClipMan(toReserve, toGrow);
		assert(ClipMan::poInstance);
	}
}

void ClipMan::Destroy()
{
	ClipMan* pManager = ClipMan::prInstance();
	assert(pManager);

	//delete comparison node
	delete pManager->poComparison;
	pManager->poComparison = nullptr;

	//remove active & reserve lists
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		Clip* temp = (Clip*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	it = pManager->baseGetReserveIterator();
	pNode = it->First();
	while (!it->IsDone())
	{
		Clip* temp = (Clip*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	//delete instance
	delete pManager->poInstance;
	pManager->poInstance = nullptr;
}

Clip* ClipMan::Add(Clip::Name name, const char* filename)
{
	assert(filename);
	ClipMan* pManager = ClipMan::prInstance();

	//load file
	anim_proto aproto;
	pManager->prLoadFile(filename, aproto);

	//grab node from pool
	Clip* pNode = (Clip*)pManager->baseAddToFront();
	assert(pNode);

	//set data
	//assert(aproto.numClips == 1);	//do i need to accomodate multiple clipsa
	pNode->Set(name, aproto.clips[0], aproto.skelSize);

	return pNode;
}

Clip* ClipMan::Find(Clip::Name name)
{
	ClipMan* pManager = ClipMan::prInstance();

	pManager->poComparison->Set(name);
	Clip* pNode = (Clip*)pManager->baseFind(pManager->poComparison);

	return pNode;
}

void ClipMan::Remove(Clip* clip)
{
	assert(clip);
	ClipMan* pManager = ClipMan::prInstance();

	pManager->baseRemove(clip);
}

void ClipMan::Print()
{
	ClipMan* pManager = ClipMan::prInstance();

	Trace::out("\n--------------Clip Manager-----------\n");
	pManager->basePrint();
}

//---------------------------------------------------------------------------
//	PROTECTED METHODS
//---------------------------------------------------------------------------

Node* ClipMan::derivedCreateNode()
{
	DLink* pNode = new Clip();
	assert(pNode);

	return pNode;
}


//---------------------------------------------------------------------------
//	PRIVATE METHODS
//---------------------------------------------------------------------------

ClipMan* ClipMan::prInstance()
{
	assert(ClipMan::poInstance != nullptr);
	return ClipMan::poInstance;
}

bool ClipMan::prLoadFile(const char* filename, anim_proto& aproto)
{
	assert(filename);
	bool status;

	//load anim proto
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