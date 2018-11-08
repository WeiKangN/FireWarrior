#include "RoleController.h"
#include"MainPlayer.h"
#include <stdlib.h>
#include <math.h>

#define Tag_Bg_Layer 0
#define Tag_Ball_Layer 1

#define Default_ball_d_bg (float)1/2  
#define Default_bg_color Color4F(100, 100, 0, 100) 
#define Default_ball_color Color4F(100, 100,0, 50)  

USING_NS_CC;
using namespace cocos2d::ui;



RoleController::RoleController()
{
	listener = nullptr;
	//Sprite* _test = Sprite::create("Art/knight_idle (1).png");
	//this->addChild(_test);
}

RoleController * RoleController::createController(float radius, const Vec2 offset)
{
	auto sceeenSize = Director::getInstance()->getWinSize();
	auto _layer = RoleController::create();
	
	_layer->setAnchorPoint(Vec2(0.0f, 0.0f));
	_layer->radius = radius;
	_layer->offset = offset;
	_layer->bg_resouce_path = "Art/limit_circle.png";
	_layer->ball_resouce_path = "Art/control_circle.png";
	_layer->setContentSize(sceeenSize);
	_layer->setPosition(160.0f, 160.0f);
	
	_layer->createBg();
	_layer->createBall();


	//Sprite* _test = Sprite::create("Art/knight_idle (1).png");
	//_layer->addChild(_test);

	auto touchListner = EventListenerTouchOneByOne::create();
	touchListner->onTouchBegan = CC_CALLBACK_2(RoleController::touchBeganCallback, _layer);
	touchListner->onTouchMoved = CC_CALLBACK_2(RoleController::touchMovedCallback, _layer);
	touchListner->onTouchEnded = CC_CALLBACK_2(RoleController::touchEndedCallback, _layer);
	_layer->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListner, _layer);

	return _layer;
}



bool RoleController::init()
{
	if (!Layer::init()) {
		return false;
	}
	/*auto winSize = Director::getInstance()->getWinSize();
	_btnPlay = Button::create("Art/ButtonHit_1.png", "Art/ButtonHit_1.png", "Art/ButtonHit_1.png");
	this->addChild(_btnPlay);
	_btnPlay->setPosition(winSize * 0.5f);
	_btnPlay->addTouchEventListener(CC_CALLBACK_2(RoleController::PlayButtonHit, this));*/
	return true;
}
//void RoleController::PlayButtonHit()
//{
//
//}

void RoleController::createBg()
{
	this->tempLayer = nullptr;
	if (this->bg_resouce_path == "") {
		auto drawNode = DrawNode::create();
		drawNode->setContentSize(Size(this->radius * 2, this->radius * 2));
		drawNode->drawDot(Vec2(this->radius, this->radius),
			this->radius,
			this->bg_color == Color4F (-1.0f, -1.0f, -1.0f, -1.0f) ? Default_bg_color : this->bg_color);

		this->tempLayer = drawNode;
	}
	else {
		auto resouceSprite = Sprite::create(this->bg_resouce_path);
		this->tempLayer = resouceSprite;
	}
	this->tempLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->tempLayer->setPosition(Vec2(this->radius, this->radius) + this->offset);
	this->addChild(this->tempLayer, 1, Tag_Bg_Layer);
}

void RoleController::createBall()
{
	if (this->ball_resouce_path == "")
	{
		auto drawNode2 = DrawNode::create();
		drawNode2->setContentSize(Size(this->radius * 2, this->radius * 2) * (this->ball_d_bg != 0 ? this->ball_d_bg : Default_ball_d_bg));
		drawNode2->drawDot(Vec2(this->radius * (this->ball_d_bg != 0 ? this->ball_d_bg : Default_ball_d_bg),
			this->radius * (this->ball_d_bg != 0 ? this->ball_d_bg : Default_ball_d_bg)),
			this->radius * (this->ball_d_bg != 0 ? this->ball_d_bg : Default_ball_d_bg),
			this->ball_color == Color4F(-1.0f, -1.0f, -1.0f, -1.0f) ? Default_ball_color : this->ball_color);
		this->tempLayer2 = drawNode2;
	}
	else {
		auto resouceSprite = Sprite::create(this->ball_resouce_path);
		this->tempLayer2 = resouceSprite;
	}

	this->tempLayer2->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->tempLayer2->setPosition(Vec2(this->radius, this->radius) + this->offset);
	this->addChild(this->tempLayer2, 2, Tag_Ball_Layer);
}

