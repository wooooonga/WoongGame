#include "CharacterSprite.h"

USING_NS_CC;

CharacterSprite::CharacterSprite(void)
{
}


CharacterSprite::~CharacterSprite(void)
{
}

Sprite*
CharacterSprite::CreateSprite()
{
	Sprite *Turtle = Sprite::create("Img/Tortoise_Green_1.png");
	return Turtle;
}

bool
CharacterSprite::init()
{
	return true;
}