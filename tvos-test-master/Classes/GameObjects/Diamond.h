//
//  Diamond.h
//  gamebase
//
//  Created by Phi Dzung on 6/15/15.
//
//

#ifndef __gamebase__Diamond__
#define __gamebase__Diamond__

#include "BaseBomb.h"

class Diamond : public BaseBomb
{
public:
    Diamond();
    ~Diamond();
    CREATE_FUNC(Diamond);
    
    static Diamond* createWithLevel(int level);
    
    void onDestroyObject() override;
    
    bool worldUpdate() override;
    void inputUpdate() override;
private:
    bool initWithLevel(int id);
    int stateToAnimation(State state) const override;
};

#endif /* defined(__gamebase__Diamond__) */
