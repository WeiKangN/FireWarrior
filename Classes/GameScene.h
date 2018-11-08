#ifndef _GAME_SCENCE_H
#define _GAME_SCENCE_H

#include"cocos2d.h"
#include "RoleController.h"
#include "ui/CocosGUI.h"
class GamePlayLayer;
class MainPlayer;
class GameScene :public cocos2d::Node, public RoleControllerListenr
{
public:
	GameScene();
	~GameScene();
	static cocos2d::Scene* createGameScene();
	CREATE_FUNC(GameScene);
	void onControllerTouchBegan(cocos2d::Vec2 velocity);
	void onControllerTouchMoving(cocos2d::Vec2 velocity);
	void onControllerTouchEnded(cocos2d::Vec2 velocity);
	virtual bool init();
	void update(float delta);
	void PlayButtonHit(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	cocos2d::ui::Button*	_btnPlay;
private:
	GamePlayLayer* gamePlayLayer;
	RoleController* controller;

};

#endif // !_GAME_SCENCE_H
