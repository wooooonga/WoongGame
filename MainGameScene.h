#ifndef __MAINGAMESCENE_H__
#define __MAINGAMESCENE_H__

#include "cocos2d.h"
#include "Tube.h"

USING_NS_CC;

class MainGameScene : public cocos2d::Layer
{

public:
	MainGameScene(void);
	~MainGameScene(void);

	void setPhyWorld(PhysicsWorld* world) {m_world = world;}
	static Scene* CreateScene();
	virtual bool init();
	virtual void update(float dt);

	CREATE_FUNC(MainGameScene);


	EventListenerTouchOneByOne* _touchListener;
	EventListenerPhysicsContact* _contactListener;
	EventListenerKeyboard* _keyboardListener;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	bool onContactBegin(const PhysicsContact& contact);
	void GoBackToMain();

private:
	template <class T>
	void AddScore();
	void BirdAction();
	void GameStart();
	void GameFinish();
	void TurtleDead();
	void SetArrowPosition(TubeNum);
	void CreateScoreBoard();
	TubeNum SetNewTubeType();

	const PhysicsMaterial MATERIAL_NONE;

	int iScore_;
	float yVelolcity;
	PhysicsWorld *m_world;
	Tube* pTube_;
	Point staticImgSize_;
	Point bottomImgSize_;
	Point topImgSize_;
	Sprite *pTurtle;
	Sprite *pArrowSprite_;
	LabelBMFont *pScoreLabel;
	ParallaxNode *paraNodeFirst_;
	ParallaxNode *paraNodeSecond_;

	int gameState_;
};



#endif