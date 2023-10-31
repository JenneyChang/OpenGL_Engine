#include "Glyph.h"


//--------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------

Glyph::Glyph()
	: DLink(), name(Glyph::Name::UNINITIALIZED), pTexture(nullptr)
{ }

Glyph::~Glyph()
{ 
	this->keys.clear();
}


//--------------------------------------------------------------------------
//	PUBLIC METHODS
//--------------------------------------------------------------------------

void Glyph::Set(Glyph::Name _name)
{
	this->name = _name;
}

Texture* Glyph::GetTexture()
{
	assert(pTexture);
	return this->pTexture;
}

void Glyph::Set(Glyph::Name _name, Texture* texture, font_proto& fproto)
{
	assert(texture);

	this->name = _name;
	this->pTexture = texture;
	this->listSize = fproto.keylist.size();

	for (size_t i = 0; i < fproto.keylist.size(); ++i)
	{
		keys.emplace(fproto.keylist[i].key, 
			    Rect((float)fproto.keylist[i].x, 
					 (float)fproto.keylist[i].y, 
					 (float)fproto.keylist[i].w, 
					 (float)fproto.keylist[i].h));
	}
}

Rect Glyph::GetKey(int key)
{
	return this->keys[key];
}

GLuint Glyph::GetTexID()
{
	return this->pTexture->GetID();
}


//--------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//--------------------------------------------------------------------------

void Glyph::ResetLink()
{
	DLink::ResetLink();

	this->name = Glyph::Name::UNINITIALIZED;
	this->pTexture = nullptr;
	this->keys.clear();
}

bool Glyph::Compare(Node* pNode)
{
	assert(pNode != nullptr);
	Glyph* pTemp = (Glyph*)pNode;

	//finds 1 set of glyphs
	if (this->name == pTemp->name)
	{
		return true;
	}

	return false;
}