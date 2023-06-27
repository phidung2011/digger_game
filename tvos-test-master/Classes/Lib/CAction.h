//
//  CAction.h
//  rectdemo
//
//  Created by Phi Dzung on 6/8/15.
//
//

#ifndef __rectdemo__CAction__
#define __rectdemo__CAction__

#include "DataObject.h"

enum class ACTIONID
{
    INVALID_ID,
    CALLFUNC,
    SEQUENCE,
    MOVE,
};

class CAction : public cocos2d::Ref
{
public:
    virtual void update(float rate){};
    virtual void step();
    virtual bool isDone();
    
    
    virtual void startWithOwner(DataObject* owner);
private:
    
    
protected:
    CAction();
    ~CAction();
    DataObject* _owner;
    
    virtual bool initWithTotalLoop(int totalLoop);
    
    CC_SYNTHESIZE(ACTIONID, _id, Id);
    CC_SYNTHESIZE(int, _tag, Tag);
    CC_SYNTHESIZE(int, _totalLoop, TotalLoop);
    CC_SYNTHESIZE(int, _loadedLoop, LoadedLoop);
};

#endif /* defined(__rectdemo__CAction__) */
