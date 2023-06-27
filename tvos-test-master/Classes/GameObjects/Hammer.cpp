//
//  Hammer.cpp
//  gamebase
//
//  Created by Phi Dzung on 6/30/15.
//
//

#include "Hammer.h"
#include "MainGameScene.h"
#include "GameConfig.h"
#include "AvatarConfig.h"
USING_NS_CC;
Hammer::Hammer()
{
    
}
Hammer::~Hammer()
{
    
}

bool Hammer::init()
{
    if (!BaseCharacter::initWithKey(AnimationKey::HAMMER_KEY) || !BaseCharacter::init())
    {
        return false;
    }
    _speed = 2.4;
    _idTile = (int)IDTILE::CHARACTER;
    
    dirSkill = dt_right;
    
    movableDir.push_back(1);
    movableDir.push_back(2);
    movableDir.push_back(3);
    movableDir.push_back(4);
    
    return true;
}

int Hammer::getMove()
{
    if (!movableDir.empty())
    {
        int maxIndex = movableDir.size()-1;
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


void Hammer::inputUpdate()
{
    //execute control
    if (_actPool.empty())
    {
        if (isMovable(dirSkill))
        {
            this->move(dirSkill, sMoving);
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


void Hammer::resetMove()
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


