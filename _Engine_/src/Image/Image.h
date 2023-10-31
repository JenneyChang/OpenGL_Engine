#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include "DLink.h"
#include "Rect.h"
#include "Texture.h"

using namespace Azul;

class Image : public DLink
{
public:
	enum class Name
	{
		OCTOPUS_OPEN,
		OCTOPUS_CLOSED,
		CRAB_OPEN,
		CRAB_CLOSED,
		SQUID_OPEN,
		SQUID_CLOSED,

		SM_WALKING0,
		SM_WALKING1,
		SM_WALKING2,
		SM_WALKING3,
		SM_WALKING4,
		SM_WALKING5,
		SM_WALKING6,
		SM_WALKING7,

		SM_RUNNING0,
		SM_RUNNING1,
		SM_RUNNING2,
		SM_RUNNING3,
		SM_RUNNING4,
		SM_RUNNING5,

		SM_JUMPING0,
		SM_JUMPING1,
		SM_JUMPING2,
		SM_JUMPING3,

		SM_POGOSTICK0,
		SM_POGOSTICK1,
		SM_POGOSTICK2,

		SM_FALLING0,
		SM_FALLING1,
		SM_FALLING2,
		SM_FALLING3,
		SM_FALLING4,
		SM_FALLING5,

		SM_DICE0,
		SM_DICE1,
		SM_DICE2,
		SM_DICE3,

		SF_KICK0,
		SF_KICK1,
		SF_KICK2,
		SF_KICK3,
		SF_KICK4,

		SF_STAB0,
		SF_STAB1,
		SF_STAB2,
		SF_STAB3,
		SF_STAB4,

		SF_IDLE0,
		SF_IDLE1,
		SF_IDLE2,
		SF_IDLE3,
		SF_IDLE4,
		SF_IDLE5,

		LWALK0,
		LWALK1,
		LWALK2,
		LWALK3,
		LWALK4,
		LWALK5,
		LWALK6,
		LWALK7,
		LWALK8,
		LWALK9,

		LSWING0,
		LSWING1,
		LSWING2,
		LSWING3,
		LSWING4,
		LSWING5,
		LSWING6,
		LSWING7,
		LSWING8,
		LSWING9,
		LSWING10,
		LSWING11,
		LSWING12,

		UNINITIALIZED
	};

	Image();
	~Image();

	void Set(Image::Name _name, Texture* pTexture, Rect rect);
	void Set(Image::Name _name);
	Image::Name Get();

	void ResetLink() override;
	bool Compare(Node* pNode) override;


public:
	Image::Name name;
	Texture* pTexture;
	Rect pRect;


};
#endif // !IMAGE_H
