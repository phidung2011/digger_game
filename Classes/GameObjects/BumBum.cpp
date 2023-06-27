//
//  BumBum.cpp
//  gamebase
//
//  Created by NGOCDIEP on 6/25/15.
//
//

#include "BumBum.h"
#include "MainGameScene.h"
#include "GameConfig.h"
#include "AvatarConfig.h"

BumBum::BumBum()
: _destroyedFlag(false)
{
    
}
BumBum::~BumBum()
{
    CCLOG("%s", __PRETTY_FUNCTION__);
}

BumBum* BumBum::createWithKey(AnimationKey key)
{
    BumBum* item = new (std::nothrow) BumBum;
    if (item && item->initWithKey(key))
    {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}

bool BumBum::initWithKey(AnimationKey key)
{
    if (!TiledObject::init() || !TiledObject::initWithKey(key))
    {
        return false;
    }
    _idTile = (int)IDTILE::BOOM_BOMB;
    
    this->setOnAnimationFinishCallback([this](int animId)
                                       {
                                           if (animId == 0)
                                           {
                                               this->destroy();
                                           }
                                       });
    
    _isValid = false;
     _frontDir = 0;
    return true;
}

void BumBum::boom()
{
    if (MainGameScene::getInstance()->getPlayer()->getCollisionBound().intersectsRect(this->getCollisionBound()))
    {
        MainGameScene::getInstance()->getPlayer()->destroy();
    }
    auto pools = MainGameScene::getInstance()->getObjectPool();
    for (auto i = 0; i < 25; i++)
    {
        if (i != _key.index)
        {
            for (auto itr = pools[i].begin(); itr != pools[i].end();)
            {
                if (this->getCollisionBound().intersectsRect((*itr)->getCollisionBound()))
                {
                    (*itr)->destroy();
                    itr = pools[i].erase(itr);
                }
                else
                    itr++;
            }
        }
    }
}

void BumBum::inputUpdate()
{

}

bool BumBum::worldUpdate()
{
    int totalLoop = this->getAnimation()->getTotalFrame()*this->getAnimation()->getAnimSpeed();
    if (MainGameScene::getInstance()->getCurrentMainLoop() - this->getAnimationStartLoop() == 0.4*totalLoop)
    {
        auto pos = this->getMatrixPos();
        //    auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(pos);
        MainGameScene::getInstance()->getTileMap()->setIdTile(pos,(int)IDTILE::DEFAULT);
    }
    
    if(!_destroyedFlag && MainGameScene::getInstance()->getCurrentMainLoop() - this->getAnimationStartLoop() == 1)
    {
        this->boom();
        _destroyedFlag = true;
    }
    
    return _isValid;
}


bool BumBum::destroy()
{
    if (!_isValid)
    {
        this->removeFromParentAndCleanup(false);
        MainGameScene::getInstance()->getReleasePool().pushBack(this);
        
        _isValid = true;
    }
    return _isValid;
}

//Class BigBang
BigBang::BigBang()
{
    
}
BigBang::~BigBang()
{
    
}
bool BigBang::init()
{
    return true;
}


void BigBang::loangBum(int m[5][5], int i, int j){
    
    
    //Add gia tri loang duoc vao list
    if(m[i][j] == 0){
        _listBum.push_back(Vec2(i,j));
        m[i][j] = 1;
    }
    
    //Loang 4 huong
    
    if(i - 1 >= 0 && m[i - 1][j] == 0)
        loangBum(m, i - 1, j);
    
    if(i + 1 < 5 && m[i + 1][j] == 0)
        loangBum(m, i + 1, j);
    
    if(j - 1 >= 0 && m[i][j - 1] == 0)
        loangBum(m, i, j - 1);
    
    if(j + 1 < 5 && m[i][j + 1] == 0)
        loangBum(m, i, j + 1);
}


void BigBang::setup(std::vector<cocos2d::Vec2> listPos, AnimationKey flag)
{
    if (!listPos.empty())
    {
        if (GameSingleton::getInstance()->_loopSound == 0) {
            if (flag == AnimationKey::BOOM_TIME_BOMB_KEY)
            {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_DYNAMITE_3);
#else
                AUDIO::play2d(EFFECT_DYNAMITE_3, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
            else if (flag == AnimationKey::BOOM_MINE_KEY)
            {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_ROCKET_2);
#else
                AUDIO::play2d(EFFECT_ROCKET_2, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
            else
            {
#if (USE_SIMPLE_AUDIO_ENGINE)
                SIMPLE_AUDIO->playEffect(EFFECT_BOMB_2);
#else
                AUDIO::play2d(EFFECT_BOMB_2, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
            }
            GameSingleton::getInstance()->_loopSound = 3;
        }
        int matrix[5][5] =
        {
            {1,1,1,1,1},
            {1,1,1,1,1},
            {1,1,1,1,1},
            {1,1,1,1,1},
            {1,1,1,1,1},
        };
        
        std::vector<Vec2> temp = listPos;
        auto rootPos = listPos.at(0);
        
        auto delta = rootPos - Vec2(2,2);
        
        
        for(auto i = 0; i < temp.size(); i++)
        {
            auto actualPos = temp.at(i);
            auto newPos = actualPos - delta;
            
            
            if (MainGameScene::getInstance()->getTileMap()->getIdTile(actualPos) != (int)IDTILE::WALL_HARD)
                matrix[(int)newPos.x][(int)newPos.y] = 0;
        }
        
        loangBum(matrix, 2, 2);
        
//        for(auto i = _listBum.begin(); i != _listBum.end(); i++)
//        {
//            log("%f  %f", i->x + delta.x, i->y + delta.y);
//        }
        
        
        if (!_listBum.empty()) {
            for(auto i = _listBum.begin(); i != _listBum.end(); i++)
            {
                auto itr = (*i);
                
                auto actualPos = itr + delta;
                
                if (actualPos.x < MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix.width &&
                    actualPos.y < MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix.height &&
                    actualPos.x > 0 &&
                    actualPos.y > 0)
                {
                    auto idTile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(actualPos);
                    switch (idTile)
                    {
                            //            case IDTILE::DIAMOND :
                            //            case IDTILE::DEFAULT :
                            //            case IDTILE::DEFAULT :
                            //            case IDTILE::GRASS :
                            //            case IDTILE::STONE :
                            //            case IDTILE::BOMB_DROP :
                            //            case IDTILE::BOMB_SPIKES :
                            //            case IDTILE::BOMB_TIME :
                            //            case IDTILE::CHARACTER :
                            //            case IDTILE::BOX_BOMB_DROP :
                            //            case IDTILE::BOX_BOMB_FIRE :
                            //            case IDTILE::BOX_GOLD :
                            //            case IDTILE::PLAYER :
                            //            case IDTILE::GRASS_DIAMOND :
                            //            case IDTILE::WALL_SOFT :
                            //            case IDTILE::MARKED_PLAYER:
                            //            case IDTILE::MARKED_CHARACTER:
                            //            case IDTILE::MARKED_ITEM:
                            //                break;
                        case IDTILE::WALL_HARD :
                        case IDTILE::BOOM_BOMB :
                        case IDTILE::NEXT_STAGE_DOOR :
                            break;
                        default:
                        {
                            BumBum* bum = BumBum::createWithKey(flag);
                            bum->setPosition(ConvertUtils::convertCDMatrixtoMap(actualPos, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix));
                            MainGameScene::getInstance()->getTileMap()->setIdTile(actualPos, (int)IDTILE::BOOM_BOMB);
                            MainGameScene::getInstance()->addObject(bum,999);
                            //                bum->boom();
                            
                            MainGameScene::getInstance()->shake();
                        }
                            break;
                            
                    }
                }
                
            }
        }
        
        
    }
}
