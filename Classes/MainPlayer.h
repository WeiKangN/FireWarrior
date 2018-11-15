#ifndef _MAIN_PLAYER_
#define _MAIN_PLAYER_

#include"RoleController.h"
#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameObject.h"
#include "ui\UILoadingBar.h"

class MainPlayer : public GameObject 
{
public:
	MainPlayer();
	~MainPlayer();
	CREATE_FUNC(MainPlayer);
	virtual bool init();
	void update(float dt);
	enum  Direction
	{
		LEFT,
		RIGHT,
		DOWN,
		UP

	};
	void setvelocity(cocos2d::Vec2 vec);
	void setvec(cocos2d::Vec2 Vector);
	void PlayAnimation();
	void PlayAnimationRight();
	void PlayAnimationLeft();
	void PlayAnimationUp();
	void PlayAnimationDown();
	void PlayAnimationHit();
	void PlayAnimationHitUp();
	void PlayAnimationHitLeft();
	void PlayAnimationHitRight();
	void Attack();
	void Stop();
	void updateHealthBar(float percent);
	void setHealthBar(float percent);
	void TakeDamage();
	
	virtual void onContactBeganWith(GameObject* obj) override;
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
private:
	cocos2d::ui::LoadingBar *healthbarMaverick;
	cocos2d::Sprite*_Maverick;
	cocos2d::Sprite*_MaverickHitLeft;
	cocos2d::Vec2 m_velocity;
	cocos2d::ui::Button*	_btnHit;
	int _typeAnim;
	int _typeHit;
	Direction _direction;
	float Health;
	float Damage;
};


#endif // !_MAIN_PLAYER_

