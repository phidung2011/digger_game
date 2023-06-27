//
//  CSequence.cpp
//  rectdemo
//
//  Created by Nguyễn Lê Lợi on 6/8/15.
//
//

#include "CSequence.h"



CSequence::CSequence()
{
    
}

CSequence::~CSequence()
{
    
}

CSequence* CSequence::create(CAction *action, ...)
{
    va_list params;
    va_start(params, action);
    
    CSequence* ret = new (std::nothrow) CSequence;
    if (ret && ret->initWithVariableList(action,params))
    {
        ret->autorelease();
        va_end(params);
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
bool CSequence::initWithVariableList(CAction* action, va_list args)
{
    bool ret = true;
    do
    {
        CAction* prev = action;
        
        while (prev)
        {
            _seqPool.pushBack(prev);
            prev = va_arg(args, CAction*);
            _id = ACTIONID::SEQUENCE;
        }
        
    } while (0);
    return ret;
}

CSequence* CSequence::create(const cocos2d::Vector<CAction*>& arrayOfActions)
{
    CSequence* act = new (std::nothrow) CSequence;
    if (act && act->initWithArray(arrayOfActions))
    {
        act->autorelease();
        return act;
    }
    CC_SAFE_DELETE(act);
    return nullptr;
}
bool CSequence::initWithArray(const cocos2d::Vector<CAction *> &arrayOfActions)
{
    bool ret = true;
    do
    {
        _seqPool = arrayOfActions;
        _id = ACTIONID::SEQUENCE;
        
    } while (0);
    return ret;
}

void CSequence::update(float rate)
{
    if (!_seqPool.empty())
    {
        _seqPool.back()->step();
        _loadedLoop++;
        if (_seqPool.back()->isDone())
        {
            _seqPool.popBack();
            if (!_seqPool.empty() && _seqPool.back()->getId() == ACTIONID::CALLFUNC)
            {
                _seqPool.back()->step();
                if (!_seqPool.empty())
                {
                    _seqPool.popBack();

                }
            }
        }
    }
}
bool CSequence::isDone()
{
    return _seqPool.empty();
}

void CSequence::startWithOwner(DataObject *owner)
{
    CAction::startWithOwner(owner);
    for (auto& action : _seqPool)
    {
        action->startWithOwner(owner);
    }
}