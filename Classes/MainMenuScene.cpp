#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenuScene::createMainMenuScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return MainMenuScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//  super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add BackGround
	auto sprite = Sprite::create("menu.jpg");
	if (sprite == nullptr)
	{
		problemLoading("'menued.jpg'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}

	// add Font Menu
	auto label = Label::createWithTTF("ten game", "fonts/Lobster-Regular.ttf", 72);
	if (label == nullptr)
	{
		problemLoading("'fonts/Lobster-Regular.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	//add button Play
	auto playImage = MenuItemImage::create(
		"startbutton.png",
		"FON.png",
		CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
	playImage->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	auto menu1 = Menu::create(playImage, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);
	//btn2
	auto optionsImage = MenuItemImage::create(
		"OPTIONS.png",
		"OPTIONS1.png",
		CC_CALLBACK_1(MainMenuScene::GoToGameOptions, this));
	optionsImage->setPosition(visibleSize.width /2 , visibleSize.height/3 );
	optionsImage->getContentSize().width;
	optionsImage->getContentSize().height;
	optionsImage->setScale(0.5f);
	auto menu2 = Menu::create(optionsImage, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 2);

	auto _quitBtn = cocos2d::ui::Button::create("QuitButton3.png");
	_quitBtn->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height*0.2f));
	_quitBtn->setScale(1.0f);
	_quitBtn->setTag(2);
	_quitBtn->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::TouchQuitButton, this));
	this->addChild(_quitBtn, 3);
	//Label Quit
	auto _labelQuit = Label::createWithTTF("Quit", "fonts/arial.ttf", 25);
	_labelQuit->setPosition(_quitBtn->getPosition());
	this->addChild(_labelQuit, 3);
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Whack.mp3");
	return true;
}

void MainMenuScene::TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->end();
	}
}
//out cua nut close
void MainMenuScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif


}
//Chuyen den gamescenehihi
void MainMenuScene::GoToGameScene(cocos2d::Ref * pSender)
{
	auto game = Scene::create();
	Director::getInstance()->replaceScene(game);
}

void MainMenuScene::GoToGameOptions(cocos2d::Ref * pSender)
{
	auto gameoptions = Scene::create();
	Director::getInstance()->replaceScene(gameoptions);
}
