//
//  DCDraw.cpp
//  gamebase
//
//  Created by NGOCDIEP on 5/4/15.
//
//

#include "Popup.h"
#include "GameConfig.h"


CPopup::CPopup()
: _okButton(NULL)
, _cancelButton(NULL)
, _closeButton(NULL)
{

}

CPopup::~CPopup()
{

}
//bool CPopup::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
//{
//    if (_background)
//    {
//        if (!_background->getBoundingBox().containsPoint(touch->getLocation()))
//        {
//            this->onExitTransition();
//        }
//    }
//    return true;
//}

bool CPopup::init()
{
//    _listener = EventListenerTouchOneByOne::create();
//    _listener->setSwallowTouches(true);
//    _listener->onTouchBegan = CC_CALLBACK_2(CPopup::onTouchBegan, this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
    
    if (!LayerDisplay::init())
    {
        return false;
    }
    LayerColor* layer = LayerColor::create(Color4B::BLACK);
    layer->setOpacity(100);
    this->addChild(layer, -1);
    this->ignoreAnchorPointForPosition(true);
    
    return true;
}

void CPopup::onExitTransition()
{

    if (_background) {
        _background->setScale(1);
        auto call = CallFunc::create([this]()
                                     {
                                         
                                         _background->setScale(1);
                                         _background->setOpacity(255);
                                         _eventDispatcher->setEnabled(true);
                                         this->removeFromParent();
                                         
                                     });
        
        auto spawn = Spawn::create(FadeOut::create(0.08), ScaleTo::create(0.08, 0.0), NULL);
        
        auto seqRemove = Sequence::create(ScaleTo::create(0.12, 0.95),
                                          ScaleTo::create(0.12, 1.05),
                                          spawn,
                                          call, NULL);
        
        _eventDispatcher->setEnabled(false);
        _background->runAction(seqRemove);
    }
    
}

void CPopup::onEnterTransition()
{
    if (_background) {
        _background->setScale(0);
        auto call = CallFunc::create([this]()
                                     {
                                         
//                                         _background->setScale(1);
//                                         _background->setOpacity(255);
                                         _eventDispatcher->setEnabled(true);
                                         this->popupTransition();
                                     });
        auto seqAdd = Sequence::create(Animator::pumpIn(_background),
                                       call, NULL);
        _eventDispatcher->setEnabled(false);
        _background->runAction(seqAdd);
        
    }

}


