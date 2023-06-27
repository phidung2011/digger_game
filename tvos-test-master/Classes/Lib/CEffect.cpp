//
//  CEffect.cpp
//  gamebase
//
//  Created by Phi Dzung on 8/28/15.
//
//

#include "CEffect.h"

CEffect::CEffect()
: _tag(cocos2d::Node::INVALID_TAG)
, _loadedLoop(0)
, _totalLoop(0)
, _owner(NULL)
, _id((EffectId)-1)
{
    
}

CEffect::~CEffect()
{
    
}
bool CEffect::isDone()
{
    return _loadedLoop >= _totalLoop;
}
void CEffect::step()
{
    _loadedLoop++;
    this->update((float)_loadedLoop/_totalLoop);
}

void CEffect::startWithOwner(DataObject *owner)
{
    _owner = owner;
    _loadedLoop = 0;
}

bool CEffect::initWithTotalLoop(int totalLoop)
{
    _totalLoop = totalLoop;
    return true;
}
