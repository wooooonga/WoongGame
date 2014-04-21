#include "MainGameScene.h"
#include "CharacterSprite.h"

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
	Scene *scene = Scene::create();
	MainGameScene *layer = MainGameScene::create();
    scene->addChild(layer);
    return scene;
}
bool 
MainGameScene::init()
{
	Size visibleSize_ = Director::getInstance()->getWinSize();
	this->scheduleUpdate();
	//////////////////////////
	//add background spite - static
	//////////////////////////
	Sprite *pStaticBG = Sprite::create("Img/MarioBackground-static.png");
	pStaticBG->setAnchorPoint(Point(0, 0));
	pStaticBG->setPosition(Point(visibleSize_.width / 2, 0));
	this->addChild(pStaticBG);
	//////////////////////////
	//add background spite - bottom
	//////////////////////////
	Sprite *pScrollBottom1 = Sprite::create("Img/MarioBackground-scrolling.png");
	pScrollBottom1->setAnchorPoint(Point(0 ,0));
	Sprite *pScrollBottom2 = Sprite::create("Img/MarioBackground-scrolling.png");
	pScrollBottom2->setAnchorPoint(Point(0 ,0));
	bottomImgSize_ = pScrollBottom1->getBoundingBox().size;
	//////////////////////////
	//add background spite - top
	//////////////////////////
	Sprite *pScrollTop1 = Sprite::create("Img/MarioBackground-scrolling-top.png");
	pScrollTop1->setAnchorPoint(Point(0 ,1));
	Sprite *pScrollTop2 = Sprite::create("Img/MarioBackground-scrolling-top.png");		
	pScrollTop2->setAnchorPoint(Point(0 ,1));
	topImgSize_ = pScrollTop1->getBoundingBox().size;
	//////////////////////////
	//create scroll
	//////////////////////////
	paraNode = ParallaxNode::create();
	paraNode->addChild(pScrollBottom1, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2, 0));
	paraNode->addChild(pScrollBottom2, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2 
										+ pScrollBottom1->getBoundingBox().size.width-1, 0));
	paraNode->addChild(pScrollTop1, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2, pStaticBG->getBoundingBox().size.height));
	paraNode->addChild(pScrollTop2, 1, Point(2.0f, 0.0f), Point(visibleSize_.width / 2 + pScrollTop1->getBoundingBox().size.width- 1, 
										pStaticBG->getBoundingBox().size.height));

	this->addChild(paraNode, 2);

	//////////////////////////
	//add Score
	//////////////////////////
	pScoreLabel = LabelTTF::create("Score : 0", "Arial", 40);
	pScoreLabel->setPosition(visibleSize_.width / 2, visibleSize_.height / 4 * 3);
	pScoreLabel->setColor(Color3B(0, 255, 255));
	this->addChild(pScoreLabel, 5);
	int scoreTemp = 0;

	//////////////////////////
	//add Character
	//////////////////////////
	pTurtle = CharacterSprite::CreateSprite();
	pTurtle->setPosition(pStaticBG->getPosition().x + (pStaticBG->getBoundingBox().size.width / 2),
						pStaticBG->getPosition().y + (pStaticBG->getBoundingBox().size.height / 2));
	this->addChild(pTurtle, 10);

	return true;
}
void
MainGameScene::update(float dt)
{
	//cocos2d::log("%d , %d",paraNode->getPosition().x, paraNode->getPosition().y);
	paraNode->setPosition(Point(paraNode->getPosition().x - 1, paraNode->getPosition().y));
	if(paraNode->getPosition().x + bottomImgSize_.x) paraNode->setPosition(
}
template <class T>
void MainGameScene::AddScore()
{
	if(iScore_ >= 100)
	{
		pScoreLabel->setString("Score Exceed 100 above");
	}
	T coinScore[100] = {0};
	sprintf(coinScore, "Score: %d", ++iScore_);
	pScoreLabel->setString(coinScore);

}