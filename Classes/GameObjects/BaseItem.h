//
//  BaseItem.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 7/8/15.
//
//

#ifndef __gamebase__BaseItem__
#define __gamebase__BaseItem__

#include <TiledObject.h>

class BaseItem : public TiledObject
{
public:

    static BaseItem* createWithKey(ObjectKey key, int tileId);
    
    bool destroy() override;
private:
    
    
    int stateToAnimation(State state) const override {return 0;};
protected:
    BaseItem();
    ~BaseItem();
    bool initWithKey(ObjectKey key, int tileId);
};

#endif /* defined(__gamebase__BaseItem__) */
