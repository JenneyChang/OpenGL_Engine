#pragma once
#ifndef FONT_MAN_H
#define FONT_MAN_H

#include "Manager.h"
#include "Font.h"
#include "Glyph.h"

class FontMan : public Manager
{
public:
	FontMan() = delete;
	FontMan(const FontMan&) = delete;
	FontMan& operator=(const FontMan&) = delete;

	static void Create(int toReserve = 3, int toGrow = 1);
	static void Destroy();

	static Font* Add(GraphicsObj_Font* graphicsobj, FontName font,
		Glyph::Name glyph, std::string mssg, float x, float y);

	static Font* Find(FontName name);


protected:
	Node* derivedCreateNode() override;


private:
	Font* poComparison;

	static FontMan* poInstance;
	static FontMan* prInstance();

	FontMan(int toReserve, int toGrow);
	~FontMan();


};
#endif // !FONT_MAN_H
