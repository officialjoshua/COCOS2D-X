#include "cocos2d.h"
#include "GameScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include <vector>

USING_NS_CC;

Vec2 prevprev;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    key = 3;
    fps = 0;
    score = 0;
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    std::string scoreStr = "Score: " + std::to_string(score);
    label->setString(scoreStr);
    
    label->setPosition( Vec2( 105 , 650 ) );
    
    this->addChild( label, 100 );
    
    auto scoreBoard = Sprite::create( "scoreboard.jpg" );
    scoreBoard->setPosition( Vec2( 105 , 650 ) );
    
    this->addChild( scoreBoard, 99 );
    
    this->generateWalls();
    
    auto backgroundSprite = Sprite::create( "img_background.jpg" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    this->generateWalls();
    
    nyannyan->setPosition( Vec2(360, 360) );
    
    this->addChild( nyannyan, 1 );
    
    nyanfood->setPosition( Vec2(600, 600) );
    
    this->addChild( nyanfood, 1 );
 
    this->initBody();
    
    this->addListeners();
    
    this->scheduleUpdate();
    
    return true;
}

void GameScene::initBody()
{
    for ( int i = 0; i < 3; i++ )
    {
        auto temp = Rainbow( 3 );
        temp.rainbowSprite->setPosition( 360, 360 - ( 60 * (i + 1 ) ) );
        
        nyanRainbow.push_back(temp);
        this->addChild( temp.rainbowSprite );
    }
}

void GameScene::addListeners()
{
    // implement key listeners here like WASD key movements.
    auto eventListener = EventListenerKeyboard::create();
    
    eventListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event)
    {
        Vec2 loc = event->getCurrentTarget()->getPosition();
        
        switch(keyCode)
        {
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_A:
                if ( loc.x > 0 && event->getCurrentTarget()->getRotation() != 90 )
                    key = 1;
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
                if (loc.x < 1200 && event->getCurrentTarget()->getRotation() != 270 )
                    key = 2;
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            case EventKeyboard::KeyCode::KEY_W:
                if (loc.y < 720 && event->getCurrentTarget()->getRotation() != 180 )
                    key = 3;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
                if (loc.y > 60 && event->getCurrentTarget()->getRotation() != 0 )
                    key = 4;
                break;
            default:
                key = 0;
                break;
        }
    };
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority( eventListener, nyannyan );
}

void GameScene::generateWalls()
{
    /* generate width */
    for ( int i = 0 ; i <= 1200 ; i+=60) {
        /* generate width */
        for ( int j = 0 ; j <= 720 ; j+=60) {
            
            if ( ( j == 0 || j == 720 || i == 0 || i == 1200 ) &&
                !( j == 0 && i == 0 ) &&
                !( j == 0 && i == 1200 ) &&
                !( j == 720 && i == 0 ) &&
                !( j == 720 && i == 1200 ) )
            {
                int rotation;
                
                if ( j == 0 || j == 720)
                {
                    rotation = 0;
                }
                else if ( i == 0 || i == 1200 )
                {
                    rotation = 90;
                }
                
                auto tempWall = Wall( 1 );
                
                tempWall.wallSprite->setPosition( Vec2(i, j) );
                tempWall.wallSprite->setRotation( rotation );
                
                gameWall.push_back( tempWall );
                this->addChild( tempWall.wallSprite );
                
                rotation = 0;
                
            } else if ( ( j == 0 && i == 0 ) ||
                ( j == 0 && i == 1200 ) ||
                ( j == 720 && i == 0 ) ||
                ( j == 720 && i == 1200 ))
            {
                int rotation;
                
                if ( j == 0 && i == 0 )
                {
                    rotation = 270;
                }
                else if ( j == 0 && i == 1200 )
                {
                    rotation = 180;
                }
                else if ( j == 720 && i == 0  )
                {
                    rotation = 0;
                }
                else if ( j == 720 && i == 1200 )
                {
                    rotation = 90;
                }
                
                auto tempWall = Wall( 2 );
                
                tempWall.wallSprite->setPosition( Vec2(i, j) );
                tempWall.wallSprite->setRotation( rotation );
                
                gameWall.push_back( tempWall );
                this->addChild( tempWall.wallSprite );
            }
        }
    }
}

