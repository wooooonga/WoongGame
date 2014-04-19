#include "MainGameScene.h"

USING_NS_CC;

MainGameScene::MainGameScene(void)
{
}
MainGameScene::~MainGameScene(void)
{
}
Scene* 
MainGameScene::CreateScene()
{
	Scene *scene = Scene::create();
	MainGameScene *layer = MainGameScene::create();
    scene->addChild(layer);
    return scene;
}
bool 
MainGameScene::init()
{
	Size visibleSize_ = Director::getInstance()->getWinSize();

	this->setColor(ccc3(255,255,0));
	LabelTTF *tempLabel = LabelTTF::create("Hello", "Arial", 40);
	tempLabel->setPosition(Point(visibleSize_.width / 2, visibleSize_.height / 2));
	this->addChild(tempLabel);

	//add background spite - static
	Sprite *pStaticBG = Sprite::create("Img/MarioBackground-static.png");
	pStaticBG->setAnchorPoint(Point(0, 0));
	pStaticBG->setPosition(Point(visibleSize_.width / 2, 0));
	this->addChild(pStaticBG);
	//add background spite - bottom
	Sprite *pScrollBottom1 = Sprite::create("Img/MarioBackground-scrolling.png");
	pScrollBottom1->setAnchorPoint(Point(0 ,0));
	pScrollBottom1->setPosition(Point(visibleSize_.width / 2 
									+ pStaticBG->getBoundingBox().size.width, 0));
	this->addChild(pScrollBottom1);
	Sprite *pScrollBottom2 = Sprite::create("Img/MarioBackground-scrolling.png");
	pScrollBottom2->setAnchorPoint(Point(0 ,0));
	pScrollBottom2->setPosition(Point(visibleSize_.width / 2 
									+ pStaticBG->getBoundingBox().size.width
									+ pScrollBottom1->getBoundingBox().size.width
									 -1, 0));
	this->addChild(pScrollBottom2);

	//add background spite - top
	Sprite *pScrollTop1 = Sprite::create("Img/MarioBackground-scrolling.png");
	pScrollTop1->setAnchorPoint(Point(0 ,0));
	pScrollTop1->setPosition(Point(visibleSize_.width / 2 
								+ pStaticBG->getBoundingBox().size.width, 0));
	this->addChild(pScrollTop1);
	Sprite *pScrollTop2 = Sprite::create("Img/MarioBackground-scrolling.png");
	pScrollTop2->setAnchorPoint(Point(0 ,0));
	pScrollTop2->setPosition(Point(visibleSize_.width / 2 
							+ pStaticBG->getBoundingBox().size.width 
							+ pScrollTop1->getBoundingBox().size.width 
							- 1, 0));
	this->addChild(pScrollTop2);

	//PhysicsWorld *pWorld =  PhysicsWorld::getphy
	return true;
}