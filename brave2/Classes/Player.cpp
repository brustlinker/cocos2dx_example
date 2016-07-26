#include "Player.h"


Player* Player::create(PlayerType type)
{
	Player* player = new Player();
	if (player && player->initWithPlayerType(type))
	{
		player->autorelease();
		return player;
	}
	else
	{
		delete player;
		player = NULL;
		return NULL;
	}
}

bool Player::initWithPlayerType(PlayerType type)
{
	std::string sfName = "";
	_type = type;
	int animationFrameNum[5] = { 4, 4, 4, 2, 4 };
	int animationFrameNum2[5] = { 3, 3, 3, 2, 0 };

	//根据英雄的类别来初始化
	switch (type)
	{
	case PlayerType::PLAYER:
		sfName = "player1-1-1.png";
		_name = "player1";
		_animationNum = 5;
		_animationFrameNum.assign(animationFrameNum, animationFrameNum + 5);
		_speed = 125;
		break;
	case PlayerType::ENEMY1:
		sfName = "enemy1-1-1.png";
		_name = "enemy1";
		_animationNum = 4;
		_animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
		break;
	case PlayerType::ENEMY2:
		sfName = "enemy2-1-1.png";
		_name = "enemy2";
		_animationNum = 4;
		_animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
		break;
	}

	//设置默认序列帧
	this->initWithSpriteFrameName(sfName);

	string animationNames[] = { "walk", "attack", "dead", "hit", "skill" };
	_animationNames.assign(animationNames, animationNames + 5);


	//添加动画
	this->addAnimation();

	return true;
}


void Player::addAnimation()
{
	// 检测动画是否已经添加到动画缓存当中
	auto animation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("%s-%s", _name.c_str(),
		_animationNames[0])->getCString());
	if (animation)
		return;


	//每个动画
	for (int i = 0; i<_animationNum; i++)
	{
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.2f);
		//动画的一个序列帧
		for (int j = 0; j< _animationFrameNum[i]; j++)
		{
			//这是一种比较快捷的方式
			//一个样例：player1 - 3 - 2.png
			auto sfName = String::createWithFormat("%s-%d-%d.png", _name.c_str(), i + 1, j + 1)->getCString();
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName));
		}

		// 将 animation 保存到缓存当中
		//一个样例：player1-walk
		AnimationCache::getInstance()->addAnimation(animation, String::createWithFormat("%s-%s", _name.c_str(),
			_animationNames[i].c_str())->getCString());
	}


}


//播放第几个动画
void Player::playAnimationForever(int index)
{
	//防御式编程，非常好的习惯
	if (index <0 || index >= _animationNum)
	{
		log("illegal animation index!");
		return;
	}
	//一个样例：“player1-walk”
	auto str = String::createWithFormat("%s-%s", _name.c_str(), _animationNames[index].c_str())->getCString();
	//从animation的缓存当中获取animation
	auto animation = AnimationCache::getInstance()->getAnimation(str);
	
	//播放动画
	auto animate = RepeatForever::create(Animate::create(animation));
	this->runAction(animate);
}


void Player::walkTo(Vec2 dest)
{
	//停掉当前的序列帧动画
	if (_seq)
		this->stopAction(_seq);


	auto curPos = this->getPosition();

	//如果向后移动，那么反转
	if (curPos.x > dest.x)
		 this->setFlippedX(true);
	else
		 this->setFlippedX(false);
	
	//计算移动需要的时间
	auto diff = dest - curPos;
	auto time = diff.getLength() / _speed;

	//_seq，先移动，移动完成删除_seq
	auto move = MoveTo::create(time, dest);
	auto func = [&]()
	{
		this->stopAllActions();
		_seq = nullptr;
	};
	auto callback = CallFunc::create(func);
	_seq = Sequence::create(move, callback, nullptr);
	
	//播放帧动画
	this->runAction(_seq);
	this->playAnimationForever(0);

}

