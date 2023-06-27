//
//  TransitionManager.cpp
//  gamebase
//
//  Created by NGOCDIEP on 4/20/15.
//
//

#include "TransitionManager.h"
#include "SceneDisplay.h"
#include "VisibleRect.h"
#include "Popup.h"
USING_NS_CC;
//--------------
//class TransitionManager
TransitionManager* TransitionManager::_instance = NULL;

TransitionManager* TransitionManager::getInstance()
{
    if (!_instance)
    {
        _instance = new TransitionManager();
    }
    return _instance;
}

TransitionManager::TransitionManager()
: _isTransitioning(false)
, _canvas(NULL)
, _loadingLayer(NULL)
, _loadingCallback(NULL)
, _finishingCallback(NULL)
, _removeLayerPos(Vec2::ZERO)
, _addLayerPos(Vec2::ZERO)
, _transitionTime(0)
{
    
}

TransitionManager::~TransitionManager()
{
    
}
bool TransitionManager::removeFromScene(const LAYER_ID removeLayerId, TransitionType transition, cocos2d::Ref* pSender, float time)
{

    this->setupDefault();
    auto removeLayer = _canvas->getDictionary().at(removeLayerId);
    
    if(_isTransitioning || removeLayerId == INVALID_LAYER_ID || !removeLayer)
        return false;
    
    _transitionTime = time;
    
    Director::getInstance()->getEventDispatcher()->setEnabled(false);
    
    this->setTransitionState(transition);
    
    if (transition == TransitionType::FADE || transition == TransitionType::ROTATE)
    {
        // callback when transition is loaded half
        _loadingCallback = CallFunc::create([this, removeLayer]()
                                            {
                                                if (removeLayer)
                                                {
                                                    //remove the _removeLayer by it's index
                                                    
                                                    removeLayer->atLayerUnInit();
                                                    _canvas->getLayerContainer()->getLayerByIndex(removeLayer->getLayerIndex())->removeChild(removeLayer,false);
                                                }
                                            });
    }
    
    
    // callback when trasition get over
    _finishingCallback = CallFunc::create([this, removeLayer]()
                                          {
                                              //remove _loadingLayer from scene if the transition is the loading transition type
                                              if(_loadingLayer)
                                                  _loadingLayer->removeFromParentAndCleanup(true);
                                              
                                              if(removeLayer)
                                              {
                                                  removeLayer->atLayerUnInit();
                                                  _canvas->getLayerContainer()->getLayerByIndex(removeLayer->getLayerIndex())->removeChild(removeLayer,false);
                                              }
                                              _isTransitioning = false;
                                              Director::getInstance()->getEventDispatcher()->setEnabled(true);
                                          });
    
    this->setupTransition(NULL, removeLayer, transition);
    
    removeLayer->atLayerDestroy();
    
    _isTransitioning = true;
    
    return true;
}

