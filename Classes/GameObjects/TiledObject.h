//
//  TiledObject.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 8/21/15.
//
//

#ifndef __gamebase__TiledObject__
#define __gamebase__TiledObject__

#include "DataObject.h"

class TiledObject : public DataObject
{
public:
    CREATE_FUNC(TiledObject);
    
    virtual bool destroy() override;
    
    virtual bool updateTile(cocos2d::Vec2 nextPos){return false;};
    
    virtual void stop() override;
    
    
    cocos2d::Vec2 getFrontPosition() const;
    cocos2d::Vec2 getBackPosition() const;
    
    cocos2d::Vec2 getMatrixPos() const;
    
    
    cocos2d::Vec2 getFrontMatrixPosition() const;
    cocos2d::Vec2 getBackMatrixPosition() const;
    
    
    void loadToMap();
    void resetPos();
private:
    
    
protected:
    TiledObject()
    :  _frontDir(0)
    , _delta (cocos2d::Vec2::ZERO)
    , _isCollisionOnMap(false)
    , _speed (0)
    {
    };
    ~TiledObject(){};
    
    bool _isCollisionOnMap;
    
    CC_SYNTHESIZE(int, _idTile, IdTile);
    CC_SYNTHESIZE(int,  _frontDir, FrontDir);
    CC_SYNTHESIZE(int, _backDir, BackDir);
    CC_SYNTHESIZE(float, _speed, Speed);
    CC_SYNTHESIZE(cocos2d::Vec2, _delta, Delta);
};

#endif /* defined(__gamebase__TiledObject__) */
