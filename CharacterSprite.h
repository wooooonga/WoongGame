#ifndef __CharacterSprite_H__
#define __CharacterSprite_H__

#include "cocos2d.h"

class CharacterSprite : public cocos2d::Sprite
{
public:
	CharacterSprite(void);
	~CharacterSprite(void);
	static Sprite* CreateSprite();
	virtual bool init();


};

#endif