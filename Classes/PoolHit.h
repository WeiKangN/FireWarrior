#ifndef _POOL_HIT_H_
#define _POOL_HIT_H

#include"cocos2d.h"

class Hit;
class PoolHit
{
public:
	PoolHit();
	~PoolHit();

	Hit* createHit();

private:
	cocos2d::Vector<Hit*> _listHit;

private:
	void returnHitToPool(Hit* hit);
};






#endif // !_POOL_HIT_H_

