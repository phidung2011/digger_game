//
//  TransitionManager.h
//  gamebase
//
//  Created by NGOCDIEP on 4/20/15.
//
//

#ifndef __gamebase__TransitionManager__
#define __gamebase__TransitionManager__

#include "LayerDisplay.h"
#include "SceneDisplay.h"

enum class TransitionType
{
    NONE,
    FADE,
    SLASH,
    SLIDE_LEFT,
    SLIDE_RIGHT,
    SLIDE_UP,
    SLIDE_DOWN,
    ROTATE,
    SCALE,
};
class TransitionManager
{
public:
    TransitionManager();
    ~TransitionManager();
    
    static TransitionManager* getInstance();
    
    
    bool isTransitioning(){return _isTransitioning;};
    
    bool addToScene(const LAYER_ID addLayerId, TransitionType transition = TransitionType::NONE, cocos2d::Ref* pSender = NULL, float time = 1.0f);
    
    bool removeFromScene(const LAYER_ID removeLayerId, TransitionType transition = TransitionType::NONE, cocos2d::Ref* pSender = NULL, float time = 1.0f);
    
    bool go(const LAYER_ID removeLayerId, const LAYER_ID addLayerId, TransitionType transition = TransitionType::NONE, cocos2d::Ref* pSender = NULL, float time = 1.0f);
    
    SceneDisplay* getCanvas(){return _canvas;};
    
    void setCanvas(SceneDisplay* canvas){_canvas = canvas;};
    
    bool addToSceneByCustomTransition(const LAYER_ID addLayerId, cocos2d::Ref* pSender = NULL);
    bool removeFromSceneByCustomTransition(const LAYER_ID removeLayerId, cocos2d::Ref* pSender = NULL);
    
private:
    bool _isTransitioning;
    
    float _transitionTime;
    
    SceneDisplay* _canvas;
    cocos2d::Layer* _loadingLayer;
    
    cocos2d::Vec2 _addLayerPos;
    cocos2d::Vec2 _removeLayerPos;
    
    cocos2d::CallFunc* _loadingCallback;
    cocos2d::CallFunc* _finishingCallback;
    
    void setTransitionState(TransitionType type);
    
    static TransitionManager* _instance;
    
    
    void setupTransition(LayerDisplay* addLayer, LayerDisplay* removeLayer ,TransitionType transition);
    
    void setupDefault();
};

#endif /* defined(__gamebase__TransitionManager__) */
