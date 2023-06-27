//
//  TiledObject.cpp
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 8/21/15.
//
//

#include "TiledObject.h"
#include "MainGameScene.h"
#include "AvatarConfig.h"
#include "GameConfig.h"

bool TiledObject::destroy()
{
    auto tileMap = MainGameScene::getInstance()->getTileMap();
    
    auto posFront = this->getFrontMatrixPosition();
    auto posBack = this->getBackMatrixPosition();
    
    auto tileFront = tileMap->getIdTile(posFront);
    auto tileBack = tileMap->getIdTile(posBack);
    
    if (tileFront == _idTile) {
        tileMap->setIdTile(posFront, (int)IDTILE::DEFAULT);
    }
    if (tileBack == _idTile) {
        tileMap->setIdTile(posBack, (int)IDTILE::DEFAULT);
    }
    return DataObject::destroy();
}


void TiledObject::stop()
{
    this->stopAllAct();
    _delta = Vec2::ZERO;
    this->setState(sIdle);
    _frontDir = 0;
}

cocos2d::Vec2 TiledObject::getBackPosition() const
{
    switch ( _frontDir)
    {
        case dt_bot:
            return this->getPosition() + Vec2(0,TILE_SIZE*0.5f - EX);
        case dt_right:
            return this->getPosition() + Vec2(-TILE_SIZE*0.5f + EX,0);
        case dt_top:
            return this->getPosition() + Vec2(0,-TILE_SIZE*0.5f + EX);
        case dt_left:
            return this->getPosition() + Vec2(TILE_SIZE*0.5f - EX,0);
        case 0:
            return this->getPosition();
    }
    return Vec2::ZERO;
}

void TiledObject::resetPos()
{
    this->setPosition(ConvertUtils::convertCDMatrixtoMap(this->getMatrixPos(), MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix));
}



cocos2d::Vec2 TiledObject::getFrontPosition() const
{
    switch (_frontDir)
    {
        case 0:
            return this->getPosition();
            break;
        case dt_top:
            return (this->getPosition() + Vec2(0, TILE_SIZE * 0.5 - EX));
            break;
        case dt_left:
            return (this->getPosition() + Vec2(-TILE_SIZE * 0.5 + EX, 0));
            break;
        case dt_right:
            return (this->getPosition() + Vec2(TILE_SIZE * 0.5 - EX, 0));
            break;
        case dt_bot:
            return (this->getPosition() + Vec2(0, -TILE_SIZE * 0.5 + EX));
            break;
    }
    return Vec2::ZERO;
}

cocos2d::Vec2 TiledObject::getMatrixPos() const
{
    return ConvertUtils::convertCDMaptoMatrix(this->getPosition(), MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
}


void TiledObject::loadToMap()
{
    MainGameScene::getInstance()->getTileMap()->setIdTile(this->getMatrixPos(), _idTile);
}

cocos2d::Vec2 TiledObject::getFrontMatrixPosition() const
{
    return ConvertUtils::convertCDMaptoMatrix(this->getFrontPosition(), MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
}

cocos2d::Vec2 TiledObject::getBackMatrixPosition() const
{
    return ConvertUtils::convertCDMaptoMatrix(this->getBackPosition(), MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
}