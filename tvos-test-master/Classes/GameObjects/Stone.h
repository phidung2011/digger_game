//
//  Stone.h
//  gamebase
//
//  Created by Phi Dzung on 6/19/15.
//
//

#ifndef __gamebase__Stone__
#define __gamebase__Stone__

#include "BaseBomb.h"

class Stone : public BaseBomb
{
public:

    CREATE_FUNC(Stone);
    
    void onDestroyObject() override;
    bool worldUpdate() override;
    void inputUpdate() override;
private:
    bool init() override;
    int stateToAnimation(State state) const override;
protected:
    Stone();
    ~Stone();
};

#endif /* defined(__gamebase__Stone__) */
