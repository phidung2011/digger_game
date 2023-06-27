//
//  BomTime.cpp
//  gamebase
//
//  Created by NGOCDIEP on 6/25/15.
//
//

#include "BomTime.h"
#include "MainGameScene.h"
#include "GameConfig.h"
#include "AvatarConfig.h"
#include "BumBum.h"

BomTime::BomTime()
{
    
}
BomTime::~BomTime()
{
    
}
bool BomTime::init()
{
    if (!BaseBomb::init() || !BaseBomb::initWithKey(AnimationKey::BOMB_TIME_KEY))
    {
        return false;
    }
    _speed = 0;
    _idTile = (int)IDTILE::BOMB_TIME;
    _boomKey = AnimationKey::BOOM_TIME_BOMB_KEY;
    this->setOnAnimationFinishCallback([this](int animId)
    {
        if (animId == 0)
        {
            this->destroy();
        }
    });
    return true;
}

void BomTime::animUpdate(unsigned int currentLoop)
{
    auto deltaLoop = currentLoop - _animationStartLoop;
    
    auto loadedFrame = deltaLoop/_animation->getAnimSpeed(); //số lượng frame đã chạy kể từ startLoop
    
    int currentFrame = loadedFrame % _animation->getTotalFrame(); //frame hiện tại trong animation
    
    if (_animation->getRepeatTime() > 0 &&
        loadedFrame >= _animation->getTotalFrame()*_animation->getRepeatTime())
    {
        if (_animationFinishCallback)
        {
            _animationFinishCallback(_animation->getId());
            return;
        }
    }
    
    if (_currentFrame != currentFrame)
    {
        
        
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_DYNAMITE_2);
#else
        AUDIO::play2d(EFFECT_DYNAMITE_2, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        auto spriteFrame = this->getSpriteFrameByKey(_key.type, _key.id, _key.level, _animation->getId(), currentFrame, _baseDir);
        this->setSpriteFrame(spriteFrame);
        _currentFrame = currentFrame;
    }
}

void BomTime::inputUpdate()
{
    if (_isPushed) // đẩy đá
    {
        float pushSpeed = MainGameScene::getInstance()->getPlayer()->getSpeed();
        float temp = _speed;
        _speed = pushSpeed*0.5f;
        this->move(_dirPushed, sPushed);
        _speed = temp;
        _isPushed = false;
        return;
    }
    if (_actPool.empty())
    {
        this->stop();
    }
}

void BomTime::onDestroyObject()
{
    Vec2 p = this->getMatrixPos();
    std::vector<Vec2> pos;
    pos.push_back(Vec2(p.x, p.y));
    pos.push_back(Vec2(p.x + 1, p.y));
    pos.push_back(Vec2(p.x + 1, p.y + 1));
    pos.push_back(Vec2(p.x, p.y + 1));
    pos.push_back(Vec2(p.x - 1, p.y + 1));
    pos.push_back(Vec2(p.x - 1, p.y));
    pos.push_back(Vec2(p.x - 1, p.y - 1));
    pos.push_back(Vec2(p.x, p.y - 1));
    pos.push_back(Vec2(p.x + 1, p.y - 1));
    
    pos.push_back(Vec2(p.x, p.y + 2));
    pos.push_back(Vec2(p.x, p.y - 2));
    pos.push_back(Vec2(p.x + 2, p.y));
    pos.push_back(Vec2(p.x - 2, p.y));
    
    BigBang* bg = BigBang::create();
    bg->setup(pos, _boomKey);
}

bool BomTime::isMovable(int dir)
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

int BomTime::stateToAnimation(State state) const
{
    switch (state)
    {
        case sIdle:
            return 0;
        case sPushed:
            return 0;
        default:
            return -1;
    }
}