//
//  MoveBy.cpp
//  rectdemo
//
//  Created by Phi Dzung on 6/8/15.
//
//

#include "CMoveBy.h"
#include <ConvertUtils.h>
#include "TiledObject.h"
USING_NS_CC;
CMoveBy* CMoveBy::create(cocos2d::Vec2 delta, int totalLoop)
{
    CMoveBy* act = new (std::nothrow) CMoveBy;
    if (act && act->initWithTotalLoop(delta, totalLoop))
    {
        act->autorelease();
        return act;
    }
    CC_SAFE_DELETE(act);
    return nullptr;
}
CMoveBy::CMoveBy()
{
}
CMoveBy::~CMoveBy()
{
}
bool CMoveBy::initWithTotalLoop(cocos2d::Vec2 delta, int totalLoop)
{
    bool ret = true;
    do
    {
        if (!CAction::initWithTotalLoop(totalLoop))
        {
            ret = false;
            break;
        }
        _id = ACTIONID::MOVE;
        _delta = delta;
    } while (0);
    return ret;
}


void CMoveBy::update(float rate)
{
    if (_owner)
    {
        Vec2 currentPos = _owner->getPosition();
        Vec2 diff = currentPos - _previous;
        _start = _start + diff;
        Vec2 newPos =  _start + (_delta * rate);
        dynamic_cast<TiledObject*>(_owner)->setDelta(newPos - currentPos);
        _owner->setPosition(newPos);
        _previous = newPos;
    }
}
