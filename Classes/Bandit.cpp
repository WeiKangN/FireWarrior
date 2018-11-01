#include "Bandit.h"
#include "GamePlayLayer.h"
#include"Const.h"

USING_NS_CC;
Bandit::Bandit()
{
}

Bandit::~Bandit()
{
}

bool Bandit::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size WinSize = Director::getInstance()->getWinSize();
	_Enemy = Sprite::create("Art/Bandit/idle (1).png");
	this->addChild(_Enemy);
	_Enemy->setPosition(this->getContentSize() * 0.5f);
	this->setScale (6.0f);
	this->setScaleX(-6.0f);
	return true;
}

void Bandit::Idle()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string Demons = StringUtils::format("idle (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Demons));

	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_Enemy->runAction(RepeatForever::create(animate));
}



void Bandit::Attack()
{
}

void Bandit::Run()
{
}
