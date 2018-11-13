#ifndef _PHYSICS_HANDLER_H
#define _PHYSICS_HANDLER_H

#include "cocos2d.h"

// this class purpose is handle event physics
class PhysicsHandler
{
public:
	PhysicsHandler();
	~PhysicsHandler();

	virtual bool onContactBegin(cocos2d::PhysicsContact& contact);

	virtual void onContactSeperated(cocos2d::PhysicsContact& contact);

	virtual bool onContactPreSolve(cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve);

	virtual void onContactPostSolve(cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve);
};
#endif // !_PHYSICS_HANDLER_H

