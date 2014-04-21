#ifndef __CharacterSprite_H__
#define __CharacterSprite_H__

#include "cocos2d.h"

class CharacterSprite : public cocos2d::Sprite
{
public:
	CharacterSprite(void);
	~CharacterSprite(void);
	static cocos2d::Sprite* CreateSprite();
	virtual bool init();
	CREATE_FUNC(CharacterSprite);
};

#endif