#include"PoolHit.h"
#include "Hit.h"

PoolHit::PoolHit()
{
}

PoolHit::~PoolHit()
{
}

Hit * PoolHit::createHit()
{
	Hit* instance = nullptr;
	if (_listHit.size()<=0) 
	{
		instance = Hit::create();
		instance->setOnDestroyCallback(CC_CALLBACK_1(PoolHit::returnHitToPool, this));

	}
	else
	{
		instance = _listHit.back(); // get last element
		instance->reset();
		instance->retain();
		_listHit.popBack(); // erase last element
	}
	return instance;
}

void PoolHit::returnHitToPool(Hit * hit)
{
	_listHit.pushBack(hit);
}
