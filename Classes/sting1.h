#ifndef _sting1_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class sting1 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
#define TRANSITTION_TIME 0.5
	void onTouchBegan(Ref *senser, cocos2d::ui::Widget::TouchEventType type);
	//void onTouchBegan_2(Ref *senser, cocos2d::ui::Widget::TouchEventType type);
	CREATE_FUNC(sting1);
private:
	void CombackMainMenuScene(cocos2d::Ref *sender);

	cocos2d::ui::Button *soundbutton;
	cocos2d::ui::Button *musicbutton;
};


#endif // !_sting1_H