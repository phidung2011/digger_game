//
//  ObjectValue.h
//  digger
//
//  Created by Nguyễn Lê Lợi on 10/27/15.
//
//

#ifndef __digger__ObjectValue__
#define __digger__ObjectValue__

#include "DataObject.h"

class ObjectValue
{
public:
//    static ObjectValue* create();
    cocos2d::Vector<DataObject*>& getPool(){return _pool;};
    uint32_t* getObjectMap(){return _objectMap;};
    
    uint32_t getIdAt(cocos2d::Vec2 pos);
    void setIdAt(cocos2d::Vec2 pos, uint32_t value);
    
private:
protected:
    ObjectValue();
    ~ObjectValue();
    
    
    
    uint32_t* _objectMap;
    cocos2d::Vector<DataObject*> _pool;
};

#endif /* defined(__digger__ObjectValue__) */
