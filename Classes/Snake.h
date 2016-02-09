#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "cocos2d.h"

class Snake
{
public:
    Snake( cocos2d::Layer *layer );
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    cocos2d::Sprite *nyanCat;
};

#endif // __GAMEOVER_SCENE_H__
