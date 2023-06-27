//
//  CAction.cpp
//  rectdemo
//
//  Created by Nguyễn Lê Lợi on 6/8/15.
//
//

#include "CAction.h"


CAction::CAction()
: _tag(cocos2d::Node::INVALID_TAG)
, _loadedLoop(0)
, _totalLoop(0)
, _id(ACTIONID::INVALID_ID)
, _owner(NULL)
{

}

CAction::~CAction()
{

}
bool CAction::isDone()
{
    return _loadedLoop >= _totalLoop;
}
void CAction::step()
{
    _loadedLoop++;
    this->update((float)_loadedLoop/_totalLoop);
}

void CAction::startWithOwner(DataObject *owner)
{
    _owner = owner;
    _loadedLoop = 0;
}

bool CAction::initWithTotalLoop(int totalLoop)
{
    _totalLoop = totalLoop;
    return true;
}
