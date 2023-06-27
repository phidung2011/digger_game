//
//  CarShipper.h
//  gamebase
//
//  Created by NGOCDIEP on 7/3/15.
//
//

#ifndef __gamebase__CarShipper__
#define __gamebase__CarShipper__

#include <ConvertUtils.h>
#include <GameConfig.h>
#include <BaseCharacter.h>

class CarShipper : public BaseCharacter
{
public:

    CREATE_FUNC(CarShipper);
    void inputUpdate() override;
    void initDir();
    void setRotate();
    
    void move(int dir, State state) override;
private:
protected:
    CarShipper();
    ~CarShipper();
    
    int _landDir;
    bool _direction;
    bool init() override;
    int _count;
    bool isHaveLand();

    int _countLand;
    int getMove() override;
    bool goAHead;
//    int _rotation;
    
//    int checkDir(cocos2d::Vec2 pos, int dir, int rotation);
//    int checkMove();
//    int getDir(int roation);
};
#endif /* defined(__gamebase__CarShipper__) */
