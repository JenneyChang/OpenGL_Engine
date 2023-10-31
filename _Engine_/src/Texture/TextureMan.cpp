#include "TextureMan.h"
#include "File.h"

using namespace Azul;

TextureMan* TextureMan::poInstance = nullptr;

//--------------------------------------------------------------------------
//	PRIVATE CONSTRUCTOR
//--------------------------------------------------------------------------

TextureMan::TextureMan(int numReserve, int numGrow)
	: Manager(numGrow)
{
	//fill reserve
	this->FillReserve(numReserve);

	//initialize comparison node
	this->poComparison = new Texture();
	assert(this->poComparison);
}

TextureMan::~TextureMan()
{ }


//--------------------------------------------------------------------------
//	PUBLIC STATIC METHODS
//--------------------------------------------------------------------------

void TextureMan::Create(int numReserve, int numGrow)
{
	if (TextureMan::poInstance == nullptr)
	{
		TextureMan::poInstance = new TextureMan(numReserve, numGrow);
		assert(TextureMan::poInstance);
	}
}

void TextureMan::Destroy()
{
	TextureMan* pManager = TextureMan::prInstance();

	//delete comparison node
	delete pManager->poComparison;
	pManager->poComparison = nullptr;

	//delete active & reserve lists
	Iterator* it = pManager->baseGetActiveIterator();
	Node* pNode = it->First();
	while (!it->IsDone())
	{
		Texture* ptemp = (Texture*)it->Curr();
		pNode = it->Next();
		delete ptemp;
	}

	it = pManager->baseGetReserveIterator();
	pNode = it->First();
	while (!it->IsDone())
	{
		Texture* ptemp = (Texture*)it->Curr();
		pNode = it->Next();
		delete ptemp;
	}

	//delete instance
	delete TextureMan::poInstance;
	TextureMan::poInstance = nullptr;
}

Texture* TextureMan::Add(const char* const filename, Texture::Name name)
{
	assert(filename);
	TextureMan* pManager = TextureMan::prInstance();

	GLuint texID;
	GLuint* pTexID = &texID;

	//generate opengl ID
	glGenTextures(1, &*pTexID);

	//bind texture
	glBindTexture(GL_TEXTURE_2D, *pTexID);

	//load proto texture
	texture_proto tproto;

	bool status = pManager->prLoadProtoTexture(tproto, filename);
	assert(status);

	//grab node from pool
	Texture* pNode = (Texture*)pManager->baseAddToFront();
	assert(pNode);

	//fill data
	pNode->Set(tproto.filename, name, texID, Translate::GetFilter(tproto.minFilter), 
		Translate::GetFilter(tproto.magFilter), Translate::GetWrap(tproto.wrapS), 
		Translate::GetWrap(tproto.wrapT), tproto.width, tproto.height, tproto.hash);

	return pNode;
}

Texture* TextureMan::Add(texture_proto& tproto, Texture::Name name)
{
	TextureMan* pManager = TextureMan::prInstance();

	GLuint texID;
	GLuint* pTexID = &texID;

	//generate opengl ID
	glGenTextures(1, &*pTexID);

	//bind texture
	glBindTexture(GL_TEXTURE_2D, *pTexID);

	bool status = pManager->prLoadTexture(tproto);
	assert(status);

	//grab node from pool
	Texture* pNode = (Texture*)pManager->baseAddToFront();
	assert(pNode);

	//fill data
	pNode->Set(tproto.filename, name, texID, Translate::GetFilter(tproto.minFilter),
		Translate::GetFilter(tproto.magFilter), Translate::GetWrap(tproto.wrapS),
		Translate::GetWrap(tproto.wrapT), tproto.width, tproto.height, tproto.hash);
	
	return pNode;
}

Texture* TextureMan::Find(Texture::Name name)
{
	TextureMan* pManager = TextureMan::prInstance();
	pManager->poComparison->SetName(name);

	Texture* pNode = (Texture*)pManager->baseFind(pManager->poComparison);
	assert(pNode);

	return pNode;
}

void TextureMan::Remove(Texture* pNode)
{
	assert(pNode);
	TextureMan* pManager = TextureMan::prInstance();
	pManager->baseRemove(pNode);
}

GLuint TextureMan::FindID(Texture::Name name)
{
	TextureMan* pManager = TextureMan::prInstance();

	Texture* pNode = pManager->Find(name);
	assert(pNode);

	return pNode->GetID();
}

void TextureMan::Print()
{
	TextureMan* pManager = TextureMan::prInstance();

	Trace::out("\n------------Texture Manager------------\n");
	pManager->basePrint();
}


//--------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//--------------------------------------------------------------------------

Node* TextureMan::derivedCreateNode()
{
	DLink* pNode = new Texture();
	assert(pNode != nullptr);

	return pNode;
}


//--------------------------------------------------------------------------
//	PRIVATE METHODS
//--------------------------------------------------------------------------

TextureMan* TextureMan::prInstance()
{
	assert(TextureMan::poInstance != nullptr);
	return TextureMan::poInstance;
}

bool TextureMan::prLoadProtoTexture(texture_proto& tproto, const char* filename)
{
	assert(filename);
	bool status = false;

	File::Handle fh;
	File::Error err;

	//open & grab file size
	err = File::Open(fh, filename, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	err = File::Seek(fh, File::Position::END, 0);
	assert(err == File::Error::SUCCESS);

	DWORD flength;
	err = File::Tell(fh, flength);
	assert(err == File::Error::SUCCESS);

	//read into buffer
	char* buffer = new char[flength]();
	assert(buffer);

	err = File::Seek(fh, File::Position::BEGIN, 0);
	assert(err == File::Error::SUCCESS);

	err = File::Read(fh, buffer, flength);
	assert(err == File::Error::SUCCESS);

	//close out
	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	//deserialize proto data-----------------------------------------------
	texture_proto_mssg mssg;
	status = mssg.ParseFromArray(buffer, flength);
	tproto.deserialize(mssg);

	delete[] buffer;

	status = this->prLoadTexture(tproto);

	return status;
}

bool TextureMan::prLoadTexture(texture_proto& tproto)
{
	bool status = false;

	//grab texture data from proto
	void* pBits = tproto.pData;

	if (pBits > 0)
	{
		int width = (int)tproto.width;
		int height = (int)tproto.height;

		int components = (int)Translate::GetComponent(tproto.ncomponent);
		GLenum eformat = Translate::GetFormat(tproto.eformat);
		GLuint minFilter = (GLint)Translate::GetFilter(tproto.minFilter);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)Translate::GetWrap(tproto.wrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)Translate::GetWrap(tproto.wrapT));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)Translate::GetFilter(tproto.minFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)Translate::GetFilter(tproto.magFilter));

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0, eformat, GL_UNSIGNED_BYTE, pBits);

		if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST ||
			minFilter == GL_NEAREST_MIPMAP_LINEAR || minFilter == GL_NEAREST_MIPMAP_NEAREST)
			glGenerateMipmap(GL_TEXTURE_2D);

		status = true;
	}

	return status;
}