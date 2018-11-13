#ifndef _UI_SCENE_H
#define _UI_SCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
USING_NS_CC;
class MainMenuScene : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createMainMenuScene();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void GoToGameScene(cocos2d::Ref* pSender);
	void GoToGameOptions(cocos2d::Ref* pSender);
	void TouchQuitButton(Ref* pSender, ui::Widget::TouchEventType eEventType);
	CREATE_FUNC(MainMenuScene);
	virtual bool init();
private:

};


#endif // !_UI_SCENE_H
