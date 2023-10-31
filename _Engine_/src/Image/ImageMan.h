#pragma once
#ifndef IMAGE_MAN_H
#define IMAGE_MAN_H

#include "Manager.h"
#include "Image.h"

class ImageMan : public Manager
{
public:
	ImageMan() = delete;
	ImageMan(const ImageMan&) = delete;
	ImageMan& operator=(const ImageMan&) = delete;

	static void Create(int toReserve = 3, int toGrow = 2);
	static void Destroy();

	static Image* Add(Image::Name name, Texture* texture, Rect rect);
	static Image* Find(Image::Name name);
	static void Remove(Image* img);
	static void Print();


protected:
	Node* derivedCreateNode() override;


private:
	Image* poComparison;
	
	static ImageMan* poInstance;
	static ImageMan* prInstance();

	ImageMan(int toReserve, int toGrow);
	virtual ~ImageMan();


};
#endif // !IMAGE_MAN_H


