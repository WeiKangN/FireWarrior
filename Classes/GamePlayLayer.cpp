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
	_Knight->setHealthBar(100.0f);
	
	//Enemy01
	Size WinSize = Director::getInstance()->getWinSize();
	_bandit = Bandit::create();
	this->addChild(_bandit,2);
	_bandit->setPosition(1200.0f, 620.0f);
	_bandit->Idle();
	_bandit->Attack();
	_bandit->setHealthBar(100.0f);

	//Enemy02
	//auto resetHealth = ;
	_HellDog = EvilDog::create();
	this->addChild(_HellDog,2);
	_HellDog->setPosition(1000.0f, 500.0f);
	_HellDog->DogIdle();
	_HellDog->setHealthBar(100.0f);
	_HellDog->enalbeAI(_Knight);
	
	
	//khoang cach giua chó vs Maverick
	


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
			_tileMap->addChild(wall);
			wall->setPosition(x, y);

			PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(100.0f, 0.0f, 0.0f));
			tilePhysics->setDynamic(false);   //static is good enough for walls
			tilePhysics->setGravityEnable(false);
			tilePhysics->setRotationEnable(false);
			tilePhysics->setPositionOffset(Vec2(1500.0f, 60.0f));
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

void GamePlayLayer::update(float delta)
{
	/*if (_HellDog!= nullptr)
	{
		auto distance = _HellDog->getPosition() - _Knight->getPosition();
		Vec2 MinDis = Vec2(700.0f, 700.0f);
		if (distance < MinDis)
		{
			_HellDog->Run();
			_HellDog->chaseMaverick(_Knight->getPosition());
		}
	}
	*/
	
}

void GamePlayLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event*e)
{
	if (keycode == EventKeyboard::KeyCode::KEY_S)
	{
		_Knight->setvelocity(Vec2(0.0f, -1.0f));
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_C)
	{
		_Knight->Attack();
	}
}

void GamePlayLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event*e)
{
	if (keycode == EventKeyboard::KeyCode::KEY_S)
	{
		_Knight->setvelocity(Vec2(0.0f, -1.0f));
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_C)
	{
		_Knight->Attack();
	}
}