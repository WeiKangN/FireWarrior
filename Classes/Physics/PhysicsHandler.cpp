#include "PhysicsHandler.h"
#include "cocos2d.h"
#include "GameObject.h"
USING_NS_CC;

PhysicsHandler::PhysicsHandler()
{
}

PhysicsHandler::~PhysicsHandler()
{
}

bool PhysicsHandler::onContactBegin(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	// Cach 2
	auto obj1 = dynamic_cast<GameObject*>(bodyA->getNode());
	auto obj2 = dynamic_cast<GameObject*>(bodyB->getNode());

	if (obj1 && obj2)
	{
		obj1->onContactBeganWith(obj2);
		obj2->onContactBeganWith(obj1);
	}
	//
	// Cach 1
	//auto userDataA = static_cast<Node*>(bodyA->GetUserData());
	//auto userDataB = static_cast<Node*>(bodyB->GetUserData());
	//if (userDataA->getTag() == (int)ObjectTAG::TAG_CHARACTER)
	//{
	//	//
	//}
	//else if (userDataB->getTag() == (int)ObjectTAG::TAG_CHARACTER)
	//{
	//	//
	//}
	// 
	//auto castobj = static_cast<MainCharacter*>(bodyA->GetUserData());
	//if (castobj) // A la character
	//{
	//	castobj->jump();
	//	auto platform = static_cast<Platform*>(bodyB->GetUserData());
	//	platform->fallDown();
	//}
	//else // B la character
	//{
	//	auto body = static_cast<MainCharacter*>(bodyB->GetUserData());
	//	body->jump();
	//	auto platform = static_cast<Platform*>(bodyA->GetUserData());
	//	platform->fallDown();
	//}
	return true;
}

void PhysicsHandler::onContactSeperated(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	// Cach 2
	auto obj1 = static_cast<GameObject*>(bodyA->getOwner());
	auto obj2 = static_cast<GameObject*>(bodyB->getOwner());

	if (obj1 && obj2)
	{
		obj1->onContactSeparateWith(obj2, contact);
		obj2->onContactSeparateWith(obj1, contact);
	}
}

bool PhysicsHandler::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	// Cach 2
	auto obj1 = static_cast<GameObject*>(bodyA->getOwner());
	auto obj2 = static_cast<GameObject*>(bodyB->getOwner());
	if (obj1 && obj2)
	{
		obj1->onContactPreSolveWith(obj2, contact, solve);
		obj2->onContactPreSolveWith(obj1, contact, solve);
	}

	return true;
}

void PhysicsHandler::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	// Cach 2
	auto obj1 = dynamic_cast<GameObject*>(bodyA->getOwner());
	auto obj2 = dynamic_cast<GameObject*>(bodyB->getOwner());
	if (obj1 && obj2)
	{
		obj1->onContactPostSolveWith(obj2, contact, solve);
		obj2->onContactPostSolveWith(obj1, contact, solve);
	}
}