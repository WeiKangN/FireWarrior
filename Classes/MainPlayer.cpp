#include "MainPlayer.h"
#include"RoleController.h"
#include"Const.h"


USING_NS_CC;
using namespace cocos2d::ui;

#define CHARACTER_SPEED 5.5f
#define ANIM_NONE 0
#define ANIM_RIGHT 1
#define ANIM_UP 2
#define ANIM_DOWN 3
#define ANIM_LEFT 4
#define ANIM_HIT_DOWN 5
#define ANIM_HIT_UP 6
#define ANIM_HIT_LEFT 7 
#define ANIM_HIT_RIGHT 8

MainPlayer::MainPlayer()
{
	m_velocity = Vec2::ZERO;
	_typeAnim = 0;
	_typeHit = 0;
}

MainPlayer::~MainPlayer()
{
}

bool MainPlayer::init()
{
	if (!Node::init())
	{
		return false;
	}

	//winSize = Director::getInstance()->getWinSize();
	_Maverick = Sprite::create("Art/knight_idle (1).png");
	this->addChild(_Maverick);
	_Maverick->setPosition(this->getContentSize() * 0.5f);
	this->setScale(2.2f);
	scheduleUpdate();

	/*_btnPlay = Button::create("Art/ButtonHit_1.png","Art/ButtonHit_1.png","Art/ButtonHit_1.png");
	this->addChild(_btnPlay);
	_btnPlay->setPosition(this->getContentSize() * 0.5f);
	_btnPlay->addTouchEventListener(CC_CALLBACK_2(MainPlayer::PlayAnimationHit, this));
	*/

	// Physic
	PhysicsBody *physBody = PhysicsBody::createBox(Size(30.0f, 50.0f), PhysicsMaterial(0.1f, 0.5f, 0.0f));
	physBody->setGravityEnable(false);
	physBody->setDynamic(true);
	physBody->setCategoryBitmask(MAVERICK_CATEGORY_BITMASK); // 0001
	physBody->setCollisionBitmask(MAVERICK_COLLISION_AND_CONTACT_TEST_BITMASK); // 0010
	physBody->setContactTestBitmask(MAVERICK_COLLISION_AND_CONTACT_TEST_BITMASK);
	//apply physicsBody to the sprite
	this->addComponent(physBody);
	this->setTag(TAG_MAVERICK);

	return true;
}
void MainPlayer::update(float dt)
{



	auto winSize = Director::getInstance()->getWinSize();
	Vect newPosition = this->getPosition() + Vec2(this->m_velocity.x, this->m_velocity.y) / 60.0f * CHARACTER_SPEED;
	/*if (newPosition.x> 0 && newPosition.x < winSize.width
		&& newPosition.y > 0 && newPosition.y < winSize.height)*/
		this->setPosition(newPosition);
	
}
void MainPlayer::setvelocity(Vec2 vec)
{
	m_velocity = vec;
	auto X = (m_velocity.x);
	auto Y = (m_velocity.y);
	if (X == 0 && Y == 0)
	{
		if (_typeAnim != ANIM_NONE)
		{
			_typeAnim = ANIM_NONE;	
			_Maverick->stopActionByTag(1);
			PlayAnimation();
		}
	}
	else if (X > 0)
	{
		_direction = RIGHT;
		if (_typeAnim != ANIM_RIGHT)
		{
			_typeAnim = ANIM_RIGHT;
			_Maverick->stopActionByTag(1);
			PlayAnimationRight();
			
		}

	}
	else if (X < 0)
	{
		_direction = LEFT;
		if (_typeAnim != ANIM_LEFT)
		{
			_typeAnim = ANIM_LEFT;
			_Maverick->stopActionByTag(1);
			PlayAnimationLeft();
		
		}
	}
	else if (Y > 0)
	{
		_direction = UP;
		if (_typeAnim != ANIM_UP)
		{
			_typeAnim = ANIM_UP;
			_Maverick->stopActionByTag(1);
			PlayAnimationUp();
		
		}
	}
	else if (Y < 0)
	{
		_direction = DOWN;
		if (_typeAnim != ANIM_DOWN)
		{
			_typeAnim = ANIM_DOWN;
			_Maverick->stopActionByTag(1);
			PlayAnimationDown();
		}
		
	}
	
}

