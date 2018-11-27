#ifndef _PLASH_SCENE_H_
#define	_PLASH_SCENE_H_
#include "ui/CocosGUI.h"
#include "cocos2d.h"
class loading : public cocos2d::Scene
{
public:
	loading();
	~loading();
	void	createloading();
	static cocos2d::Scene* createscene();
	virtual bool init();
	void goToMainMenuScene();
	CREATE_FUNC(loading);
private:
	//void GotoMainMenuScene(float dt);

};
//auto loadingBar = LoadingBar::create("LoadingBarFile.png");
//
//loadingBar->setDirection(LoadingBar::Direction::RIGHT);
//
//// something happened, change the percentage of the loading bar
//loadingBar->setPercent(40);
//
//this->addChild(loadingBar);
#endif 
