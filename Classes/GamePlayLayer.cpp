#include "GamePlayLayer.h"
#include "MainPlayer.h"
#include "GameScene.h"
#include "Bandit.h"
#include "EvilDog.h"
#include "RoleController.h"
#include "Const.h"
#include "Physics/PhysicsHandler.h"
#include "Wall.h"

USING_NS_CC;
using namespace cocos2d::ui;

GamePlayLayer::GamePlayLayer()
{
	_physicsHandler = new PhysicsHandler();
}

GamePlayLayer::~GamePlayLayer()
{
	CC_SAFE_DELETE(_physicsHandler);
}

bool GamePlayLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setColor(Color3B::RED);

	right = true;

	//MainPlayer
	winSize = Director::getInstance()->getWinSize();
	_Knight = MainPlayer::create();
	this->addChild(_Knight,2);
	_Knight->setPosition(250.0f, 600.0f);
	_Knight->PlayAnimation();
	
	//Enemy01
	Size WinSize = Director::getInstance()->getWinSize();
	_bandit = Bandit::create();
	this->addChild(_bandit,2);
	_bandit->setPosition(1200.0f, 620.0f);
	_bandit->Idle();

	//Enemy02
	
	_HellDog = EvilDog::create();
	this->addChild(_HellDog,2);
	_HellDog->setPosition(1000.0f, 500.0f);
	_HellDog->DogIdle();
	




	//Key
	EventListenerKeyboard* eventClick = EventListenerKeyboard::create() ;
	eventClick->onKeyReleased = CC_CALLBACK_2(GamePlayLayer::onKeyReleased, this); 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventClick, this);
	scheduleUpdate();

	auto ePhysics = EventListenerPhysicsContact::create();
	ePhysics->onContactBegin = CC_CALLBACK_1(PhysicsHandler::onContactBegin, _physicsHandler);
	ePhysics->onContactPostSolve = CC_CALLBACK_2(PhysicsHandler::onContactPostSolve, _physicsHandler);
	ePhysics->onContactPreSolve = CC_CALLBACK_2(PhysicsHandler::onContactPreSolve, _physicsHandler);
	ePhysics->onContactSeparate = CC_CALLBACK_1(PhysicsHandler::onContactSeperated, _physicsHandler);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ePhysics, this);

	//map

	auto _tileMap = TMXTiledMap::create("Art/Underground/underground2.tmx");
	_tileMap->setScale(6.5f);
	_tileMap->setPosition(-20.0f,-2400.0f);
	addChild(_tileMap, 0, 99);


	auto ObjectWall = _tileMap->getObjectGroup("wall");
	auto Wall = ObjectWall->getObjects();
	for (int i = 0; i < Wall.size(); i++)
	{

		auto objInfo = Wall.at(i).asValueMap();
		int type = objInfo.at("type").asInt();
		if (type==1)
		{
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			int width = objInfo.at("width").asInt();
			int height = objInfo.at("height").asInt();

			auto wall = Wall::create();
			this->addChild(wall);
			wall->setPosition(x, y);

			PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(100.0f, 0.0f, 0.0f));
			tilePhysics->setDynamic(false);   //static is good enough for walls
			tilePhysics->setGravityEnable(false);
			tilePhysics->setRotationEnable(false);
			tilePhysics->setCategoryBitmask(WALL_CATEGORY_BITMASK);
			tilePhysics->setCollisionBitmask(WALL_COLLISION_AND_CONTACT_TEST_BIT_MASK);
			tilePhysics->setContactTestBitmask(WALL_COLLISION_AND_CONTACT_TEST_BIT_MASK);
			wall->setPhysicsBody(tilePhysics);

			//auto node = Node::create();
			//this->addChild(node);
			//node->setPosition(x, y);

			//PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(1.0f, 0.0f, 0.0f));
			//tilePhysics->setDynamic(false);   //static is good enough for walls
			//tilePhysics->setGravityEnable(false);
			//tilePhysics->setRotationEnable(false);
			//node->setPhysicsBody(tilePhysics);
		}
		
	}

	return true;
}