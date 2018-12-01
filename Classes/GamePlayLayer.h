#ifndef _Game_Play_Layer
#define _Game_Play_Layer

#include"cocos2d.h"
#include"RoleController.h"
#include "ui/CocosGUI.h"

class EvilDog;
class MainPlayer;
class Bandit;
class PhysicsHandler;
class GamePlayLayer:public cocos2d::Layer

{
public:
	GamePlayLayer();
	~GamePlayLayer();
	CREATE_FUNC(GamePlayLayer);
	virtual bool init();
	MainPlayer*_Knight;
	Bandit*_bandit;
	EvilDog*_HellDog;
	cocos2d::Size winSize;
	cocos2d::Camera* _Cam;
	cocos2d::Vec3 campos;
	cocos2d::ui::Button*	_buttonPlay;
	
protected:
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event*e);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event*e);

private:
	RoleController*controller;
	bool right;
	bool left;
	bool up;
	bool down;

	PhysicsHandler* _physicsHandler;
};


#endif // !_Game_Play_Layer

