//
//  BomDrop.cpp
//  gamebase
//
//  Created by NGOCDIEP on 6/25/15.
//
//

#include "BomDrop.h"
#include "MainGameScene.h"
#include "GameConfig.h"
#include "AvatarConfig.h"
#include "BumBum.h"
BomDrop::BomDrop()
{
    
}
BomDrop::~BomDrop()
{
    
}
bool BomDrop::init()
{
    if (!BaseBomb::init() || !BaseBomb::initWithKey(AnimationKey::BOMB_DROP_KEY))
    {
        return false;
    }
    _speed = 3.3;
    _boomKey = AnimationKey::BOOM_BOMB_KEY;
    _idTile = (int)IDTILE::BOMB_DROP;
    return true;
}

void BomDrop::onDestroyObject()
{
    Vec2 p = this->getMatrixPos();
    std::vector<Vec2> pos;
    pos.push_back(Vec2(p.x, p.y));
    pos.push_back(Vec2(p.x + 1, p.y));
    pos.push_back(Vec2(p.x + 1, p.y + 1));
    pos.push_back(Vec2(p.x - 1, p.y));
    pos.push_back(Vec2(p.x - 1, p.y + 1));
    pos.push_back(Vec2(p.x, p.y + 1));
    
    BigBang* bg = BigBang::create();
    bg->setup(pos, _boomKey);
}
void BomDrop::inputUpdate()
{
    if (_isPushed)
    {
        float pushSpeed = MainGameScene::getInstance()->getPlayer()->getSpeed();
        float temp = _speed;
        _speed = pushSpeed*0.5f;
        this->move(_dirPushed, sPushed);
        _speed = temp;
        _isPushed = false;
    }
    
    //execute control
    if (_actPool.empty())
    {
        bool act = dropping();
        if (act)
        {
            
        }
        else
        {
            this->stop();
        }
    }
}

bool BomDrop::worldUpdate()
{
    if (_state == sFalling)
    {
        if (_isCollisionOnMap)
        {
            auto frontPos = this->getFrontMatrixPosition();
            auto tileNext = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos);
            switch (tileNext)
            {
                case IDTILE::PLAYER :
                case IDTILE::CHARACTER :
                {
                    _boomKey = AnimationKey::BOOM_CHARACTER_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::BOMB_SPIKES :
                {
                    _boomKey = AnimationKey::BOOM_MINE_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::BOMB_TIME :
                case IDTILE::BOMB_DROP :
                {
                    _boomKey = AnimationKey::BOOM_BOMB_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::MARKED_PLAYER :
                {
                    auto tileLeft = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(-1,0));
                    auto tileRight = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(1,0));
                    if (tileLeft == IDTILE::PLAYER || tileRight == IDTILE::PLAYER)
                    {
                        _boomKey = AnimationKey::BOOM_CHARACTER_KEY;
                        this->destroy();
                    }
                    MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::BOMB_DROP);
                }
                    break;
                case IDTILE::MARKED_CHARACTER :
                {
                    auto tileLeft = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(-1,0));
                    auto tileRight = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(1,0));
                    if (tileLeft == IDTILE::CHARACTER || tileRight == IDTILE::CHARACTER)
                    {
                        _boomKey = AnimationKey::BOOM_CHARACTER_KEY;
                        this->destroy();
                    }
                    MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::BOMB_DROP);
                }
                    break;
                case IDTILE::DEFAULT :
                {
                    MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::BOMB_DROP);
                }
                    break;
                default:
                    break;
            }
            _isCollisionOnMap = false;
        }
    }
    
    if (_actPool.empty())
    {
        if (_state == sFalling)
        {
            if (!isMovable(dt_bot))
            {
                onFallingCollision();
            }
        }
    }
    
    return _isValid;
}
bool BomDrop::onFallingCollision()
{
    this->destroy();
    return true;
}
int BomDrop::stateToAnimation(State state) const
{
    switch (state)
    {
        case sIdle:
            return 0;
        case sPushed:
            return 0;
        case sRolling:
            return 0;
        case sFalling:
            return 0;
        default:
            return -1;
    }
}