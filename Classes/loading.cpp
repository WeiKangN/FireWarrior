#include "SimpleAudioEngine.h"
#include "loading.h"
#include "ui/CocosGUI.h"
#include "MainMenuScene.h"
USING_NS_CC;

loading::loading()
{
}
loading::~loading()
{
}
Scene* loading::createScene()
{
	auto scene = Scene::create();

	auto layer = loading::create();

	scene->addChild(layer);
	return scene;

}


bool loading::init()
{
	////////////////////////////

	if (!Scene::init())
	{
		return false;
	}
	/*auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Whack.mp3", false);*/

	
	createloading();
	///////////////////////////
	/*createSprSplash();*/
	return true;
}
void loading::goToMainMenuScene()
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}
void loading::createloading()
{
	//Back Ground
	Size winSize = Director::getInstance()->getWinSize();
	/*auto backgound = Sprite::create("menu.jpg");
	this->addChild(backgound);
	backgound->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	backgound->setPosition(this->getContentSize() * 0.5f);
	float scaleX = winSize.width*0.8 / (backgound->getContentSize().width);
	float scaleY = winSize.height*0.8 / (backgound->getContentSize().height);
	backgound->setScaleX(scaleX);
	backgound->setScaleY(scaleY);*/
	//cái vỏ 
	auto Loading = Sprite::create("art/loadingbar_border.png");
	this->addChild(Loading);
	Loading->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
	Loading->setScaleX(1.5);
	/*Loading->setScaleY(0.5);*/
	//cái ruột
	auto loadingBar = ui::LoadingBar::create("art/loadingbar_inside.png");
	loadingBar->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
	loadingBar->setScaleX(1.5);
	loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingBar->setPercent(0);

	this->addChild(loadingBar);
	this->schedule([=](float delta) {
		float percen = loadingBar->getPercent();
		percen++;
		loadingBar->setPercent(percen);
		if (percen >= 100.0f)
		{
			this->unschedule("updateloadingBar");
			this->goToMainMenuScene();
		}
	}, 0.05f, "updateloadingBar"); 

}