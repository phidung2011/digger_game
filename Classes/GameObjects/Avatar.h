//
//  Avatar.h
//  rectdemo
//
//  Created by Nguyễn Lê Lợi on 6/2/15.
//
//

#ifndef __rectdemo__Avatar__
#define __rectdemo__Avatar__

#include "cocos2d.h"
#include "CAnimation.h"
#include "AnimationKey.h"

enum // enum for animations
{
    anim_idle = 0,
    anim_run = 1,
    anim_open = 2,
};

class Avatar : public cocos2d::Sprite
{
private:

    
public:
    void setOnAnimationFinishCallback(const std::function<void (int)> &func);
    virtual void animUpdate(unsigned int currentLoop); // chạy update cho animation
    void playAnim(int anim); // hàm thực thi animation
    
    /* type : Loại obj nhân vật hay item
     * objId : Id của nhân vật và item
     * level : level của nhân vật và item
     * anim : id của animation truyền vào
     * frame : frame hiện tại của state
     * dir : hướng cơ bản của obj (0,1,2,3,...)
     */
    cocos2d::SpriteFrame* getSpriteFrameByKey(std::string type, int objId, int  level, int animId, int frame, int dir);
protected:
    Avatar();
    ~Avatar();
    bool initWithKey(AnimationKey key);
    
    std::function<void (int)> _animationFinishCallback;
    
    CC_SYNTHESIZE(CAnimation*, _animation, Animation); //animation hiện tại của obj
    CC_SYNTHESIZE(int, _currentFrame, CurrentFrame); //frame hiện tại của animation hiện tại của obj
    CC_SYNTHESIZE(unsigned int, _animationStartLoop, AnimationStartLoop);
    CC_SYNTHESIZE(int, _baseDir, BaseDir);
    CC_SYNTHESIZE(AnimationKey, _key, Key);
};

#endif /* defined(__rectdemo__Avatar__) */
