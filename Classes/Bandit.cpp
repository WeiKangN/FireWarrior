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

	// Physic
	PhysicsBody *physBody = PhysicsBody::createBox(Size(13.0f, 25.0f), PhysicsMaterial(1.0f, 1.0f, 0.0f));;
	physBody->setGravityEnable(false);
	physBody->setDynamic(true);
	physBody->setPositionOffset(Vec2(-10.0f, -10.0f));
	physBody->setCategoryBitmask(ENEMY_CATEGORY_BITMASK); // 0001
	physBody->setCollisionBitmask(ENEMY_COLLISION_AND_CONTACT_TEST_BITMASK); // 0010
	physBody->setContactTestBitmask(ENEMY_COLLISION_AND_CONTACT_TEST_BITMASK);
	//apply physicsBody to the sprite
	this->addComponent(physBody);
	

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
