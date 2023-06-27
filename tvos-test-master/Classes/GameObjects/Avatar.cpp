//
//  Avatar.cpp
//  rectdemo
//
//  Created by Phi Dzung on 6/2/15.
//
//

#include "Avatar.h"
#include "AnimationManager.h"
#include "MainGameScene.h"

Avatar::Avatar()
: _currentFrame(0)
, _baseDir(0)
, _animationStartLoop(0)
, _animation(NULL)
, _animationFinishCallback(NULL)
{

};

Avatar::~Avatar()
{
    
}

bool Avatar::initWithKey(AnimationKey key)
{
    _key = key;
    std::string s = cocos2d::StringUtils::format("%s_%d_%d/0/image0000.png",_key.type.c_str(), _key.id, _key.level);
    this->initWithSpriteFrameName(s);
    this->playAnim(anim_idle);
    return true;
}

cocos2d::SpriteFrame* Avatar::getSpriteFrameByKey(std::string type, int objId, int  level, int animId, int frame, int dir)
{
    std::string str = cocos2d::StringUtils::format("%s_%d_%d/%d/image%.4d.png", type.c_str(), objId, level, animId, frame + _animation->getTotalFrame() * dir);
    cocos2d::SpriteFrame *spf = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
    return spf;
}


void Avatar::animUpdate(unsigned int currentLoop)
{
    auto deltaLoop = currentLoop - _animationStartLoop;
    
    auto loadedFrame = deltaLoop/_animation->getAnimSpeed(); //số lượng frame đã chạy kể từ startLoop
    
    int currentFrame = loadedFrame % _animation->getTotalFrame(); //frame hiện tại trong animation
    
    if (_animation->getRepeatTime() > 0 &&
        loadedFrame >= _animation->getTotalFrame()*_animation->getRepeatTime())
    {
        if (_animationFinishCallback)
        {
            _animationFinishCallback(_animation->getId());
        }
    }
    
    if (_currentFrame != currentFrame)
    {
        auto spriteFrame = this->getSpriteFrameByKey(_key.type, _key.id, _key.level, _animation->getId(), currentFrame, _baseDir);
        this->setSpriteFrame(spriteFrame);
        _currentFrame = currentFrame;
    }
}

void Avatar::setOnAnimationFinishCallback(const std::function<void (int)> &func)
{
    _animationFinishCallback = func;
}

void Avatar::playAnim(int anim)
{
    auto currentAnim = _animation;
    auto nextAnim = AnimationManager::getInstance()->getAnimationData().at(_key).at(anim);
    if (currentAnim != nextAnim)
    {
        _animation = AnimationManager::getInstance()->getAnimationData().at(_key).at(anim);
        _animationStartLoop = MainGameScene::getInstance()->getCurrentMainLoop();
        _currentFrame = 0;
        auto spriteFrame = this->getSpriteFrameByKey(_key.type, _key.id, _key.level, _animation->getId(), _currentFrame, _baseDir);
        this->setSpriteFrame(spriteFrame);
    }
}
