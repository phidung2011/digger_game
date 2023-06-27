//
//  DataObject.cpp
//  rectdemo
//
//  Created by Nguyễn Lê Lợi on 6/2/15.
//
//

#include "DataObject.h"
#include "MainGameScene.h"
#include "CAction.h"
#include "CEffect.h"
#include "GameConfig.h"
#include "AvatarConfig.h"

DataObject::DataObject()
: _state(sIdle)
, _isRunningUpdate(true)
, _cleanEffect(false)
, _isValid(false)
{
    _actPool.clear();
    _effectPool.clear();
}

DataObject::~DataObject()
{
    this->stopAllAct();
    this->removeAllEffect();
}

void DataObject::stopAct(CAction* act)
{
    // explicit nil handling
    if (_actPool.empty())
    {
        log("action pool is empty");
        return;
    }
    ssize_t index = _actPool.getIndex(act);
    if( index != CC_INVALID_INDEX )
    {
        _actPool.erase(index);
    }
}
void DataObject::runAct(CAction *act)
{
    if (act)
    {
        act->startWithOwner(this);
        _actPool.pushBack(act);
    }
}
void DataObject::stopAllAct()
{
    if (_actPool.empty())
    {
        return;
    }
    _actPool.clear();
}

cocos2d::Vector<CAction*>& DataObject::getActionPool()
{
    return _actPool;
}

void DataObject::actionUpdate()
{
    if (_actPool.empty())
    {
        return;
    }
    
    for (auto itr = _actPool.begin(); itr != _actPool.end(); )
    {
        (*itr)->step();
        if ((*itr)->isDone())
        {
            itr = _actPool.erase(itr);
        }
        else
            ++itr;
    }
}

void DataObject::stopActByTag(int tag)
{
    CCASSERT( tag != Node::INVALID_TAG, "Invalid tag");
    
    if (_actPool.empty())
    {
        return;
    }
    
    for (auto& action : _actPool)
    {
        if(action && action->getTag() == tag)
            this->stopAct(action);
    }
}

CAction* DataObject::getActByTag(int tag)
{
    CCASSERT( tag != Node::INVALID_TAG, "Invalid tag");
    
    if (_actPool.empty())
    {
        return nullptr;
    }
    
    for (auto& action : _actPool)
    {
        if(action && action->getTag() == tag)
            return action;
    }
    
    return nullptr;
}

void DataObject::pauseUpdate()
{
    _isRunningUpdate = false;
}
void DataObject::resumeUpdate()
{
    _isRunningUpdate = true;
}

void DataObject::addEffect(CEffect *effect)
{
    if (effect)
    {
        auto itr = _effectPool.find(effect->getId());
        if (itr != _effectPool.end())
        {
            itr->second->release();
            _effectPool.erase(itr);
        }
        effect->startWithOwner(this);
        _effectPool.insert(effect->getId(), effect);
    }
}

bool DataObject::isEffected(EffectId effectId)
{
    auto itr = _effectPool.find(effectId);
    if (itr != _effectPool.end())
        return true;
    else return false;
}

bool DataObject::removeEffect(EffectId effectId)
{
    auto itr = _effectPool.find(effectId);
    if (itr != _effectPool.end())
    {
        _effectPool.erase(itr);
        return true;
    }
    return false;
}

void DataObject::removeAllEffect()
{
    if (_effectPool.empty())
    {
        return;
    }
    
    _effectPool.clear();
}

void DataObject::effectUpdate()
{
    if (_effectPool.empty())
    {
        return;
    }
    
    for (auto iter = _effectPool.begin(); iter != _effectPool.end(); )
    {
        iter->second->step();
        if (iter->second->isDone())
        {
            iter->second->onStop();
            iter = _effectPool.erase(iter);
        }
        else
            ++iter;
    }
}

bool DataObject::update(unsigned int currentLoop)
{
    if (!_isValid) {
        this->effectUpdate();
        if (_isRunningUpdate)
        {
            this->inputUpdate();
            this->actionUpdate();
            this->animUpdate(currentLoop);
        }
        else
            _animationStartLoop++;
    }
    
    return _isValid;
}

bool DataObject::destroy()
{
    if (!_isValid)
    {
        this->onDestroyObject();
        this->stopAllAct();
        this->removeAllEffect();
        this->removeFromParentAndCleanup(false);
        
        if (_cleanEffect)
        {
            auto currentAnim = this->getAnimation();
            auto dieAnim = AnimationManager::getInstance()->getAnimationData().at(this->getKey()).back();
            if (currentAnim != dieAnim)
            {
                this->setAnimation(AnimationManager::getInstance()->getAnimationData().at(this->getKey()).back());
                this->setAnimationStartLoop(MainGameScene::getInstance()->getCurrentMainLoop());
                _currentFrame = 0;
                auto spriteFrame = this->getSpriteFrameByKey(_key.type, _key.id, _key.level, this->getAnimation()->getId(), _currentFrame, this->getBaseDir());
                this->setSpriteFrame(spriteFrame);
                MainGameScene::getInstance()->getLayerContainer()->effectLayer()->addChild(this);
                MainGameScene::getInstance()->getEffectPool().pushBack(this);
            }
        }
        else
            MainGameScene::getInstance()->getReleasePool().pushBack(this);
        
        auto key = this->getKey();
        _isValid = true;
    }
    
    return _isValid;
}

void DataObject::cleanByEffect()
{
    if (_cleanEffect)
    {
        MainGameScene::getInstance()->getReleasePool().pushBack(this);
        this->removeFromParentAndCleanup(false);
        MainGameScene::getInstance()->getEffectPool().eraseObject(this);
    }
}

void DataObject::stop()
{
    this->stopAllAct();
    this->setState(sIdle);
}


cocos2d::Rect DataObject::getCollisionBound() const
{
    Rect thisRect = getBound();
    return thisRect;
}

cocos2d::Rect DataObject::getBound() const
{
    auto rect = Rect(this->getPositionX() - TILE_SIZE*0.5f + EX,
                     this->getPositionY() - TILE_SIZE*0.5f + EX,
                     TILE_SIZE - 2*EX,
                     TILE_SIZE - 2*EX);
    return rect;
}
