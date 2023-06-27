//
//  Diamond.cpp
//  gamebase
//
//  Created by Phi Dzung on 6/15/15.
//
//

#include "Diamond.h"
#include "GameConfig.h"
#include "MainGameScene.h"
#include "AvatarConfig.h"
#include "BumBum.h"

Diamond::Diamond()
{
    
}
Diamond::~Diamond()
{
    CCLOG("%s", __PRETTY_FUNCTION__);
}

bool Diamond::initWithLevel(int level)
{
    auto key = ObjectKey::DIAMOND_KEY;
    if (!BaseBomb::init() || !BaseBomb::initWithKey(AnimationKey(ObjectKey::DIAMOND_KEY, level)))
    {
        return false;
    }
    _cleanEffect = true;
    
    this->setOnAnimationFinishCallback([this](int animId)
    {
        if (animId == 1)
        {
            this->cleanByEffect();
        }
    });
    _speed = 3.3;
    _idTile = (int)IDTILE::DIAMOND;
    _boomKey = AnimationKey::BOOM_BOMB_KEY;
    return true;
}

Diamond* Diamond::createWithLevel(int level)
{
    Diamond* item = new (std::nothrow) Diamond;
    if (item && item->initWithLevel(level))
    {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}


void Diamond::inputUpdate()
{
    
    //execute control
    if (_actPool.empty())
    {
        auto currentState = _state;
        bool act = dropping();
        if (act)
        {
            if (currentState != _state && (_state == sRolling || _state == sFalling))
            {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_GEM_1);
#else
                AUDIO::play2d(EFFECT_GEM_1, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
        }
        else
        {
            this->stop();
        }
    }
}

bool Diamond::worldUpdate()
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
                    MainGameScene::getInstance()->getPlayer()->collectItem(this);
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
                        MainGameScene::getInstance()->getPlayer()->collectItem(this);
                        break;
                    }
                    MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::DIAMOND);
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
                    MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::DIAMOND);
                }
                    break;
                case IDTILE::DEFAULT :
                {
                    MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::DIAMOND);
                }
                    break;
                default:
                    break;
            }
        }
        _isCollisionOnMap = false;
    }
    
    return _isValid;
}

void Diamond::onDestroyObject()
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
}

int Diamond::stateToAnimation(State state) const
{
    switch (state)
    {
        case sIdle:
            return 0;
        case sRolling:
            return 0;
        case sFalling:
            return 0;
        default:
            return -1;
    }
}
