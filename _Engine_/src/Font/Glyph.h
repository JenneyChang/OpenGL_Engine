#pragma once
#ifndef GLYPH_H
#define GLYPH_H

#include "DLink.h"
#include "Texture.h"
#include "Rect.h"

#include "font_proto.h"

using namespace Azul;

class Glyph : public DLink
{
public:
	enum class Name
	{
		CONSOLAS36PT,
		CAIYUN_80PT,
		COMICSANS_55PT,
		MAGNETO_45PT,

		NULLFONT,
		UNINITIALIZED
	};

	Glyph();
	~Glyph();
	Glyph(const Glyph&) = delete;
	Glyph& operator=(const Glyph&) = delete;

	void Set(Glyph::Name _name);
	void Set(Glyph::Name _name, Texture* texture, font_proto& fproto);

	Rect GetKey(int key);
	Texture* GetTexture();
	GLuint GetTexID();

	void ResetLink() override;
	bool Compare(Node* pNode) override;


private:
	Glyph::Name name;
	Texture* pTexture;

	size_t listSize;
	std::map<int, Rect> keys;


};
#endif // !GLYPH_H
