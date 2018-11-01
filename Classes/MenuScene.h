#ifndef _MENU_SCENE_
#define _MENU_SCENE_
#include "cocos2d.h"

class MenuScene : public cocos2d::Scene

{
public:
	MenuScene();
	~MenuScene();
	CREATE_FUNC(MenuScene);
	virtual bool init();
	void createStart();
	static cocos2d::Scene* createMenuScene();
protected:
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
private:

};





#endif // !_MENU_SCENE_

