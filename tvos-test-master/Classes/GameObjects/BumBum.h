//
//  BumBum.h
//  gamebase
//
//  Created by Phi Dzung on 6/25/15.
//
//

#ifndef __gamebase__BumBum__
#define __gamebase__BumBum__

#include "TiledObject.h"
class BumBum : public TiledObject
{
public:
    BumBum();
    ~BumBum();
    static BumBum* createWithKey(AnimationKey key);
    bool initWithKey(AnimationKey key);
    void inputUpdate() override;
    bool destroy() override;
    void boom();
    bool worldUpdate() override;
    
    
private:
    bool _destroyedFlag;
};

class BigBang : public cocos2d::Node
{
public:
    BigBang();
    ~BigBang();
    CREATE_FUNC(BigBang);
    void setup(std::vector<cocos2d::Vec2> pos, AnimationKey flag);
    bool init() override;
    
    std::vector<cocos2d::Vec2> _listBum;
    
    void loangBum(int m[5][5], int i, int j);
    
};

#endif /* defined(__gamebase__BumBum__) */
