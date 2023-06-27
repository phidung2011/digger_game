//
//  DataObject.h
//  rectdemo
//
//  Created by Phi Dzung on 6/2/15.
//
//

#ifndef __rectdemo__DataObject__
#define __rectdemo__DataObject__

#include "cocos2d.h"
#include "Avatar.h"

class CAction;
class CEffect;

enum
{
    dt_top = 1,
    dt_left = 2,
    dt_bot = 3,
    dt_right = 4
};

typedef enum // enum for state
{
    sIdle = 0,
    sMoving = 1,
    sFalling = 2,
    sRolling = 3,
    sPushing = 4,
    sPushed = 10,
    sOpened = 5,
    sOpening = 6,
    sAttacking = 7,
    sFreezing = 9,
}State;

typedef enum // enum for effects
{
    eFreezed = 0,
    ePushed = 1,
}EffectId;


class DataObject : public Avatar
{
    
private:
    
    virtual int stateToAnimation(State state) const {return -1;};
    
    
public:
    virtual bool update(unsigned int currentLoop);
    
    virtual void effectUpdate();
    virtual void inputUpdate(){}; // input update with state changing, object AI updating
    virtual bool worldUpdate(){return _isValid;}; // game logic update
    
    void actionUpdate(); // chạy update cho các action trong mảng
    void stopAct(CAction* act); // hàm stop action
    void runAct(CAction* act); // hàm thực thi action
    void stopAllAct(); // hàm stop tất cả action hiện có của đối tượng
    void stopActByTag(int tag); // remove action bằng tag
    bool isRunningUpdate(){return _isRunningUpdate;};
    
    void pauseUpdate();
    void resumeUpdate();
    
    void setState(State state)
    {
        if (_state != state)
        {
            this->playAnim(this->stateToAnimation(state));
            _previousState = _state;
            _state = state;
        }
    };
    
    void addEffect(CEffect *effect);
    
    bool isEffected(EffectId effectId);
    
    bool removeEffect(EffectId effectId);
    
    void removeAllEffect();
    
    State getState(){return _state;};
    
    cocos2d::Rect getCollisionBound() const;
    cocos2d::Rect getBound() const;
    CAction* getActByTag(int tag);
    
    virtual bool destroy();
    virtual void cleanByEffect();
    
    virtual void onDestroyObject(){};
    
    cocos2d::Vector<CAction*>& getActionPool();
    virtual void stop();
    
    cocos2d::Map<int, CEffect*>& getEffectPool(){return _effectPool;};
    bool isCleanEffect(){return _cleanEffect;};
    
    void setCleanEffect(){_cleanEffect = true;};
    
    bool isValid(){return _isValid;};
protected:
    DataObject();
    ~DataObject();

    bool _isRunningUpdate;
    bool _cleanEffect;
    bool _isValid;
    State _state;
    cocos2d::Map<int, CEffect*> _effectPool;
    
    
    
    CC_SYNTHESIZE(State, _previousState, PreviousState);
    cocos2d::Vector<CAction*> _actPool; // mảng lưu trữ các action hiện có của data object
};

#endif /* defined(__rectdemo__DataObject__) */
