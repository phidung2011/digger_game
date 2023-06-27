//
//  CCallback.h
//  rectdemo
//
//  Created by Nguyễn Lê Lợi on 6/8/15.
//
//

#ifndef __rectdemo__CCallback__
#define __rectdemo__CCallback__

#include "cocos2d.h"
#include "CAction.h"

class CCallback : public CAction
{
private:
    std::function<void ()> _func;
public:
    static CCallback* create(const std::function<void ()> &func)
    {
        CCallback* ret = new CCallback();
        if (ret)
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
        ret->_id = ACTIONID::CALLFUNC;
        ret->_func = func;
        return ret;
    }
    void execute()
    {
        if (_func)
        {
            _func();
        }
    }
    
    bool isDone() override
    {
        return true;
    };
    
    void update(float rate) override
    {
        execute();
    };
protected:
    CCallback(){};
    ~CCallback()
    {
        //        cocos2d::log("%s",__PRETTY_FUNCTION__);
    };
    
};

#endif /* defined(__rectdemo__CCallback__) */
