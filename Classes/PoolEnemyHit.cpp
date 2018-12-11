#include "PoolEnemyHit.h"
#include "EnemyHit.h"

PoolEnemyHit::PoolEnemyHit()
{
}

PoolEnemyHit::~PoolEnemyHit()
{
}

EnemyHit * PoolEnemyHit::createEnemyHit()
{

	EnemyHit* instance = nullptr;
	if (_listHit.size() <= 0)
	{
		instance = EnemyHit::create();
		instance->setOnDestroyCallback(CC_CALLBACK_1(PoolEnemyHit::returnHitToPool, this));

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

void PoolEnemyHit::returnHitToPool(EnemyHit * hit)
{
	_listHit.pushBack(hit);
}
