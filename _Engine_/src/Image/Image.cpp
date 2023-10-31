#include "Image.h"

//---------------------------------------------------------------------------
//	CONSTRUCTOR
//---------------------------------------------------------------------------

Image::Image()
{
	this->name = Image::Name::UNINITIALIZED;
	this->pTexture = nullptr;
	this->pRect.Clear();
}

Image::~Image()
{ }


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void Image::Set(Image::Name _name, Texture* _pTexture, Rect rect)
{
	assert(_pTexture);

	this->name = _name;
	this->pTexture = _pTexture;
	this->pRect = rect;
}

void Image::Set(Image::Name _name)
{
	this->name = _name;
}

Image::Name Image::Get()
{
	return this->name;
}


//---------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//---------------------------------------------------------------------------

void Image::ResetLink()
{
	DLink::ResetLink();

	this->name = Image::Name::UNINITIALIZED;
	this->pTexture = nullptr;
	this->pRect.Clear();
}

bool Image::Compare(Node* pNode)
{
	assert(pNode);
	Image* pTemp = (Image*)pNode;

	if (this->name == pTemp->Get())
	{
		return true;
	}

	return false;
}