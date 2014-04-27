#ifndef __MAINGAMESCENE_H__
#define __MAINGAMESCENE_H__

#include "cocos2d.h"
#include "Tube.h"
USING_NS_CC;


namespace TAGNAME
{
	enum
	{
		TURTLE = 1,
		BOTTOMBOX = 2

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
	EventListenerPhysicsContact* _contactListener;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	bool onContactBegin(const PhysicsContact& contact);
	void GoBackToMain();

private:
	template <class T>
	void AddScore();
	void BirdAction();
	void GameFinish();
	void TurtleDead();


	const PhysicsMaterial MATERIAL_NONE;
	

	int iScore_;
	float yVelolcity;
	PhysicsWorld *m_world;
	Tube* pTube_;
	Point staticImgSize_;
	Point bottomImgSize_;
	Point topImgSize_;
	Point startingPoint_;

	Sprite *pTurtle;
	LabelTTF *pScoreLabel;
	ParallaxNode *paraNodeFirst_;
	ParallaxNode *paraNodeSecond_;
};

#endif