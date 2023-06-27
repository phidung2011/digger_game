//
//  CAnimation.h
//  rectdemo
//
//  Created by Phi Dzung on 6/4/15.
//
//

#ifndef __rectdemo__CAnimation__
#define __rectdemo__CAnimation__

#include "cocos2d.h"

class CAnimation : public cocos2d::Ref
{
public:
    static CAnimation* create();
    
private:
    bool init();
protected:
    CAnimation();
    ~CAnimation();
    CC_SYNTHESIZE(int, _totalFrame, TotalFrame);
    CC_SYNTHESIZE(int, _id, Id);
    CC_SYNTHESIZE(int, _animSpeed, AnimSpeed);
    CC_SYNTHESIZE(int, _repeatTime, RepeatTime);
};

#endif /* defined(__rectdemo__State__) */
