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
	return true;
}