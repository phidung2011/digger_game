//
//  CShake.cpp
//  gamebase
//
//  Created by Phi Dzung on 8/25/15.
//
//

#include "CShake.h"
USING_NS_CC;
CShake::CShake()
: _strength_x(0),
_strength_y(0)
{
    
}

CShake* CShake::create(float d, float strength )
{
    // call other construction method with twice the same strength
    return create( d, strength, strength );
}

CShake* CShake::create(float duration, float strength_x, float strength_y)
{
    CShake *p_action = new CShake();
    p_action->initWithDuration(duration, strength_x, strength_y);
    p_action->autorelease();
    
    return p_action;
}

bool CShake::initWithDuration(float duration, float strength_x, float strength_y)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _strength_x = strength_x;
        _strength_y = strength_y;
        return true;
    }
    
    return false;
}

// Helper function. I included it here so that you can compile the whole file
// it returns a random value between min and max included
float CShake::fgRangeRand(float min, float max)
{
    float rnd = ((float)rand()/(float)RAND_MAX);
    return rnd*(max-min)+min;
}

void CShake::update(float time)
{
    if (_target)
    {
        float randx = fgRangeRand(-_strength_x, _strength_x);
        float randy = fgRangeRand(-_strength_y, _strength_y);
#if CC_ENABLE_STACKABLE_ACTIONS
        Vec2 currentPos = _target->getPosition();
        
        Vec2 diff = currentPos - _previousPosition;
        _startPosition = diff + _startPosition;
        
        Vec2 newPos = _startPosition + Vec2(randx,randy);
        _target->setPosition(newPos);
        
        _previousPosition = newPos;
#else
        _target->setPosition(_startPosition + Vec2(randx,randy));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

void CShake::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    
    // save the initial position
    _startPosition = _previousPosition = target->getPosition();
}

void CShake::stop()
{
    _target->setPosition(_startPosition);
    ActionInterval::stop();
}
