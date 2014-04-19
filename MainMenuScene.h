#ifndef __MAINMENUSCENE_H__
#define __MAINMENUSCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* CreateScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
private:
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuGoToGame(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually 
    CREATE_FUNC(MainMenuScene); // layer의 create를 만들어 주는 함수
};

#endif // __MAINMENUSCENE_H__