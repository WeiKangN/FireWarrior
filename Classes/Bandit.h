#ifndef _BANDIT_H_
#define _BANDIT_H_
#include "cocos2d.h"
#include "GamePlayLayer.h"

class Bandit:public cocos2d::Node

{
public:
	Bandit();
	~Bandit();
	CREATE_FUNC(Bandit);
	virtual bool init();
	void Idle();
	void Attack();
	void Run();
private:
	cocos2d::Sprite*_Enemy;

};



#endif // !_BANDIT_H_

