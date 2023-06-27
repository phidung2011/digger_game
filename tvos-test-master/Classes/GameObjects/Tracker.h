//
//  Tracker.h
//  gamebase
//
//  Created by Phi Dzung on 7/9/15.
//
//

#ifndef __gamebase__Tracker__
#define __gamebase__Tracker__

#include <BaseCharacter.h>

class Tracker : public BaseCharacter
{
public:

    CREATE_FUNC(Tracker);
    void inputUpdate() override;
    bool isMovable(int dir) override;
private:

protected:
    Tracker();
    ~Tracker();
    bool init() override;
    int getMove() override;
    
    std::vector<int> movableDir;
    void resetMove();
    CC_SYNTHESIZE(int, _range, Range);
};

#endif /* defined(__gamebase__Tracker__) */
