//
//  Tracker.cpp
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 7/9/15.
//
//

#include "Tracker.h"
#include <MainGameScene.h>
#include <GameConfig.h>
#include <AStar.h>
#include "AvatarConfig.h"
USING_NS_CC;
Tracker::Tracker()
{
    
}
Tracker::~Tracker()
{
    
}

bool Tracker::init()
{
    if (!BaseCharacter::initWithKey(AnimationKey::TRACKER_KEY) || !BaseCharacter::init())
    {
        return false;
    }
    _speed = 2.3;
    _idTile = (int)IDTILE::CHARACTER;
    _range = 5;
    
    dirSkill = dt_right;
    
    movableDir.push_back(1);
    movableDir.push_back(2);
    movableDir.push_back(3);
    movableDir.push_back(4);
    
    return true;
}

int Tracker::getMove()
{
    if (!movableDir.empty())
    {
        int maxIndex = (int)movableDir.size()-1;
        int rdIndex = random(0, maxIndex);
        int rd = movableDir.at(rdIndex);
        
        if (isMovable(rd))
        {
            if (rd != _backDir)
            {
                return rd;
            }
            else if (rd == _backDir && movableDir.size() == 1)
            {
                return rd;
            }
            else
                return getMove();
        }
        else
        {
            auto iter = std::find(movableDir.begin(), movableDir.end(), rd);
            //            if (iter != movableDir.end())
            //            {
            movableDir.erase(iter);
            //            }
            return getMove();
        }
    }
    return INVALID_TAG;
}
bool Tracker::isMovable(int dir)
{
    Vec2 pos = this->getMatrixPos();
    switch (dir)
    {
        case dt_top:
            pos = pos + Vec2(0,-1);
            break;
            
        case dt_bot:
            pos = pos + Vec2(0,1);
            break;
            
        case dt_left:
            pos = pos + Vec2(-1,0);
            break;
            
        case dt_right:
            pos = pos + Vec2(1,0);
            break;
        case 0:
            return false;
        default:
            break;
    }
    
    auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(pos);
    
    if (tile == IDTILE::DEFAULT)
    {
        return true;
    }
    
    if (_state == sMoving &&
        (tile == IDTILE::PLAYER ||
         tile == IDTILE::MARKED_PLAYER))
    {
        return true;
    }
    
    return false;
}

void Tracker::inputUpdate()
{
    //execute control
    if (_actPool.empty())
    {
        if (AStar::getEuclideDistance(this->getMatrixPos(), MainGameScene::getInstance()->getPlayer()->getMatrixPos()) <= _range)
        {
            auto vec = AStar::calculatePath(this->getMatrixPos(), MainGameScene::getInstance()->getPlayer()->getMatrixPos(), _range);
            if (!vec.empty())
            {
                auto fPos = vec.back()->_pos;
                vec.popBack();
                auto sPos = vec.back()->_pos;
                auto delta = sPos - fPos;
                if (delta == Vec2(0,1))
                {
                    if (isMovable(dt_bot))
                    {
                        this->flip(dt_bot);
                        this->move(dt_bot, sMoving);
                    }
                    else
                        stop();
                }
                else if (delta == Vec2(0,-1))
                {
                    if (isMovable(dt_top))
                    {
                        this->flip(dt_top);
                        this->move(dt_top, sMoving);
                    }
                    else
                        stop();
                }
                else if (delta == Vec2(1,0))
                {
                    if (isMovable(dt_right))
                    {
                        this->flip(dt_right);
                        this->move(dt_right, sMoving);
                    }
                    else
                        stop();
                }
                else
                {
                    if (isMovable(dt_left))
                    {
                        this->flip(dt_left);
                        this->move(dt_left, sMoving);
                    }
                    else
                        stop();
                }
                vec.clear();
            }
            else
            {
                int rd = random(1, 4);
                
                if (rd > 3)
                {
                    int rdDir = random(1, 4);
                    
                    if (isMovable(rdDir) && rdDir !=  _frontDir && rdDir != _backDir)
                    {
                        this->flip(rdDir);
                        this->move(rdDir, sMoving);
                    }
                    else
                    {
                        if (isMovable( _frontDir))
                        {
                            this->flip( _frontDir);
                            this->move( _frontDir, sMoving);
                        }
                        else
                        {
                            auto getMove = this->getMove();
                            if (getMove != INVALID_TAG)
                            {
                                this->flip(getMove);
                                this->move(getMove, sMoving);
                            }
                            resetMove();
                        }
                    }
                }
                else
                {
                    if (isMovable( _frontDir))
                    {
                        this->flip( _frontDir);
                        this->move( _frontDir, sMoving);
                    }
                    else
                    {
                        auto getMove = this->getMove();
                        if (getMove != INVALID_TAG)
                        {
                            this->flip(getMove);
                            this->move(getMove, sMoving);
                        }
                        resetMove();
                    }
                }
            }
        }
        else
        {
            int rd = random(1, 4);
            
            if (rd > 3)
            {
                int rdDir = random(1, 4);
                
                if (isMovable(rdDir) && rdDir !=  _frontDir && rdDir != _backDir)
                {
                    this->flip(rdDir);
                    this->move(rdDir, sMoving);
                }
                else
                {
                    if (isMovable( _frontDir))
                    {
                        this->flip( _frontDir);
                        this->move( _frontDir, sMoving);
                    }
                    else
                    {
                        auto getMove = this->getMove();
                        if (getMove != INVALID_TAG)
                        {
                            this->flip(getMove);
                            this->move(getMove, sMoving);
                        }
                        resetMove();
                    }
                }
            }
            else
            {
                if (isMovable( _frontDir))
                {
                    this->flip( _frontDir);
                    this->move( _frontDir, sMoving);
                }
                else
                {
                    auto getMove = this->getMove();
                    if (getMove != INVALID_TAG)
                    {
                        this->flip(getMove);
                        this->move(getMove, sMoving);
                    }
                    resetMove();
                }
            }
        }
    }
}

void Tracker::resetMove()
{
    if (!movableDir.empty())
    {
        movableDir.clear();
    }
    movableDir.push_back(1);
    movableDir.push_back(2);
    movableDir.push_back(3);
    movableDir.push_back(4);
}