void RoleController::setPositioin(cocos2d::Vec2 position)
{
	setOffset(position);
}

void RoleController::setOffset(cocos2d::Vec2 offset)
{
	this->offset = offset;
	this->tempLayer->setPosition(Vec2(this->radius, this->radius) + this->offset);
	this->tempLayer2->setPosition(Vec2(this->radius, this->radius) + this->offset);
}

void RoleController::setBgResoucePath(std::string path)
{
	this->bg_resouce_path = path;
}

void RoleController::setBallResoucePath(std::string path)
{
	this->ball_resouce_path = path;
}

bool RoleController::touchBeganCallback(cocos2d::Touch *touch, cocos2d::Event *event)
{
	//Vec2 touchP = this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(touch->getLocation()));
	Vec2 touchP = this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()));
	Vec2 centerP = tempLayer->getPosition();

	float distance = sqrt(pow(touchP.x - centerP.x, 2) + pow(touchP.y - centerP.y, 2));
	if (distance < this->radius) {
		tempLayer2->setPosition(touchP);
		touchIngInside = true;
		if (this->listener != nullptr)
			this->listener->onControllerTouchBegan(touchP - centerP);
	}
	else {
		touchIngInside = false;
	}
	return true;
}

void RoleController::touchMovedCallback(cocos2d::Touch *touch, cocos2d::Event *event)
{
	//Vec2 touchP = touch->getLocation();
	//Vec2 centerP = tempLayer->getPosition();
	//float distance = sqrt(pow(touchP.x - centerP.x, 2) + pow(touchP.y - centerP.y, 2));
	Vec2 touchP = this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()));
	Vec2 centerP = tempLayer->getPosition();

	float distance = sqrt(pow(touchP.x - centerP.x, 2) + pow(touchP.y - centerP.y, 2));
	if (distance < this->radius) {
		tempLayer2->setPosition(touchP);
		if (this->listener != nullptr)
			this->listener->onControllerTouchMoving(touchP - centerP);
	}
	else {
		if (touchIngInside) {
			float targetX = 0, targetY = 0;
			if (touchP.x >= centerP.x && touchP.y >= centerP.y) {
				targetX = centerP.x + radius * (touchP.x - centerP.x) / distance;
				targetY = centerP.y + radius * (touchP.y - centerP.y) / distance;
			}
			else if (touchP.x < centerP.x && touchP.y >= centerP.y) {
				targetX = centerP.x - radius * (centerP.x - touchP.x) / distance;
				targetY = centerP.y + radius * (touchP.y - centerP.y) / distance;
			}
			else if (touchP.x < centerP.x && touchP.y < centerP.y) {
				targetX = centerP.x - radius * (centerP.x - touchP.x) / distance;
				targetY = centerP.y - radius * (centerP.y - touchP.y) / distance;
			}
			else if (touchP.x >= centerP.x && touchP.y < centerP.y) {
				targetX = centerP.x + radius * (touchP.x - centerP.x) / distance;
				targetY = centerP.y - radius * (centerP.y - touchP.y) / distance;
			}
			tempLayer2->setPosition(targetX, targetY);
			if (this->listener != nullptr)
				this->listener->onControllerTouchMoving(Vec2(targetX, targetY) - centerP);
		}
	}
}

void RoleController::touchEndedCallback(cocos2d::Touch *touch, cocos2d::Event *event)
{
	touchIngInside = false;
	Vec2 centerP = tempLayer->getPosition();
	tempLayer2->setAnchorPoint(Vec2(0.5f, 0.5f));
	tempLayer2->setPosition(centerP);
	if (this->listener != nullptr)
		this->listener->onControllerTouchEnded(Vec2::ZERO);
}

void RoleController::setRoleControllerListenr(RoleControllerListenr * listener)
{
	this->listener = listener;
}


