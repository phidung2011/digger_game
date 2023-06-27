//
//  Tanker.cpp
//  gamebase
//
//  Created by Phi Dzung on 7/8/15.
//
//

#include "Tanker.h"
#include <MainGameScene.h>
#include <GameConfig.h>
#include <BomFire.h>
#include "AvatarConfig.h"

Tanker::Tanker()
{
    
}
Tanker::~Tanker()
{
    
}

bool Tanker::init()
{
    if (!BaseCharacter::initWithKey(AnimationKey::TANKER_KEY) || !BaseCharacter::init())
    {
        return false;
    }
    _speed = 1.7f;
    _idTile = (int)IDTILE::CHARACTER;
    
    
    dirSkill = dt_right;
    movableDir.push_back(1);
    movableDir.push_back(2);
    movableDir.push_back(3);
    movableDir.push_back(4);
    return true;
}

int Tanker::getMove()
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

void Tanker::inputUpdate()
{
    
    //execute control
    if (_actPool.empty())
    {

        if (lookingForPlayer() && !MainGameScene::getInstance()->getPlayer()->isDead && isFirable())
        {
            this->fire();
        }
        
        
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
                if (isMovable(dirSkill))
                {
                    this->flip(dirSkill);
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
        else
        {
            if (isMovable(dirSkill))
            {
                this->flip(dirSkill);
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
}

void Tanker::fire()
{
    auto pos = Vec2::ZERO;
    switch (dirSkill) {
        case dt_top:
            pos = Vec2(0,TILE_SIZE);
            break;
        case dt_left:
            pos = Vec2(-TILE_SIZE,0);
            break;
        case dt_bot:
            pos = Vec2(0,-TILE_SIZE);
            break;
        case dt_right:
            pos = Vec2(TILE_SIZE,0);
            break;
        default:
            break;
    }
    BomFire* bom = BomFire::createWithDir(dirSkill);
    bom->setOwner(this);
    bom->setPosition(this->getPosition() + pos);
    MainGameScene::getInstance()->addObject(bom);
}

void Tanker::resetMove()
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

bool Tanker::lookingForPlayer()
{
    auto player = MainGameScene::getInstance()->getPlayer();
    _frontDir = dirSkill;
    auto playerPos = player->getFrontMatrixPosition();
    auto thisPos = this->getFrontMatrixPosition();
    
    if (_baseDir == 0) {
        if (playerPos.y == thisPos.y)
        {
            switch (dirSkill)
            {
                case dt_left:
                    if (playerPos.x < thisPos.x - 1)
                    {
                        bool check = true;
                        for (int i = 1; i < thisPos.x - playerPos.x; i++)
                        {
                            auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(Vec2(thisPos.x - i,thisPos.y));
                            if (tile != IDTILE::DEFAULT)
                            {
                                if (tile == IDTILE::PLAYER || tile == IDTILE::MARKED_PLAYER)
                                {
                                }
                                else
                                    check = false;
                            }
                        }
                        return check;
                    }
                    else return false;
                    break;
                case dt_right:
                    if (playerPos.x > thisPos.x + 1)
                    {
                        bool check = true;
                        for (int i = 1; i < playerPos.x - thisPos.x; i++)
                        {
                            auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(Vec2(thisPos.x + i,thisPos.y));
                            if (tile != IDTILE::DEFAULT)
                            {
                                if (tile == IDTILE::PLAYER || tile == IDTILE::MARKED_PLAYER)
                                {
                                }
                                else
                                    check = false;
                            }
                        }
                        return check;
                    }
                    else return false;
                    break;
                default:
                    break;
            }
        }
        else
            return false;
    }
    
    
    
    if (_baseDir == 1) {
        if (playerPos.x == thisPos.x)
        {
            switch (dirSkill)
            {
                case dt_top:
                    if (playerPos.y < thisPos.y - 1)
                    {
                        bool check = true;
                        for (int i = 1; i < thisPos.y - playerPos.y; i++)
                        {
                            auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(Vec2(thisPos.x,thisPos.y - i));
                            if (tile != IDTILE::DEFAULT)
                            {
                                if (tile == IDTILE::PLAYER || tile == IDTILE::MARKED_PLAYER)
                                {
                                }
                                else
                                    check = false;
                            }
                        }
                        return check;
                    }
                    else return false;
                    break;
                case dt_bot:
                    if (playerPos.y > thisPos.y + 1)
                    {
                        bool check = true;
                        for (int i = 1; i < playerPos.y - thisPos.y; i++)
                        {
                            auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(Vec2(thisPos.x,thisPos.y + i));
                            if (tile != IDTILE::DEFAULT)
                            {
                                if (tile == IDTILE::PLAYER || tile == IDTILE::MARKED_PLAYER)
                                {
                                }
                                else
                                    check = false;
                            }
                        }
                        return check;
                    }
                    else return false;
                    break;
                default:
                    break;
            }
        }
        else
            return false;
    }
    
    return false;
}


