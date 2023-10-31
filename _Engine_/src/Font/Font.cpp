#include "Font.h"


//--------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------

Font::Font()
	: DLink(), name(FontName::Uninitialized), pGraphicsFont(nullptr)
{ }

Font::~Font()
{ }


//--------------------------------------------------------------------------
//	PUBLIC METHODS
//--------------------------------------------------------------------------

void Font::Set(FontName _name)
{
	this->name = _name;
}

void Font::Set(GraphicsObj_Font* graphicsobj, FontName _name, Glyph::Name glyph, std::string mssg, float x, float y)
{
	assert(graphicsobj);
	assert(!mssg.empty());

	this->name = _name;
	this->pGraphicsFont = graphicsobj;
	this->pGraphicsFont->Set(glyph, mssg, x, y);

}

void Font::UpdateMessage(std::string mssg)
{
	assert(!mssg.empty());
	assert(this->pGraphicsFont);

	this->pGraphicsFont->UpdateMessage(mssg);
}


//--------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//--------------------------------------------------------------------------

void Font::ResetLink() 
{
	DLink::ResetLink();
	this->name = FontName::Null;
}

bool Font::Compare(Node* pNode)
{
	assert(pNode);
	Font* tmp = (Font*)pNode;

	if (this->name == tmp->name)
	{
		return true;
	}

	return false;
}