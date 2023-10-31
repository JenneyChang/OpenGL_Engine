#pragma once
#ifndef TEXTURE_MAN_H
#define TEXTURE_MAN_H

#include "Manager.h"
#include "Texture.h"
#include "texture_proto.h"
#include "Translate.h"

class TextureMan : public Manager
{
public:
	TextureMan() = delete;
	TextureMan(const TextureMan&) = delete;
	TextureMan& operator=(const TextureMan&) = delete;

	static void Create(int toReserve = 2, int toGrow = 1);
	static void Destroy();

	//load proto texture file
	static Texture* Add(const char* const filename, Texture::Name name);
	static Texture* Add(texture_proto& tproto, Texture::Name name);

	static Texture* Find(Texture::Name name);
	static GLuint FindID(Texture::Name name);
	static void Remove(Texture* pNode);
	static void Print();


protected:
	Node* derivedCreateNode() override;


private:
	Texture* poComparison;

	static TextureMan* poInstance;
	static TextureMan* prInstance();

	TextureMan(int toReserve, int toGrow);
	virtual ~TextureMan();

	bool prLoadProtoTexture(texture_proto& tproto, const char* filename);
	bool prLoadTexture(texture_proto& tproto);


};
#endif // !TEXTURE_MAN_H