void MainPlayer::PlayAnimation()
{
	_typeAnim = ANIM_NONE;
	Animation*animationIdle = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		std::string Stand = StringUtils::format("knight_idle (%d).png", i);
		animationIdle->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Stand));

	}
	animationIdle->setDelayPerUnit(1 / 12.0f);

	Animate* animateIdle = Animate::create(animationIdle);
	auto repeatForever = RepeatForever::create(animateIdle);
	repeatForever->setTag(1);
	_Maverick->setScale(1.0f);
	_Maverick->runAction(repeatForever);

}

void MainPlayer::PlayAnimationRight()
{
	_typeAnim = ANIM_RIGHT;
	Animation*animationRight = Animation::create();
	for (int i = 2; i < 7; i++)
	{
		std::string Right = StringUtils::format("knight_run_right (%d).png", i);
		animationRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Right));

	}
	animationRight->setDelayPerUnit(1 / 12.0f);
	Animate* animateRight = Animate::create(animationRight);
	auto repeatForever = RepeatForever::create(animateRight);
	repeatForever->setTag(1);
	_Maverick->runAction(repeatForever);
	_Maverick->setScale(1.2f);
}

void MainPlayer::PlayAnimationLeft()
{
	_typeAnim = ANIM_LEFT;
	Animation*animationLeft = Animation::create();
	for (int i = 2; i < 7; i++)
	{
		std::string Right = StringUtils::format("knight_run_left (%d).png", i);
		animationLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Right));

	}
	animationLeft->setDelayPerUnit(1 / 12.0f);
	Animate* animateLeft = Animate::create(animationLeft);
	auto repeatForever = RepeatForever::create(animateLeft);
	repeatForever->setTag(1);
	_Maverick->runAction(repeatForever);
	_Maverick->setScale(1.2f);
}

void MainPlayer::PlayAnimationUp()
{
	_typeAnim = ANIM_UP;
	Animation*animationUp = Animation::create();
	for (int i = 1; i < 6; i++)
	{
		std::string Up = StringUtils::format("knight_run_up (%d).png", i);
		animationUp->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Up));

	}
	animationUp->setDelayPerUnit(1 / 12.0f);
	Animate* animateUp = Animate::create(animationUp);
	auto repeatForever = RepeatForever::create(animateUp);
	repeatForever->setTag(1);
	_Maverick->runAction(repeatForever);
	_Maverick->setScale(1.2f);
}

void MainPlayer::PlayAnimationDown()
{
	_typeAnim = ANIM_DOWN;
	Animation*animationDown = Animation::create();
	for (int i = 5; i < 10; i++)
	{
		std::string Down = StringUtils::format("knight_run_down (%d).png", i);
		animationDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Down));

	}
	animationDown->setDelayPerUnit(1 / 12.0f);
	Animate* animateDown = Animate::create(animationDown);
	auto repeatForever = RepeatForever::create(animateDown);
	repeatForever->setTag(1);
	_Maverick->runAction(repeatForever);
	_Maverick->setScale(1.2f);
}

void MainPlayer::PlayAnimationHit()
{
	Animation*animation = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		std::string Knite = StringUtils::format("knight_idle (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Knite));

	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	auto repeatForever = RepeatForever::create(animate);
	repeatForever->setTag(1);
	_Maverick->setScale(1.0f);
	_Maverick->runAction(repeatForever);

	_typeHit = ANIM_HIT_DOWN;
	Animation*animationHit = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string Hit = StringUtils::format("knight_slice_down (%d).png", i);
		animationHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Hit));

	}
	animationHit->setDelayPerUnit(1 / 10.0f);
	Animate* animateHit = Animate::create(animationHit);
	/*auto repeatForever = RepeatForever::create(animateHit);
	repeatForever->setTag(1);*/
	_Maverick->runAction(animateHit);
	_Maverick->setScale(1.2f);
	_Maverick->stopActionByTag(1);

	auto Next = Sequence::create(animateHit, animate,nullptr);
	_Maverick->runAction(Next);
}

