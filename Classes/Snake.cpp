#include "Snake.h"
#include "Definitions.h"
#include <vector>

USING_NS_CC;

Snake::Snake( cocos2d::Layer *layer )
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    auto nyanCat = Sprite::create( "img_cat_up.png" );
    nyanCat->setPosition( Point( 0, 0 ) );
    
    layer->addChild( nyanCat, 100 );
}
