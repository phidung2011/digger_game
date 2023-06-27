//
//  SceneDisplay.cpp
//  gamebase
//
//  Created by Phi Dzung on 5/15/15.
//
//

#include "SceneDisplay.h"
#include "TransitionManager.h"
USING_NS_CC;

SceneDisplay::SceneDisplay()
{
    
}
SceneDisplay::~SceneDisplay()
{
    CCLOG("%s",__PRETTY_FUNCTION__);
    if (!_dictionary.empty())
    {
        _dictionary.clear();
    }
    delete _layerContainer;
}

bool SceneDisplay::init()
{
    if (!Scene::init())
    {
        return false;
    }
    _layerContainer = new LayerContainer(this);
    return true;
}

bool SceneDisplay::insertLayer(const LAYER_ID layerId, LayerDisplay *layer)
{
    if(_dictionary.at(layerId) == NULL)
    {
        _dictionary.insert(layerId, layer);
        return true;
    }
    return false;
}

void SceneDisplay::onEnter()
{
    TransitionManager::getInstance()->setCanvas(this);
    cocos2d::Scene::onEnter();
}

#ifdef __cplusplus
extern "C" {
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
    JNIEXPORT void JNICALL Java_com_newwindsoft_basegame_UtilActivity_resultFunc(JNIEnv *env, jobject obj, jint flag)
    {
        int fl = (int)flag;
    }
#endif
#ifdef __cplusplus
}
#endif