void GameScene::update( float dt )
{
    auto rainbowTemp = Rainbow( 0 );
    int foodCheck = 0;
    
    if ( key != 0 )
    {
    Vec2 loc = nyannyan->getPosition();
    
    fps += 1;
    fps = fps % 15;
        
    if ( fps == 14 )
    {
        //CCLOG("HEAD (A) --- X: %f and Y: %f", loc.x, loc.y);
        //CCLOG("DIRECTION: %d" ,key);
        
        /* Head Movement */
        switch (key)
        {
            case 1:
                if ( loc.x > 0 )
                {
                    nyannyan->setPosition( loc.x-60, loc.y );
                    nyannyan->setRotation( 270 );
                }
                break;
                
            case 2:
                if ( loc.x < 1260 )
                {
                    nyannyan->setPosition( loc.x+60, loc.y );
                    nyannyan->setRotation( 90 );
                }
                break;
                
            case 3:
                if ( loc.y < 720 )
                {
                    nyannyan->setPosition( loc.x, loc.y+60 );
                    nyannyan->setRotation( 0 );
                }
                break;
                
            case 4:
                if ( loc.y > 60 )
                {
                    nyannyan->setPosition( loc.x, loc.y-60 );
                    nyannyan->setRotation( 180 );
                }
                break;
                
            default:
                break;
        }
        
        /* Check for food */
        if ( nyannyan->getPosition() == nyanfood->getPosition() )
        {
            /* Collision Function */
            foodCollision();
            rainbowTemp = foodGetPosition();
            foodCheck = 1;
            score = score + 10;
            std::string scoreStr = "Score: " + std::to_string(score);
            label->setString(scoreStr);
        }
        
        /* Check for tail collisions */
        for ( int i = 0; i < nyanRainbow.size(); i++ )
        {
            if ( nyanRainbow.at( i ).rainbowSprite->getPosition() == nyannyan->getPosition() )
            {
                GoToGameOverScene( this );
            }
        }
        
        /* Check for tail collisions */
        for ( int i = 0; i < gameWall.size(); i++ )
        {
            if ( gameWall.at( i ).wallSprite->getPosition() == nyannyan->getPosition() )
            {
                GoToGameOverScene( this );
            }
        }
        
        
        //CCLOG("HEAD (B) --- X: %f and Y: %f", loc.x, loc.y);

        /* Connector */
        Vec2 loc0 = nyanRainbow.at(0).rainbowSprite->getPosition();
        
        //CCLOG("BODY (A) --- X: %f and Y: %f", loc0.x, loc0.y);
        //CCLOG("DIRECTION NEW: %d" , nyanRainbow.at(0).direction);
        
        
        switch (nyanRainbow.at(0).direction)
        {
            case 1:
                if ( loc0.x > 0 )
                {
                    nyanRainbow.at(0).rainbowSprite->setPosition( loc0.x-60, loc0.y );
                    nyanRainbow.at(0).rainbowSprite->setRotation( 270 );
                }
                break;
                
            case 2:
                if ( loc0.x < 1260 )
                {
                    nyanRainbow.at(0).rainbowSprite->setPosition( loc0.x+60, loc0.y );
                    nyanRainbow.at(0).rainbowSprite->setRotation( 90 );
                }
                break;
                
            case 3:
                if ( loc0.y < 720 )
                {
                    nyanRainbow.at(0).rainbowSprite->setPosition( loc0.x, loc0.y+60 );
                    nyanRainbow.at(0).rainbowSprite->setRotation( 0 );
                }
                break;
                
            case 4:
                if ( loc0.y > 60 )
                {
                    nyanRainbow.at(0).rainbowSprite->setPosition( loc0.x, loc0.y-60 );
                    nyanRainbow.at(0).rainbowSprite->setRotation( 180 );
                }
                break;
                
            default:
                break;
        }
        
        //CCLOG("BODY (B) --- X: %f and Y: %f", loc0.x, loc0.y);
        
        /* Body Movement */
        if ( key != 0 )
        {
            for ( int i = nyanRainbow.size()-1 ; i > 0 ; i-- )
            {
                if ( nyanRainbow.at( i ).direction == 1 && nyanRainbow.at( i-1 ).direction == 3 )
                    nyanRainbow.at(i).rainbowSprite->setTexture("1_line.png");
                else if ( nyanRainbow.at( i ).direction == 1 && nyanRainbow.at( i-1 ).direction == 4 )
                    nyanRainbow.at(i).rainbowSprite->setTexture("img_line_up_left.png");
                else if ( nyanRainbow.at( i ).direction == 2 && nyanRainbow.at( i-1 ).direction == 3 )
                    nyanRainbow.at(i).rainbowSprite->setTexture("img_line_up_left.png");
                else if ( nyanRainbow.at( i ).direction == 2 && nyanRainbow.at( i-1 ).direction == 4 )
                    nyanRainbow.at(i).rainbowSprite->setTexture("1_line.png");
                else if ( nyanRainbow.at( i ).direction == 4 && nyanRainbow.at( i-1 ).direction == 1 )
                    nyanRainbow.at(i).rainbowSprite->setTexture("1_line.png");
                else if ( nyanRainbow.at( i ).direction == 4 && nyanRainbow.at( i-1 ).direction == 2 )
                    nyanRainbow.at(i).rainbowSprite->setTexture("img_line_up_left.png");
                else if ( nyanRainbow.at( i ).direction == 3 && nyanRainbow.at( i-1 ).direction == 2 )
                    nyanRainbow.at(i).rainbowSprite->setTexture("1_line.png");
                else if ( nyanRainbow.at( i ).direction == 3 && nyanRainbow.at( i-1 ).direction == 1 )
                    nyanRainbow.at(i).rainbowSprite->setTexture("img_line_up_left.png");
                else
                    nyanRainbow.at(i).rainbowSprite->setTexture("img_line_up.png");

                Vec2 loc1 = nyanRainbow.at(i).rainbowSprite->getPosition();
                
                switch (nyanRainbow.at(i).direction)
                    {
                        case 1:
                            if ( loc1.x > 0 )
                            {
                                nyanRainbow.at(i).rainbowSprite->setPosition( loc1.x-60, loc1.y );
                                nyanRainbow.at(i).rainbowSprite->setRotation( 270 );
                            }
                            break;
         
                        case 2:
                            if ( loc1.x < 1260 )
                            {
                                nyanRainbow.at(i).rainbowSprite->setPosition( loc1.x+60, loc1.y );
                                nyanRainbow.at(i).rainbowSprite->setRotation( 90 );
                            }
                            break;
         
                        case 3:
                            if ( loc1.y < 720 )
                            {
                                nyanRainbow.at(i).rainbowSprite->setPosition( loc1.x, loc1.y+60 );
                                nyanRainbow.at(i).rainbowSprite->setRotation( 0 );
                            }
                            break;
         
                        case 4:
                            if ( loc1.y > 60 )
                            {
                                nyanRainbow.at(i).rainbowSprite->setPosition( loc1.x, loc1.y-60 );
                                nyanRainbow.at(i).rainbowSprite->setRotation( 180 );
                            }
                            break;
         
                        default:
                            break;
                    }
                    nyanRainbow.at(i).direction = nyanRainbow.at(i-1).direction;
                
                }
                nyanRainbow.at(0).direction = key;
            }
        
            if ( foodCheck == 1 )
            {
                /* Collision Function */
                foodAppendBody( rainbowTemp );
                foodCheck = 0;
            }
        }
    }
}

