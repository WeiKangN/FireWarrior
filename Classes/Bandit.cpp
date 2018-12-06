#include "Bandit.h"
#include "GamePlayLayer.h"
#include"Const.h"
#include "Physics\PhysicsHandler.h"

#define DAMAGE_BANDIT  27.5F
#define HEALTH_BANDIT 50.0F
// toc do theo chieu x , y ma con enemy chay theo nhan vat
#define SPEED_X 150.0f
#define SPEED_Y SPEED_X
// tag action ai
#define TAG_ACTION_AI_CHASE_PLAYER 100

USING_NS_CC;
Bandit::Bandit():
	Health(HEALTH_BANDIT)
{
	_dmg = DAMAGE_BANDIT;
	_timeUpdateAI = 0.3f;
}

Bandit::~Bandit()
{
}

bool Bandit::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size WinSize = Director::getInstance()->getWinSize();
	_Enemy = Sprite::create("Art/Bandit/idle (1).png");
	this->addChild(_Enemy);
	this->setTag(TAG_BANDIT);
	_Enemy->setPosition(this->getContentSize() * 0.5f);
	this->setScale (6.0f);
	this->setScaleX(-6.0f);

	// Physic
	PhysicsBody *physBody = PhysicsBody::createBox(Size(13.0f, 25.0f), PhysicsMaterial(1.0f, 1.0f, 0.0f));;
	physBody->setGravityEnable(false);
	physBody->setDynamic(false);
	physBody->setPositionOffset(Vec2(-10.0f, -10.0f));
	physBody->setCategoryBitmask(ENEMY_CATEGORY_BITMASK); // 0001
	physBody->setCollisionBitmask(ENEMY_COLLISION_AND_CONTACT_TEST_BITMASK); // 0010
	physBody->setContactTestBitmask(ENEMY_COLLISION_AND_CONTACT_TEST_BITMASK);
	//apply physicsBody to the sprite
	this->addComponent(physBody);
	

	return true;
}

void Bandit::Idle()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string Demons = StringUtils::format("idle (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Demons));

	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_Enemy->runAction(RepeatForever::create(animate));
}



void Bandit::Attack()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 8; i++)
	{
		std::string Demons = StringUtils::format("attack (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Demons));

	}
	animation->setDelayPerUnit(1 / 2.0f);

	Animate* animate = Animate::create(animation);
	_Enemy->runAction(RepeatForever::create(animate));
}

void Bandit::Run()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 9; i++)
	{
		std::string Demons = StringUtils::format("run (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Demons));

	}
	animation->setDelayPerUnit(1 / 2.0f);

	Animate* animate = Animate::create(animation);
	_Enemy->runAction(RepeatForever::create(animate));
}

void Bandit::TakeDamage()
{
	this->Health -= ObjDmg;
	this->updateHealthBar(this->Health);
	if (this->Health <= 0)
	{

		this->getPhysicsBody()->setContactTestBitmask(false);
		CallFunc*stopAllAction = CallFunc::create([=] {
			this->stopAllActions();
		});
		CallFunc *removeCallback = CallFunc::create([=] {
			this->removeFromParent();
		});
		runAction(Sequence::create(stopAllAction,Blink::create(0.0f, 1), removeCallback, nullptr));
	}
	else
	{
		TintBy* tint = TintBy::create(0.5f, 255, 0.0f, 0.0f);
		_Enemy->runAction(Sequence::create(tint, tint->reverse(), NULL));
	}
}

void Bandit::updateHealthBar(float percent)
{
	healthbarBandit->removeFromParent();
	setHealthBar(percent);
}

void Bandit::setHealthBar(float percent)
{
	auto winSize = Director::getInstance()->getWinSize();

	healthbarBandit = ui::LoadingBar::create("Art/HealthBar.png");
	this->addChild(healthbarBandit);
	healthbarBandit->setDirection(ui::LoadingBar::Direction::LEFT);
	healthbarBandit->setScaleX(0.2f);
	healthbarBandit->setScaleY(0.11f);
	healthbarBandit->setPercent(percent);
	healthbarBandit->setPosition(Vec2(15.0f, 10.0f));
	healthbarBandit->setVisible(false);
}

void Bandit::onContactBeganWith(GameObject * obj)
{
	if (obj->getTag() == TAG_HIT|| obj->getTag()==TAG_MAVERICK)
	{
		ObjDmg = obj->getDmg();
		this->TakeDamage();
	}
}

void Bandit::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void Bandit::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void Bandit::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}


void Bandit::enalbeAI(MainPlayer * player)
{
	_player = player;
	this->schedule(CC_SCHEDULE_SELECTOR(Bandit::scheduleUpdateAI), _timeUpdateAI, CC_REPEAT_FOREVER, 0.0f);
}

void Bandit::scheduleUpdateAI(float delta)
{
	if (_player != nullptr)
	{
		float distanceX = std::abs(this->getPosition().x - _player->getPosition().x);
		if (distanceX < 500)
		{
			{

				if (distanceX < _Enemy->getContentSize().width * 0.5f + 100.0f) 
				{

				}
				else // neu no khong thoa khoang cach thi no di theo player
				{

					chasePlayer();
				}
			}
		}
	}
}

void Bandit::chasePlayer()
{
	auto targetPos = _player->getPosition();
	auto distance = targetPos - this->getPosition();
	auto timeX = std::abs(distance.x / SPEED_X);
	auto timeY = std::abs(distance.y / SPEED_Y);
	auto time = timeX > timeY ? timeX : timeY;
	auto aMove = MoveBy::create(time, distance);
	aMove->setTag(TAG_ACTION_AI_CHASE_PLAYER);
	this->stopActionByTag(TAG_ACTION_AI_CHASE_PLAYER);
	this->runAction(aMove);
	Run();
}
