#include "Texture.h"


//---------------------------------------------------------------------------
//	CONSTRUCTOR
//---------------------------------------------------------------------------

Texture::Texture()
	: width(0), height(0), name(Texture::Name::UNINITIALIZED), textureID(0), 
	  minFilter(GL_LINEAR), magFilter(GL_LINEAR), wrapS(GL_CLAMP_TO_EDGE), wrapT(GL_CLAMP_TO_EDGE), hashID(0)
{
	memset(this->assetName, 0, NAMESIZE);
}

Texture::~Texture()
{ }


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void Texture::Set(const char* const _assetName, Texture::Name _name, GLuint texID, 
	GLenum min, GLenum mag, GLenum _wrapS, GLenum _wrapT, unsigned int w, unsigned int h, 
	unsigned int hash)
{
	//copy over name
	memcpy(this->assetName, _assetName, NAMESIZE - 1);

	this->name = _name;
	this->textureID = texID;
	this->minFilter = min;
	this->magFilter = mag;
	this->wrapS = _wrapS;
	this->wrapT = _wrapT;
	this->width = w;
	this->height = h;
	this->hashID = hash;
}

void Texture::SetName(Texture::Name _name)
{
	this->name = _name;
}

GLuint Texture::GetID()
{
	return this->textureID;
}

//---------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//---------------------------------------------------------------------------

bool Texture::Compare(Node* pNode)
{
	assert(pNode);
	Texture* pTemp = (Texture*)pNode;

	if (this->name == pTemp->name)
	{
		return true;
	}

	return false;
}

void Texture::ResetLink()
{
	DLink::ResetLink();

	//clear name
	memset(this->assetName, 0, NAMESIZE);

	this->name = Texture::Name::UNINITIALIZED;
	this->textureID = 0;
	this->minFilter = GL_LINEAR;
	this->magFilter = GL_LINEAR;
	this->wrapS = GL_CLAMP_TO_EDGE;
	this->wrapT = GL_CLAMP_TO_EDGE;
	this->width = 0;
	this->height = 0;
}