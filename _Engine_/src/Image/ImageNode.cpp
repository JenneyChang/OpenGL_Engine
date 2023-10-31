#include "ImageNode.h"
#include "ImageMan.h"


//---------------------------------------------------------------------------
//	CONSTRUCTION
//---------------------------------------------------------------------------

ImageNode::ImageNode(Image* image)
{
	assert(image != nullptr);
	this->pImage = image;
}

ImageNode::~ImageNode()
{ }


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void ImageNode::Set(Image* image)
{
	assert(image != nullptr);
	this->pImage = image;
}

void ImageNode::Set(Image::Name name)
{
	this->pImage = ImageMan::Find(name);
	assert(this->pImage);
}

Image* ImageNode::Get()
{
	assert(this->pImage);
	return this->pImage;
}


//---------------------------------------------------------------------------
//	PRIVATE METHODS
//---------------------------------------------------------------------------

bool ImageNode::Compare(Node* pNode)
{
	AZUL_UNUSED_VAR(pNode);
	return false;
}