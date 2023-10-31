#pragma once
#ifndef IMAGE_NODE_H
#define IMAGE_NODE_H

#include "SLink.h"
#include "Image.h"

class ImageNode : public SLink
{
public:
	ImageNode(Image* image);
	virtual ~ImageNode();

	void Set(Image* image);
	void Set(Image::Name name);
	Image* Get();


private:
	Image* pImage;

	//not used
	bool Compare(Node* pNode) override;

};
#endif // !IMAGE_NODE_H
