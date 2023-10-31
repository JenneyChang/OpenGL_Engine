#include "ImageMan.h"

ImageMan* ImageMan::poInstance = nullptr;

//---------------------------------------------------------------------------
//	CONSTRUCTION
//---------------------------------------------------------------------------

ImageMan::ImageMan(int toReserve, int toGrow)
	: Manager(toGrow)
{
	//prefill reserve
	this->FillReserve(toReserve);

	//setup comparison node
	this->poComparison = new Image();
	assert(this->poComparison);
}

ImageMan::~ImageMan()
{ }


//---------------------------------------------------------------------------
//	PUBLIC STATIC METHODS
//---------------------------------------------------------------------------

void ImageMan::Create(int toReserve, int toGrow)
{
	if (ImageMan::poInstance == nullptr)
	{
		ImageMan::poInstance = new ImageMan(toReserve, toGrow);
		assert(ImageMan::poInstance != nullptr);
	}
}

void ImageMan::Destroy()
{
	ImageMan* pManager = ImageMan::prInstance();
	assert(pManager);

	//delete comparison node
	delete pManager->poComparison;
	pManager->poComparison = nullptr;

	//delete active list
	Iterator* it = pManager->baseGetActiveIterator();
	Node* node = it->First();
	while (!it->IsDone())
	{
		Image* deleteIt = (Image*)it->Curr();
		node = it->Next();

		delete deleteIt;
	}

	//delete reserve list
	it = pManager->baseGetReserveIterator();
	node = it->First();
	while (!it->IsDone())
	{
		Image* deleteIt = (Image*)it->Curr();
		node = it->Next();

		delete deleteIt;
	}

	//delete instance
	delete ImageMan::poInstance;
	ImageMan::poInstance = nullptr;
}

Image* ImageMan::Add(Image::Name name, Texture* texture, Rect rect)
{
	assert(texture);
	ImageMan* pManager = ImageMan::prInstance();

	//grab node from pool
	Image* pNode = (Image*)pManager->baseAddToFront();
	assert(pNode);

	//set data
	pNode->Set(name, texture, rect);

	return pNode;
}

Image* ImageMan::Find(Image::Name name)
{
	ImageMan* pManager = ImageMan::prInstance();

	pManager->poComparison->Set(name);
	Image* pNode = (Image*)pManager->baseFind(pManager->poComparison);

	return pNode;
}

void ImageMan::Remove(Image* img)
{
	assert(img);
	ImageMan* pManager = ImageMan::prInstance();
	pManager->baseRemove(img);
}

void ImageMan::Print()
{
	ImageMan* pManager = ImageMan::prInstance();

	Trace::out("\n-----------Image Manager----------\n");
	pManager->basePrint();
}


//---------------------------------------------------------------------------
//	PROTECTED METHODS
//---------------------------------------------------------------------------

Node* ImageMan::derivedCreateNode()
{
	DLink* pNode = new Image();
	assert(pNode);

	return pNode;
}


//---------------------------------------------------------------------------
//	PRIVATE METHODS
//---------------------------------------------------------------------------

ImageMan* ImageMan::prInstance()
{
	assert(ImageMan::poInstance != nullptr);
	return ImageMan::poInstance;
}