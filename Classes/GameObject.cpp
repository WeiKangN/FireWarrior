#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

bool GameObject::init()
{
	if (!cocos2d::Node::init())
	{
		return false;
	}
	return true;
}
float GameObject::getDmg()
{
	return _dmg;
}