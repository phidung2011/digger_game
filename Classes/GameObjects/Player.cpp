//
//  Player.cpp
//  rectdemo
//
//  Created by Nguyễn Lê Lợi on 6/2/15.
//
//

#include "Player.h"
#include "MainGameScene.h"
#include "GameConfig.h"
#include "DroppingObject.h"
#include "DataManager.h"
#include "AvatarConfig.h"
#include "BumBum.h"
#include "CFreezeEffect.h"
#include "EffectDrill.h"
USING_NS_CC;
Player::Player()
: isDead(false)
{
    
}
Player::~Player()
{
    
}
bool Player::init()
{
    if (!BaseCharacter::init() || !BaseCharacter::initWithKey(AnimationKey::PLAYER_KEY))
    {
        return false;
    }
    _speed = 3.3;
    _totalScore = 0;
    _idTile = (int)IDTILE::PLAYER;
    
    _timePlay = 0;
    _totalGrassDiamond = 0;
    
    _maxHp = 3;
    _currentHp = 3;
    dirSkill = dt_right;
    _objectPushing = NULL;
    
//    _data = MapData(1, 100, 0, 1000, 10, 10, 10, 10);
    _data = DATA_MGR->getMapDataAtLevel((int)MainGameScene::getInstance()->getLand(),MainGameScene::getInstance()->getLevelMap()) + MainGameScene::getInstance()->getBonusPackage();
    
    MainGameScene::getInstance()->getTileMap()->setTotalScoreFull(MainGameScene::getInstance()->getTileMap()->getTotalScoreFull() + (_data.bombs + _data.mines + _data.rockets + _data.time_bombs)*(int)SCORE::BONUS_BOMB + _data.time*(int)SCORE::BONUS_TIME);
    
    CCLOG("----- total score full %d", MainGameScene::getInstance()->getTileMap()->getTotalScoreFull());
    _isImmortal = false;
    _immortalTime = 10;
    return true;
}

bool Player::destroy()
{
    if (!MainGameScene::getInstance()->GAME_OVER) {
        _objectPushing = NULL;
        
        if (!_isImmortal)
        {
            _currentHp--;
            MainGameScene::getInstance()->getMenuBar()->getLabelPlayerLives()->setString(StringUtils::format("%d", _currentHp));
            if (_currentHp > 0)
            {
                _isImmortal = true;
            }
            else
            {
                isDead = true;
                this->pauseUpdate();
                MainGameScene::getInstance()->setGameOver();
                this->setVisible(false);
                _eventDispatcher->setEnabled(false);
                MainGameScene::getInstance()->getControl()->getAnalog()->setEnabled(false);
            }
        }
        
        this->stop();
        this->resetPos();
        onDestroyObject();
    }
    return _isValid;
}

void Player::onDestroyObject()
{
    BaseBomb::onDestroyObject();
}

void Player::inputUpdate()
{
    if (_actPool.empty())
    {
        this->stop();
    }
}

