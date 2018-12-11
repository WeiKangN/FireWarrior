#include "EnemyHit.h"
#include "Const.h"
USING_NS_CC;

#define TIME_AUTO_DESTROY 0.1f

EnemyHit::EnemyHit():_willBeDestroy(false)
{
	_dmg = 10;
}

EnemyHit::~EnemyHit()
{

}

bool EnemyHit::init()
{
	if (!GameObject::init())
	{
		return false;
	}
	PhysicsBody *phyBody = PhysicsBody::createBox(Size(20.0f, 20.0f), PhysicsMaterial(0.1f, 0.0f, 0.0f));
	phyBody->setGravityEnable(false);
	phyBody->setRotationEnable(false);
	phyBody->setDynamic(true);
	phyBody->setPositionOffset(Vec2(3.0f, -30.0f));
	phyBody->setCategoryBitmask(LINE_CATEGORY_BITMASK); // 0001
	phyBody->setCollisionBitmask(LINE_COLISION_AND_CONTACT_TEST_BITMASK); // 0010
	phyBody->setContactTestBitmask(LINE_COLISION_AND_CONTACT_TEST_BITMASK);
	//apply physicsBody to the sprite
	this->setPhysicsBody(phyBody);
	this->setTag(TAG_EHIT);
	scheduleUpdate();

	
	return true;
}

void EnemyHit::onContactBeganWith(GameObject * obj)
{
	if (obj->getTag() == TAG_MAVERICK)
	{
		
		_willBeDestroy = true;
		this->setVisible(false);
	}
}

void EnemyHit::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void EnemyHit::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void EnemyHit::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void EnemyHit::setOnDestroyCallback(OnHitDestroyCallback callback)
{
	_onHitDestroyCallback = callback;
}

void EnemyHit::reset()
{
	this->setVisible(true);
	scheduleUpdate();
}

void EnemyHit::attackAt(cocos2d::Vec2 pos)
{
	this->setPosition(pos);
	this->scheduleAutoDestroy();
}

void EnemyHit::scheduleAutoDestroy()
{
	auto delay = DelayTime::create(TIME_AUTO_DESTROY);
	auto seq = Sequence::create(delay, CallFunc::create([=]()
	{
		this->_willBeDestroy = true;
	}), NULL);
	this->runAction(seq);
}

float EnemyHit::getDmg()
{
	return _dmg;
}

void EnemyHit::update(float delta)
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

