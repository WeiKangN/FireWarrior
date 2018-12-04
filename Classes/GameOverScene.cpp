#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* GameOverScene::createscene()
{
    
    auto scene = Scene::create();
    
    
    auto layer = GameOverScene::create();

    
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create( "menu.jpg" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    auto retryItem = MenuItemImage::create( "retrybutton0.png", "retrybutton1.png", CC_CALLBACK_1( GameOverScene::GoToGameScene, this ) );
    retryItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3 ) );
    
    /*auto mainMenuItem = MenuItemImage::create( "Play Button.png", "trovemenu Clicked.png", CC_CALLBACK_1( GameOverScene::GoToMainMenuScene, this ) );
    mainMenuItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 ) );*/
    
    auto menu = Menu::create( retryItem, /*mainMenuItem,*/ NULL );
    menu->setPosition( Point::ZERO );
    
    this->addChild( menu );
    
    return true;
}

void GameOverScene::GoToGameScene(cocos2d::Ref *sender)
{
	auto gameoverscene = MainMenuScene::createscene();
	Director::getInstance()->replaceScene(gameoverscene);
	
}
void GameOverScene::GoToMainMenuScene(cocos2d::Ref *sender)
{
	
};





