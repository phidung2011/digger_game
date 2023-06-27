//
//  AnimationManager.h
//  gamebase
//
//  Created by Phi Dzung on 7/2/15.
//
//

#ifndef __gamebase__AnimationManager__
#define __gamebase__AnimationManager__

#include "CAnimation.h"
#include "AnimationKey.h"

class AnimationManager
{
public:
    static AnimationManager* getInstance();
    
    std::unordered_map<AnimationKey, cocos2d::Vector<CAnimation*>>& getAnimationData(){return _animationData;};
private:
    
    static AnimationManager* _instance;
    std::unordered_map<AnimationKey, cocos2d::Vector<CAnimation*>> _animationData;
    void loadAnimationDataFromFile(AnimationKey animationKey);
    
protected:
    AnimationManager();

    
    
};



#endif /* defined(__gamebase__AnimationManager__) */
