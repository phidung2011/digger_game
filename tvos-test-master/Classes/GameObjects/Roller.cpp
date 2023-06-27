//
//  Roller.cpp
//  gamebase
//
//  Created by Phi Dzung on 7/13/15.
//
//

#include "Roller.h"
#include "MainGameScene.h"
#include "GameConfig.h"
#include "BomFire.h"
#include "AvatarConfig.h"
#include "CShading.h"

Roller::Roller()
{
    
}
Roller::~Roller()
{
    
}

bool Roller::init()
{
    if (!BaseCharacter::initWithKey(AnimationKey::ROLLER_KEY) || !BaseCharacter::init())
    {
        return false;
    }
    _speed = 2.0f;
    _idTile = (int)IDTILE::CHARACTER;
    
//    auto shade = CShading::create(0.23f, 3);
//    this->runAction(shade);
    dirSkill = dt_right;
    
    movableDir.push_back(1);
    movableDir.push_back(2);
    movableDir.push_back(3);
    movableDir.push_back(4);
    
    return true;
}

bool Roller::isMovable(int dir)
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

int Roller::getMove()
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
            movableDir.erase(iter);
            return getMove();
        }
    }
    return INVALID_TAG;
}

void Roller::inputUpdate()
{
    
    //execute control
    if (_actPool.empty())
    {

        int rd = random(1, 4);
        
        if (rd > 2)
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

void Roller::resetMove()
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
