//
//  CSequence.h
//  rectdemo
//
//  Created by Nguyễn Lê Lợi on 6/8/15.
//
//

#ifndef __rectdemo__CSequence__
#define __rectdemo__CSequence__

#include "CAction.h"

class CSequence : public CAction
{
public:
    CSequence();
    ~CSequence();
    void update(float rate) override;
    static CSequence* create(const cocos2d::Vector<CAction*>& arrayOfActions);
    static CSequence* create(CAction* action, ...);
    bool isDone() override;
    virtual void startWithOwner(DataObject* owner);
private:
    cocos2d::Vector<CAction*> _seqPool;
    
    bool initWithArray(const cocos2d::Vector<CAction*>& arrayOfActions);
    bool initWithVariableList(CAction* action, va_list args);
};

#endif /* defined(__rectdemo__CSequence__) */
