#include "EvilDog.h"
#include "GamePlayLayer.h"
#include "Const.h"

USING_NS_CC;

EvilDog::EvilDog()
{
}

EvilDog::~EvilDog()
{
}

bool EvilDog::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size WinSize = Director::getInstance()->getWinSize();
	_sprDoggie = Sprite::create("Art/Evil/dog_idle  (1).png");
	this->addChild(_sprDoggie);
	_sprDoggie->setPosition(this->getContentSize() * 0.5f);
	this->setScale(4.0f);
	

	return true;

}

void EvilDog::DogIdle()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string Demons = StringUtils::format("dog_idle  (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Demons));

	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_sprDoggie->runAction(RepeatForever::create(animate));

	/*auto sequence = Sequence::create(animateHitUp, animate, nullptr);
	_Maverick->runAction(sequence);*/

}



void EvilDog::Run()
{

}
