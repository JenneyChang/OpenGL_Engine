#include "GlyphMan.h"
#include "File.h"
#include "TextureMan.h"

using namespace Azul;

GlyphMan* GlyphMan::poInstance = nullptr;

//--------------------------------------------------------------------------
//	PRIVATE CONSTRUCTION
//--------------------------------------------------------------------------

GlyphMan::GlyphMan(int toReserve, int toGrow)
	: Manager(toGrow)
{ 
	//prefill reserve
	this->FillReserve(toReserve);

	//setup comparison node
	this->poComparison = new Glyph();
	assert(this->poComparison);
}

GlyphMan::~GlyphMan()
{ }


//--------------------------------------------------------------------------
//	PUBLIC STATIC METHODS
//--------------------------------------------------------------------------

void GlyphMan::Create(int toReserve, int toGrow)
{
	if (GlyphMan::poInstance == nullptr)
	{
		GlyphMan::poInstance = new GlyphMan(toReserve, toGrow);
		assert(GlyphMan::poInstance != nullptr);
	}
}

void GlyphMan::Destroy()
{
	GlyphMan* pManager = GlyphMan::prInstance();
	assert(pManager);

	//active & reserve list
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		Glyph* temp = (Glyph*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	it = pManager->baseGetReserveIterator();
	pNode = it->First();
	while (!it->IsDone())
	{
		Glyph* temp = (Glyph*)it->Curr();
		pNode = it->Next();

		delete temp;
	}

	//delete comparison
	delete pManager->poComparison;
	pManager->poComparison = nullptr;

	//delete instance
	delete pManager->poInstance;
	pManager->poInstance = nullptr;
}

void GlyphMan::Add(Glyph::Name name, const char* filename, Texture::Name texname)
{
	assert(filename);
	GlyphMan* pManager = GlyphMan::prInstance();

	//load file
	font_proto fproto;
	pManager->prLoadFile(filename, fproto);

	//add texture
	Texture* texture = TextureMan::Add(fproto.fontTex, texname);
	assert(texture);

	//grab node from reserve
	Glyph* pNode = (Glyph*)pManager->baseAddToFront();
	assert(pNode);

	//set data
	pNode->Set(name, texture, fproto);
}

void GlyphMan::Remove(Glyph* glyph)
{
	assert(glyph);

	GlyphMan* pManager = GlyphMan::prInstance();
	pManager->baseRemove(glyph);
}

Glyph* GlyphMan::Find(Glyph::Name name)
{
	assert(name != Glyph::Name::UNINITIALIZED);
	
	GlyphMan* pManager = GlyphMan::prInstance();
	
	pManager->poComparison->Set(name);
	Glyph* pGlyph = (Glyph*)pManager->baseFind(pManager->poComparison);

	return pGlyph;
}

Rect GlyphMan::FindKey(Glyph::Name name, int key)
{
	assert(key);
	assert(name != Glyph::Name::UNINITIALIZED);

	Glyph* pGlyph = Find(name);
	assert(pGlyph);

	Rect pRect = pGlyph->GetKey(key);

	return pRect;
}


//--------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//--------------------------------------------------------------------------

Node* GlyphMan::derivedCreateNode()
{
	Glyph* pNode = new Glyph();
	assert(pNode != nullptr);

	return pNode;
}


//--------------------------------------------------------------------------
//	PRIVATE METHODS
//--------------------------------------------------------------------------

GlyphMan* GlyphMan::prInstance()
{
	assert(GlyphMan::poInstance != nullptr);
	return GlyphMan::poInstance;
}

void GlyphMan::prLoadFile(const char* filename, font_proto& fproto)
{
	assert(filename != nullptr);

	//read font proto file
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

	//parse proto message
	font_proto_mssg mssg;
	mssg.ParseFromArray(buffer, fileLength);

	//deserialize it
	fproto.deserialize(mssg);

	//clean up
	delete[] buffer;
}