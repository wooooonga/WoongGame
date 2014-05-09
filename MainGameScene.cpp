#include "MainGameScene.h"
#include "MainMenuScene.h"
#include "Tube.h"
#include "GlobalVar.h"
#include "ScoreBoard.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

MainGameScene::MainGameScene(void)
	:iScore_(0),
	staticImgSize_(320, 568),
	bottomImgSize_(909, 120),
	topImgSize_(909, 270),
	gameState_(GAMESTATE::READY)	{}

MainGameScene::~MainGameScene(void)
{}

Scene* 
MainGameScene::CreateScene()
{
	Scene *scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0.0f, -500.0f));
	MainGameScene *layer = MainGameScene::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
    return scene;
}
bool 
MainGameScene::init()
{
	Size visibleSize_ = Director::getInstance()->getWinSize();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/ExampleBGM2.mp3", true);

	//////////////////////////
	//add background spite - static background
	//////////////////////////
	Sprite *pStaticBG = Sprite::create("Img/MarioBackground-static.png");
	pStaticBG->setPosition(staticImgSize_.x / 2, staticImgSize_.y / 2);
	this->addChild(pStaticBG, -1);

	//////////////////////////
	//add background spite - bottom
	//////////////////////////
	Sprite *pScrollBottom1 = Sprite::create("Img/MarioBackground-scrolling.png");
	pScrollBottom1->setAnchorPoint(Point(0 ,0));
	Sprite *pScrollBottom2 = Sprite::create("Img/MarioBackground-scrolling.png");
	pScrollBottom2->setAnchorPoint(Point(0 ,0));

	//////////////////////////
	//add background spite - top
	//////////////////////////
	Sprite *pScrollTop1 = Sprite::create("Img/MarioBackground-scrolling-top.png");
	pScrollTop1->setAnchorPoint(Point(0 ,1));
	Sprite *pScrollTop2 = Sprite::create("Img/MarioBackground-scrolling-top.png");		
	pScrollTop2->setAnchorPoint(Point(0 ,1));

	//////////////////////////
	//create scroll
	//////////////////////////
	paraNodeFirst_	= ParallaxNode::create();
	paraNodeSecond_	= ParallaxNode::create();
	paraNodeFirst_->addChild(pScrollBottom1, 1, Point(2.0f, 0.0f), Point(0, 0));
	paraNodeSecond_->addChild(pScrollBottom2, 1, Point(2.0f, 0.0f), Point(bottomImgSize_.x - 1, 0));
	paraNodeFirst_->addChild(pScrollTop1, 1, Point(2.0f, 0.0f), Point(0, staticImgSize_.y));
	paraNodeSecond_->addChild(pScrollTop2, 1, Point(2.0f, 0.0f), Point(topImgSize_.x - 1, staticImgSize_.y));
	this->addChild(paraNodeFirst_, -1);
	this->addChild(paraNodeSecond_, -1);

	//////////////////////////
	//add Score
	//////////////////////////
	pScoreLabel = LabelBMFont::create("Score\n0", "fonts/FlappyFont.fnt", visibleSize_.width / 1.5, kCCTextAlignmentCenter);
	pScoreLabel->setPosition(visibleSize_.width / 2, visibleSize_.height / 4 * 3);
	pScoreLabel->setColor(Color3B(0, 0, 255));
	this->addChild(pScoreLabel, 5);

	//////////////////////////
	// make touch enable. 
	//////////////////////////
	_touchListener = EventListenerTouchOneByOne::create();
	_touchListener->setSwallowTouches(true);
	_touchListener->onTouchBegan = CC_CALLBACK_2(MainGameScene::onTouchBegan, this);
	_touchListener->onTouchEnded = CC_CALLBACK_2(MainGameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

	//////////////////////////
	// make collision enable
	//////////////////////////
	_contactListener = EventListenerPhysicsContact::create();
    _contactListener->onContactBegin = CC_CALLBACK_1(MainGameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_contactListener, this);

	//////////////////////////
	//add turtle
	//////////////////////////
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/Tortoise_Red.plist");
	pTurtle = Sprite::create("Img/Tortoise_Red_1.png");
	pTurtle->setPosition(staticImgSize_.x / 3, staticImgSize_.y / 2);
	pTurtle->setTag(TAGNAME::TURTLE);
	this->addChild(pTurtle, 10);

	//////////////////////////
	//add HowToPlay img
	//////////////////////////
	Sprite* pHowToPlay = Sprite::create("Img/Tap.png");
	pHowToPlay->setPosition(visibleSize_.width / 2, visibleSize_.height /2);
	pHowToPlay->setTag(TAGNAME::HOWTOPLAY);
	this->addChild(pHowToPlay);

	//////////////////////////
	// Arrow sprite 
	//////////////////////////
	pArrowSprite_ = Sprite::create("Img/Arrow.png");
	pArrowSprite_->setPosition(staticImgSize_.x / 10 * 9, -50);
	this->addChild(pArrowSprite_);

	return true;
}

void
MainGameScene::GameStart()
{
	this->scheduleUpdate();
	this->removeChildByTag(TAGNAME::TURTLE);
	this->removeChildByTag(TAGNAME::HOWTOPLAY);

	//////////////////////////
	//add turtle physics body
	//////////////////////////
	pTurtle = Sprite::create("Img/Tortoise_Red_1.png");
	pTurtle->setPosition(staticImgSize_.x / 3, staticImgSize_.y / 2);
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
	pTurtle->runAction(actionFly);

	PhysicsBody *turtleBody = PhysicsBody::createBox(pTurtle->getContentSize(),PhysicsMaterial(.5f, 0.3f, 1.f));
	turtleBody->setDynamic(true);
	turtleBody->setMass(2.f);
	turtleBody->setContactTestBitmask(0x1<<0);
	pTurtle->setPhysicsBody(turtleBody);
	pTurtle->setTag(TAGNAME::TURTLE);
	this->addChild(pTurtle, 10);

	//////////////////////////
	// pressed Backbutton
	//////////////////////////
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(MainGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

	//////////////////////////
	//Physics world
	//////////////////////////
	auto *body1 = PhysicsBody::createEdgeBox(Size(staticImgSize_.x, staticImgSize_.y / 100 * 10), 
											MATERIAL_NONE, 3, Point(staticImgSize_.x / 2, (staticImgSize_.y / 100 * 5)));
	body1->setLinearDamping(0);
	Node *BottomBoxNode = Node::create();
	BottomBoxNode->setPosition(0, 0);
	BottomBoxNode->setPhysicsBody(body1);
	BottomBoxNode->setTag(TAGNAME::BOTTOMBOX);
	this->addChild(BottomBoxNode);

	auto *bodyFrame = PhysicsBody::createEdgeBox(Size(staticImgSize_.x, staticImgSize_.y), MATERIAL_NONE, 4, Point(staticImgSize_.x / 2, (staticImgSize_.y / 2)));
	bodyFrame->setLinearDamping(0);
	Node *frameBoxNode = Node::create();
	frameBoxNode->setPosition(0, 0);
	frameBoxNode->setPhysicsBody(bodyFrame);
	frameBoxNode->setTag(TAGNAME::FRAMEBOX);
	this->addChild(frameBoxNode);

	//////////////////////////
	// Tube sprite 
	//////////////////////////
	Point tubeBottomPoint(staticImgSize_.x, staticImgSize_.y / 10);
	Point tubeTopPoint(staticImgSize_.x, staticImgSize_.y);
	float endingPoint = staticImgSize_.x;
	pTube_ = Tube::CreateTube(tubeTopPoint, tubeBottomPoint, endingPoint);
	this->addChild(pTube_);

}

void
MainGameScene::update(float dt)
{
	yVelolcity = clampf(pTurtle->getPhysicsBody()->getVelocity().y, -500.f, 300.f);
	pTurtle->getPhysicsBody()->setVelocity(Point(0 ,yVelolcity));
	//Check if sprite is out of bound
	paraNodeFirst_->setPosition(paraNodeFirst_->getPosition().x -1, 0);
	paraNodeSecond_->setPosition(paraNodeSecond_->getPosition().x -1, 0);
	if(paraNodeFirst_->getPosition().x + (bottomImgSize_.x / 2) < 0) // scrollSpeed is 2.0f. so ImgSize divide by 2
	{
		paraNodeFirst_->setPosition(bottomImgSize_.x / 2 - 1, 0);
	}
	else if(paraNodeSecond_->getPosition().x + (bottomImgSize_.x) < 0)
	{
		paraNodeSecond_->setPosition(-1, 0);
	}
	if(pTube_->GetTubePosition().x < staticImgSize_.x / 3 && pTube_->GetWaitingTubeState() == false)
	{
		AddScore<char>();
		TubeNum pTubeNum = pTube_->SetNewTubeType();
		SetArrowPosition(pTubeNum);
	}
}

void
MainGameScene::SetArrowPosition(TubeNum tubeNum)
{
	float lastTopTubePos = staticImgSize_.y - (tubeNum.top * 52.f);
	float lastBottomTubePos = (staticImgSize_.y / 10) + (tubeNum.bottom * 52.f);

	float arrowPosY = (lastTopTubePos - lastBottomTubePos) / 2;
	pArrowSprite_->setPosition(pArrowSprite_->getPosition().x, lastBottomTubePos + arrowPosY);
}

void
MainGameScene::BirdAction()
{
	pTurtle->getPhysicsBody()->applyImpulse(Point(0, 400.f));
	//SimpleAudioEngine::getInstance()->playEffect("Sound/flyTurtle.mp3");
}

bool
MainGameScene::onTouchBegan(Touch* touch, Event* event)
{
	if(gameState_ == GAMESTATE::READY)
	{
		GameStart();
		gameState_ = GAMESTATE::START;
	}
	BirdAction();
	return true;
}
void
MainGameScene::onTouchEnded(Touch* touch, Event* event)
{
}
bool
MainGameScene::onContactBegin(const PhysicsContact& contact)
{
	int object1	= contact.getShapeA()->getBody()->getNode()->getTag();
	int object2	= contact.getShapeB()->getBody()->getNode()->getTag();
	if((TAGNAME::TURTLE == object1 && TAGNAME::TUBE == object2) || 
		(TAGNAME::TUBE == object1 && TAGNAME::TURTLE == object2))
	{
		SimpleAudioEngine::getInstance()->playEffect("Sound/tubeCollision.mp3");
		GameFinish();
	}
	return true;
}
void
MainGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if(keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		GoBackToMain();
		Director::getInstance()->getEventDispatcher()->removeEventListener(_keyboardListener);
	}
}

template <class T>
void 
MainGameScene::AddScore()
{
	if(iScore_ >= 100)
	{
		pScoreLabel->setString("Score Exceed 100 above");
	}

	T coinScore[100] = {0};
	sprintf(coinScore, "Score\n%d", ++iScore_);
	pScoreLabel->setString(coinScore);
}


void
MainGameScene::TurtleDead()
{
	pTurtle->stopAllActions();
	pTurtle->setTexture("Img/Tortoise_Brown_1.png");
	pTurtle->getPhysicsBody()->applyImpulse(Point(0, 400));
	pTurtle->getPhysicsBody()->setAngularVelocity(3);
	FiniteTimeAction *flipTurtle = FlipY::create(true);
	ActionInterval *delayTime = DelayTime::create(4.0);
	CallFunc *createScoreBoard = CallFunc::create(CC_CALLBACK_0(MainGameScene::CreateScoreBoard, this));
	CallFunc *goBackToMain = CallFunc::create(CC_CALLBACK_0(MainGameScene::GoBackToMain, this));
	FiniteTimeAction *seq = Sequence::create(flipTurtle, createScoreBoard, delayTime,goBackToMain, NULL);
	pTurtle->runAction(seq);
}

void
MainGameScene::CreateScoreBoard()
{
	ScoreBoard* scoreBoard = ScoreBoard::CreateScoreBoard(iScore_);
	this->addChild(scoreBoard, 30);
}

void
MainGameScene::GameFinish()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	//////////////////////////
	//delete eventListeners.
	//////////////////////////
	Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(_contactListener);


	//////////////////////////
	// unscheldule Updates and Remove bottom Box.
	//////////////////////////
	this->unscheduleUpdate();
	pTube_->unscheduleUpdate();
	Node *bottomBoxForCollision = (Node*)getChildByTag(TAGNAME::BOTTOMBOX);
	Node *FrameBoxForCollision = (Node*)getChildByTag(TAGNAME::FRAMEBOX);
	this->removeChild(bottomBoxForCollision, true);
	this->removeChild(FrameBoxForCollision, true);

	//////////////////////////
	// Actions before going to main menu
	//////////////////////////
	TurtleDead();

}

void
MainGameScene::GoBackToMain()
{
	if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) 
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Scene *pScene = MainMenuScene::CreateScene();
	Director::getInstance()->replaceScene(pScene);
}



