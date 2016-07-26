#include "MainScene.h"
#include "SimpleAudioEngine.h"



Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//载入图片集合
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/role.plist", "image/role.pvr.ccz");

	//载入背景
	Sprite* background = Sprite::create("image/background.png");
	background->setPosition(origin + visibleSize / 2);
	this->addChild(background);

	//添加player
	_player = Player::create(Player::PlayerType::PLAYER);
	_player->setPosition(origin.x + _player->getContentSize().width / 2, origin.y + visibleSize.height / 2);
	this->addChild(_player);


	//添加一个敌人
	_enemy1 = Player::create(Player::PlayerType::ENEMY1);
	_enemy1->setPosition(origin.x + visibleSize.width - _player->getContentSize().width / 2, origin.y + visibleSize.height / 2);
	this->addChild(_enemy1);

	//player->playAnimationForever(1);
	_enemy1->playAnimationForever(1);
    
	_listener_touch = EventListenerTouchOneByOne::create();
	_listener_touch->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);

    return true;
}


void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}


bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 pos = this->convertToNodeSpace(touch->getLocation());
	_player->walkTo(pos);
	//log("MainScene::onTouchBegan");
	return true;
}