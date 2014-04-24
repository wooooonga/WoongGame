#include "MainGameScene.h"
#include "CharacterSprite.h"
#include "Tube.h"

USING_NS_CC;

MainGameScene::MainGameScene(void)
	:iScore_(0)
{
}
MainGameScene::~MainGameScene(void)
{
}
Scene* 
MainGameScene::CreateScene()
{
	Scene *scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0.0f, -150.0f));
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
	pScrollBottom1->setTag(SCROLLTAG::BOTTOM1);
	Sprite *pScrollBottom2 = Sprite::create("Img/MarioBackground-scrolling.png");
	pScrollBottom2->setAnchorPoint(Point(0 ,0));
	pScrollBottom1->setTag(SCROLLTAG::BOTTOM2);
	bottomImgSize_ = pScrollBottom1->getBoundingBox().size;

	//////////////////////////
	//add background spite - top
	//////////////////////////
	Sprite *pScrollTop1 = Sprite::create("Img/MarioBackground-scrolling-top.png");
	pScrollTop1->setAnchorPoint(Point(0 ,1));
	pScrollTop1->setTag(SCROLLTAG::TOP1);
	Sprite *pScrollTop2 = Sprite::create("Img/MarioBackground-scrolling-top.png");		
	pScrollTop2->setAnchorPoint(Point(0 ,1));
	pScrollTop2->setTag(SCROLLTAG::TOP2);

	//////////////////////////
	//create scroll
	//////////////////////////
	paraNodeFirst_	= ParallaxNode::create();
	paraNodeSecond_	= ParallaxNode::create();
	paraNodeFirst_->addChild(pScrollBottom1, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2, 0));
	paraNodeSecond_->addChild(pScrollBottom2, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2 + pScrollBottom1->getBoundingBox().size.width-1, 0));
	paraNodeFirst_->addChild(pScrollTop1, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2, pStaticBG->getBoundingBox().size.height));
	paraNodeSecond_->addChild(pScrollTop2, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2 + pScrollTop1->getBoundingBox().size.width- 1, 
																pStaticBG->getBoundingBox().size.height));
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
	//Physics world


	auto *body2 = PhysicsBody::createEdgeBox(Size(pStaticBG->getContentSize().width, 
											pStaticBG->getContentSize().height / 100 * 10), 
											MATERIAL_NONE, 3, 
											Point(pStaticBG->getContentSize().width / 2, 
											(pStaticBG->getContentSize().height / 100 * 5)));
	body2->setLinearDamping(0);
	auto edgeNode2 = Node::create();
	edgeNode2->setPosition(Point(startingPoint_.x, startingPoint_.y));
	edgeNode2->setPhysicsBody(body2);
	this->addChild(edgeNode2);
	//////////////////////////
	//add Character
	//////////////////////////
	pTurtle = CharacterSprite::CreateSprite();
	pTurtle->setPosition(pStaticBG->getPosition().x + (pStaticBG->getBoundingBox().size.width / 2),
						pStaticBG->getPosition().y + (pStaticBG->getBoundingBox().size.height / 2));
	PhysicsBody *turtlebody = PhysicsBody::createBox(pTurtle->getContentSize());
	turtlebody->setLinearDamping(0);
	pTurtle->setPhysicsBody(turtlebody);
	this->addChild(pTurtle, 10);

	//////////////////////////
	// make touch enable. 
	//////////////////////////
	_touchListener = EventListenerTouchOneByOne::create();
	_touchListener->setSwallowTouches(true);
	_touchListener->onTouchBegan = CC_CALLBACK_2(MainGameScene::onTouchBegan, this);
	_touchListener->onTouchEnded = CC_CALLBACK_2(MainGameScene::onTouchEnded, this);
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

	//////////////////////////
	// Tube sprite 
	//////////////////////////
	Point tubeTopPoint(pStaticBG->getPosition().x + pStaticBG->getContentSize().width, 
							pStaticBG->getPosition().y + pStaticBG->getContentSize().height);
	Point tubeBottomPoint(pStaticBG->getPosition().x + pStaticBG->getContentSize().width, 
							pStaticBG->getPosition().y + pScrollBottom1->getContentSize().height / 2);
	float endingPoint = pStaticBG->getContentSize().width;
	Tube* pTube_ = Tube::CreateTube(tubeTopPoint, tubeBottomPoint, endingPoint);
	this->addChild(pTube_);

	return true;
}
void
MainGameScene::update(float dt)
{
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
	cocos2d::log("touch start");
	return true;
}
void
MainGameScene::onTouchEnded(Touch* touch, Event* event)
{
	cocos2d::log("touch ended");

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
	//ActionInterval *UpAction = MoveBy::create(0.1,Point(0, 45));
	//pTurtle->runAction(UpAction);

	pTurtle->getPhysicsBody()->setVelocity(Point(0,100));
	ActionInterval *RotateAction = RotateBy::create(1, 130);
	pTurtle->runAction(RotateAction);

	pTurtle->setRotation(30);

}