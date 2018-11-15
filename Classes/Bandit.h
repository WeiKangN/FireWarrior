#ifndef _BANDIT_H_
#define _BANDIT_H_
#include "cocos2d.h"
#include "GamePlayLayer.h"
#include"GameObject.h"
#include"Physics\PhysicsHandler.h"

class Bandit:public GameObject

{
public:
	Bandit();
	~Bandit();
	CREATE_FUNC(Bandit);
	virtual bool init();
	void Idle();
	void Attack();
	void Run();
	virtual void onContactBeganWith(GameObject* obj) override;
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
private:
	cocos2d::Sprite*_Enemy;

};



#endif // !_BANDIT_H_

