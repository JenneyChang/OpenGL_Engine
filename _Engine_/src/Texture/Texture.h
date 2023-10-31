#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "sb7.h"
#include "DLink.h"

class Texture : public DLink
{
public:
	enum class Name
	{
		CRATE,		//test
		FRIGATE,	//req
		DUCK,
		ANTIQUE_CAMERA,
		WATCH_TOWER,
		BARRAMUNDI_FISH,
		CORSET,
		SNOWMAN,
		AVOCADO,
		DOGE,
		LORD_SHIVA,
		SNEAKER,

		ALIENS,
		SAILORMOON,
		SFVEGA,
		LINK,
		LINK1,

		R2,
		CHICKEN_BOT,
		MOUSEY,

		CONSOLAS36PT,	//font
		CAIYUN,
		COMICSANS,
		MAGNETO,

		HOTPINK,
		UNINITIALIZED,
		DEFAULT = HOTPINK
	};

	unsigned int width;
	unsigned int height;

	Texture();
	virtual ~Texture();
	Texture(const Texture&) = default;
	Texture& operator=(const Texture&) = default;

	void Set(const char* const assetName, Texture::Name _name, GLuint texID, GLenum min, 
		GLenum mag, GLenum wrapS, GLenum wrapT, unsigned int w, unsigned int h, unsigned int hash);

	void SetName(Texture::Name _name);
	GLuint GetID();

	bool Compare(Node* pNode) override;
	void ResetLink() override;


private:
	static const unsigned int NAMESIZE = 64;
	char assetName[NAMESIZE];

	Texture::Name name;
	GLuint textureID;
	GLenum minFilter;
	GLenum magFilter;
	GLenum wrapS;
	GLenum wrapT;

	unsigned int hashID;


};
#endif // !TEXTURE_H
