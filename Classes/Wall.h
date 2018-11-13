#ifndef WALL_H
#define WALL_H

#include "GameObject.h"

class Wall : public GameObject
{
public:
	Wall();
	~Wall();
	virtual void onContactBeganWith(GameObject* obj) override;
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
	virtual bool init();
	CREATE_FUNC(Wall);
private:

};


#endif // !WALL_H
