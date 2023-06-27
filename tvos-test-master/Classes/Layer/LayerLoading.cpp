//
//  LayerLoading.cpp
//  gamebase
//
//  Created by Phi Dzung on 9/30/15.
//
//

#include "LayerLoading.h"
#include "GameConfig.h"

LayerLoading::LayerLoading()
: _loadingCircle(NULL)
, _loadingLayer(NULL)
{
    
}

LayerLoading::~LayerLoading()
{
    _eventDispatcher->removeEventListener(_listener);
}

bool LayerLoading::init()
{
    if (!LayerDisplay::init())
    {
        return false;
    }
    
    
    this->_layerId = LAYER_LOADING_ID;
    this->_layerIndex = LOADING_LAYER_INDEX;
    
    


    
    
    return true;
}

void LayerLoading::onEnterTransition()
{
//    _loadingLayer->setOpacity(0);
//    _eventDispatcher->setEnabled(false);
//    
//    auto call = CallFunc::create([this]{
//        _eventDispatcher->setEnabled(true);
//        _loadingCircle->setVisible(true);
//    });
//    
//    auto fade = FadeTo::create(0.2, 100);
//    auto seq = Sequence::create(fade, call, NULL);
//    
//    
//    auto rot = RotateBy::create(1, 360);
//    auto rep = RepeatForever::create(rot);
//    
//    _loadingCircle->runAction(rep);
//    
//    _loadingLayer->runAction(seq);

}

void LayerLoading::onExitTransition()
{

    this->removeFromParent();
}