bool Player::updateTile(cocos2d::Vec2 nextPos)
{
    auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(nextPos);
    switch (tile) {
        case IDTILE::GRASS_DIAMOND:
        {
            _totalScore += (int)SCORE::GRASS_DIAMOND;
            _totalGrassDiamond++;
            updateScore();
            MainGameScene::getInstance()->getTileMap()->setIdTile(nextPos, _idTile);
            auto land = MainGameScene::getInstance()->getLand();
            
            auto effect = EffectDrill::createWithKey(AnimationKey(ObjectKey::EFFECT_LAND_KEY,(int)land));
            effect->playAnim(dirSkill - 1);
            
            auto mapPos = ConvertUtils::convertCDMatrixtoMap(nextPos, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
            
            effect->setPosition(mapPos);
            MainGameScene::getInstance()->addObject(effect,-1);
            
            
            if (land == LAND::PLAIN)
            {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_DIG_1);
#else
                AUDIO::play2d(EFFECT_DIG_1, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
            else if (land == LAND::GRASS_LAND)
            {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_DIG_2);
#else
                AUDIO::play2d(EFFECT_DIG_2, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
            else
            {
                int rd = random(1, 2);
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(StringUtils::format(EFFECT_DIG_SNOW, rd).c_str());
#else
                AUDIO::play2d(StringUtils::format(EFFECT_DIG_SNOW, rd).c_str(), false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
            
        }
            return true;
        case IDTILE::GRASS:
        {
            MainGameScene::getInstance()->getTileMap()->setIdTile(nextPos, _idTile);
            auto land = MainGameScene::getInstance()->getLand();
            
            auto effect = EffectDrill::createWithKey(AnimationKey(ObjectKey::EFFECT_LAND_KEY,(int)land));
            effect->playAnim(dirSkill - 1);
            
            auto mapPos = ConvertUtils::convertCDMatrixtoMap(nextPos, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
            
            effect->setPosition(mapPos);
            MainGameScene::getInstance()->addObject(effect,-1);
            
            if (land == LAND::PLAIN)
            {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_DIG_1);
#else
                AUDIO::play2d(EFFECT_DIG_1, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
            else if (land == LAND::GRASS_LAND)
            {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_DIG_2);
#else
                AUDIO::play2d(EFFECT_DIG_2, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
            else
            {
                int rd = random(1, 2);
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(StringUtils::format(EFFECT_DIG_SNOW, rd).c_str());
#else
                AUDIO::play2d(StringUtils::format(EFFECT_DIG_SNOW, rd).c_str(), false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
        }
            return true;
        case IDTILE::DEFAULT:
            MainGameScene::getInstance()->getTileMap()->setIdTile(nextPos, _idTile);
            return true;
        default:
            return false;
    }
    return true;
}

void Player::executeControl(int dir)
{
    if (_actPool.empty())
    {
        this->flip(dir);
        if (_data.fuel >= 0.12 && isMovable(dir))
        {
            if (_objectPushing)
            {
                float temp = _speed;
                _speed = 0.5*temp;
                this->move(dir, sPushing);
                _speed = temp;
                _objectPushing->setPush(dir);
                _objectPushing = NULL;
            }
            else
                this->move(dir, sMoving);
        }
    }
}

bool Player::isMovable(int dir)
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
        case 0:
            return false;
        default:
            break;
    }
    
    Vec2 posMatrix = ConvertUtils::convertCDMaptoMatrix(pos, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
    
    auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(posMatrix);
    
    if (tile == IDTILE::WALL_HARD ||
        tile == IDTILE::BOOM_BOMB ||
        tile == IDTILE::MARKED_ITEM ||
        tile == IDTILE::WALL_SOFT)
    {
        return false;
    }
    
    
    if (tile == IDTILE::STONE)
    {
        if (dir == dt_left || dir == dt_right)
        {
            auto objectPool = MainGameScene::getInstance()->getObjectPool();
            for (auto& object : objectPool[ObjectKey::STONE_KEY.index])
            {
                if (object->getState() == sIdle || object->getState() == sPushed)
                {
                    auto stone = (DroppingObject*)object;
                    auto deltaRect = this->getCollisionBound();
                    auto delta = Vec2::ZERO;
                    
                    if (dir == dt_left)
                        delta = Vec2(-_speed,0);
                    else
                        delta = Vec2(_speed,0);
                    
                    deltaRect.origin = deltaRect.origin + delta;
                    
                    if (deltaRect.intersectsRect(stone->getCollisionBound()))
                    {
                        if (!stone->isMovable(dt_bot) && stone->isMovable(dir))
                        {
                            _objectPushing = stone;
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        return false;
    }
    
    if (tile == IDTILE::BOMB_DROP)
    {
        if (dir == dt_left || dir == dt_right)
        {
            auto objectPool = MainGameScene::getInstance()->getObjectPool();
            for (auto& object : objectPool[ObjectKey::BOMB_DROP_KEY.index])
            {
                if (object->getActionPool().empty())
                {
                    auto stone = (DroppingObject*)object;
                    auto deltaRect = this->getCollisionBound();
                    auto delta = Vec2::ZERO;
                    
                    if (dir == dt_left)
                        delta = Vec2(-_speed,0);
                    else
                        delta = Vec2(_speed,0);
                    
                    deltaRect.origin = deltaRect.origin + delta;
                    
                    if (deltaRect.intersectsRect(stone->getCollisionBound()))
                    {
                        if (!stone->isMovable(dt_bot) && stone->isMovable(dir))
                        {
                            _objectPushing = stone;
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        return false;
    }
    
    if (tile == IDTILE::BOX_GOLD)
    {
        if (dir == dt_left || dir == dt_right)
        {
            auto objectPool = MainGameScene::getInstance()->getObjectPool();
            for (auto& object : objectPool[ObjectKey::BOX_GOLD_KEY.index])
            {
                if (object->getActionPool().empty())
                {
                    auto stone = (DroppingObject*)object;
                    auto deltaRect = this->getCollisionBound();
                    auto delta = Vec2::ZERO;
                    
                    if (dir == dt_left)
                        delta = Vec2(-_speed,0);
                    else
                        delta = Vec2(_speed,0);
                    
                    deltaRect.origin = deltaRect.origin + delta;
                    
                    if (deltaRect.intersectsRect(stone->getCollisionBound()))
                    {
                        if (!stone->isMovable(dt_bot) && stone->isMovable(dir))
                        {
                            _objectPushing = stone;
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        return false;
    }
    
    
    if (tile == IDTILE::BOMB_TIME)
    {
        auto objectPool = MainGameScene::getInstance()->getObjectPool();
        for (auto& object : objectPool[ObjectKey::BOMB_TIME_KEY.index])
        {
            if (object->getActionPool().empty())
            {
                auto stone = (DroppingObject*)object;
                auto deltaRect = this->getCollisionBound();
                auto delta = Vec2::ZERO;
                
                switch (dir)
                {
                    case dt_left:
                        delta = Vec2(-_speed,0);
                        break;
                    case dt_right:
                        delta = Vec2(_speed,0);
                        break;
                    case dt_top:
                        delta = Vec2(0,_speed);
                        break;
                    case dt_bot:
                        delta = Vec2(0,-_speed);
                        break;
                }
                deltaRect.origin = deltaRect.origin + delta;
                
                if (deltaRect.intersectsRect(stone->getCollisionBound()))
                {
                    if (stone->isMovable(dir))
                    {
                        _objectPushing = stone;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    return true;
}

void  Player::updateScore(){
    MainGameScene::getInstance()->getMenuBar()->getLabelScore()->setString(StringUtils::format("%d",_totalScore));
}

void Player::collectItem(DataObject* item)
{
    auto itemId = (IDITEM)item->getKey().id;
    switch (itemId)
    {
        case IDITEM::DIAMOND:
        {
            if (_data.diamonds > 0)
            {
                _data.diamonds--;
                

                MainGameScene::getInstance()->getMenuBar()->getLabelDiamonds()->setString(StringUtils::format("%d",_data.diamonds));
                if (_data.enemies == 0 && _data.diamonds == 0)
                {
                    MainGameScene::getInstance()->SHOW_NEXT_STAGE_DOOR = true;
                }
            }
            int dmLevel = item->getKey().level;
            switch (dmLevel) {
                case 1:
                    _totalScore += (int)SCORE::DIAMOND_1;
                    break;
                case 2:
                    _totalScore += (int)SCORE::DIAMOND_2;
                    break;
                case 3:
                    _totalScore += (int)SCORE::DIAMOND_3;
                    break;
            }
            int rd = random(1, 2);
            if (rd == 1) {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_GEM_2);
#else
                AUDIO::play2d(EFFECT_GEM_2, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
            else
            {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_GEM_3);
#else
                AUDIO::play2d(EFFECT_GEM_3, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
            _bonusScore.diamonds++;
        }
            break;
        case IDITEM::GOLD:
            _totalScore += (int)SCORE::BOX_GOLD;
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_GET_ITEM_6);
#else
            AUDIO::play2d(EFFECT_GET_ITEM_6, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            break;
        case IDITEM::FUEL:
            _data.fuel += 40;
            if (_data.fuel > 100)
            {
                _data.fuel = 100;
            }
            MainGameScene::getInstance()->getMenuBar()->getProgressBarFuel()->setValue(_data.fuel);
            _totalScore += (int)SCORE::FUEL;
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_GET_ITEM_2);
#else
            AUDIO::play2d(EFFECT_GET_ITEM_2, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            break;
        case IDITEM::BOX_BOMB_DROP:
            _data.bombs += 3;
            MainGameScene::getInstance()->getSkillLayer()->updateSkill();
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_GET_ITEM_3);
#else
            AUDIO::play2d(EFFECT_GET_ITEM_3, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            break;
        case IDITEM::BOX_BOMB_FIRE:
            _data.rockets += 3;
            MainGameScene::getInstance()->getSkillLayer()->updateSkill();
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_GET_ITEM_4);
#else
            AUDIO::play2d(EFFECT_GET_ITEM_4, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            break;
        case IDITEM::BOX_BOMB_SPIKE:
            _data.mines += 3;
            MainGameScene::getInstance()->getSkillLayer()->updateSkill();
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_GET_ITEM_3);
#else
            AUDIO::play2d(EFFECT_GET_ITEM_3, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            break;
        case IDITEM::BOX_BOMB_TIME:
            _data.time_bombs += 3;
            MainGameScene::getInstance()->getSkillLayer()->updateSkill();
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_GET_ITEM_3);
#else
            AUDIO::play2d(EFFECT_GET_ITEM_3, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            break;
        case IDITEM::SNOW_FLAKE:
        {
            auto map = MainGameScene::getInstance()->getObjectPool();
            for (auto i = 0; i < 25; i++)
            {
                for (auto &object : map[i])
                {
                    if (object && object->getKey().type == "CHAR")
                    {
                        object->addEffect(CFreezeEffect::create(300));
                    }
                }
            }
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_GET_ITEM_1);
#else
            AUDIO::play2d(EFFECT_GET_ITEM_1, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            break;
        }
        case IDITEM::HP_UP:
        {
            _currentHp++;
            MainGameScene::getInstance()->getMenuBar()->getLabelPlayerLives()->setString(StringUtils::format("%d", _currentHp));
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_GET_ITEM_5);
#else
            AUDIO::play2d(EFFECT_GET_ITEM_5, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        }
            break;
        case IDITEM::NEXT_STAGE_DOOR:
            MainGameScene::getInstance()->setGameWin();
            
            return;
            break;
        default:
            break;
    }
    updateScore();
    item->destroy();
//    MainGameScene::getInstance()->getObjectPool()[item->getKey().index].eraseObject(item);
}

bool Player::worldUpdate()
{
    if (_isImmortal && _immortalTime > 0)
    {
        _immortalTime--;
        if (_immortalTime == 0)
        {
            _isImmortal = false;
            _immortalTime = 10;
        }
    }
//    CCLOG("-----speed player: %f ", _speed);
    auto frontPos = this->getFrontMatrixPosition();
    auto tileNext = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos);
    auto mapPos = ConvertUtils::convertCDMatrixtoMap(frontPos, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
    
    if (tileNext == IDTILE::DEFAULT)
    {
        MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::PLAYER);
    }
    
    if (!_actPool.empty())
    {
        if (_isCollisionOnMap)
        {
            auto rect = Rect(mapPos.x - 0.5*TILE_SIZE + EX, mapPos.y - 0.5*TILE_SIZE + EX, TILE_SIZE - 2*EX, TILE_SIZE - 2*EX);
            switch (tileNext)
            {
                case IDTILE::DIAMOND:
                {
//                    auto pool = MainGameScene::getInstance()->getObjectPool()[ObjectKey::DIAMOND_KEY.index];
                    
                    for (auto&object : MainGameScene::getInstance()->getObjectPool()[ObjectKey::DIAMOND_KEY.index])
                    {
                        if (object->getCollisionBound().intersectsRect(rect))
                        {
                            this->collectItem(object);
                            break;
                        }
                    }
                }
                    
                    break;
                case IDTILE::GOLD:
                    for (auto&object : MainGameScene::getInstance()->getObjectPool()[ObjectKey::GOLD_KEY.index])
                    {
                        if (object->getCollisionBound().intersectsRect(rect))
                        {
                            this->collectItem(object);
                            break;
                        }
                    }
                    break;
                case IDTILE::HP_UP:
                    for (auto&object : MainGameScene::getInstance()->getObjectPool()[ObjectKey::HP_UP_KEY.index])
                    {
                        if (object->getCollisionBound().intersectsRect(rect))
                        {
                            this->collectItem(object);
                            break;
                        }
                    }
                    break;
                case IDTILE::SNOW_FLAKE:
                    for (auto&object : MainGameScene::getInstance()->getObjectPool()[ObjectKey::SNOW_FLAKE_KEY.index])
                    {
                        if (object->getCollisionBound().intersectsRect(rect))
                        {
                            this->collectItem(object);
                            break;
                        }
                    }
                    break;
                case IDTILE::FUEL:
                    for (auto&object : MainGameScene::getInstance()->getObjectPool()[ObjectKey::FUEL_KEY.index])
                    {
                        if (object->getCollisionBound().intersectsRect(rect))
                        {
                            this->collectItem(object);
                            break;
                        }
                    }
                    break;
                case IDTILE::BOX_BOMB_DROP:
                    for (auto&object : MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOX_BOMB_DROP_KEY.index])
                    {
                        if (object->getCollisionBound().intersectsRect(rect))
                        {
                            this->collectItem(object);
                            break;
                        }
                    }
                    break;
                case IDTILE::BOX_BOMB_FIRE:
                    for (auto&object : MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOX_BOMB_FIRE_KEY.index])
                    {
                        if (object->getCollisionBound().intersectsRect(rect))
                        {
                            this->collectItem(object);
                            break;
                        }
                    }
                    break;
                case IDTILE::BOX_BOMB_SPIKE:
                    for (auto&object : MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOX_BOMB_SPIKE_KEY.index])
                    {
                        if (object->getCollisionBound().intersectsRect(rect))
                        {
                            this->collectItem(object);
                            break;
                        }
                    }
                    break;
                case IDTILE::BOX_BOMB_TIME:
                    for (auto&object : MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOX_BOMB_TIME_KEY.index])
                    {
                        if (object->getCollisionBound().intersectsRect(rect))
                        {
                            this->collectItem(object);
                            break;
                        }
                    }
                    break;
                case IDTILE::BOMB_SPIKES:
                case IDTILE::CHARACTER:
                    this->destroy();
                    break;
                case IDTILE::MARKED_CHARACTER:
                    if ( _frontDir == dt_bot ||  _frontDir == dt_top)
                    {
                        auto tileRight = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(1,0));
                        auto tileLeft = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(-1,0));
                        if (tileRight == IDTILE::CHARACTER || tileLeft == IDTILE::CHARACTER)
                        {
                            this->destroy();
                            break;
                        }
                        else
                        {
                            MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::PLAYER);
                        }
                    }
                    
                    if ( _frontDir == dt_left ||  _frontDir == dt_right)
                    {
                        auto tileTop = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(0,-1));
                        auto tileBot = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(0,1));
                        if (tileTop == IDTILE::CHARACTER || tileBot == IDTILE::CHARACTER)
                        {
                            this->destroy();
                            break;
                        }
                        else
                        {
                            MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::PLAYER);
                        }
                    }
                    break;
                    
                case IDTILE::NEXT_STAGE_DOOR :
                    for (auto&object : MainGameScene::getInstance()->getObjectPool()[ObjectKey::NEXT_STAGE_DOOR_KEY.index])
                    {
                        if (object->getCollisionBound().intersectsRect(rect))
                        {
                            this->collectItem(object);
                            break;
                        }
                    }
                    break;
                default:
                    break;
            }
            if ((IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos) != IDTILE::BOOM_BOMB)
            {
                MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, _idTile);
            }
            _isCollisionOnMap = false;
        }
    }
    return _isValid;
}

void Player::move(int dir, State state)
{
    Vec2 vector = Vec2::ZERO;
    Vec2 matrixVector = Vec2::ZERO;
    _frontDir = dir;
    dirSkill = dir;
    int totalLoop = TILE_SIZE/_speed;
    this->setState(state);
    switch (dir)
    {
        case dt_top:
        {
            vector = Vec2(0,TILE_SIZE);
            matrixVector = Vec2(0,-1);
            _backDir = dt_bot;
            break;
        }
        case dt_left:
        {
            vector = Vec2(-TILE_SIZE,0);
            matrixVector = Vec2(-1,0);
            _backDir = dt_right;
            break;
        }
        case dt_right:
        {
            vector = Vec2(TILE_SIZE,0);
            matrixVector = Vec2(1,0);
            _backDir = dt_left;
            break;
        }
        case dt_bot:
        {
            vector = Vec2(0,-TILE_SIZE);
            matrixVector = Vec2(0,1);
            _backDir = dt_top;
            break;
        }
    }
    CMoveBy* move = CMoveBy::create(vector, totalLoop);
    Vec2 prevPos = this->getMatrixPos();
    MainGameScene::getInstance()->getTileMap()->setIdTile(prevPos, (int)IDTILE::MARKED_PLAYER);
    
    auto call = CCallback::create([prevPos, this]()
                                  {
                                      if (MainGameScene::getInstance()->getTileMap()->getIdTile(prevPos) == (int)IDTILE::MARKED_PLAYER)
                                      {
                                          MainGameScene::getInstance()->getTileMap()->setIdTile(prevPos,(int)IDTILE::DEFAULT);
                                      }
                                  });
    auto seq = CSequence::create(call, move, NULL);
    this->runAct(seq);
    _isCollisionOnMap = !this->updateTile(prevPos + matrixVector);
    _data.fuel -= 0.12;
    MainGameScene::getInstance()->getMenuBar()->getProgressBarFuel()->setValue(_data.fuel);
}

int Player::stateToAnimation(State state) const
{
    switch (state)
    {
        case sIdle:
            return 0;
        case sPushing:
            return 1;
        case sMoving:
            return 1;
        default:
            return -1;
    }
}
