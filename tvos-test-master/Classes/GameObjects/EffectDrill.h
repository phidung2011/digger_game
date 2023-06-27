//
//  EffectDrill.h
//  gamebase
//
//  Created by Phi Dzung on 9/17/15.
//
//

#ifndef __gamebase__EffectDrill__
#define __gamebase__EffectDrill__

#include "DataObject.h"

class EffectDrill : public DataObject
{
public:
    static EffectDrill* createWithKey(AnimationKey key);
private:
protected:
    EffectDrill();
    ~EffectDrill();
    bool initByKey(AnimationKey key);
};

#endif /* defined(__gamebase__EffectDrill__) */
