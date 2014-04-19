#ifndef __MAINGAMESCENE_H__
#define __MAINGAMESCENE_H__

#include "cocos2d.h"

class MainGameScene : public cocos2d::Layer
{
public:
	MainGameScene(void);

	virtual bool init();
	static cocos2d::Scene* CreateScene();
	

	CREATE_FUNC(MainGameScene);
	~MainGameScene(void);

};

#endif