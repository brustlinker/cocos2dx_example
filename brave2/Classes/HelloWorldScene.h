#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"


USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(HelloWorld);


	bool onTouchBegan(Touch* touch, Event* event);
private:
	Player* _player;
	Player* _enemy1;
	EventListenerTouchOneByOne* _listener_touch;
};

#endif // __HELLOWORLD_SCENE_H__
