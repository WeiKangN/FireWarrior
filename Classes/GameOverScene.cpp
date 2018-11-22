#include "GameOverScene.h"

#include "MainMenuScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
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

    auto backgroundSprite = Sprite::create( "Background" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    auto retryItem = MenuItemImage::create( "batdaulai.png", "bat dau lai Clicked.png", CC_CALLBACK_1( GameOverScene::GoToGameScene, this ) );
    retryItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3 ) );
    
    auto mainMenuItem = MenuItemImage::create( "trovemenu.png", "trovemenu Clicked.png", CC_CALLBACK_1( GameOverScene::GoToMainMenuScene, this ) );
    mainMenuItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 ) );
    
    auto menu = Menu::create( retryItem, mainMenuItem, NULL );
    menu->setPosition( Point::ZERO );
    
    this->addChild( menu );
    
    return true;
}







