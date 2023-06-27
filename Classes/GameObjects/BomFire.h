//
//  BomFire.h
//  gamebase
//
//  Created by NGOCDIEP on 6/29/15.
//
//

#ifndef __gamebase__BomFire__
#define __gamebase__BomFire__

#include "BaseCharacter.h"

class BomFire : public BaseCharacter
{
public:

    static BomFire* createWithDir(int dir);
    
    bool isMovable(int dir) override;
    bool destroy() override;
    
    void onDestroyObject() override;
    void inputUpdate() override;
    bool worldUpdate() override;
private:
    int stateToAnimation(State state) const override;

protected:
    BomFire();
    ~BomFire();
    bool fly();
    int _dirFly;
    bool initWithDir(int dir);
    bool onFlyingCollision();
    CC_SYNTHESIZE(DataObject*, _owner, Owner);
};
#endif /* defined(__gamebase__BomFire__) */
