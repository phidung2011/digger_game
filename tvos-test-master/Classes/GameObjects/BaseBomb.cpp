//
//  BaseBomb.cpp
//  gamebase
//
//  Created by Phi Dzung on 6/30/15.
//
//

#include "BaseBomb.h"
#include <BumBum.h>
#include <GameConfig.h>
#include <MainGameScene.h>
#include "AvatarConfig.h"


void BaseBomb::onDestroyObject()
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
    BigBang* bg = BigBang::create();
    bg->setup(pos, _boomKey);
}

