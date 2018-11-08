#include "GamePlayLayer.h"
#include "MainPlayer.h"
#include "GameScene.h"
#include "Bandit.h"
#include "EvilDog.h"
#include "RoleController.h"
#include "Const.h"


USING_NS_CC;
using namespace cocos2d::ui;

GamePlayLayer::GamePlayLayer()
{
}

GamePlayLayer::~GamePlayLayer()
{
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

			auto node = Node::create();
			this->addChild(node);
			node->setPosition(x, y);

			PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(1.0f, 0.0f, 0.0f));
			tilePhysics->setDynamic(false);   //static is good enough for walls
			tilePhysics->setGravityEnable(false);
			tilePhysics->setRotationEnable(false);
			node->setPhysicsBody(tilePhysics);
		}
		
	}

	

	return true;
}








bool GamePlayLayer::onGameContactBegin(cocos2d::PhysicsContact & contact)

{
	PhysicsShape* playerA = contact.getShapeA();
	PhysicsShape* playerB = contact.getShapeB();
	Node* nodeA = playerA->getBody()->getOwner();
	Node* nodeB = playerB->getBody()->getOwner();
	Size winSize = Director::getInstance()->getWinSize();

	MainPlayer* mainplayer = nullptr;
	if (playerA->getCollisionBitmask() == 1 && playerB->getCollisionBitmask() == 2 || playerA->getCollisionBitmask() == 2 && playerB->getCollisionBitmask() == 1)
	{
		/*
		auto gameOver = GameScene::createGameScene();
		Director::getInstance()->replaceScene(gameOver);
		*/
	}
	return true;
}
