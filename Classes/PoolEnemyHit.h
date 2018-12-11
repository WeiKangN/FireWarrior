#ifndef _POOL_ENEMY_HIT
#define _POOL_ENEMY_HIT

#include"cocos2d.h"

class EnemyHit;
class PoolEnemyHit
{
public:
	PoolEnemyHit();
	~PoolEnemyHit();

	EnemyHit* createEnemyHit();
private:
	cocos2d::Vector<EnemyHit*> _listHit;

private:
	void returnHitToPool(EnemyHit* hit);
};






#endif // !_POOL_ENEMY_HIT

