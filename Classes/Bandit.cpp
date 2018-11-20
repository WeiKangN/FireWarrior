#include "Bandit.h"
#include "GamePlayLayer.h"
#include"Const.h"
#include "Physics\PhysicsHandler.h"

#define DAMAGE_BANDIT  50.0F
#define HEALTH_BANDIT 50.0F
USING_NS_CC;
Bandit::Bandit():
	Health(HEALTH_BANDIT)
{
	_dmg = DAMAGE_BANDIT;
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
	this->setTag(TAG_BANDIT);
	_Enemy->setPosition(this->getContentSize() * 0.5f);
	this->setScale (6.0f);
	this->setScaleX(-6.0f);

	// Physic
	PhysicsBody *physBody = PhysicsBody::createBox(Size(13.0f, 25.0f), PhysicsMaterial(1.0f, 1.0f, 0.0f));;
	physBody->setGravityEnable(false);
	physBody->setDynamic(false);
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
	Animation* animation = Animation::create();
	for (int i = 1; i < 8; i++)
	{
		std::string Demons = StringUtils::format("attack (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Demons));

	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_Enemy->runAction(RepeatForever::create(animate));
}

void Bandit::Run()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 9; i++)
	{
		std::string Demons = StringUtils::format("run (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Demons));

	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_Enemy->runAction(RepeatForever::create(animate));
}

void Bandit::TakeDamage()
{

	this->Health -= this->_dmg;
	this->updateHealthBar(this->Health);
	if (this->Health <= 0)
	{

		this->getPhysicsBody()->setContactTestBitmask(false);
		CallFunc *removeCallback = CallFunc::create([=] {
			this->removeFromParent();
		});
		runAction(Sequence::create(Blink::create(3.0f, 3), removeCallback, nullptr));


	}
}

void Bandit::updateHealthBar(float percent)
{
	healthbarBandit->removeFromParent();
	setHealthBar(percent);
}

void Bandit::setHealthBar(float percent)
{
	auto winSize = Director::getInstance()->getWinSize();

	healthbarBandit = ui::LoadingBar::create("Art/HealthBar.png");
	this->addChild(healthbarBandit);
	healthbarBandit->setDirection(ui::LoadingBar::Direction::LEFT);
	healthbarBandit->setScaleX(0.1f);
	healthbarBandit->setScaleY(0.11f);
	healthbarBandit->setPercent(percent);
	healthbarBandit->setPosition(Vec2(7.0f, 10.0f));
}

void Bandit::onContactBeganWith(GameObject * obj)
{
	if (obj->getTag() == TAG_MAVERICK)
	{
		this->TakeDamage();
	}
}

void Bandit::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void Bandit::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void Bandit::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}
