#ifndef _UI_SCENE_H
#define _UI_SCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
USING_NS_CC;
class MainMenuScene : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();
	/*void menuCloseCallback(cocos2d::Ref* pSender);*/
	void GoToGameScene(cocos2d::Ref* pSender);
	void GoTosting1(cocos2d::Ref* pSender);
	void TouchQuitButton(Ref* pSender, ui::Widget::TouchEventType eEventType);
	
	virtual bool init();


	cocos2d::Animation *createAnimation(std::string prefixName, int pFramesOrder, float delay);
		 
	cocos2d:: Animation *animation;

	CREATE_FUNC(MainMenuScene);
private:

};


#endif // !_UI_SCENE_H
