#ifndef _EVIL_DOG_
#define _EVIL_DOG_

#include "ui/CocosGUI.h"
#include"GameObject.h"
#include"cocos2d.h"
#include"GamePlayLayer.h"
#include"Physics\PhysicsHandler.h"
#include "MainPlayer.h"
class EvilDog : public GameObject

{
public:
	EvilDog();
	~EvilDog();
	virtual void onContactBeganWith(GameObject* obj) override;
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
	
	
	void enalbeAI(MainPlayer *player);
	void scheduleUpdateAI(float delta);

	CREATE_FUNC(EvilDog);
	virtual bool init();
	void DogIdle();
	void Run();
	void TakeDamage();
	void chaseMaverick(cocos2d::Vec2 location);
	void updateHealthBar(float percent);
	void setHealthBar(float percent);
	cocos2d::ui::LoadingBar *healthbarEvilDog;
private:
	cocos2d::Sprite*_sprDoggie;
	float Health;
	float  _timeUpdateAI;
	MainPlayer* _player;

	void chasePlayer();

};



#endif // !_EVIL_DOG_