bool TransitionManager::addToScene(const LAYER_ID addLayerId, TransitionType transition, cocos2d::Ref* pSender, float time)
{
    this->setupDefault();
    
    auto addLayer = _canvas->getDictionary().at(addLayerId);
    
    
    if(_isTransitioning || addLayerId == INVALID_LAYER_ID || !addLayer)
        return false;
    
    _transitionTime = time;
    
    Director::getInstance()->getEventDispatcher()->setEnabled(false);
    
    this->setTransitionState(transition);
    
    if (transition == TransitionType::FADE || transition == TransitionType::ROTATE)
    {
        // callback when transition is loaded half
        _loadingCallback = CallFunc::create([this, addLayer]()
                                            {
                                                if (addLayer)
                                                {
                                                    //addchild the _addLayer by it's index
                                                    _canvas->getLayerContainer()->getLayerByIndex(addLayer->getLayerIndex())->addChild(addLayer);
                                                }
                                            });
    }
    else
        _canvas->getLayerContainer()->getLayerByIndex(addLayer->getLayerIndex())->addChild(addLayer);
    
    
    // callback when trasition get over
    _finishingCallback = CallFunc::create([this, pSender, addLayer]()
                                          {
                                              //remove _loadingLayer from scene if the transition is the loading transition type
                                              if(_loadingLayer)
                                                  _loadingLayer->removeFromParentAndCleanup(true);
                                              
                                              if (addLayer)
                                              {
                                                  addLayer->atLayerExecute();
                                              }
                                              
                                              if (pSender)
                                              {
                                                  pSender->release();
                                              }
                                              
                                              _isTransitioning = false;
                                              Director::getInstance()->getEventDispatcher()->setEnabled(true);
                                          });
    
    
    
    this->setupTransition(addLayer, NULL, transition);
    
    if (pSender)
    {
        pSender->retain();
        addLayer->setSender(pSender);
    }
    
    addLayer->atLayerInit();
    
    _isTransitioning = true;
    return true;
}
bool TransitionManager::go(const LAYER_ID removeLayerId, const LAYER_ID addLayerId, TransitionType transition, cocos2d::Ref* pSender, float time)
{

    this->setupDefault();
    
    //get layer needed to be removed and layer needed to be added
    auto removeLayer = _canvas->getDictionary().at(removeLayerId);
    auto addLayer = _canvas->getDictionary().at(addLayerId);
    
    if(_isTransitioning || removeLayerId == INVALID_LAYER_ID || addLayerId == INVALID_LAYER_ID || !removeLayer || !addLayer)
        return false;
    
    _transitionTime = time;
    
    Director::getInstance()->getEventDispatcher()->setEnabled(false);
    
    this->setTransitionState(transition);
    
    if (transition == TransitionType::FADE || transition == TransitionType::ROTATE)
    {
        // callback when transition is loaded half
        _loadingCallback = CallFunc::create([this, addLayer, removeLayer]()
                                            {
                                                if (addLayer)
                                                {
                                                    //addchild the _addLayer by it's index
                                                    addLayer->setPosition(Vec2::ZERO);
                                                    _canvas->getLayerContainer()->getLayerByIndex(addLayer->getLayerIndex())->addChild(addLayer);
                                                }
                                                
                                                if (removeLayer)
                                                {
                                                    //remove the _removeLayer by it's index
                                                    removeLayer->atLayerUnInit();
                                                    _canvas->getLayerContainer()->getLayerByIndex(removeLayer->getLayerIndex())->removeChild(removeLayer, false);
                                                }
                                            });
    }
    else
        _canvas->getLayerContainer()->getLayerByIndex(addLayer->getLayerIndex())->addChild(addLayer);

    
    // callback when trasition get over
    _finishingCallback = CallFunc::create([this, pSender, addLayer, removeLayer]()
                                     {
                                         //remove _loadingLayer from scene if the transition is the loading transition type
                                         if(_loadingLayer)
                                             _loadingLayer->removeFromParentAndCleanup(true);
                                         
                                         if(removeLayer)
                                         {
                                             removeLayer->atLayerUnInit();
                                             _canvas->getLayerContainer()->getLayerByIndex(removeLayer->getLayerIndex())->removeChild(removeLayer,false);
                                         }
                                         
                                         if (addLayer)
                                         {
                                             addLayer->atLayerExecute();
                                         }
                                         
                                         
                                         if (pSender)
                                         {
                                             pSender->release();
                                         }

                                         _isTransitioning = false;
                                         Director::getInstance()->getEventDispatcher()->setEnabled(true);
                                     });
    
    this->setupTransition(addLayer, removeLayer, transition);
    
    removeLayer->atLayerDestroy();
    if (pSender)
    {
        pSender->retain();
        addLayer->setSender(pSender);
    }
    
    addLayer->atLayerInit();
    
    _isTransitioning = true;
    return true;
}

void TransitionManager::setTransitionState(TransitionType transition)
{
    _addLayerPos = Vec2::ZERO;
    _removeLayerPos = Vec2::ZERO;
    
    auto winSize = Director::getInstance()->getWinSize();
    
    switch (transition)
    {
        case TransitionType::SLIDE_LEFT:
            _addLayerPos = Vec2(winSize.width, 0);
            _removeLayerPos = Vec2(-winSize.width,0);
            break;
        case TransitionType::SLIDE_RIGHT:
            _addLayerPos = Vec2(-winSize.width, 0);
            _removeLayerPos = Vec2(winSize.width,0);
            break;
        case TransitionType::NONE:
            _transitionTime = 0;
            _addLayerPos = Vec2::ZERO;
            _removeLayerPos = Vec2::ZERO;
            break;
        case TransitionType::SLIDE_UP:
            _addLayerPos = Vec2(0,-winSize.height);
            _removeLayerPos = Vec2(0, winSize.height);
            break;
        case TransitionType::SLIDE_DOWN:
            _addLayerPos = Vec2(0,winSize.height);
            _removeLayerPos = Vec2(0, -winSize.height);
            break;
        case TransitionType::FADE:
        case TransitionType::ROTATE:
        case TransitionType::SCALE:
            _addLayerPos = Vec2::ZERO;
            _removeLayerPos = Vec2::ZERO;
            break;
        default:
            break;
    }
}



bool TransitionManager::addToSceneByCustomTransition(const LAYER_ID addLayerId, cocos2d::Ref* pSender)
{
    auto addLayer = _canvas->getDictionary().at(addLayerId);
    
    if(addLayerId == INVALID_LAYER_ID || !addLayer || addLayer->getParent())
        return false;
    
    
    
    if (pSender)
    {
        addLayer->setSender(pSender);
        pSender->retain();
    }
    _canvas->getLayerContainer()->getLayerByIndex(addLayer->getLayerIndex())->addChild(addLayer);
    addLayer->onEnterTransition();
    
    return true;
}

