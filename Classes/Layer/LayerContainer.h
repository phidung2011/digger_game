//
//  LayerContainer.h
//  gamebase
//
//  Created by NGOCDIEP on 3/27/15.
//
//

#ifndef __gamebase__LayerContainer__
#define __gamebase__LayerContainer__

#include "cocos2d.h"

#define NUMBER_OF_LAYER 6


typedef enum
{
    INVALID_LAYER_INDEX = -1,
    BASE_LAYER_INDEX = 0,
    GAME_LAYER_INDEX,
    GUI_LAYER_INDEX,
    EFFECT_LAYER_INDEX,
    POPUP_LAYER_INDEX,
    LOADING_LAYER_INDEX,
}LAYER_INDEX;

class LayerContainer
{
private:
    cocos2d::Layer* _arrLayers[NUMBER_OF_LAYER];

public:
    LayerContainer(cocos2d::Node* canvas);
    ~LayerContainer();
    
    cocos2d::Layer* baseLayer();
    cocos2d::Layer* gameLayer();
    cocos2d::Layer* guiLayer();
    cocos2d::Layer* loadingLayer();
    cocos2d::Layer* popupLayer();
    cocos2d::Layer* effectLayer();
    cocos2d::Layer* getLayerByIndex(LAYER_INDEX index);
};

#endif /* defined(__gamebase__LayerContainer__) */
