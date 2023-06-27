//
//  BaseItem.cpp
//  gamebase
//
//  Created by Phi Dzung on 7/8/15.
//
//

#include "BaseItem.h"
#include "MainGameScene.h"
#include "GameConfig.h"
#include "AvatarConfig.h"
BaseItem::BaseItem()
{
    
}
BaseItem::~BaseItem()
{
    
}

BaseItem* BaseItem::createWithKey(ObjectKey key, int tileId)
{
    BaseItem* item = new (std::nothrow) BaseItem;
    if (item && item->initWithKey(key, tileId))
    {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}
bool BaseItem::initWithKey(ObjectKey key, int tileId)
{
    if (!TiledObject::init() || !TiledObject::initWithKey(AnimationKey(key,1)))
    {
        return false;
    }
    
    _idTile = tileId;
    
    return true;
}

bool BaseItem::destroy()
{
    auto tileMap = MainGameScene::getInstance()->getTileMap();
    auto pos = this->getMatrixPos();
    auto tile = tileMap->getIdTile(pos);
    
    if (tile == _idTile)
    {
        tileMap->setIdTile(pos, (int)IDTILE::DEFAULT);
    }
    return DataObject::destroy();
}




