//
//  Animator.h
//  gamebase
//
//  Created by Phi Dzung on 9/4/15.
//
//

#ifndef __gamebase__Animator__
#define __gamebase__Animator__

#include "cocos2d.h"

class Animator
{
public:
//    static Animator* getInstance();
    
    static cocos2d::ActionInterval* jumpIn(cocos2d::Node* node, float delayTime = 0);
    static cocos2d::ActionInterval* jumpOut(cocos2d::Node* node, float delayTime = 0);
    static void multiJumpIn(float delayTime, cocos2d::Node *node, ...);
    static void multiJumpIn(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime = 0);
    static void multiJumpOut(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime = 0);
    
    static cocos2d::ActionInterval* dropDown(cocos2d::Node* node, std::function<void()> callback = NULL, float delayTime = 0);
    
    static void multiDropDown(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, std::function<void()> callback = NULL);
    
    
    
    static cocos2d::ActionInterval* fadeOut(cocos2d::Node* node, float delayTime = 0);
    
    static void multiFadeOut(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime = 0);
    static void multiMark(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime = 0);
    static void multiFlyUp(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime = 0);
    static cocos2d::ActionInterval* flyUp(cocos2d::Node *node, float delayTime = 0);
    
    static cocos2d::ActionInterval* mark(cocos2d::Node *node, float delayTime = 0);
    
    static cocos2d::ActionInterval* turning(cocos2d::Node* node, float delayTime = 0);
    static void multiTurning(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime = 0);
    
    static cocos2d::ActionInterval* pumpIn(cocos2d::Node* node, float delayTime = 0);
    static void multiPumpIn(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime = 0);
private:
//    static Animator* _instance;
protected:
//    Animator();
//    ~Animator();
    
};

#endif /* defined(__gamebase__Animator__) */
