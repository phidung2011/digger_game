//
//  Roller.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 7/13/15.
//
//

#ifndef __gamebase__Roller__
#define __gamebase__Roller__

#include <BaseCharacter.h>

class Roller : public BaseCharacter
{
public:

    CREATE_FUNC(Roller);
    void inputUpdate() override;
    bool isMovable(int dir) override;
private:

protected:
    Roller();
    ~Roller();
    bool init() override;
    int getMove() override;
    std::vector<int> movableDir;
    void resetMove();
};


#endif /* defined(__gamebase__Roller__) */