bool TransitionManager::removeFromSceneByCustomTransition(const LAYER_ID removeLayerId, cocos2d::Ref* pSender)
{
    auto removeLayer = _canvas->getDictionary().at(removeLayerId);
    
    if(removeLayerId == INVALID_LAYER_ID || !removeLayer || !removeLayer->getParent())
        return false;
    
    removeLayer->onExitTransition();
    
    return true;
}

void TransitionManager::setupDefault()
{
    _loadingLayer = NULL;
    _loadingCallback = NULL;
    _finishingCallback = NULL;
    _removeLayerPos = Vec2::ZERO;
    _addLayerPos = Vec2::ZERO;
    _transitionTime = 0;
}

void TransitionManager::setupTransition(LayerDisplay* addLayer, LayerDisplay* removeLayer, TransitionType transition)
{
    switch (transition)
    {
        case TransitionType::FADE:
        {
            _loadingLayer = LayerColor::create(Color4B::BLACK);
            _loadingLayer->setOpacity(0);
            auto prevAction = FadeTo::create(_transitionTime, 255);
            auto nextAction = FadeTo::create(_transitionTime, 0);
            auto seq = Sequence::create(prevAction, _loadingCallback, nextAction, _finishingCallback, NULL);
            _loadingLayer->runAction(seq);
            _canvas->getLayerContainer()->getLayerByIndex(LOADING_LAYER_INDEX)->addChild(_loadingLayer);
        }
            break;
        case TransitionType::ROTATE:
        {
            _loadingLayer = Layer::create();
            auto size = Director::getInstance()->getWinSize();	//get the windows size.
            
            auto clipper = ClippingNode::create();		// create the ClippingNode object
            auto clipper2 = ClippingNode::create();
            auto clipper3 = ClippingNode::create();
            
            Vec2 rectangle[4];
            rectangle[0] = Vec2( - size.width , -size.height/2);
            rectangle[1] = Vec2(size.width, -size.height/2);
            rectangle[2] = Vec2(size.width, size.height/2);
            rectangle[3] = Vec2( -size.width, size.height/2);
            
            auto stencil = DrawNode::create();
            stencil->drawPolygon(rectangle, 4, Color4F::GREEN, 0, Color4F::GREEN);
            
            auto stencil2 = DrawNode::create();
            stencil2->drawPolygon(rectangle, 4, Color4F::GREEN, 0, Color4F::GREEN);
            
            auto stencil3 = DrawNode::create();
            stencil3->drawPolygon(rectangle, 4, Color4F::GREEN, 0, Color4F::GREEN);
            
            clipper->setAnchorPoint(Vec2(0.5f, 0.5f));
            clipper->setPosition(size.width/2, size.height/2);
            clipper->setStencil(stencil);
            clipper->setInverted(true);
            
            clipper2->setAnchorPoint(Vec2(0.5f, 0.5f));
            clipper2->setPosition(size.width/2, size.height/2);
            clipper2->setStencil(stencil2);
            clipper2->setInverted(true);
            
            clipper3->setAnchorPoint(Vec2(0.5f, 0.5f));
            clipper3->setPosition(size.width/2, size.height/2);
            clipper3->setStencil(stencil3);
            clipper3->setInverted(true);
            
            auto blackRect = LayerColor::create(Color4B::BLACK);
            blackRect->setPosition(-size.width/2, -size.height/2);
            
            auto opaRect = LayerColor::create(Color4B::WHITE);
            opaRect->setPosition(-size.width/2, -size.height/2);
            
            auto opaRect2 = LayerColor::create(Color4B::WHITE);
            opaRect2->setPosition(-size.width/2, -size.height/2);
            
            opaRect->setOpacity(144);
            opaRect2->setOpacity(100);
            
            clipper2->addChild(opaRect);
            clipper->addChild(blackRect);
            clipper3->addChild(opaRect2);
            
            _loadingLayer->addChild(clipper, 3);
            _loadingLayer->addChild(clipper2,2);
            _loadingLayer->addChild(clipper3,1);
            
            auto easeIn = EaseSineInOut::create(Spawn::create(ScaleTo::create(_transitionTime, 1.0f, 0.0f), RotateBy::create(_transitionTime, -45), NULL));
            auto easeInOpa1 = EaseSineInOut::create(Spawn::create(ScaleTo::create(_transitionTime, 1.0f, 0.0f), RotateBy::create(_transitionTime, -48), NULL));
            auto easeInOpa2 = EaseSineInOut::create(Spawn::create(ScaleTo::create(_transitionTime, 1.0f, 0.0f), RotateBy::create(_transitionTime, -51), NULL));
            
            
            auto easeOut = EaseSineInOut::create(Spawn::create(ScaleTo::create(_transitionTime, 1.0f, 1.0f), RotateBy::create(_transitionTime, 45), NULL));
            auto easeOutOpa1 = EaseSineInOut::create(Spawn::create(ScaleTo::create(_transitionTime, 1.0f, 1.0f), RotateBy::create(_transitionTime, 48), NULL));
            auto easeOutOpa2 = EaseSineInOut::create(Spawn::create(ScaleTo::create(_transitionTime, 1.0f, 1.0f), RotateBy::create(_transitionTime, 51), NULL));
            
            auto call2 = CallFunc::create([&,clipper, clipper2, clipper3](){
                clipper->removeFromParentAndCleanup(true);
                clipper2->removeFromParentAndCleanup(true);
                clipper3->removeFromParentAndCleanup(true);
            });
            
            auto seq = Sequence::create(DelayTime::create(_transitionTime*0.16f), easeIn, _loadingCallback, easeOut, NULL);
            
            auto seq2 = Sequence::create(DelayTime::create(_transitionTime*0.08f), easeInOpa1, DelayTime::create(_transitionTime*0.16f), easeOutOpa1, NULL);
            
            auto seq3 = Sequence::create(easeInOpa2,DelayTime::create(_transitionTime*0.32f), easeOutOpa2, call2, _finishingCallback, NULL);
            
            stencil->runAction(seq);
            stencil2->runAction(seq2);
            stencil3->runAction(seq3);
            
            _canvas->getLayerContainer()->getLayerByIndex(LOADING_LAYER_INDEX)->addChild(_loadingLayer);
        }
            break;
        case TransitionType::NONE:
        {
            _canvas->runAction(_finishingCallback);
        }
            break;
        case TransitionType::SCALE:
        {
            if (addLayer && removeLayer)
            {
                auto call = CallFunc::create([removeLayer]()
                                             {
                                                 removeLayer->setScale(1);
                                             });
                auto seqAdd = Sequence::create(ScaleTo::create(0.0, 0.0),
                                               ScaleTo::create(0.08, 1.05),
                                               ScaleTo::create(0.12, 0.95),
                                               ScaleTo::create(0.12, 1.0),
                                               _finishingCallback, call, NULL);
                auto seqRemove = Sequence::create(ScaleTo::create(0.1, 0.0), NULL);
                addLayer->getBackground()->runAction(seqAdd);
                
                removeLayer->runAction(seqRemove);
                
            }
            else if (!addLayer && removeLayer)
            {
                auto call = CallFunc::create([removeLayer]()
                                             {
                                                 removeLayer->setScale(1);
                                             });
                auto seqRemove = Sequence::create(ScaleTo::create(0.0, 1.0),
                                                  ScaleTo::create(0.12, 0.95),
                                                  ScaleTo::create(0.12, 1.05),
                                                  ScaleTo::create(0.08, 0.0),
                                                  _finishingCallback, call, NULL);
                removeLayer->getBackground()->runAction(seqRemove);
            }
            else if (addLayer && !removeLayer)
            {
                auto seqAdd = Sequence::create(ScaleTo::create(0.0, 0.0),
                                               ScaleTo::create(0.08, 1.05),
                                               ScaleTo::create(0.12, 0.95),
                                               ScaleTo::create(0.12, 1.0),
                                               _finishingCallback, NULL);
                
                addLayer->getBackground()->runAction(seqAdd);
            }
        }
            break;
        default:
        {
            if (addLayer && removeLayer)
            {
                addLayer->setPosition(_addLayerPos);
                auto removeEasing = EaseElasticInOut::create(MoveTo::create(_transitionTime, _removeLayerPos), 4);
                auto addEasing = EaseElasticInOut::create(MoveTo::create(_transitionTime, Vec2::ZERO), 4);
                auto seq = Sequence::create(addEasing, _finishingCallback, NULL);
                removeLayer->runAction(removeEasing);
                addLayer->runAction(seq);
            }
            else if (!addLayer && removeLayer)
            {
                removeLayer->setPosition(_removeLayerPos);
                auto removeEasing = EaseElasticInOut::create(MoveTo::create(_transitionTime, Vec2(_removeLayerPos)), 4);
                auto seq = Sequence::create(removeEasing, _finishingCallback, NULL);
                removeLayer->runAction(seq);
            }
            else if (addLayer && !removeLayer)
            {
                auto addEasing = EaseElasticInOut::create(MoveTo::create(_transitionTime, Vec2::ZERO), 4);
                auto seq = Sequence::create(addEasing, _finishingCallback, NULL);
                addLayer->runAction(seq);
            }
        }
            break;
    }
}
