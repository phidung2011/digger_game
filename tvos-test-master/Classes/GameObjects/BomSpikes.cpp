//
//  BomSpikes.cpp
//  gamebase
//
//  Created by Phi Dzung on 6/25/15.
//
//

#include "BomSpikes.h"
#include "MainGameScene.h"
#include "GameConfig.h"
#include "AvatarConfig.h"
BomSpikes::BomSpikes()
{
    
}
BomSpikes::~BomSpikes()
{
    
}
bool BomSpikes::init()
{
    if (!BaseBomb::init() || !BaseBomb::initWithKey(AnimationKey::BOMB_SPIKE_KEY))
    {
        return false;
    }
    _idTile = (int)IDTILE::BOMB_SPIKES;
    _boomKey = AnimationKey::BOOM_MINE_KEY;
    return true;
}
int BomSpikes::stateToAnimation(State state) const
{
    switch (state)
    {
        case sIdle:
            return 0;
        default:
            return -1;
    }
}
