//
//  Stone.cpp
//  gamebase
//
//  Created by Phi Dzung on 6/19/15.
//
//

#include "Stone.h"
#include "MainGameScene.h"
#include "GameConfig.h"
#include "AvatarConfig.h"
#include "BumBum.h"
Stone::Stone()
{
    
}
Stone::~Stone()
{
    
}
bool Stone::init()
{
    if (!BaseBomb::init() || !BaseBomb::initWithKey(AnimationKey::STONE_KEY))
    {
        return false;
    }
    _speed = 3.3;
    
    _idTile = (int)IDTILE::STONE;
    _boomKey = AnimationKey::BOOM_BOMB_KEY;

    return true;
}

void Stone::inputUpdate()
{
    if (_isPushed) // đẩy đá
    {
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_ROCK_1);
#else
        AUDIO::play2d(EFFECT_ROCK_1, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        //        CCLOG("stone state --- %d",this->getState());
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
            if (_state == sRolling)
            {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_ROCK_1);
#else
                AUDIO::play2d(EFFECT_ROCK_1, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif

            }
        }
        else
        {
            if (_state == sFalling)
            {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_ROCK_2);
#else
                AUDIO::play2d(EFFECT_ROCK_2, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
            this->stop();
        }
    }
}

void Stone::onDestroyObject()
{
    if (_isBoom)
    {
        short rd = random(0, 1);
        if (rd == 0)
        {
            Vec2 p = this->getMatrixPos();
            std::vector<Vec2> pos;
            pos.push_back(Vec2(p.x, p.y));
            pos.push_back(Vec2(p.x, p.y + 1));
            pos.push_back(Vec2(p.x - 1, p.y + 1));
            pos.push_back(Vec2(p.x - 1, p.y));
            BigBang* bg = BigBang::create();
            bg->setup(pos, _boomKey);
        }
        else
        {
            Vec2 p = this->getMatrixPos();
            std::vector<Vec2> pos;
            pos.push_back(Vec2(p.x, p.y));
            pos.push_back(Vec2(p.x + 1, p.y));
            pos.push_back(Vec2(p.x + 1, p.y + 1));
            pos.push_back(Vec2(p.x, p.y + 1));
            BigBang* bg = BigBang::create();
            bg->setup(pos, _boomKey);
        }
    }
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->playEffect(EFFECT_ROCK_3);
#else
    AUDIO::play2d(EFFECT_ROCK_3, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
}
bool Stone::worldUpdate()
{
//    CCLOG("%d",_state);
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
                    _isBoom = true;
                    _boomKey = AnimationKey::BOOM_CHARACTER_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::CHARACTER :
                {
                    _isBoom = true;
                    _boomKey = AnimationKey::BOOM_CHARACTER_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::BOMB_DROP :
                {
                    _isBoom = true;
                    _boomKey = AnimationKey::BOOM_BOMB_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::BOMB_SPIKES :
                {
                    _isBoom = true;
                    _boomKey = AnimationKey::BOOM_MINE_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::BOMB_TIME :
                {
                    _isBoom = true;
                    _boomKey = AnimationKey::BOOM_TIME_BOMB_KEY;
                    this->destroy();
                }
                    break;
                case IDTILE::MARKED_PLAYER :
                {
                    auto tileLeft = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(-1,0));
                    auto tileRight = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(1,0));
                    if (tileLeft == IDTILE::PLAYER || tileRight == IDTILE::PLAYER)
                    {
                        _isBoom = true;
                        _boomKey = AnimationKey::BOOM_CHARACTER_KEY;
                        this->destroy();
                        break;
                    }
                    MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::STONE);
                }
                    break;
                case IDTILE::MARKED_CHARACTER :
                {
                    auto tileLeft = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(-1,0));
                    auto tileRight = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(1,0));
                    if (tileLeft == IDTILE::CHARACTER || tileRight == IDTILE::CHARACTER)
                    {
                        _isBoom = true;
                        _boomKey = AnimationKey::BOOM_CHARACTER_KEY;
                        this->destroy();
                        break;
                    }
                    MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::STONE);
                }
                    break;
                case IDTILE::DEFAULT :
                {
                    MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::STONE);
                }
                    break;

                default:
                    break;
            }
            _isCollisionOnMap = false;
        }
    }
    else if (_state == sRolling || sPushed)
    {
        if (_state == sRolling)
        {
            if (_frontDir == dt_left)
            {
                this->setRotation(this->getRotation() - _speed/(TILE_SIZE*PI_NUMBER)*360);
            }
            else if (_frontDir == dt_right)
            {
                this->setRotation(this->getRotation() + _speed/(TILE_SIZE*PI_NUMBER)*360);
            }
        }
        else if (_state == sPushed)
        {
            float speed = MainGameScene::getInstance()->getPlayer()->getSpeed()*0.5f;
            if (_frontDir == dt_left)
            {
                this->setRotation(this->getRotation() - speed/(TILE_SIZE*PI_NUMBER)*360);
            }
            else if (_frontDir == dt_right)
            {
                this->setRotation(this->getRotation() + speed/(TILE_SIZE*PI_NUMBER)*360);
            }
        }
    }
    return _isValid;
}

int Stone::stateToAnimation(State state) const
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
