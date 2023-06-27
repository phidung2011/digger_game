//
//  Tanker.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 7/8/15.
//
//

#ifndef __gamebase__Tanker__
#define __gamebase__Tanker__

#include "BaseCharacter.h"

class Tanker : public BaseCharacter
{
public:

    CREATE_FUNC(Tanker);
    void inputUpdate() override;
private:

    
protected:
    Tanker();
    ~Tanker();
    bool _isTurned;
    bool init() override;
    int getMove() override;
    void fire();
    bool lookingForPlayer();
    std::vector<int> movableDir;
    void resetMove();
};

#endif /* defined(__gamebase__Tanker__) */
