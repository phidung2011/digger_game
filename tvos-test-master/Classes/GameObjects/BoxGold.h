//
//  BoxGold.h
//  gamebase
//
//  Created by Phi Dzung on 7/13/15.
//
//

#ifndef __gamebase__BoxGold__
#define __gamebase__BoxGold__

#include "BaseBomb.h"

class BoxGold : public BaseBomb
{
public:

    CREATE_FUNC(BoxGold);
    bool onFallingCollision() override;
    bool dropping() override;
    bool worldUpdate() override;
    void inputUpdate() override;
private:
    bool init() override;
    void onDestroyObject() override;
    
    int stateToAnimation(State state) const override;
protected:
    BoxGold();
    ~BoxGold();
    bool _opened;
};

#endif /* defined(__gamebase__BoxGold__) */
