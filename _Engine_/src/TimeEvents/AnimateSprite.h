#pragma once
#ifndef ANIMATE_SPRITE_H
#define ANIMATE_SPRITE_H

#include "Command.h"
#include "SLinkMan.h"

#include "GameObj2D.h"
#include "Image.h"
#include "TimerEvent.h"

class AnimateSprite : public Command
{
public:
	AnimateSprite(GameObj2D* sprite, TimerEvent::Name eventName);
	virtual ~AnimateSprite();

	void AttachImage(Image::Name name);
	void AttachImage(Image* img);

	void Execute(AnimTime delta) override;


private:
	TimerEvent::Name name;
	GameObj2D* pSprite;
	SLinkMan* pImageList;
	Iterator* it;


};
#endif // !ANIMATE_SPRITE_H
