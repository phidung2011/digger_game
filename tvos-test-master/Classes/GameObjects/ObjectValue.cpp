//
//  ObjectValue.cpp
//  digger
//
//  Created by Phi Dzung on 10/27/15.
//
//

#include "ObjectValue.h"
#include "MainGameScene.h"

ObjectValue::ObjectValue()
{
    
}

ObjectValue::~ObjectValue()
{
    
}

uint32_t ObjectValue::getIdAt(cocos2d::Vec2 pos)
{
    auto size = MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix;
    CCASSERT(pos.x < size.width && pos.y < size.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");

    
    ssize_t idx = static_cast<int>((pos.x + pos.y * size.width));
    // Bits on the far end of the 32-bit global tile ID are used for tile flags
    uint32_t tile = _objectMap[idx];
    
    return tile;
}

void ObjectValue::setIdAt(cocos2d::Vec2 pos, uint32_t value)
{
    
}
