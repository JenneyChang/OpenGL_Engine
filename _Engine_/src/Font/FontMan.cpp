#include "FontMan.h"

FontMan* FontMan::poInstance = nullptr;

//--------------------------------------------------------------------------
//	PRIVATE CONSTRUCTION
//--------------------------------------------------------------------------

FontMan::FontMan(int toReserve, int toGrow)
	: Manager(toGrow)
{
	//prefill reserve
	this->FillReserve(toReserve);

	//create node
	this->poComparison = new Font();
	assert(poComparison);
}

FontMan::~FontMan()
{ }


//--------------------------------------------------------------------------
//	PUBLIC STATIC METHODS
//--------------------------------------------------------------------------

void FontMan::Create(int toReserve, int toGrow)
{
	if (FontMan::poInstance == nullptr)
	{
		FontMan::poInstance = new FontMan(toReserve, toGrow);
		assert(FontMan::poInstance != nullptr);
	}
}

void FontMan::Destroy()
{
	FontMan* pManager = FontMan::prInstance();
	assert(pManager);

	//active & reserve list
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		Font* tmp = (Font*)it->Curr();
		pNode = it->Next();

		delete tmp;
	}

	it = pManager->baseGetReserveIterator();
	pNode = it->First();
	while (!it->IsDone())
	{
		Font* tmp = (Font*)it->Curr();
		pNode = it->Next();

		delete tmp;
	}

	//remove comparison
	delete pManager->poComparison;
	pManager->poComparison = nullptr;

	//remove instance
	delete pManager->poInstance;
	pManager->poInstance = nullptr;
}

Font* FontMan::Add(GraphicsObj_Font* graphicsobj, FontName font,
	Glyph::Name glyph, std::string mssg, float x, float y)
{
	assert(!mssg.empty());
	assert(graphicsobj != nullptr);

	FontMan* pManager = FontMan::prInstance();

	//grab node from pool
	Font* pNode = (Font*)pManager->baseAddToFront();
	assert(pNode);

	//set data
	pNode->Set(graphicsobj, font, glyph, mssg, x, y);

	return pNode;
}

Font* FontMan::Find(FontName name)
{
	FontMan* pManager = FontMan::prInstance();

	pManager->poComparison->Set(name);
	Font* pNode = (Font*)pManager->baseFind(pManager->poComparison);

	return pNode;
}


//--------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//--------------------------------------------------------------------------

Node* FontMan::derivedCreateNode()
{
	DLink* pNode = new Font();
	assert(pNode);

	return pNode;
}


//--------------------------------------------------------------------------
//	PRIVATE METHODS
//--------------------------------------------------------------------------

FontMan* FontMan::prInstance()
{
	assert(FontMan::poInstance != nullptr);
	return FontMan::poInstance;
}
