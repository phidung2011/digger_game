//
//  SplashScene.h
//  gamebase
//
//  Created by NGOCDIEP on 4/16/15.
//
//

#ifndef __gamebase__SplashScene__
#define __gamebase__SplashScene__

#include "ConvertUtils.h"
#include "../cocos2d.h"
#include "LayerContainer.h"
#include <SceneDisplay.h>

USING_NS_CC;
class SplashScene: public SceneDisplay
{
public:
    SplashScene();
    ~SplashScene();
    CREATE_FUNC(SplashScene);
    void onEnterTransitionDidFinish();
    
    LayerContainer* _LayerContainer;
};
#endif /* defined(__gamebase__SplashScene__) */
