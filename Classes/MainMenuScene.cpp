#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("vday.mp3", true);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto backgroundSprite = Sprite::create( "img_mainmenu.jpg" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    auto playItem = MenuItemImage::create( "img_play.jpg", "img_play_click.jpg", CC_CALLBACK_1( MainMenuScene::GoToGameScene, this ) );
    
    playItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50) );
    
    auto menu = Menu::create( playItem, NULL );
    menu->setPosition( Point::ZERO );
    
    this->addChild( menu );
    
    return true;
}

void MainMenuScene::GoToGameScene( cocos2d::Ref *sender )
{
    auto scene = GameScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

