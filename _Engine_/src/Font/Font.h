#pragma once
#ifndef FONT_H
#define FONT_H

#include "DLink.h"
#include "Glyph.h"

#include "GraphicsObj_Font.h"

class GraphicsObj_Font;

enum class FontName
{
	Tester,
	Counter,

	Walk,
	Run,
	FrontHit,
	DieRight,

	JoyfulJump,
	MouseWalk,
	MouseRun,

	Demo1A,
	Demo1B,
	Demo1C,
	Demo1D,

	Null,
	Uninitialized
};

class Font : public DLink
{
public:
	Font();
	~Font();
	Font(const Font&) = delete;
	Font& operator=(const Font&) = delete;

	void Set(FontName _name);
	void Set(GraphicsObj_Font* graphicsobj, FontName _name, Glyph::Name glyph, std::string mssg, float x, float y);

	void UpdateMessage(std::string mssg);

	void ResetLink() override;
	bool Compare(Node* pNode) override;


private:
	FontName name;
	GraphicsObj_Font* pGraphicsFont;


};
#endif // !FONT_H
