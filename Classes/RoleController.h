#ifndef  __ROLE_CONTROLLER_H__
#define  __ROLE_CONTROLLER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class RoleControllerListenr 

{
public:
	virtual void onControllerTouchBegan(cocos2d::Vec2 velocity) = 0;
	virtual void onControllerTouchMoving(cocos2d::Vec2 velocity) = 0;
	virtual void onControllerTouchEnded(cocos2d::Vec2 velocity) = 0;
	
	
};
class RoleController:public cocos2d ::Layer

{
	//void PlayButtonHit();
	//cocos2d::ui::Button*	_btnPlay;
private:
	RoleController();
	

public:
	
	bool touchIngInside = false;
	float radius = 0;
	cocos2d::Vec2 offset;
	float ball_d_bg = 0;

	cocos2d::Color4F bg_color = cocos2d::Color4F(-1.0f, -1.0f, -1.0f, -1.0f);
	cocos2d::Color4F ball_color = cocos2d::Color4F(-1.0f, -1.0f, -1.0f, -1.0f);

	Node * tempLayer;
	Node * tempLayer2;
	std::string bg_resouce_path;
	std::string ball_resouce_path;
	static RoleController* createController(float radius, const cocos2d::Vec2 offset);

	RoleControllerListenr * listener;

	virtual bool init();

	void createBg();
	void createBall();

	void setPositioin(cocos2d::Vec2 position);
	void setOffset(cocos2d::Vec2 offset);

	void setBgResoucePath(std::string path);
	void setBallResoucePath(std::string path);


	bool touchBeganCallback(cocos2d::Touch*, cocos2d::Event*);
	void touchMovedCallback(cocos2d::Touch*, cocos2d::Event*);
	void touchEndedCallback(cocos2d::Touch*, cocos2d::Event*);

	void setRoleControllerListenr(RoleControllerListenr * listener);

	CREATE_FUNC(RoleController);
};



#endif // ! __ROLE_CONTROLLER_H__
