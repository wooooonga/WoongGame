#include "MainGameScene.h"
#include "MainMenuScene.h"
#include "CharacterSprite.h"
#include "Tube.h"

USING_NS_CC;

MainGameScene::MainGameScene(void)
	:iScore_(0),
	staticImgSize_(320, 568),
	bottomImgSize_(909, 120),
	topImgSize_(909, 270)
{}
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
	this->scheduleUpdate();
	this->setTouchEnabled(true);

	//////////////////////////
	//add background spite - static background
	//////////////////////////
	Sprite *pStaticBG = Sprite::create("Img/MarioBackground-static.png");
	pStaticBG->setAnchorPoint(Point(0, 0));
	pStaticBG->setPosition(Point(visibleSize_.width / 2, 0));
	this->addChild(pStaticBG, -1);
	startingPoint_ = Point(pStaticBG->getPosition().x, pStaticBG->getPosition().y);

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
	paraNodeFirst_->addChild(pScrollBottom1, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2, 0));
	paraNodeSecond_->addChild(pScrollBottom2, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2 + bottomImgSize_.x - 1, 0));
	paraNodeFirst_->addChild(pScrollTop1, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2, staticImgSize_.y));
	paraNodeSecond_->addChild(pScrollTop2, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2 + topImgSize_.x - 1, staticImgSize_.y));
	this->addChild(paraNodeFirst_, -1);
	this->addChild(paraNodeSecond_, -1);

	//////////////////////////
	//add Score
	//////////////////////////
	pScoreLabel = LabelTTF::create("Score : 0", "Arial", 40);
	pScoreLabel->setPosition(visibleSize_.width / 2, visibleSize_.height / 4 * 3);
	pScoreLabel->setColor(Color3B(0, 255, 255));
	this->addChild(pScoreLabel, 5);
	int scoreTemp = 0;


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
	//Physics world
	auto *body1 = PhysicsBody::createEdgeBox(Size(staticImgSize_.x, staticImgSize_.y / 100 * 10), 
											MATERIAL_NONE, 3, Point(staticImgSize_.x / 2, (staticImgSize_.y / 100 * 5)));
	body1->setLinearDamping(0);
	Node *BottomBoxNode = Node::create();
	BottomBoxNode->setPosition(Point(startingPoint_.x, startingPoint_.y));
	BottomBoxNode->setPhysicsBody(body1);
	BottomBoxNode->setTag(TAGNAME::BOTTOMBOX);
	this->addChild(BottomBoxNode);

	auto *bodyFrame = PhysicsBody::createEdgeBox(Size(staticImgSize_.x, staticImgSize_.y), MATERIAL_NONE, 4, Point(staticImgSize_.x / 2, (staticImgSize_.y / 2)));
	bodyFrame->setLinearDamping(0);
	Node *frameBoxNode = Node::create();
	frameBoxNode->setPosition(Point(startingPoint_.x, startingPoint_.y));
	frameBoxNode->setPhysicsBody(bodyFrame);
	frameBoxNode->setTag(TAGNAME::FRAMEBOX);
	this->addChild(frameBoxNode);

	//////////////////////////
	//add Character
	//////////////////////////
	pTurtle = CharacterSprite::CreateSprite();
	pTurtle->setPosition(pStaticBG->getPosition().x + (staticImgSize_.x / 2),
						pStaticBG->getPosition().y + (staticImgSize_.y / 2));
	PhysicsBody *turtleBody = PhysicsBody::createBox(pTurtle->getContentSize());
	turtleBody->setLinearDamping(0);
	turtleBody->setDynamic(true);
	turtleBody->setMass(2.f);
	turtleBody->setContactTestBitmask(0x1<<0);
	pTurtle->setPhysicsBody(turtleBody);
	pTurtle->setTag(TAGNAME::TURTLE);
	this->addChild(pTurtle, 10);

	//////////////////////////
	// Tube sprite 
	//////////////////////////
	Point tubeTopPoint(pStaticBG->getPosition().x + staticImgSize_.x, 
							pStaticBG->getPosition().y + staticImgSize_.y);
	Point tubeBottomPoint(pStaticBG->getPosition().x + staticImgSize_.x, 
							pStaticBG->getPosition().y + bottomImgSize_.y / 2);
	float endingPoint = staticImgSize_.x;
	pTube_ = Tube::CreateTube(tubeTopPoint, tubeBottomPoint, endingPoint);
	this->addChild(pTube_);
	return true;
}
void
MainGameScene::update(float dt)
{
	yVelolcity = clampf(pTurtle->getPhysicsBody()->getVelocity().y, -500.f, 400.f);
	pTurtle->getPhysicsBody()->setVelocity(Point(0 ,yVelolcity));

	if((int)(pTube_->GetTubePosition().x) == (int)(startingPoint_.x + (staticImgSize_.x / 2)))
	{
		AddScore<char>();
	}
	//Check if sprite is out of bound
	paraNodeFirst_->setPosition(paraNodeFirst_->getPosition().x -1, paraNodeFirst_->getPosition().y);
	paraNodeSecond_->setPosition(paraNodeSecond_->getPosition().x -1, paraNodeSecond_->getPosition().y);
	if(paraNodeFirst_->getPosition().x + (bottomImgSize_.x / 2) < 0) // scrollSpeed is 2.0f. so ImgSize divide by 2
	{
		paraNodeFirst_->setPosition(bottomImgSize_.x / 2 - 1, 0);
	}
	else if(paraNodeSecond_->getPosition().x + (bottomImgSize_.x) < 0)
	{
		paraNodeSecond_->setPosition(-1, 0);
	}
}
bool
MainGameScene::onTouchBegan(Touch* touch, Event* event)
{
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
	int Tube	= contact.getShapeA()->getBody()->getNode()->getTag();
	int Turtle	= contact.getShapeB()->getBody()->getNode()->getTag();
	if( (1 == Turtle && 2 == Tube) || (2 == Turtle && 1 == Tube))
		GameFinish();
	return true;
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
	sprintf(coinScore, "Score: %d", ++iScore_);
	pScoreLabel->setString(coinScore);
}

void
MainGameScene::BirdAction()
{
	pTurtle->getPhysicsBody()->applyImpulse(Point(0, 400.f));
	cocos2d::log("applyImpulse : %f",pTurtle->getPhysicsBody()->getVelocity().y);
}
void
MainGameScene::TurtleDead()
{
	pTurtle->stopAllActions();
	pTurtle->setTexture(Director::getInstance()->getTextureCache()->addImage("Img/Tortoise_Brown_1.png"));
}
void
MainGameScene::GameFinish()
{

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
	pTurtle->getPhysicsBody()->applyImpulse(Point(0, 100), Point(pTurtle->getPosition().x, pTurtle->getPosition().y));
	ActionInterval *movingUp = MoveBy::create(1, Point(0, 100));
	FiniteTimeAction *flipTurtle = FlipY::create(true);
	FiniteTimeAction *spawnturtle = Spawn::create(movingUp, flipTurtle, NULL);
	ActionInterval *delayTime = DelayTime::create(4.0);
	CallFunc *goBackToMain = CallFunc::create(CC_CALLBACK_0(MainGameScene::GoBackToMain, this));
	FiniteTimeAction *seq = Sequence::create(spawnturtle, delayTime,goBackToMain, NULL);
	pTurtle->runAction(seq);

}

void
MainGameScene::GoBackToMain()
{
	Scene *pScene = MainMenuScene::CreateScene();
	Director::getInstance()->replaceScene(pScene);
}