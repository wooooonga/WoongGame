	#ifndef __MAINMENUSCENE_H__
#define __MAINMENUSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* CreateScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	EventListenerKeyboard* _keyboardListener;
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    // a selector callback
private:
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuGoToGame(cocos2d::Ref* pSender);
	void ShowHighScore(cocos2d::Ref* pSender);
    // implement the "static create()" method manually 
    CREATE_FUNC(MainMenuScene); // new와 여러가지 

	enum
	{
		MENU		= 1,
		SCOREBOARD	= 2
	};
};

#endif // __MAINMENUSCENE_H__