//
//  LayerContainer.cpp
//  gamebase
//
//  Created by Phi Dzung on 3/27/15.
//
//

#include "LayerContainer.h"

USING_NS_CC;
LayerContainer::~LayerContainer()
{
    
}

LayerContainer::LayerContainer(cocos2d::Node* canvas)
{
    //create layer
    cocos2d::Layer * baseLayer = cocos2d::Layer::create();
    baseLayer->setName("base");
    _arrLayers[BASE_LAYER_INDEX] = baseLayer;
    
    cocos2d::Layer * gameLayer = cocos2d::Layer::create();
    gameLayer->setName("game");
    _arrLayers[GAME_LAYER_INDEX] = gameLayer;
    
    cocos2d::Layer * effectLayer = cocos2d::Layer::create();
    effectLayer->setName("effect");
    _arrLayers[EFFECT_LAYER_INDEX] = effectLayer;

    cocos2d::Layer * guiLayer = cocos2d::Layer::create();
    guiLayer->setName("gui");
    _arrLayers[GUI_LAYER_INDEX] = guiLayer;
    
    cocos2d::Layer * popupLayer = cocos2d::Layer::create();
    popupLayer->setName("popup");
    _arrLayers[POPUP_LAYER_INDEX] = popupLayer;
    
    cocos2d::Layer * loadingLayer = cocos2d::Layer::create();
    loadingLayer->setName("loading");
    _arrLayers[LOADING_LAYER_INDEX] = loadingLayer;
    
    //add layer
    canvas->addChild(baseLayer,BASE_LAYER_INDEX);
    canvas->addChild(gameLayer,GAME_LAYER_INDEX);
    canvas->addChild(effectLayer,EFFECT_LAYER_INDEX);
    canvas->addChild(popupLayer,POPUP_LAYER_INDEX);
    canvas->addChild(guiLayer,GUI_LAYER_INDEX);
    canvas->addChild(loadingLayer,LOADING_LAYER_INDEX);
}

cocos2d::Layer* LayerContainer::getLayerByIndex(LAYER_INDEX index)
{
    return _arrLayers[index];
}

cocos2d::Layer * LayerContainer::baseLayer()
{
    return _arrLayers[BASE_LAYER_INDEX];
}
cocos2d::Layer * LayerContainer::gameLayer()
{
    return _arrLayers[GAME_LAYER_INDEX];
}
cocos2d::Layer * LayerContainer::effectLayer()
{
    return _arrLayers[EFFECT_LAYER_INDEX];
}
cocos2d::Layer * LayerContainer::guiLayer()
{
    return _arrLayers[GUI_LAYER_INDEX];
}
cocos2d::Layer * LayerContainer::popupLayer()
{
    return _arrLayers[POPUP_LAYER_INDEX];
}
cocos2d::Layer * LayerContainer::loadingLayer()
{
    return _arrLayers[LOADING_LAYER_INDEX];
}
