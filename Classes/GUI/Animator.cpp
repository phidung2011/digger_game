//
//  Animator.cpp
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 9/4/15.
//
//

#include "Animator.h"

//Animator* Animator::_instance = NULL;
//
//Animator* Animator::getInstance()
//{
//    if (!_instance) {
//        _instance = new Animator();
//    }
//    return _instance;
//}

//Animator::Animator()
//{
//    
//}
//
//Animator::~Animator()
//{
//    
//}
USING_NS_CC;

cocos2d::ActionInterval* Animator::pumpIn(cocos2d::Node *node, float delayTime)
{
    node->setAnchorPoint(Vec2(0.5,0.5));
    node->setScale(0);
    auto scale = ScaleTo::create(0.2, 1.15);
    auto scale2 = ScaleTo::create(0.08, 0.94);
    auto scale3 = ScaleTo::create(0.08, 1);
    auto seq = Sequence::create(DelayTime::create(delayTime), scale,scale2,scale3, NULL);
    return seq;
}

void Animator::multiPumpIn(float delayTime, const cocos2d::Vector<cocos2d::Node *> &arrayOfNodes, float startTime)
{
    auto count = 0;
    
    if (!arrayOfNodes.empty())
    {
        for (auto& node : arrayOfNodes)
        {
            node->runAction(Sequence::create(DelayTime::create(startTime),Animator::pumpIn(node,delayTime*count), NULL));
            count++;
        }
    }
}

cocos2d::ActionInterval* Animator::turning(cocos2d::Node *node, float delayTime)
{
//    node->setOpacity(255);
//    node->setScale(1);
    
    auto scale = ScaleTo::create(0.05, -1, 1);
    auto scale2 = ScaleTo::create(0.05, 1, 1);
    
    auto seq = Sequence::create(scale,scale2, NULL);
    
    auto repeat = Repeat::create(seq, 10);
    
    auto ease = EaseCubicActionInOut::create(repeat);
    return Sequence::create(DelayTime::create(delayTime), ease, NULL);
}

void Animator::multiTurning(float delayTime, const cocos2d::Vector<cocos2d::Node *> &arrayOfNodes, float startTime)
{
    auto count = 0;
    
    if (!arrayOfNodes.empty())
    {
        for (auto& node : arrayOfNodes)
        {
            node->runAction(Sequence::create(DelayTime::create(startTime),Animator::turning(node,delayTime*count), NULL));
            count++;
        }
    }
}


cocos2d::ActionInterval* Animator::fadeOut(cocos2d::Node *node, float delayTime)
{
    node->setOpacity(255);
    node->setScale(1);
    
    auto fade = FadeTo::create(0.4, 0);
    auto seq = Sequence::create(DelayTime::create(delayTime), fade, NULL);
    
    return seq;
}


void Animator::multiMark(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime)
{
    auto count = 0;
    
    if (!arrayOfNodes.empty())
    {
        for (auto& node : arrayOfNodes)
        {
            node->runAction(Sequence::create(DelayTime::create(startTime),Animator::mark(node,delayTime*count), NULL));
            count++;
        }
    }
}



void Animator::multiFadeOut(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime)
{
    auto count = 0;
    
    if (!arrayOfNodes.empty())
    {
        for (auto& node : arrayOfNodes)
        {
            node->runAction(Sequence::create(DelayTime::create(startTime),Animator::fadeOut(node,delayTime*count), NULL));
            count++;
        }
    }
}


cocos2d::ActionInterval* Animator::dropDown(cocos2d::Node *node, std::function<void()> callback, float delayTime)
{
    node->setScale(1);
    node->setAnchorPoint(Vec2(0.5,0));
    auto endPos = node->getPosition();
    auto startPos = endPos + Vec2(0, 500);
    
    node->setPosition(startPos);
    
    auto move = EaseIn::create(MoveTo::create(0.3, endPos),5);
    
    auto scale2 = ScaleTo::create(0.18, 1.07,0.83);
    auto scale3 = ScaleTo::create(0.12, 1);
    
    auto call = CallFunc::create([callback]{
        if (callback)
        {
            callback();
        }
    });
    
    auto seqSub = Sequence::create(EaseQuarticActionOut::create(scale2), EaseQuarticActionIn::create(scale3), NULL);
    
    
    auto seq = Sequence::create(DelayTime::create(delayTime), move, call, seqSub, NULL);
    
    return seq;
}

cocos2d::ActionInterval* Animator::flyUp(cocos2d::Node *node, float delayTime)
{
//    node->setOpacity(255);
    node->setScale(1);
    node->setAnchorPoint(Vec2(0.5,1));
    auto endPos = node->getPosition();
    auto winSize = Director::getInstance()->getWinSize();
    auto startPos = endPos + Vec2(0,-500);
    
    node->setPosition(startPos);
    
    auto move = EaseIn::create(MoveTo::create(0.4, endPos),5);
    
    auto scale2 = ScaleTo::create(0.18, 1.07,0.83);
    auto scale3 = ScaleTo::create(0.12, 1);
    
    auto seqSub = Sequence::create(EaseQuarticActionOut::create(scale2), EaseQuarticActionIn::create(scale3), NULL);
    
    
    auto seq = Sequence::create(DelayTime::create(delayTime), move,seqSub, NULL);
    
    return seq;
}

