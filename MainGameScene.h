#ifndef __MAINGAMESCENE_H__
#define __MAINGAMESCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MainGameScene : public cocos2d::Layer
{
public:
	MainGameScene(void);

	virtual bool init();
	static cocos2d::Scene* CreateScene();

	template <class T>
	void AddScore();

	CREATE_FUNC(MainGameScene);
	~MainGameScene(void);

private:
	int iScore_;
	LabelTTF *pScoreLabel;

};

#endif