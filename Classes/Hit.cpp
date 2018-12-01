#include "Hit.h"
#include "Const.h"

USING_NS_CC;

Hit::Hit() : _willBeDestroy(false)
{
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
	PhysicsBody *phyBody = PhysicsBody::createBox(Size(30.0f, 50.0f), PhysicsMaterial(0.1f, 0.0f, 0.0f));
	phyBody->setGravityEnable(false);
	phyBody->setRotationEnable(false);
	phyBody->setDynamic(true);
	phyBody->setCategoryBitmask(LINE_CATEGORY_BITMASK); // 0001
	phyBody->setCollisionBitmask(LINE_COLISION_AND_CONTACT_TEST_BITMASK); // 0010
	phyBody->setContactTestBitmask(LINE_COLISION_AND_CONTACT_TEST_BITMASK);
	//apply physicsBody to the sprite
	this->setPhysicsBody(phyBody);
	hit();
	this->setTag((int)ObjectTAG::TAG_LINE);
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
	hit();
	scheduleUpdate();
}

void Hit::hit()
{
	auto moveBy = MoveBy::create(0.5f, Vec2(500.0f, 0.0f));
	this->runAction(moveBy);
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
