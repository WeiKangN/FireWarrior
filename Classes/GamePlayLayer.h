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
	void update(float delta);
	
protected:
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event*e);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event*e);
	void EvilDog02();
	void EvilDog03();
	void EvilDog04();
	void EvilDog05();
	void EvilDog06();
	void EvilDog07();

	void Bandit02();
	void Bandit03();
	void Bandit04();
	void Bandit05();
	void Bandit06();
	void Bandit07();
	void Bandit08();
	void Bandit09();
	void Bandit010();
	void Bandit011();

private:
	RoleController*controller;
	bool right;
	bool left;
	bool up;
	bool down;
	EvilDog*_EvilDog2;
	EvilDog*_EvilDog3;
	EvilDog*_EvilDog4;
	EvilDog*_EvilDog5;
	EvilDog*_EvilDog6;
	EvilDog*_EvilDog7;

	Bandit*_Bandit2;
	Bandit*_Bandit3;
	Bandit*_Bandit4;
	Bandit*_Bandit5;
	Bandit*_Bandit6;
	Bandit*_Bandit7;
	Bandit*_Bandit8;
	Bandit*_Bandit9;
	Bandit*_Bandit10;
	Bandit*_Bandit11;
	PhysicsHandler* _physicsHandler;
};


#endif // !_Game_Play_Layer

