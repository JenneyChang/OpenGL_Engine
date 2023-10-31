#include "SkeletonMan.h"
#include "File.h"

using namespace Azul;

SkeletonMan* SkeletonMan::poInstance = nullptr;

//-----------------------------------------------------------------------------------
//	PRIVATE CONSTRUCTION
//-----------------------------------------------------------------------------------

SkeletonMan::SkeletonMan(int toReserve, int toGrow)
	: Manager(toGrow)
{
	//prefill reserve
	this->FillReserve(toReserve);

	//setup comparison node
	this->poComparison = new Skeleton();
	assert(this->poComparison);
}

SkeletonMan::~SkeletonMan()
{ }


//-----------------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------------

void SkeletonMan::Create(int toReserve, int toGrow)
{
	if (SkeletonMan::poInstance == nullptr)
	{
		SkeletonMan::poInstance = new SkeletonMan(toReserve, toGrow);
		assert(SkeletonMan::poInstance != nullptr);
	}
}

void SkeletonMan::Destroy()
{
	SkeletonMan* pManager = SkeletonMan::prInstance();
	assert(pManager);

	//delete comparison 
	delete pManager->poComparison;
	pManager->poComparison = nullptr;

	//delete active & reserve list
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		Skeleton* temp = (Skeleton*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	it = pManager->baseGetReserveIterator();
	pNode = it->First();
	while (!it->IsDone())
	{
		Skeleton* temp = (Skeleton*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	//delete instance
	delete pManager->poInstance;
	pManager->poInstance = nullptr;
}

Skeleton* SkeletonMan::Add(Skeleton::Name name, const char* filename)
{
	assert(filename);
	SkeletonMan* pManager = SkeletonMan::prInstance();

	//load file
	hierarchy_proto hproto;
	pManager->prLoadFile(filename, hproto);

	//grab node from pool
	Skeleton* pNode = (Skeleton*)pManager->baseAddToFront();
	assert(pNode);

	//set data
	pNode->Set(name, hproto);

	return pNode;
}

Skeleton* SkeletonMan::Find(Skeleton::Name name)
{
	SkeletonMan* pManager = SkeletonMan::prInstance();
	pManager->poComparison->Set(name);
	
	Skeleton* pNode = (Skeleton*)pManager->baseFind(pManager->poComparison);
	assert(pNode);

	return pNode;
}

void SkeletonMan::Remove(Skeleton* skeleton)
{
	assert(skeleton);
	SkeletonMan* pManager = SkeletonMan::prInstance();

	pManager->baseRemove(skeleton);
}

void SkeletonMan::Print()
{
	SkeletonMan* pManager = SkeletonMan::prInstance();

	Trace::out("\n-------------Skeleton Manager-------------\n");
	pManager->basePrint();
}


//-----------------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//-----------------------------------------------------------------------------------

Node* SkeletonMan::derivedCreateNode()
{
	DLink* pNode = new Skeleton();
	assert(pNode != nullptr);

	return pNode;
}


//-----------------------------------------------------------------------------------
//	PRIVATE METHODS
//-----------------------------------------------------------------------------------

SkeletonMan* SkeletonMan::prInstance()
{
	assert(SkeletonMan::poInstance != nullptr);
	return SkeletonMan::poInstance;
}

bool SkeletonMan::prLoadFile(const char* filename, hierarchy_proto& hproto)
{
	assert(filename);
	bool status;

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

	hierarchy_proto_mssg mssg;
	status = mssg.ParseFromArray(buffer, fileLength);
	hproto.deserialize(mssg);

	delete[] buffer;

	return status;
}