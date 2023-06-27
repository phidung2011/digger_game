//
//  CShake.h
//  gamebase
//
//  Created by Phi Dzung on 8/25/15.
//
//

#ifndef __gamebase__CShake__
#define __gamebase__CShake__

#include "cocos2d.h"

class CShake : public cocos2d::ActionInterval
{
public:
    // Create the action with a time and a strength (x = y)
    static CShake* create(float d, float strength );
    // Create the action with a time and strengths (x != y)
    static CShake* create(float d, float strength_x, float strength_y );
    bool initWithDuration(float d, float strength_x, float strength_y );
    
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
    virtual void stop() override;
protected:
    CShake();
    ~CShake(){};
    // Strength of the action
    float _strength_x, _strength_y;
    float fgRangeRand( float min, float max );
    cocos2d::Vec2 _previousPosition;
    cocos2d::Vec2 _startPosition;
};

#endif /* defined(__gamebase__CShake__) */
