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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/Tortoise_Red.plist");
	Sprite *turtle = Sprite::create("Img/Tortoise_Red_1.png");
	cocos2d::Vector<SpriteFrame*> aniFrames;
	char str[50] = {};
	for(int i = 1; i <= 2; i++)
	{
		sprintf(str, "Tortoise_Red_%d.png", i);
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		aniFrames.pushBack(frame);
	}
	Animation *animation = Animation::createWithSpriteFrames(aniFrames, 0.3f);
	Animate *animate = Animate::create(animation);
	auto *actionFly = RepeatForever::create(animate);
	turtle->runAction(actionFly);

	return turtle;
}

bool
CharacterSprite::init()
{
	return true;
}