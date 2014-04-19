#include "MainMenuScene.h"
#include "MainGameScene.h"

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

	MenuItemFont *pLabelStart = MenuItemFont::create("Start", this, menu_selector(MainMenuScene::menuGoToGame));
	MenuItemFont *pLabelClose = MenuItemFont::create("Close", this, menu_selector(MainMenuScene::menuCloseCallback));
	pLabelStart->setColor(ccc3(255, 0, 0));
	pLabelClose->setColor(ccc3(0, 255, 0));
	Menu *pMenu = Menu::create(pLabelStart, pLabelClose, NULL);
	pMenu->alignItemsHorizontally();

	this->addChild(pMenu, 1);

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

void MainMenuScene::menuGoToGame(Ref* pSender)
{
	Scene *pScene = MainGameScene::CreateScene();
	Director::getInstance()->replaceScene(pScene);
}
