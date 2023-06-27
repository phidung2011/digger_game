//
//  BomSpikes.h
//  gamebase
//
//  Created by NGOCDIEP on 6/25/15.
//
//

#ifndef __gamebase__BomSpikes__
#define __gamebase__BomSpikes__

#include "BaseBomb.h"

class BomSpikes : public BaseBomb
{
public:
    CREATE_FUNC(BomSpikes);
private:
    int stateToAnimation(State state) const override;
protected:
    BomSpikes();
    ~BomSpikes();
    bool init() override;
};
#endif /* defined(__gamebase__BomSpikes__) */