void GameScene::foodCollision()
{
    int locX;
    int locY;
    int check = false;
    
    while ( check != true )
    {
        check = true;
        
        locX = (std::rand() %  18 + 1) * 60;
        locY = (std::rand() %  10 + 1) * 60;
        
        if ( nyannyan->getPosition() == Vec2( locX, locY ) ) {
            check = false;
        }
        
        for ( int i = 0 ; i < nyanRainbow.size() ; i++ ) {
            if ( nyanRainbow.at(i).rainbowSprite->getPosition() == Vec2( locX, locY ) )
                check = false;
        }
    }
    
    nyanfood->setPosition( Vec2 ( locX, locY ) );
}

Rainbow GameScene::foodGetPosition()
{
    auto temp = Rainbow( nyanRainbow.at(nyanRainbow.size()-1).direction );
    temp.rainbowSprite->setPosition( nyanRainbow.at(nyanRainbow.size()-1).rainbowSprite->getPosition() );
    
    return temp;
}

void GameScene::foodAppendBody( Rainbow temp )
{
    CCLOG("Position of last: X:: %f Y:: %f", nyanRainbow.at(nyanRainbow.size()-2).rainbowSprite->getPosition().x, nyanRainbow.at(nyanRainbow.size()-1).rainbowSprite->getPosition().y );
    CCLOG("Position of new*: X:: %f Y:: %f", nyanRainbow.at(nyanRainbow.size()-1).rainbowSprite->getPosition().x, nyanRainbow.at(nyanRainbow.size()-1).rainbowSprite->getPosition().y );
    
    nyanRainbow.push_back(temp);
    this->addChild( temp.rainbowSprite );
}

void GameScene::GoToGameOverScene( cocos2d::Ref *sender )
{
    auto scene = GameOverScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( 0, scene ) );
}
