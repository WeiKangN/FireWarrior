#include "GameScene.h"
#include"GamePlayLayer.h"
#include "RoleController.h"
#include "MainPlayer.h"
#include "PoolHit.h"
#include "Hit.h"
USING_NS_CC;
using namespace cocos2d::ui;
GameScene::GameScene()/*:_poolHit(nullptr)*/
{
	/*_poolHit = new PoolHit();*/
}

GameScene::~GameScene()
{
	/*CC_SAFE_DELETE(_poolHit);*/
}

cocos2d::Scene * GameScene::createGameScene()
{
	Scene* scene = Scene::createWithPhysics();
	PhysicsWorld* world = scene->getPhysicsWorld();
	world->setSubsteps(10);
	// remember to turn off debug when release
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	GameScene* node = GameScene::create();
	scene->addChild(node);
	return scene;
}

bool GameScene::init()
{
	if (!Node::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Art/Knight.plist", "Art/Knight.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Art/Bandit/bandit.plist", "Art/Bandit/bandit.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Art/Evil/Doggo.plist", "Art/Evil/Doggo.png");
	gamePlayLayer = GamePlayLayer::create();

	this->addChild(gamePlayLayer);
	controller = RoleController::createController(70, Vec2(0, 0));
	controller->setRoleControllerListenr(this);
	this->addChild(controller, 99);
	//auto controller = RoleController::createController(40.0f, Vec2(0, 0));
	//this->addChild(controller);
	scheduleUpdate();

	//Button
	auto winSize = Director::getInstance()->getWinSize();
	_btnPlay = Button::create("Art/ButtonHit_1.png", "Art/ButtonHit_2.png", "Art/ButtonHit_1.png");
	this->addChild(_btnPlay);
	_btnPlay->setPosition(Vec2(winSize.height + 500, winSize.width / 2 - 570));
	//_btnPlay->setPosition(winSize * 0.5f);
	_btnPlay->setScale(2.5f);
	_btnPlay->addTouchEventListener(CC_CALLBACK_2(GameScene::PlayButtonHit, this));

	//Map

	//auto _tileMap = TMXTiledMap::create("Art/Underground/underground.tmx");
	//_tileMap->setScale(1.0f);
	//addChild(_tileMap,0,99);

	return true;
}

void GameScene::onControllerTouchBegan(cocos2d::Vec2 velocity)
{

}

void GameScene::onControllerTouchMoving(cocos2d::Vec2 velocity)
{

	CCLOG(" GamePlayLayer moving %f %f", velocity.x, velocity.y);
	Vec2 newVelocity = velocity;
	auto absX = abs(newVelocity.x);
	auto absY = abs(newVelocity.y);

	if (absX > absY)
	{
		newVelocity.y = 0;
	}
	else if (absY > absX)
	{
		newVelocity.x = 0;
	}
	else
	{
		newVelocity.x = 0;
		newVelocity.y = 0;
	}
	auto knight = gamePlayLayer->_Knight;
	knight->setvelocity(newVelocity);

	//auto camera = Camera::getDefaultCamera();
	//auto campos = camera->getPosition3D();
	//campos.x = knight->getPositionX();
	//campos.y = knight->getPositionY();
	//camera->setPosition3D(campos);

	auto knightWorldPos = knight->getParent()->convertToWorldSpace(knight->getPosition());
	auto scenePos = this->convertToNodeSpace(knightWorldPos);
	gamePlayLayer->setPosition(scenePos);

	/*controller->setPositioin(Vec2(_Knight->getPositionX()-200, _Knight->getPositionY()-600));*/

}

void GameScene::onControllerTouchEnded(cocos2d::Vec2 velocity)
{
	CCLOG(" GamePlayLayer end %f %f", velocity.x, velocity.y);
	gamePlayLayer->_Knight->Stop();
	//unscheduleUpdate();
}

void GameScene::update(float delta)
{
	/*auto pos = gamePlayLayer->getPosition();
	pos.x += 10.0f;
	gamePlayLayer->setPosition(pos);
	cocos2d::log("Pos = %f, %f", pos.x, pos.y);*/
	auto knight = gamePlayLayer->_Knight;
	gamePlayLayer->setPosition(Vec2(Director::getInstance()->getWinSize() * 0.5f) - knight->getPosition());
	//auto camera = Camera::getDefaultCamera();
	//auto campos = camera->getPosition3D();
	//campos.x += 10;
	//camera->setPosition3D(campos);
}

void GameScene::PlayButtonHit(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		cocos2d::log("On end button hit");

		gamePlayLayer->_Knight->Attack();
		
	}
}
