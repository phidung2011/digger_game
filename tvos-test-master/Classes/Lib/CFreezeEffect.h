//
//  CFreezeEffect.h
//  gamebase
//
//  Created by Phi Dzung on 8/31/15.
//
//

#ifndef __gamebase__CFreezeEffect__
#define __gamebase__CFreezeEffect__

#include "CEffect.h"

class CFreezeEffect : public CEffect
{
public:
    static CFreezeEffect* create(int totalLoop);
    
    virtual void update(float rate) override;
    
    void onStop() override;
    void startWithOwner(DataObject* owner) override;
private:
    
protected:
    CFreezeEffect();
    ~CFreezeEffect();
    
    bool initWithTotalLoop(int totalLoop) override;
    
};

#endif /* defined(__gamebase__CFreezeEffect__) */
