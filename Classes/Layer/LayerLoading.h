//
//  LayerLoading.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 9/30/15.
//
//

#ifndef __gamebase__LayerLoading__
#define __gamebase__LayerLoading__

#include "LayerDisplay.h"

class LayerLoading : public LayerDisplay
{
public:
    CREATE_FUNC(LayerLoading);
    
    void onExitTransition() override;
    void onEnterTransition() override;
private:
    cocos2d::EventListenerTouchOneByOne* _listener;
    
protected:
    LayerLoading();
    ~LayerLoading();
    bool init() override;
    
    
    cocos2d::DrawNode* _stencil;
    cocos2d::Sprite* _loadingCircle;
    cocos2d::LayerColor* _loadingLayer;
};

#endif /* defined(__gamebase__LayerLoading__) */
