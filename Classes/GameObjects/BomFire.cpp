//
//  BomFire.cpp
//  gamebase
//
//  Created by NGOCDIEP on 6/29/15.
//
//

#include "BomFire.h"
#include "MainGameScene.h"
#include "GameConfig.h"
#include "AvatarConfig.h"
#include "BumBum.h"

BomFire::BomFire()
{
    
}
BomFire::~BomFire()
{
    
}

BomFire* BomFire::createWithDir(int dir)
{
    BomFire* item = new (std::nothrow) BomFire;
    if (item && item->initWithDir(dir))
    {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}
bool BomFire::initWithDir(int dir)
{
    if (!BaseBomb::init() || !BaseBomb::initWithKey(AnimationKey::BOMB_FIRE_KEY))
    {
        return false;
    }
    _speed = 5;
    _dirFly = dir;
    _idTile = (int)IDTILE::CHARACTER;
    _boomKey = AnimationKey::BOOM_MINE_KEY;
    this->setOnEnterCallback([]{
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_ROCKET_1);
#else
        AUDIO::play2d(EFFECT_ROCKET_1, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
    });
    switch (_dirFly)
    {
        case dt_top:
            this->setRotation(-90);
            break;
        case dt_bot:
            this->setRotation(90);
            break;
        case dt_left:
            this->setRotation(180);
            break;
        case dt_right:
            this->setRotation(0);
            break;
    }
    return true;
}

bool BomFire::fly()
{
    if (isMovable(_dirFly))
    {
        this->move(_dirFly, sMoving);
        return true;
    }
    return false;
}

void BomFire::inputUpdate()
{
    //execute control
    if (_actPool.empty())
    {
        bool act = fly();
        if (act)
        {
            
        }
        else
        {
            this->stop();
        }
    }
}

bool BomFire::worldUpdate()
{
    
    if (_actPool.empty())
    {
        if (_state == sMoving)
        {
            if (!isMovable(_dirFly))
            {
                onFlyingCollision();
            }
        }
    }
    
    return _isValid;
}


void BomFire::onDestroyObject()
{
    BaseCharacter::onDestroyObject();
}

bool BomFire::onFlyingCollision()
{
    
    this->destroy();
    return true;
}

bool BomFire::isMovable(int dir)
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
    return false;
}

bool BomFire::destroy()
{
    if (!_isValid)
    {
        this->stop();
        this->removeAllEffect();
        this->onDestroyObject();
        this->removeFromParentAndCleanup(false);
        MainGameScene::getInstance()->getReleasePool().pushBack(this);
        _isValid = true;
    }
    
    return _isValid;
}


int BomFire::stateToAnimation(State state) const
{
    switch (state)
    {
        case sIdle:
            return 0;
        case sMoving:
            return 0;
        default:
            return -1;
    }
}