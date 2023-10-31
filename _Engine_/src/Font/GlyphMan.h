#pragma once
#ifndef GLYPH_MAN_H
#define GLYPH_MAN_H

#include "Manager.h"
#include "Glyph.h"

#include "font_proto.h"

class GlyphMan : public Manager
{
public:
	GlyphMan() = delete;
	GlyphMan(const GlyphMan&) = delete;
	GlyphMan& operator=(const GlyphMan&) = delete;

	static void Create(int toReserve = 2, int toGrow = 1);
	static void Destroy();

	static void Add(Glyph::Name name, const char* filename, Texture::Name texname);
	static void Remove(Glyph* glyph);
	static Glyph* Find(Glyph::Name name);
	static Rect FindKey(Glyph::Name name, int key);


protected:
	Node* derivedCreateNode() override;


private:
	Glyph* poComparison;
	static GlyphMan* poInstance;

	static GlyphMan* prInstance();
	GlyphMan(int toReserve, int toGrow);
	~GlyphMan();

	void prLoadFile(const char* filename, font_proto& fproto);


};
#endif // !GLYPH_MAN_H
