#include "GamePlayLayer.h"
#include "MainPlayer.h"
#include "GameScene.h"
#include "Bandit.h"
#include "EvilDog.h"
#include "RoleController.h"


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
	
	//JoyStick
	controller = RoleController::createController(70, Vec2(0, 0));
	controller->setRoleControllerListenr(this);
	//this->addChild(controller, 0);

	// Click Button Hit

	auto winSize = Director::getInstance()->getWinSize();
	_buttonPlay = Button::create("Art/ButtonHit_1.png", "Art/ButtonHit_1.png", "Art/ButtonHit_1.png");
	//this->addChild(_buttonPlay);
	_buttonPlay->setPosition(Vec2(winSize.height+500,winSize.width/2-570));
	_buttonPlay->setScale(1.5f);
	_buttonPlay->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::PlayButtonHit, this));

	//Key
	EventListenerKeyboard* eventClick = EventListenerKeyboard::create() ;
	eventClick->onKeyReleased = CC_CALLBACK_2(GamePlayLayer::onKeyReleased, this); 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventClick, this);
	scheduleUpdate();

	//map

	auto _tileMap = TMXTiledMap::create("Art/Underground/underground2.tmx");
	_tileMap->setScale(6.5f);
	_tileMap->setPosition(-700.0f,-2000.0f);
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

void GamePlayLayer::onControllerTouchBegan(cocos2d::Vec2 velocity)
{
	
}

void GamePlayLayer::onControllerTouchMoving(cocos2d::Vec2 velocity)
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
	_Knight->setvelocity(newVelocity);

	_Cam = Camera::getDefaultCamera();
	campos = _Cam->getPosition3D();
	campos.x = _Knight->getPositionX();
	campos.y = _Knight->getPositionY();
	_Cam->setPosition3D(campos);

	/*controller->setPositioin(Vec2(_Knight->getPositionX()-200, _Knight->getPositionY()-600));*/

}

void GamePlayLayer::onControllerTouchEnded(cocos2d::Vec2 velocity)
{

	CCLOG(" GamePlayLayer end %f %f", velocity.x, velocity.y);
	_Knight->setvelocity(velocity);
	unscheduleUpdate();
}



void GamePlayLayer::PlayButtonHit(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		cocos2d::log("On end button hit");

		

	}
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
