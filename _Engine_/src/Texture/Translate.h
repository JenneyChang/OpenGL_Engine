#pragma once
#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "sb7.h"
#include "Texture.h"
#include "texture_proto.h"

class Translate
{
public:
	static GLenum GetWrap(texture_proto::WRAP w);
	static GLenum GetFilter(texture_proto::MIN_FILTER min);
	static GLenum GetFilter(texture_proto::MAG_FILTER mag);
	static GLenum GetFormat(texture_proto::EFORMAT eformat);
	static GLenum GetComponent(texture_proto::NCOMPONENT ncomponent);

};
#endif // !TRANSLATE_H
