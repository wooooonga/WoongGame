#ifndef __MAINGAMESCENE_H__
#define __MAINGAMESCENE_H__

#include "cocos2d.h"
USING_NS_CC;

namespace SCROLLTAG
{
	enum
	{
		BOTTOM1 =0,
		BOTTOM2,
		TOP1,
		TOP2
	}

};
class MainGameScene : public cocos2d::Layer
{
public:
	MainGameScene(void);

	static cocos2d::Scene* CreateScene();
	virtual bool init();
	virtual void update(float dt);

	template <class T>
	void AddScore();

	CREATE_FUNC(MainGameScene);
	~MainGameScene(void);

private:
	int iScore_;
	Point bottomImgSize_;
	Point topImgSize_;
	Sprite *pTurtle;
	LabelTTF *pScoreLabel;
	ParallaxNode *paraNode;
};

#endif