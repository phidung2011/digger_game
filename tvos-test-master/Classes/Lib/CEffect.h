//
//  CEffect.h
//  gamebase
//
//  Created by Phi Dzung on 8/28/15.
//
//

#ifndef __gamebase__CEffect__
#define __gamebase__CEffect__

#include "DataObject.h"



class CEffect : public cocos2d::Ref
{
public:
    CEffect();
    ~CEffect();
    virtual void update(float rate){};
    virtual void step();
    virtual bool isDone();
    virtual void onStop(){};
    
    virtual void startWithOwner(DataObject* owner);
    
private:

protected:

    
    virtual bool initWithTotalLoop(int totalLoop);
    DataObject* _owner;
    CC_SYNTHESIZE(EffectId, _id, Id);
    CC_SYNTHESIZE(int, _tag, Tag);
    CC_SYNTHESIZE(int, _totalLoop, TotalLoop);
    CC_SYNTHESIZE(int, _loadedLoop, LoadedLoop);
};
#endif /* defined(__gamebase__CEffect__) */
