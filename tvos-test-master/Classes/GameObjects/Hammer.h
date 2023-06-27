//
//  Hammer.h
//  gamebase
//
//  Created by Phi Dzung on 6/30/15.
//
//

#ifndef __gamebase__Hammer__
#define __gamebase__Hammer__

#include <BaseCharacter.h>

class Hammer : public BaseCharacter
{
public:

    CREATE_FUNC(Hammer);
    void inputUpdate() override;
private:

    

    
protected:
    Hammer();
    ~Hammer();
    std::vector<int> movableDir;
    void resetMove();
    bool init() override;
    int getMove() override;
};

#endif /* defined(__gamebase__Hammer__) */
