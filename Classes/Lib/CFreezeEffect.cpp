//
//  CFreezeEffect.cpp
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 8/31/15.
//
//

#include "CFreezeEffect.h"
#include "BaseCharacter.h"

CFreezeEffect::CFreezeEffect()
{
    
}

CFreezeEffect::~CFreezeEffect()
{

}

CFreezeEffect* CFreezeEffect::create(int totalLoop)
{
    CFreezeEffect* act = new (std::nothrow) CFreezeEffect;
    if (act && act->initWithTotalLoop(totalLoop))
    {
        act->autorelease();
        return act;
    }
    CC_SAFE_DELETE(act);
    return nullptr;
}

void CFreezeEffect::update(float rate)
{
    if (_owner)
    {
        if (_owner->isRunningUpdate())
        {
            _owner->pauseUpdate();
        }
    }
}

void CFreezeEffect::startWithOwner(DataObject *owner)
{
    CEffect::startWithOwner(owner);
    dynamic_cast<BaseCharacter*>(_owner)->setRate(0.8);
}

bool CFreezeEffect::initWithTotalLoop(int totalLoop)
{
    if (!CEffect::initWithTotalLoop(totalLoop))
    {
        return false;
    }
    _id = eFreezed;
    return true;
}

void CFreezeEffect::onStop()
{
    dynamic_cast<BaseCharacter*>(_owner)->setRate(1);
    _owner->resumeUpdate();
}