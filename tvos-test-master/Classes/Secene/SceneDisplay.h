//
//  SceneDisplay.h
//  gamebase
//
//  Created by Phi Dzung on 5/15/15.
//
//

#ifndef __gamebase__SceneDisplay__
#define __gamebase__SceneDisplay__

#include "cocos2d.h"
#include "LayerDisplay.h"
#include "LayerContainer.h"

typedef enum
{
    LOADING_SCENE_ID = 0,
    STARTGAME_SCENE_ID,
    MAINGAME_SCENE_ID,
}SCENE_ID;

class SceneDisplay : public cocos2d::Scene
{
public:
    
    
    LayerContainer* getLayerContainer(){return _layerContainer;};
    cocos2d::Map<int, LayerDisplay*>& getDictionary(){return _dictionary;};
    
    bool insertLayer(const LAYER_ID layerId, LayerDisplay* layer);
    
    virtual void onEnter() override;
    virtual bool init() override;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JNIEXPORT void JNICALL Java_com_newwindsoft_basegame_UtilActivity_resultFunc
    (JNIEnv *, jobject, jint);
#endif
private:
    cocos2d::Map<int, LayerDisplay*> _dictionary;
    LayerContainer* _layerContainer;
protected:
    SceneDisplay();
    virtual ~SceneDisplay();
};

#endif /* defined(__gamebase__SceneDisplay__) */
