#include "Wall.h"
#include "Const.h"
Wall::Wall()
{
}

Wall::~Wall()
{
}

bool Wall::init()
{
	if (!GameObject::init())
	{
		return false;
	}
	this->setTag(TAG_WALL);
	return true;
}

void Wall::onContactBeganWith(GameObject* obj)
{

}
void Wall::onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve)
{

}

void Wall::onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact)
{

}

void Wall::onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)
{

}