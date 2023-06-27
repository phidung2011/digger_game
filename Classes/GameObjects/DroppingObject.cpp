//
//  DroppingObject.cpp
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 6/29/15.
//
//

#include "DroppingObject.h"
#include <MainGameScene.h>
#include "GameConfig.h"
#include "AvatarConfig.h"


DroppingObject::DroppingObject()
: _isBoom(false)
, _dirPushed(0)
, _isPushed(false)
{

}
DroppingObject::~DroppingObject()
{
    
}
void DroppingObject::move(int dir, State state)
{
    this->setState(state);
    Vec2 vector = Vec2::ZERO;
    Vec2 matrixVector = Vec2::ZERO;
    int totalLoop = TILE_SIZE/_speed;
    switch (dir)
    {
        case dt_top:
            vector = Vec2(0,TILE_SIZE);
            matrixVector = Vec2(0,-1);
            _backDir = dt_bot;
            break;
        case dt_bot:
            vector = Vec2(0,-TILE_SIZE);
            matrixVector = Vec2(0,1);
            _backDir = dt_top;
            break;
        case dt_left:
            vector = Vec2(-TILE_SIZE,0);
            matrixVector = Vec2(-1,0);
            _backDir = dt_right;
            break;
        case dt_right:
            vector = Vec2(TILE_SIZE,0);
            matrixVector = Vec2(1,0);
            _backDir = dt_left;
            break;
        default:
            break;
    }
    
    CMoveBy* move = CMoveBy::create(vector, totalLoop);
     _frontDir = dir;
    
    Vec2 prevPos = this->getMatrixPos();
    MainGameScene::getInstance()->getTileMap()->setIdTile(prevPos, _idTile);
    
    
    CCallback* call = NULL;
    CSequence* seq = NULL;
    if (state != sPushed) {
        call = CCallback::create([prevPos, this]()
                                      {
                                              MainGameScene::getInstance()->getTileMap()->setIdTile(prevPos, (int)IDTILE::DEFAULT);
                                          
                                      });
        seq = CSequence::create(call, move, NULL);
    }
    else
        seq = CSequence::create(move, NULL);

    this->runAct(seq);
    _isCollisionOnMap = !this->updateTile(prevPos + matrixVector);
}

bool DroppingObject::dropping()
{
    if (isMovable(dt_bot))
    {
        this->move(dt_bot, sFalling);
        return true;
    }
    else if (isDropLeftDown() && _state != sRolling)
    {
        this->move(dt_left, sRolling);
        MainGameScene::getInstance()->getTileMap()->setIdTile(this->getMatrixPos() + Vec2(-1,1), (int)IDTILE::MARKED_ITEM);
        return true;
    }
    else if (isDropRightDown() && _state != sRolling)
    {
        this->move(dt_right, sRolling);
        MainGameScene::getInstance()->getTileMap()->setIdTile(this->getMatrixPos() + Vec2(1,1), (int)IDTILE::MARKED_ITEM);
        return true;
    }
    return false;
}

bool DroppingObject::isDropLeftDown()
{
    auto thisPos = this->getMatrixPos();
    Vec2 posDown = Vec2(thisPos.x, thisPos.y + 1);
    
    auto tileDown = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(posDown);
    
    if (tileDown == IDTILE::DIAMOND ||
        tileDown == IDTILE::STONE ||
        tileDown == IDTILE::BOMB_DROP ||
        tileDown == IDTILE::BOMB_TIME ||
        tileDown == IDTILE::WALL_HARD ||
        tileDown == IDTILE::WALL_SOFT)
    {
        Vec2 posLeft = Vec2(thisPos.x - 1, thisPos.y);
        
        Vec2 posLeftDown = Vec2(thisPos.x - 1, thisPos.y + 1);
        
        auto tileLeft = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(posLeft);
        
        auto tileLeftDown = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(posLeftDown);
        
        if (tileLeft == IDTILE::DEFAULT && tileLeftDown == IDTILE::DEFAULT)
        {
            return true;
        }
    }
    return false;
}
bool DroppingObject::isDropRightDown()
{
    auto thisPos = this->getMatrixPos();
    Vec2 posDown = Vec2(thisPos.x, thisPos.y + 1);
    
    auto tileDown = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(posDown);
    
    if (tileDown == IDTILE::DIAMOND ||
        tileDown == IDTILE::STONE ||
        tileDown == IDTILE::BOMB_DROP ||
        tileDown == IDTILE::BOMB_TIME ||
        tileDown == IDTILE::WALL_HARD ||
        tileDown == IDTILE::WALL_SOFT)
    {
        Vec2 posRight = Vec2(thisPos.x + 1, thisPos.y);
        
        Vec2 posRightDown = Vec2(thisPos.x + 1, thisPos.y + 1);
        
        auto tileRight = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(posRight);
        
        auto tileRightDown = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(posRightDown);
        
        if (tileRight == IDTILE::DEFAULT && tileRightDown == IDTILE::DEFAULT)
        {
            return true;
        }
    }
    return false;
}

bool DroppingObject::isMovable(int dir)
{
    Vec2 pos = Vec2::ZERO;
    switch (dir)
    {
        case dt_top:
            pos = this->getPosition() + Vec2(0,TILE_SIZE);
            break;
            
        case dt_bot:
            pos = this->getPosition() + Vec2(0,-TILE_SIZE);
            break;
            
        case dt_left:
            pos = this->getPosition() + Vec2(-TILE_SIZE,0);
            break;
            
        case dt_right:
            pos = this->getPosition() + Vec2(TILE_SIZE,0);
            break;
            
        default:
            break;
    }
    
    Vec2 posMatrix = ConvertUtils::convertCDMaptoMatrix(pos, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
    
    auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(posMatrix);
    
    if (tile == IDTILE::DEFAULT)
    {
        return true;
    }
    
    if (_state == sRolling && tile == IDTILE::MARKED_ITEM)
        return true;
    
    if (_state == sFalling &&
        (tile == IDTILE::PLAYER ||
         tile == IDTILE::MARKED_PLAYER ||
         tile == IDTILE::CHARACTER ||
         tile == IDTILE::MARKED_CHARACTER ||
         tile == IDTILE::BOMB_DROP ||
         tile == IDTILE::BOMB_TIME ||
         tile == IDTILE::BOMB_SPIKES))
    {
        return true;
    }
    
    return false;
}

bool DroppingObject::destroy()
{
    if (_state == sRolling)
    {
        auto pendingPos = ConvertUtils::convertCDMaptoMatrix(this->getFrontPosition(), MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix) + Vec2(0,1);
        auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(pendingPos);
        if (tile == IDTILE::MARKED_ITEM)
        {
            MainGameScene::getInstance()->getTileMap()->setIdTile(pendingPos, (int)IDTILE::DEFAULT);
        }
    }
    return TiledObject::destroy();
}

bool DroppingObject::updateTile(cocos2d::Vec2 nextPos)
{
    auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(nextPos);
    if (tile == IDTILE::DEFAULT || tile == IDTILE::MARKED_ITEM)
    {
        MainGameScene::getInstance()->getTileMap()->setIdTile(nextPos, _idTile);
        return true;
    }
    else return false;
}

