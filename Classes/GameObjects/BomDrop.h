//
//  BomDrop.h
//  gamebase
//
//  Created by NGOCDIEP on 6/25/15.
//
//

#ifndef __gamebase__BomDrop__
#define __gamebase__BomDrop__

#include "BaseBomb.h"

class BomDrop : public BaseBomb
{
public:

    CREATE_FUNC(BomDrop);

    
    void onDestroyObject() override;
    bool worldUpdate() override;
    void inputUpdate() override;
private:
    bool init() override;
    bool onFallingCollision() override;
    int stateToAnimation(State state) const override;
protected:
    BomDrop();
    ~BomDrop();
};
#endif /* defined(__gamebase__BomDrop__) */
