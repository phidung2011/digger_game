//
//  BoxGold.cpp
//  gamebase
//
//  Created by Phi Dzung on 7/13/15.
//
//

#include "BoxGold.h"
#include <MainGameScene.h>
#include <GameConfig.h>
#include <BaseItem.h>
#include "AvatarConfig.h"
#include "BumBum.h"

BoxGold::BoxGold()
{
    
}
BoxGold::~BoxGold()
{
    
}
bool BoxGold::init()
{
    if (!BaseBomb::init() || !BaseBomb::initWithKey(AnimationKey::BOX_GOLD_KEY))
    {
        return false;
    }
    _speed = 3;
    _cleanEffect = true;
    _idTile = (int)IDTILE::BOX_GOLD;
    _opened = false;
    _boomKey = AnimationKey::BOOM_BOMB_KEY;
    
    this->setOnAnimationFinishCallback([this](int animId)
                                       {
                                           if (animId == 1)
                                           {
                                               this->cleanByEffect();
                                           }
                                       });
    return true;
}

bool BoxGold::dropping()
{
    if (isMovable(dt_bot))
    {
        this->move(dt_bot, sFalling);
        return true;
    }
    return false;
}

void BoxGold::inputUpdate()
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
bool BoxGold::onFallingCollision()
{
    this->destroy();
    return true;
}


bool BoxGold::worldUpdate()
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
                {
                    this->_isBoom = true;
                    _boomKey = AnimationKey::BOOM_CHARACTER_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::CHARACTER :
                {
                    this->_isBoom = true;
                    _boomKey = AnimationKey::BOOM_CHARACTER_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::BOMB_SPIKES :
                {
                    this->_isBoom = true;
                    _boomKey = AnimationKey::BOOM_MINE_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::BOMB_TIME :
                {
                    this->_isBoom = true;
                    _boomKey = AnimationKey::BOOM_TIME_BOMB_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::BOMB_DROP :
                {
                    this->_isBoom = true;
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
                        this->_isBoom = true;
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
                        this->_isBoom = true;
                        _boomKey = AnimationKey::BOOM_CHARACTER_KEY;
                        this->destroy();
                    }
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

void BoxGold::onDestroyObject()
{
    if (_isBoom)
    {
        Vec2 p = this->getMatrixPos();
        std::vector<Vec2> pos;
        pos.push_back(Vec2(p.x, p.y));
        pos.push_back(Vec2(p.x, p.y + 1));
        BigBang* bg = BigBang::create();
        bg->setup(pos, _boomKey);
    }

    
    auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(this->getFrontMatrixPosition());
    if (tile != IDTILE::BOOM_BOMB)
    {
        auto gold = BaseItem::createWithKey(ObjectKey::GOLD_KEY, (int)IDTILE::GOLD);
        gold->setPosition(ConvertUtils::convertCDMatrixtoMap(this->getMatrixPos(), MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix));
        
        MainGameScene::getInstance()->addObject(gold);
        gold->loadToMap();
    }
}


int BoxGold::stateToAnimation(State state) const
{
    switch (state)
    {
        case sIdle:
            return 0;
        case sPushed:
            return 0;
        case sFalling:
            return 0;
        default:
            return -1;
    }
}
