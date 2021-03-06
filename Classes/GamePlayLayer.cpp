#include "GamePlayLayer.h"
#include "MainPlayer.h"
#include "GameScene.h"
#include "Bandit.h"
#include "EvilDog.h"
#include "RoleController.h"
#include "Const.h"
#include "Physics/PhysicsHandler.h"
#include "Wall.h"
#include "AudioEngine.h"

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
	//Music 
	experimental::AudioEngine::preload("Sound/0-DUNGEON_dungchonhom.mp3");
	auto MusicBG = experimental::AudioEngine::play2d("Sound/0-DUNGEON_dungchonhom.mp3");
	experimental::AudioEngine::setLoop(MusicBG, true);

	//MainPlayer
	winSize = Director::getInstance()->getWinSize();
	_Knight = MainPlayer::create();
	this->addChild(_Knight,2);
	_Knight->setPosition(180.0f, 3000.0f);
	_Knight->PlayAnimation();
	_Knight->setHealthBar(100.0f);
	
	//Enemy01
	Size WinSize = Director::getInstance()->getWinSize();
	_bandit = Bandit::create();
	this->addChild(_bandit,2);
	_bandit->setPosition(1200.0f, 620.0f);
	_bandit->Idle();
	//_bandit->Attack();
	_bandit->setHealthBar(100.0f);
	_bandit->enalbeAI(_Knight);

	//Enemy02
	//auto resetHealth = ;
	_HellDog = EvilDog::create();
	this->addChild(_HellDog,2);
	_HellDog->setPosition(1000.0f, 500.0f);
	_HellDog->DogIdle();
	_HellDog->setHealthBar(100.0f);
	_HellDog->enalbeAI(_Knight);
	
	
	//khoang cach giua ch� vs Maverick
	


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
	/*_tileMap->setScale(6.5f);
	_tileMap->setPosition(-20.0,-2400.0f);*/
	_tileMap->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_tileMap->setScale(6.5f);// phai nho scale map la gia tri bao nhieu
	_tileMap->setPosition(0.0f, 0.0f);
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
			wall->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			wall->setPosition(x + width * 0.5f, y + height * 0.5f);

			PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(100.0f, 0.0f, 0.0f));
			tilePhysics->setDynamic(false);   //static is good enough for walls
			tilePhysics->setGravityEnable(false);
			tilePhysics->setRotationEnable(false);
			//tilePhysics->setPositionOffset(Vec2(1500.0f, 60.0f));
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
		else if (type == 2)
		{
			float x = objInfo.at("x").asFloat();
			float y = objInfo.at("y").asFloat();
			float width = objInfo.at("width").asFloat();
			float height = objInfo.at("height").asFloat();

			auto wall = Wall::create();
			_tileMap->addChild(wall);
			wall->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			wall->setPosition(x + width * 0.5f, y + height * 0.5f);

			PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(100.0f, 0.0f, 0.0f));
			tilePhysics->setDynamic(false);   //static is good enough for walls
			tilePhysics->setGravityEnable(false);
			tilePhysics->setRotationEnable(false);
			//tilePhysics->setPositionOffset(Vec2(1500.0f, 60.0f));
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
		else if (type == 10)
		{
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			int width = objInfo.at("width").asInt();
			int height = objInfo.at("height").asInt();
			// gio lay scale map cua map gan vo
			auto enemy = Bandit::create();
			
			this->addChild(enemy, 2);
			enemy->setPosition(6.5f*(x + width * 0.5f), 6.5f*(y+height * 0.5f));
			enemy->Idle();
			//_bandit->Attack();
			enemy->setHealthBar(100.0f);
			enemy->enalbeAI(_Knight);
		}
		else if (type == 5)
		{
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			int width = objInfo.at("width").asInt();
			int height = objInfo.at("height").asInt();
			// gio lay scale map cua map gan vo
			auto enemy = EvilDog::create();
			
			this->addChild(enemy, 2);
			enemy->setPosition(6.5f*(x + width * 0.5f), 6.5f*(y + height * 0.5f));
			enemy->DogIdle();
			//_bandit->Attack();
			enemy->setHealthBar(100.0f);
			enemy->enalbeAI(_Knight);
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

void GamePlayLayer::EvilDog02()
{
	_EvilDog2 = EvilDog::create();
	this->addChild(_EvilDog2);
	_EvilDog2->setPosition(1400.0f, 500.0f);
}

void GamePlayLayer::EvilDog03()
{
}

void GamePlayLayer::EvilDog04()
{
}

void GamePlayLayer::EvilDog05()
{
}

void GamePlayLayer::EvilDog06()
{
}

void GamePlayLayer::EvilDog07()
{
}

void GamePlayLayer::Bandit02()
{
}

void GamePlayLayer::Bandit03()
{
}

void GamePlayLayer::Bandit04()
{
}

void GamePlayLayer::Bandit05()
{
}

void GamePlayLayer::Bandit06()
{
}

void GamePlayLayer::Bandit07()
{
}

void GamePlayLayer::Bandit08()
{
}

void GamePlayLayer::Bandit09()
{
}

void GamePlayLayer::Bandit010()
{
}

void GamePlayLayer::Bandit011()
{
}
