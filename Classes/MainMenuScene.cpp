#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "sting1.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool MainMenuScene::init()
{
	//  super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	//SpriteBatchNode *spriteNode = SpriteBatchNode::create("art/title_animation.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Art/Title_animation/title_animation.plist", "Art/Title_animation/title_animation.png");
	//auto molel = Sprite::createWithSpriteFrameName("title0.png");
	auto model = Sprite::create("Art/Title_animation/title0.png");
	model->setPosition(Vec2(visibleSize.width *0.5f, visibleSize.height *0.5f+50));
	auto moveup = MoveBy::create(1.0f, Vec2(0, 80));
	auto movedown = MoveBy::create(1.0f, Vec2(0, -80));
	auto seq = Sequence::create(moveup, movedown, NULL);
	model->runAction(RepeatForever::create(seq));
	this->addChild(model,99);
	

	// add BackGround
	auto sprite = Sprite::create("Art/menu.jpg"); // file nay la file nao
	this->addChild(sprite);
	sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	if (sprite == nullptr)
	{
		//problemLoading("Art/menued.jpg"); // file nay la file nao


	}

	/*auto title = Sprite::create("art/title.png");
	addChild(title);*/




	auto playImage = MenuItemImage::create(
		"Art/sta.png",
		"Art/sta1.png",
		CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
	playImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	playImage->setPosition(Vec2(visibleSize.width * 0.5f,visibleSize.height*0.4f));
	auto menu1 = Menu::create(playImage, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);

	//btn2
	auto optionsImage = MenuItemImage::create(
		"Art/sti.png",
		"Art/sti1.png",
		CC_CALLBACK_1(MainMenuScene::GoTosting1, this));
	optionsImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	optionsImage->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.3f));
	optionsImage->getContentSize().width;
	optionsImage->getContentSize().height;
	optionsImage->setScale(1);

	auto menu2 = Menu::create(optionsImage, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 2);

	auto _quitBtn = cocos2d::ui::Button::create("Art/QuitButton3.png");
	_quitBtn->setScale(1.0f);
	_quitBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_quitBtn->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.1f));
	_quitBtn->setTag(2);
	_quitBtn->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::TouchQuitButton, this));
	this->addChild(_quitBtn, 3);
	//Label Quit
	auto _labelQuit = Label::createWithTTF("Quit", "fonts/arial.ttf", 30);
	_labelQuit->setPosition(_quitBtn->getPosition());
	this->addChild(_labelQuit, 3);

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Sound/Menu_Soundtrack.mp3", false);

	






	return true;
}
cocos2d::Animation *MainMenuScene::createAnimation(std::string prefixName, int pFramesOrder, float delay)
{
	Vector<SpriteFrame*>animFrames;

	/*taoframe*/
	for (int i = 0; i <= pFramesOrder; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);
		//cclog
		std::string srt = prefixName + buffer;
		//
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(srt);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, delay);
	return animation;
}


void MainMenuScene::TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{

	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->end();
	}



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif


}
//Chuyen den gamescenehihi
void MainMenuScene::GoToGameScene(cocos2d::Ref * pSender)
{
	auto game = GameScene::createGameScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, game));
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Art/select.mp3", false, 1.0f, 1.0f, 1.0f);

}

void MainMenuScene::GoTosting1(cocos2d::Ref * pSender)
{
	auto gamesting1 = sting1::createScene();
	Director::getInstance()->replaceScene(gamesting1);
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Art/select.mp3", false, 1.0f, 1.0f, 1.0f);
}

//void MainMenuScene::TouchQuitButton(Ref * pSender, ui::Widget::TouchEventType eEventType)
//{
//}


