//
//  ConnectionError.cpp
//  gamebase
//
//  Created by Phi Dzung on 10/8/15.
//
//

#include "ConnectionError.h"
#include "GameConfig.h"
#include "StartGameScene.h"
ConnectionError::ConnectionError()
{
    
}

ConnectionError::~ConnectionError()
{
    
}

bool ConnectionError::init()
{
    if (!CPopup::init())
        return false;
    
    
    this->_layerId = POPUP_CONNECTION_ID;
    this->_layerIndex = LOADING_LAYER_INDEX;
    
    _background = CImageView::create(UI_BG_POPUP_PAUSE);
    _background->setPosition(VisibleRect::center());
    this->addChild(_background);
    
    _labelTitle = CLabel::createWithTTF("Connection error\n Please check your internet connection!", FONT_PATH_GROBOLD, 22);
//    _labelTitle->setWidth(300);
    _labelTitle->setAlignment(cocos2d::TextHAlignment::CENTER);
//    _labelTitle->setLineBreakWithoutSpace(true);
    _labelTitle->setColor(Color3B(53, 30, 95));
    _labelTitle->setTextColor(Color4B(Color3B(53, 30, 95)));
    _labelTitle->ignoreAnchorPointForPosition(true);
    _labelTitle->setPosition(Vec2(_background->getContentSize()/2) + Vec2(-_labelTitle->getContentSize().width/2, -_labelTitle->getContentSize().height/2 + 65));
    _background->addChild(_labelTitle);
    
    _btnTryAgain = CButton::create(UI_BTN);
    _btnTryAgain->initText("Try Again", FONT_PATH_GROBOLD, 36, Size::ZERO, Color3B(53, 30, 95));
    _btnTryAgain->ignoreAnchorPointForPosition(true);
    _btnTryAgain->setPosition(Vec2(1136/2 - _btnTryAgain->getContentSize().width/2, 230));
    _btnTryAgain->setOnTouchBeganListener(this, ccw_touchbegan_selector(ConnectionError::onClick));
    m_pWindow->addChild(_btnTryAgain);
    
    m_pWindow->setPosition(-VisibleRect::center() + _background->getContentSize()/2);
    _background->addChild(m_pWindow);
    return true;
}

void ConnectionError::onClick(cocos2d::Ref *pSender)
{
    if (pSender == _btnTryAgain)
    {
        TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
    }
}
void ConnectionError::popupTransition()
{
//    cocos2d::Vector<Node*> tmp;
//    
//    for (int i = 0; i < _labelTitle->getString().length(); i++)
//    {
//        if (_labelTitle->getString().at(i) != ' ')
//        {
//            tmp.pushBack(_labelTitle->getLetter(i));
//        }
//    }
//    
//    Animator::multiJumpIn(0.02, tmp);
    
//    cocos2d::Vector<Node*> temp;
//    temp.pushBack(_btnTryAgain);
//    Animator::multiJumpIn(0,temp);
    
    _eventDispatcher->setEnabled(false);
    
    auto call = CallFunc::create([this]{_eventDispatcher->setEnabled(true);});
    this->runAction(Sequence::create(DelayTime::create(0.7),call, NULL));
}

void ConnectionError::onEnterTransition()
{
    CPopup::onEnterTransition();
//    for (int i = 0; i < _labelTitle->getString().length(); i++)
//    {
//        if (_labelTitle->getString().at(i) != ' ')
//        {
//            _labelTitle->getLetter(i)->setScale(0);
//        }
//    }
    
//    _btnTryAgain->setScale(0);
}

void ConnectionError::onExitTransition()
{
    CPopup::onExitTransition();
    auto scene = StartGameScene::getInstance();
    
    TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_LOADING_ID);
    
    auto call = CallFunc::create([scene]{
        scene->reload();
    });
    scene->runAction(Sequence::createWithTwoActions(DelayTime::create(2.0), call));
}
