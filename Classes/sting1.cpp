#include "MainMenuScene.h"
#include"GameScene.h"
#include"sting1.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d;
//#define schedule_selector
bool checksound = true;
bool checksound_2 = true;
Scene*sting1::createScene()
{
	auto scene = Scene::create();

	auto layer = sting1::create();

	scene->addChild(layer);
	return scene;
}
bool sting1::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sting = Sprite::create("Art/menu.jpg");
	this->addChild(sting);
	sting->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sting->setPosition(this->getContentSize() * 0.5f);
	float scaleX = winSize.width*1.0 / (sting->getContentSize().width);
	float scaleY = winSize.height*1.0 / (sting->getContentSize().height);
	sting->setScaleX(scaleX);
	sting->setScaleY(scaleY);
	if (checksound == true)
	{
		soundbutton = cocos2d::ui::Button::create("Art/Sound_On.png", "Art/Sound_On_Click.png");
	}
	else
	{
		soundbutton = cocos2d::ui::Button::create("Art/Sound_Off.png", "Art/Sound_Off_Click.png");
	}
	
	soundbutton->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.width*0.4f));
	soundbutton->setScale(0.35f);

	

	this->addChild(soundbutton, 2);
	
	soundbutton->addTouchEventListener(CC_CALLBACK_2(sting1::onTouchBegan, this));




	auto playbutton = MenuItemImage::create("Art/back.png", "Art/back_click.png", CC_CALLBACK_1(sting1::CombackMainMenuScene, this));
	playbutton->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.9));
	auto menu = Menu::create(playbutton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);
	

	return true;
}
void sting1::onTouchBegan(Ref * senser, cocos2d::ui::Widget::TouchEventType type)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		if (checksound == true)
		{
			audio->pauseBackgroundMusic();
			checksound = false;
			soundbutton->loadTextures("Art/Sound_Off.png", "Art/Sound_Off_Click.png");
		}
		else
		{
			audio->resumeBackgroundMusic();
			checksound = true;
			soundbutton->loadTextures("Art/Sound_On.png", "Art/Sound_On_Click.png");
		}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:

		break;
	default:
		break;
	}
}


void sting1::CombackMainMenuScene(cocos2d::Ref * sender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

