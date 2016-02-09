#include "GameOverScene.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
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
    
    auto backgroundSprite = Sprite::create( "img_gaveover.jpg" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    auto playItem = MenuItemImage::create( "img_again.jpg", "img_again_click.jpg", CC_CALLBACK_1( GameOverScene::GoToGameScene, this ) );
    
    playItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50) );
    
    auto menu = Menu::create( playItem, NULL );
    menu->setPosition( Point::ZERO );
    
    this->addChild( menu );
    
    return true;
}

void GameOverScene::GoToGameScene( cocos2d::Ref *sender )
{
    auto scene = GameScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}


