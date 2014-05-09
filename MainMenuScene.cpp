#include "MainMenuScene.h"
#include "MainGameScene.h"
#include "ScoreBoard.h"

USING_NS_CC;

Scene* MainMenuScene::CreateScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	this->setTouchEnabled(true);
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
	LabelBMFont *pBMfontStart = LabelBMFont::create("Start", "fonts/FlappyFont.fnt", visibleSize.width / 1.5, kCCTextAlignmentCenter);
	LabelBMFont *pBMfontScore = LabelBMFont::create("HighScore", "fonts/FlappyFont.fnt", visibleSize.width / 1.5, kCCTextAlignmentCenter);
	LabelBMFont *pBMfontClose = LabelBMFont::create("Close", "fonts/FlappyFont.fnt", visibleSize.width / 1.5, kCCTextAlignmentCenter);

	//MenuItemFont *pLabelStart = MenuItemFont::create("Start", this, menu_selector(MainMenuScene::menuGoToGame));
	//MenuItemFont *pLabelClose = MenuItemFont::create("Close", this, menu_selector(MainMenuScene::menuCloseCallback));
	MenuItemLabel *pLabelStart = MenuItemLabel::create(pBMfontStart, this, menu_selector(MainMenuScene::menuGoToGame));
	MenuItemLabel *pLabelScore = MenuItemLabel::create(pBMfontScore, this, menu_selector(MainMenuScene::ShowHighScore));
	MenuItemLabel *pLabelClose = MenuItemLabel::create(pBMfontClose, this, menu_selector(MainMenuScene::menuCloseCallback));
	pLabelStart->setColor(ccc3(255, 0, 0));
	pLabelClose->setColor(ccc3(0, 255, 0));
	Menu* pMenu = Menu::create(pLabelStart, pLabelClose, pLabelScore, NULL);
	pMenu->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
	pMenu->alignItemsVertically();
	pMenu->setTag(MENU);
	this->addChild(pMenu, 1);

	//////////////////////////
	// pressed Backbutton
	//////////////////////////
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(MainMenuScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

    // add "MainMenuScene" splash screen"
	Sprite* bgSprite = Sprite::create("Img/MarioBackground-static.png");
	bgSprite->setPosition((Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y)));


    // add the sprite as a child to this layer
    this->addChild(bgSprite, 0);
    
    return true;
}


void MainMenuScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void MainMenuScene::ShowHighScore(cocos2d::Ref* pSender)
{
	ScoreBoard* scoreBoard = ScoreBoard::CreateScoreBoard(100000);
	scoreBoard->setTag(SCOREBOARD);
	this->addChild(scoreBoard, 30);
	Menu* pMenu = (Menu*) this->getChildByTag(MENU);
	pMenu->setVisible(false);
}
void
MainMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if(keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		ScoreBoard* scoreBoard = (ScoreBoard*) this->getChildByTag(SCOREBOARD);
		if(scoreBoard != NULL)
		{
			this->removeChildByTag(SCOREBOARD);
			Menu* pMenu = (Menu*) this->getChildByTag(MENU);
			pMenu->setVisible(true);
		}
		else
		{
		Director::getInstance()->end();
		}
	}
}

void MainMenuScene::menuGoToGame(Ref* pSender)
{
	Scene *pScene = MainGameScene::CreateScene();
	pScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	Director::getInstance()->replaceScene(pScene);
}
