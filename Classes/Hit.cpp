#include "Hit.h"
#include "Const.h"

USING_NS_CC;

#define TIME_AUTO_DESTROY 0.1f

Hit::Hit() : _willBeDestroy(false)
{
	_dmg = 10;
}

Hit::~Hit()
{
}

bool Hit::init()
{
	if (!GameObject::init())
	{
		return false;
	}
	PhysicsBody *phyBody = PhysicsBody::createBox(Size(20.0f, 20.0f), PhysicsMaterial(0.1f, 0.0f, 0.0f));
	phyBody->setGravityEnable(false);
	phyBody->setRotationEnable(false);
	phyBody->setDynamic(true);
	phyBody->setPositionOffset(Vec2(3.0f ,-3.0f));
	phyBody->setCategoryBitmask(LINE_CATEGORY_BITMASK); // 0001
	phyBody->setCollisionBitmask(LINE_COLISION_AND_CONTACT_TEST_BITMASK); // 0010
	phyBody->setContactTestBitmask(LINE_COLISION_AND_CONTACT_TEST_BITMASK);
	//apply physicsBody to the sprite
	this->setPhysicsBody(phyBody);
	this->setTag(TAG_HIT);
	scheduleUpdate();

	return true;
}

void Hit::onContactBeganWith(GameObject * obj)
{
	if (obj->getTag() == TAG_DOG || obj->getTag() == TAG_BANDIT)
	{
		_willBeDestroy = true;
		this->setVisible(false);
	}
}

void Hit::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void Hit::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void Hit::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void Hit::setOnDestroyCallback(OnHitDestroyCallback callback)
{
	_onHitDestroyCallback = callback;
}

void Hit::reset()
{
	this->setVisible(true);
	scheduleUpdate();
}

void Hit::update(float delta)
{
	if (_willBeDestroy)
	{
		if (_onHitDestroyCallback)
		{
			_onHitDestroyCallback(this);
		}
		stopAllActions();
		//this->getPhysicsBody()-> (true);
		this->removeFromParent();
		_willBeDestroy = false;
	}
}

void Hit::scheduleAutoDestroy()
{
	auto delay = DelayTime::create(TIME_AUTO_DESTROY);
	auto seq = Sequence::create(delay, CallFunc::create([=]()
	{
		this->_willBeDestroy = true;
	}), NULL);
	this->runAction(seq);
}

void Hit::attackAt(cocos2d::Vec2 pos)
{
	this->setPosition(pos);
	this->scheduleAutoDestroy();
}
