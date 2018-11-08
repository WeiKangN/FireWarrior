#ifndef _MAIN_PLAYER_
#define _MAIN_PLAYER_

#include"RoleController.h"
#include"cocos2d.h"
#include "ui/CocosGUI.h"

class MainPlayer:public cocos2d::Node
{
	enum  Direction
	{
		LEFT,
		RIGHT,
		DOWN,
		UP

	};
public:
	MainPlayer();
	~MainPlayer();
	CREATE_FUNC(MainPlayer);
	virtual bool init();
	void update(float dt);
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

private:
	cocos2d::Sprite*_Maverick;
	cocos2d::Sprite*_MaverickHitLeft;
	cocos2d::Vec2 m_velocity;
	cocos2d::ui::Button*	_btnHit;
	int _typeAnim;
	int _typeHit;
	Direction _direction;
	

};


#endif // !_MAIN_PLAYER_

