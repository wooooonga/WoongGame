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
	};

};
class MainGameScene : public cocos2d::Layer
{

public:
	MainGameScene(void);
	~MainGameScene(void);

	void setPhyWorld(PhysicsWorld* world) {m_world = world;}
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(MainGameScene);


	EventListenerTouchOneByOne* _touchListener;
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);


private:
	template <class T>
	void AddScore();
	void BirdAction();


	const PhysicsMaterial MATERIAL_NONE;
	
	PhysicsWorld *m_world;
	Sprite* pTube_;
	int iScore_;
	Point startingPoint_;
	Point bottomImgSize_;
	Sprite *pTurtle;
	LabelTTF *pScoreLabel;
	ParallaxNode *paraNodeFirst_;
	ParallaxNode *paraNodeSecond_;
};

#endif