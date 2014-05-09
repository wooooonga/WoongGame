#include "AppDelegate.h"
#include "MainmenuScene.h"

USING_NS_CC;

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iphone" };
static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "ipad"   };
static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };

static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(320, 568);

AppDelegate::AppDelegate() {}
AppDelegate::~AppDelegate() {}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
	
    if(!glview) {
		//glview = GLView::createWithRect("My Game", Rect(0, 0, 1024, 768));
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

	//auto screenSize = glview->getFrameSize(); //기기의 프레임을 받아옴
	auto designSize = Size(320, 568);

	//if(screenSize.height > 568)
	//{
	//	auto resourceSize = Size(640, 1200);
	//	director->setContentScaleFactor(2);
	//}
	//cocos2d::log("%f",frameSize.width);

	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);

		//director->setContentScaleFactor(smallResource.size.height / designResolutionSize.height);
	// setup screen size
	//glview->setFrameSize(320, 568);
	//glview->initWithRect(Rect(320, 568), 1);
	//glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

    // turn on display FPS
    director->setDisplayStats(true);
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MainMenuScene::CreateScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
