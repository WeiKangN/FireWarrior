#include "GamePlayLayer.h"
#include "MainPlayer.h"
#include "GameScene.h"
#include "Bandit.h"
#include "EvilDog.h"


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
	_Knight = MainPlayer::create();
	this->addChild(_Knight,2);
	_Knight->setPosition(200.0f, 600.0f);
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

	auto tileMap = TMXTiledMap::create("Art/Underground/underground2.tmx");
	tileMap->setScale(6.5f);
	tileMap->setPosition(-700.0f,-2000.0f);
	addChild(tileMap, 0, 99);

	auto groupWall = tileMap->getObjectGroup("wall");
	auto wallList = groupWall->getObjects();
	for (int i = 0; i < wallList.size(); i++)
	{
		auto objInfo = wallList.at(i).asValueMap();
		int type = objInfo.at("type").asInt();
		if (type==1)
		{
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			int width = objInfo.at("width").asInt();
			int height = objInfo.at("height").asInt();
		}

	}

	return true;
}


void GamePlayLayer::menuCloseCallback(cocos2d::Ref * pSender)
{
}

void GamePlayLayer::update(float dt)
{
	

	//_Cam = Camera::getDefaultCamera();
	//campos = _Cam->getPosition3D();
	//campos.x = _Knight->getPositionX();
	//campos.y = _Knight->getPositionY();
	//_Cam->setPosition3D(campos);

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
		auto gameOver = GameScene::createGameScene();
		Director::getInstance()->replaceScene(gameOver);
	}
	return true;
}