void MainPlayer::PlayAnimationHitUp()
{
	Animation*animation = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		std::string Knite = StringUtils::format("knight_idle (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Knite));

	}
	animation->setDelayPerUnit(1 / 12.0f);

	_typeHit = ANIM_HIT_UP;
	Animate* animate = Animate::create(animation);
	auto repeatForever = RepeatForever::create(animate);
	repeatForever->setTag(1);
	_Maverick->setScale(1.0f);
	_Maverick->runAction(repeatForever);

	Animation*animationHitUp = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string Hit = StringUtils::format("knight_slice_up (%d).png", i);
		animationHitUp->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Hit));

	}
	animationHitUp->setDelayPerUnit(1 / 10.0f);
	Animate* animateHitUp = Animate::create(animationHitUp);
	/*auto repeatForever = RepeatForever::create(animateHit);
	repeatForever->setTag(1);*/
	_Maverick->runAction(animateHitUp);
	_Maverick->setScale(1.2f);
	_Maverick->stopActionByTag(1);

	auto Next = Sequence::create(animateHitUp, animate, nullptr);
	_Maverick->runAction(Next);
}

void MainPlayer::PlayAnimationHitLeft()
{
	Animation*animation = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		std::string Knite = StringUtils::format("knight_idle (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Knite));

	}
	animation->setDelayPerUnit(1 / 12.0f);

	
	Animate* animate = Animate::create(animation);
	auto repeatForever = RepeatForever::create(animate);
	repeatForever->setTag(1);
	_Maverick->setScale(1.0f);
	_Maverick->runAction(repeatForever);

	_typeHit = ANIM_HIT_LEFT;
	Animation*animationHitLeft = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string Hit = StringUtils::format("knight_slice_right (%d).png", i);
		animationHitLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Hit));

	}
	animationHitLeft->setDelayPerUnit(1 / 10.0f);
	Animate* animateHitLeft = Animate::create(animationHitLeft);
	/*auto repeatForever = RepeatForever::create(animateHit);
	repeatForever->setTag(1);*/
	_Maverick->runAction(animateHitLeft);
	_Maverick->setScale(1.2f);
	_Maverick->stopActionByTag(1);

	auto Next = Sequence::create(animateHitLeft, animate, nullptr);
	_Maverick->runAction(Next);
}

void MainPlayer::PlayAnimationHitRight()
{
	Animation*animation = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		std::string Knite = StringUtils::format("knight_idle (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Knite));

	}
	animation->setDelayPerUnit(1 / 12.0f);


	Animate* animate = Animate::create(animation);
	auto repeatForever = RepeatForever::create(animate);
	repeatForever->setTag(1);
	_Maverick->setScale(1.0f);
	_Maverick->runAction(repeatForever);

	_typeHit = ANIM_HIT_RIGHT;
	Animation*animationHitRight = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string Hit = StringUtils::format("knight_slice_left (%d).png", i);
		animationHitRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Hit));

	}
	animationHitRight->setDelayPerUnit(1 / 10.0f);
	Animate* animateHitRight = Animate::create(animationHitRight);
	/*auto repeatForever = RepeatForever::create(animateHit);
	repeatForever->setTag(1);*/
	_Maverick->runAction(animateHitRight);
	_Maverick->setScale(1.2f);
	_Maverick->stopActionByTag(1);

	auto Next = Sequence::create(animateHitRight, animate, nullptr);
	_Maverick->runAction(Next);

}

void MainPlayer::Attack()
{
	if (_direction == RIGHT)
	{
		PlayAnimationHitRight();
	}
	else if (_direction == LEFT)
	{
		PlayAnimationHitLeft();
	}
	else if (_direction == UP)
	{
		PlayAnimationHitUp();
	}
	else if (_direction == DOWN)
	{
		PlayAnimationHit();
	}
}











