#ifndef _Game_Play_Layer
#define _Game_Play_Layer

#include"cocos2d.h"
#include"RoleController.h"
#include "ui/CocosGUI.h"

class EvilDog;
class MainPlayer;
class Bandit;
class GamePlayLayer:public cocos2d::Layer, public RoleControllerListenr

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

	void menuCloseCallback(cocos2d::Ref* pSender);
	void update(float dt);
	void onControllerTouchBegan(cocos2d::Vec2 velocity);
	void onControllerTouchMoving(cocos2d::Vec2 velocity);
	void onControllerTouchEnded(cocos2d::Vec2 velocity);
	void PlayButtonHit(cocos2d::Ref* ref,cocos2d::ui::Widget::TouchEventType type);
	cocos2d::ui::Button*	_buttonPlay;
	
protected:
	/*void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event*e);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event*e);*/

private:
	bool onGameContactBegin(cocos2d::PhysicsContact& contact);
	RoleController*controller;
	bool right;
	bool left;
	bool up;
	bool down;
};


#endif // !_Game_Play_Layer

