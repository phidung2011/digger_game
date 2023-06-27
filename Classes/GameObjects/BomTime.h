//
//  BomTime.h
//  gamebase
//
//  Created by NGOCDIEP on 6/25/15.
//
//

#ifndef __gamebase__BomTime__
#define __gamebase__BomTime__


#include "BaseBomb.h"
class BomTime : public BaseBomb
{
public:
    CREATE_FUNC(BomTime);
    
    bool isMovable(int dir) override;
    void inputUpdate() override;
    void onDestroyObject() override;
    void animUpdate(unsigned int currentLoop) override;
private:
    int stateToAnimation(State state) const override;
private:
    bool init() override;
protected:
    BomTime();
    ~BomTime();
};

#endif /* defined(__gamebase__BomTime__) */
