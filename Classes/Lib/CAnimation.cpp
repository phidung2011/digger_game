//
//  CAnimation.cpp
//  rectdemo
//
//  Created by Nguyễn Lê Lợi on 6/4/15.
//
//

#include "CAnimation.h"
CAnimation::CAnimation()
{
    CCLOG("%s",__PRETTY_FUNCTION__);
}
CAnimation::~CAnimation()
{
    CCLOG("%s",__PRETTY_FUNCTION__);
}
CAnimation* CAnimation::create()
{
    CAnimation *pRet = new(std::nothrow) CAnimation();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool CAnimation::init()
{
    _id = 0;
//    _currentFrame = 0;
//    _startLoop = 0;
    _totalFrame = 0;
    _animSpeed = 0;
    _repeatTime = 0;
    return true;
}
