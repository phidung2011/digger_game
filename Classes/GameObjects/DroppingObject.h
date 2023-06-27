//
//  DroppingObject.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 6/29/15.
//
//

#ifndef __gamebase__DroppingObject__
#define __gamebase__DroppingObject__

#include <TiledObject.h>


class DroppingObject : public TiledObject
{
public:

    virtual void move(int dir, State state);
    
    virtual bool dropping();
    virtual bool isDropLeftDown();
    virtual bool isDropRightDown();
    virtual bool isMovable(int dir);
    
    virtual bool onFallingCollision(){ return false; };
    
    bool destroy() override;
    
    virtual void setPush(int dir)
    {
        _dirPushed = dir;
        _isPushed = true;
    };
    
    bool updateTile(cocos2d::Vec2 nextPos) override;
    
private:
    
protected:
    DroppingObject();
    ~DroppingObject();
    int _dirPushed;
    bool _isPushed;
    bool _isBoom;
};

#endif /* defined(__gamebase__DroppingObject__) */