void Animator::multiFlyUp(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime)
{
    auto count = 0;
    
    if (!arrayOfNodes.empty())
    {
        for (auto& node : arrayOfNodes)
        {
            node->runAction(Sequence::create(DelayTime::create(startTime),Animator::flyUp(node,delayTime*count), NULL));
            count++;
        }
    }
}


void Animator::multiDropDown(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, std::function<void()> callback)
{
    auto count = 0;
    
    if (!arrayOfNodes.empty())
    {
        for (auto& node : arrayOfNodes)
        {
//            std::function<void()> temp = callback;
            node->runAction(Animator::dropDown(node, callback, delayTime*count));
            count++;
        }
    }
}

cocos2d::ActionInterval* Animator::jumpIn(cocos2d::Node *node, float delayTime)
{
    node->setScale(0);
//    node->setOpacity(255);
    node->setAnchorPoint(Vec2(0.5,0));
    int high = 0.5*node->getContentSize().height;
    auto jumpUp = MoveBy::create(0.3, Vec2(0,high));
    auto jumpDown = MoveBy::create(0.2, Vec2(0,-high));
    
    auto scaleUp = ScaleTo::create(0.25, 0.85, 1.15);
    
    auto scale2 = ScaleTo::create(0.18, 1.07,0.83);
    auto scale3 = ScaleTo::create(0.12, 1);
    
    auto seqSub = Sequence::create(EaseQuarticActionOut::create(scale2), EaseQuarticActionIn::create(scale3), NULL);
    
    
    auto seqUp = Sequence::create(scaleUp, ScaleTo::create(0.05, 1),NULL);
    
    auto spawn = Spawn::create(jumpUp, seqUp, NULL);
    
    auto easeUp = EaseExponentialOut::create(spawn);
    auto easeDown = EaseExponentialIn::create(jumpDown);
    
    auto seq = Sequence::create(DelayTime::create(delayTime), easeUp, easeDown, seqSub, NULL);
    
    return seq;
}

cocos2d::ActionInterval* Animator::jumpOut(cocos2d::Node *node, float delayTime)
{
    node->setScale(1);
//    node->setOpacity(255);
    node->setAnchorPoint(Vec2(0.5,0));
    
    int high = 0.5*node->getContentSize().height;
    
    auto jumpUp = MoveBy::create(0.28, Vec2(0,high));
    auto jumpDown = MoveBy::create(0.2, Vec2(0,-high));
    
    auto scaleUp = ScaleTo::create(0.23, 0.85, 1.15);
    
    auto scale2 = ScaleTo::create(0.18, 1.07,0.83);
    auto scale3 = ScaleTo::create(0.12, 1);
    
    auto seqSub = Sequence::create(EaseQuarticActionOut::create(scale2), EaseQuarticActionIn::create(scale3), NULL);
    
    
    auto seqUp = Sequence::create(scaleUp, ScaleTo::create(0.05, 1),NULL);
    
    auto spawn = Spawn::create(jumpUp, seqUp, NULL);
    
    auto easeUp = EaseExponentialOut::create(spawn);
    auto easeDown = EaseExponentialIn::create(jumpDown);
    auto spawnDown = Spawn::create(ScaleTo::create(0.2, 0), easeDown, NULL);
    
    auto seq = Sequence::create(DelayTime::create(delayTime),seqSub, easeUp, spawnDown, NULL);
    
    return seq;
}

void Animator::multiJumpIn(float delayTime, cocos2d::Node *node, ...)
{
    va_list params;
    va_start(params, node);
    
    Node* prev = node;
    
    int count = 0;
    
    while (prev)
    {
        prev->runAction(Animator::jumpIn(prev, delayTime*count));
        prev = va_arg(params, Node*);
        count++;
    }
    
    va_end(params);
}

void Animator::multiJumpIn(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime)
{
    auto count = 0;
    
    if (!arrayOfNodes.empty())
    {
        for (auto& node : arrayOfNodes)
        {
            node->runAction(Sequence::create(DelayTime::create(startTime),Animator::jumpIn(node,delayTime*count), NULL));
            count++;
        }
    }
}

void Animator::multiJumpOut(float delayTime, const cocos2d::Vector<cocos2d::Node*>& arrayOfNodes, float startTime)
{
    auto count = 0;
    
    if (!arrayOfNodes.empty())
    {
        for (auto& node : arrayOfNodes)
        {
            node->runAction(Sequence::create(DelayTime::create(startTime),Animator::jumpOut(node,delayTime*count), NULL));
            count++;
        }
    }
}

cocos2d::ActionInterval* Animator::mark(cocos2d::Node* node, float delayTime)
{
    node->setScale(1.5);
    node->setOpacity(0);
    auto scale = ScaleTo::create(0.3, 1);
    auto fade = FadeTo::create(0.3, 255);
    auto spawn = Spawn::create(scale, fade, NULL);
    auto seq = Sequence::create(DelayTime::create(delayTime), spawn, NULL);
    return seq;
}