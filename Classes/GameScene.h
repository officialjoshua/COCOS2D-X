#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameOverScene.h"
#include <vector>

USING_NS_CC;

class Rainbow
{
public:
    Rainbow( int direction )
    {
        rainbowSprite = Sprite::create( "img_line_up.png" );
        this->direction = direction;
    }
    
    Sprite* rainbowSprite;
    int direction;
};

class Wall
{
public:
    Wall( int style )
    {
        switch (style) {
            case 1:
                wallSprite = Sprite::create( "wall.png" );
                break;
            case 2:
                wallSprite = Sprite::create( "wall_edge.png" );
                break;
        }
    }
    
    Sprite* wallSprite;
};

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    int key;
    int fps;
    int score;
    
    std::vector<Rainbow> nyanRainbow;
    std::vector<Wall> gameWall;
    
    Sprite* nyannyan = Sprite::create( "img_cat_up.png" );
    Sprite* nyanfood = Sprite::create( "img_food.png" );
    
    void initBody();
    
    void generateWalls();
    
    void addListeners();
    
    void update( float dt );
    
    void foodCollision();
    
    void foodAppendBody( Rainbow temp );
    
    Rainbow foodGetPosition();
    
    Label* label = Label::createWithTTF("Score", "fonts/visitor1.ttf", 20);
    
private:
    void GoToGameOverScene( cocos2d::Ref *sender );
};

#endif // __GAME_SCENE_H__
