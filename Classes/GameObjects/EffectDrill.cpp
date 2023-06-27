//
//  EffectDrill.cpp
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 9/17/15.
//
//

#include "EffectDrill.h"
EffectDrill::EffectDrill()
{
//    CCLOG("%s", __PRETTY_FUNCTION__);
}

EffectDrill::~EffectDrill()
{
//    CCLOG("%s", __PRETTY_FUNCTION__);
}

EffectDrill* EffectDrill::createWithKey(AnimationKey key)
{
    EffectDrill* item = new (std::nothrow) EffectDrill;
    if (item && item->initByKey(key))
    {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}

bool EffectDrill::initByKey(AnimationKey key)
{
    if (!DataObject::init() || !DataObject::initWithKey(key))
    {
        return false;
    }
    
    this->setOnAnimationFinishCallback([this](int animId)
    {
        this->destroy();
    });
    return true;
}

