#include "EvilDog.h"
#include "GamePlayLayer.h"
#include "Const.h"
#include "ui\UILoadingBar.h"

#define DAMAGE_EVILDOG  28.0F
#define HEALTH_DOG 50.0F
// toc do theo chieu x , y ma con enemy chay theo nhan vat
#define SPEED_X 150.0f
#define SPEED_Y SPEED_X
// tag action ai
#define TAG_ACTION_AI_CHASE_PLAYER 100

USING_NS_CC;

EvilDog::EvilDog():

	Health(HEALTH_DOG)
	{
		_dmg = DAMAGE_EVILDOG;
		_timeUpdateAI = 0.3f; // thoi gian ma con bot se cap nhap lai // cang nho con bot cang thong minh
	}


EvilDog::~EvilDog()
{
}

void EvilDog::onContactBeganWith(GameObject * obj)
{
	if (obj->getTag()==TAG_MAVERICK|| obj->getTag()==TAG_HIT)
	{
		
		this->TakeDamage();
	}

}

void EvilDog::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void EvilDog::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void EvilDog::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}


void EvilDog::enalbeAI(MainPlayer * player)
{
	_player = player;
	this->schedule(CC_SCHEDULE_SELECTOR(EvilDog::scheduleUpdateAI), _timeUpdateAI, CC_REPEAT_FOREVER, 0.0f);
}

void EvilDog::scheduleUpdateAI(float delta)
{
	if (_player != nullptr)
	{
		float distanceX = std::abs(this->getPosition().x - _player->getPosition().x);
		if (distanceX < 500)
		{
			{

				if (distanceX < _sprDoggie->getContentSize().width * 0.5f + 100.0f) // doan nay la : Khi con enemy chay den player cach mot khoang nao do la no se dung lai - dang xet theo chieu  x thui		
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

bool EvilDog::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size WinSize = Director::getInstance()->getWinSize();
	_sprDoggie = Sprite::create("Art/Evil/dog_idle  (1).png");
	this->addChild(_sprDoggie);
	this->setTag(TAG_DOG);
	_sprDoggie->setPosition(this->getContentSize() * 0.5f);

	this->setScale(4.0f);
	


	// Physic
	PhysicsBody *physBody = PhysicsBody::createBox(Size(28.0f, 13.0f), PhysicsMaterial(1.0f, 0.0f, 0.0f));;
	physBody->setGravityEnable(false);
	physBody->setRotationEnable(false);
	physBody->setDynamic(true);
	physBody->setPositionOffset(Vec2(-5.0f,-10.0f));
	physBody->setCategoryBitmask(ENEMY_CATEGORY_BITMASK); // 0001
	physBody->setCollisionBitmask(ENEMY_COLLISION_AND_CONTACT_TEST_BITMASK); // 0010
	physBody->setContactTestBitmask(ENEMY_COLLISION_AND_CONTACT_TEST_BITMASK);
	
	//apply physicsBody to the sprite
	this->addComponent(physBody);

	return true;

}

//void EvilDog::chaseMaverick(cocos2d::Vec2 location)
//{
//	auto chase = MoveTo::create(15.0f, location);
//	runAction(chase);
//}
void EvilDog::DogIdle()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string Demons = StringUtils::format("dog_idle  (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Demons));

	}
	animation->setDelayPerUnit(1 / 4.0f);

	Animate* animate = Animate::create(animation);
	_sprDoggie->runAction(RepeatForever::create(animate));

	/*auto sequence = Sequence::create(animateHitUp, animate, nullptr);
	_Maverick->runAction(sequence);*/

}



void EvilDog::Run()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 6; i++)
	{
		std::string Demons = StringUtils::format("run_doggie (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Demons));

	}
	animation->setDelayPerUnit(1 / 1.0f);

	Animate* animate = Animate::create(animation);
	_sprDoggie->runAction(RepeatForever::create(animate));
	//MoveTo* EnemyMove = MoveTo::create(60.0f, Vec2(location));

	
	//this->runAction(spawn);
}

void EvilDog::TakeDamage()
{
	/*this->Health -= this->_dmg;
	this->updateHealthBar(this->Health);
	if (this->Health <= 0)
	{}*/

	this->getPhysicsBody()->setContactTestBitmask(false);
	CallFunc*stopAllAction = CallFunc::create([=] {
		this->stopAllActions();
	});
	CallFunc *removeCallback = CallFunc::create([=] 
	{
		this->removeFromParent();
	 
	});
	runAction(Sequence::create(stopAllAction, Blink::create(0.0f, 1), removeCallback, nullptr));
}


void EvilDog::updateHealthBar(float percent)
{
	healthbarEvilDog->removeFromParent();
	setHealthBar(percent);
}

void EvilDog::setHealthBar(float percent)
{
	auto winSize = Director::getInstance()->getWinSize();

	healthbarEvilDog = ui::LoadingBar::create("Art/HealthBar.png");
	this->addChild(healthbarEvilDog);
	healthbarEvilDog->setDirection(ui::LoadingBar::Direction::LEFT);
	healthbarEvilDog->setScaleX(0.2f);
	healthbarEvilDog->setScaleY(0.1f);
	healthbarEvilDog->setPercent(percent);
	healthbarEvilDog->setPosition(Vec2(15.0f, 10.0f));
	healthbarEvilDog->setVisible(false);
	
	//healthbarEvilDog->setPosition(Vec2(winSize.width /2, winSize.height /2));
}

void EvilDog::chasePlayer() // Ham nay la ham con enemy chay theo nhan vat
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
