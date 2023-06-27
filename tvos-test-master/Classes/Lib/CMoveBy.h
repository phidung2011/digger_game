//
//  CMoveBy.h
//  rectdemo
//
//  Created by Phi Dzung on 6/8/15.
//
//

#ifndef __rectdemo__CMoveBy__
#define __rectdemo__CMoveBy__

#include "cocos2d.h"
#include "CAction.h"
class CMoveBy : public CAction
{
public:
    CMoveBy();
    ~CMoveBy();
    static CMoveBy* create(cocos2d::Vec2 delta, int totalLoop);
    void update(float rate) override;
private:
    
    
protected:
    virtual bool initWithTotalLoop(cocos2d::Vec2 delta, int totalLoop);
    cocos2d::Vec2 _delta;
    cocos2d::Vec2 _start;
    cocos2d::Vec2 _previous;
};

#endif /* defined(__rectdemo__CMoveBy__) */
