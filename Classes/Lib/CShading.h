//
//  CShading.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 9/7/15.
//
//

#ifndef __gamebase__CShading__
#define __gamebase__CShading__

#include "cocos2d.h"
#include "LighterSprite.h"

class CShading : public cocos2d::ActionInterval
{
public:
    static CShading* create(float strenght, float duration)
    {
        CShading *pobSprite = new CShading();
        if (pobSprite && pobSprite->init(strenght, duration))
        {
            pobSprite->autorelease();
            return pobSprite;
        }
        CC_SAFE_DELETE(pobSprite);
        return NULL;
    };
    
    
    CShading* clone()
    {
        return CShading::create(_strenght, _duration);
    }
    
    CShading* reverse()
    {
        return CShading::create(-_strenght, _duration);
    }
    
    virtual void startWithTarget(cocos2d::Node *target) override
    {
        cocos2d::ActionInterval::startWithTarget(target);
        _startDL = _previousDL = dynamic_cast<LighterSprite*>(target)->getRate();
    };
    
private:
    void update(float rate) override
    {
        auto target = (LighterSprite*)_target;
        if (target)
        {
            float currentDL = target->getRate();
            float diff = currentDL - _previousDL;
            _startDL = _startDL + diff;
            float newDL =  _startDL + (_strenght * rate);
            target->setRate(newDL);
            _previousDL = newDL;
        }
    };
protected:
    CShading()
    : _strenght(0)
    , _startDL(0)
    , _previousDL(0)
    {
        
    };
    virtual ~CShading()
    {
        
    };
    float _strenght;
    float _startDL;
    float _previousDL;
//    LighterSprite* _target;
    
    bool init(float strenght, float duration)
    {
        if (!ActionInterval::initWithDuration(duration))
        {
            return false;
        }
        _strenght = strenght;
        return true;
    };
};

#endif /* defined(__gamebase__CShading__) */
