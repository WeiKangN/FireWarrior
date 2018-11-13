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

void EvilDog::onContactBeganWith(GameObject * obj)
{
	

}

void EvilDog::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void EvilDog::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void EvilDog::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
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
	this->setTag(TAG_DOG);
	_sprDoggie->setPosition(this->getContentSize() * 0.5f);
	this->setScale(4.0f);
	
	// Physic
	PhysicsBody *physBody = PhysicsBody::createBox(Size(28.0f, 13.0f), PhysicsMaterial(1.0f, 1.0f, 0.0f));;
	physBody->setGravityEnable(false);
	physBody->setDynamic(true);
	physBody->setPositionOffset(Vec2(-5.0f,-10.0f));
	physBody->setCategoryBitmask(ENEMY_CATEGORY_BITMASK); // 0001
	physBody->setCollisionBitmask(ENEMY_COLLISION_AND_CONTACT_TEST_BITMASK); // 0010
	physBody->setContactTestBitmask(ENEMY_COLLISION_AND_CONTACT_TEST_BITMASK);
	//apply physicsBody to the sprite
	this->addComponent(physBody);

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
