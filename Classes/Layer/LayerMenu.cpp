//
//  LayerMenu.cpp
//  gamebase
//
//  Created by HAINX on 15/7/15.
//
//


#include "LayerMenu.h"
#include "GameConfig.h"
#include "NativeUtils.h"
#include "Utils.h"
#include "PlayGameConstants.h"
#include "StartGameScene.h"
#include "PlayGameSingleton.h"

#define TAG_BTN_PLAYGAME 1
#define TAG_BTN_SHARE_FB 2
#define TAG_BTN_SHARE_TW 3
#define TAG_BTN_SETTING 4
#define TAG_BTN_HELP 5
#define TAG_BTN_SHOP 6
#define TAG_BTN_HIGHSCORE 7
#define TAG_BTN_EXIT 8

LayerMenu::LayerMenu()
{
    
}
LayerMenu::~LayerMenu()
{
    
}

bool LayerMenu::init()
{
    if (!LayerDisplay::init())
    {
        return false;
    }
    this->_layerId = LAYER_MENU_ID;
    this->_layerIndex = GUI_LAYER_INDEX;
    
    _btnPlay = TVWidget::create(UI_BTN_PLAYGAME);
    _btnPlay->ignoreAnchorPointForPosition(true);
    _btnPlay->setPosition(Vec2(winSize.width*0.5 - _btnPlay->getContentSize().width*0.5,67));
    m_pWindow->addChild(_btnPlay);
    
//    _btnShareFB = TVWidget::create(UI_BTN_SHARE_FB);
//    _btnShareFB->ignoreAnchorPointForPosition(true);
//    _btnShareFB->setPosition(VisibleRect::rightBottom() + Vec2(-128,35));
//    m_pWindow->addChild(_btnShareFB);
    
//    _btnShareTW = TVWidget::create(UI_BTN_SHARE_TW);
//    _btnShareTW->ignoreAnchorPointForPosition(true);
//    _btnShareTW->setPosition(VisibleRect::rightBottom() + Vec2(-228,35));
//    m_pWindow->addChild(_btnShareTW);
    
    _btnHighScore = TVWidget::create(UI_BTN_HIGHSCORE);
    _btnHighScore->ignoreAnchorPointForPosition(true);
    _btnHighScore->setPosition(VisibleRect::leftTop() + Vec2(40, -100));
    m_pWindow->addChild(_btnHighScore);
    
    _btnSetting = TVWidget::create(UI_BTN_SETTING);
    _btnSetting->ignoreAnchorPointForPosition(true);
    _btnSetting->setPosition(VisibleRect::leftTop() + Vec2(130, -100));
    m_pWindow->addChild(_btnSetting);
    
    _btnShop = TVWidget::create(UI_BTN_SHOP);
    _btnShop->ignoreAnchorPointForPosition(true);
    _btnShop->setPosition(VisibleRect::leftTop() + Vec2(220, -100));
    m_pWindow->addChild(_btnShop);
    
    this->addChild(m_pWindow);
    
    this->setCurrentTarget(_btnPlay);
//    _btnPlay->setRightNode(_btnShareTW);
    _btnPlay->setLeftNode(_btnShop);
    _btnPlay->setTopNode(_btnShop);
    
//    _btnShareTW->setLeftNode(_btnPlay);
//    _btnShareTW->setRightNode(_btnShareFB);
//    _btnShareFB->setLeftNode(_btnShareTW);
    
    _btnHighScore->setRightNode(_btnSetting);
    _btnHighScore->setBotNode(_btnPlay);
    _btnSetting->setLeftNode(_btnHighScore);
    _btnSetting->setRightNode(_btnShop);
    _btnSetting->setBotNode(_btnPlay);
    _btnShop->setRightNode(_btnPlay);
    _btnShop->setBotNode(_btnPlay);
    _btnShop->setLeftNode(_btnSetting);
    
    
    _btnPlay->setOnSelectCallback([this]{
        GameSingleton::getInstance()->_coin = NativeUtils::getDataInt(USER_COIN);
        GameSingleton::getInstance()->_removeAds = NativeUtils::getDataInt(USER_REMOVE_ADS);
        
        TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
        this->setOnExitCallback([this]
                                {
                                    TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_SELECT_LAND_ID);
                                    
                                });
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_BTN_PLAY);
#else
        AUDIO::play2d(EFFECT_BTN_PLAY, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        
        NativeUtils::sendAnalytics("Game Start");
        NativeUtils::initialGCM();
    });
    
    _btnSetting->setOnSelectCallback([this]{
        TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
        this->setOnExitCallback([this]
                                {
                                    TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_SETTING_ID);
                                });
        
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
        AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        
        NativeUtils::sendAnalytics("Game Option");
    });
    
    
    _btnHighScore->setOnSelectCallback([this]{
        NativeUtils::sendAnalytics("Show Leaderboards");
        NativeUtils::showLeaderboard(LEAD_STAR_MODE);
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
        AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
    });
    
    _btnShop->setOnSelectCallback([this]{
        TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
        this->setOnExitCallback([this]
                                {
                                    TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_SHOP_BUY_COIN_ID);
                                });
        
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
        AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
    });
    
    
    return true;
}



void LayerMenu::onClick(cocos2d::Ref *pSender)
{
    if (pSender == _btnPlay)
    {
        
        
    }
    else if (pSender == _btnSetting)
    {
        
    }
    else if (pSender == _btnHighScore)
    {
        
    }
//    else if(pSender == _btnShareFB)
//    {
//#if (USE_SIMPLE_AUDIO_ENGINE)
//        SIMPLE_AUDIO->playEffect(EFFECT_BTN);
//#else
//        AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
//#endif
//        NativeUtils::shareOnFacebook("message", "google.com", "",1);
//    }
//    else if(pSender == _btnShareTW)
//    {
//#if (USE_SIMPLE_AUDIO_ENGINE)
//        SIMPLE_AUDIO->playEffect(EFFECT_BTN);
//#else
//        AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
//#endif
//        NativeUtils::shareOnTwitter("message", "google.com", "",1);
//    }
    else if (pSender == _btnShop)
    {
        TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
        this->setOnExitCallback([this]
                                {
                                    TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_SHOP_BUY_COIN_ID);
                                });
        
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
        AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
    }
}


void LayerMenu::onEnterTransition()
{
//    NativeUtils::hideAd();
    auto logoImg = StartGameScene::getInstance()->getLogoImage();
    logoImg->setOpacity(255);
    logoImg->runAction(Animator::dropDown(logoImg));
    
    _btnPlay->runAction(Animator::pumpIn(_btnPlay));
//    _btnShareFB->runAction(Animator::pumpIn(_btnShareFB));
//    _btnShareTW->runAction(Animator::pumpIn(_btnShareTW));
    
    cocos2d::Vector<cocos2d::Node*> temp;
    temp.pushBack(_btnHighScore);
    temp.pushBack(_btnSetting);
//    temp.pushBack(_btnHelp);
    temp.pushBack(_btnShop);
//    temp.pushBack(_btnExit);
    GameSingleton::getInstance()->isStartGame = true;
    
    Animator::multiDropDown(0.07, temp);
    
    _eventDispatcher->setEnabled(false);
    
    auto call = CallFunc::create([this]{
        if (PlayGameSingleton::sharedInstance()->_login)
            _eventDispatcher->setEnabled(true);
    });
    this->runAction(Sequence::create(DelayTime::create(1.2),call, NULL));
    
    StartGameScene::getInstance()->getFadeBackground()->runAction(FadeTo::create(0.3, 0));
}

void LayerMenu::onExitTransition()
{
    GameSingleton::getInstance()->isStartGame = false;
    auto logoImg = StartGameScene::getInstance()->getLogoImage();
    cocos2d::Vector<cocos2d::Node*> temp;
    temp.pushBack(_btnHighScore);
    temp.pushBack(_btnSetting);
    temp.pushBack(_btnShop);
    
//    temp.pushBack(_btnShareFB);
//    temp.pushBack(_btnShareTW);
    temp.pushBack(_btnPlay);
    temp.pushBack(logoImg);
    
    
    Animator::multiFadeOut(0, temp);
    
    
//    logoImg->runAction(FadeOut::create(1));
    _eventDispatcher->setEnabled(false);
    
    auto call = CallFunc::create([this]{this->removeFromParent();});
    
    
    
    this->runAction(Sequence::create(DelayTime::create(1),call, NULL));
}


void LayerMenu::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    if (_eventDispatcher->isEnabled())
    {
        switch (key) {
            case cocos2d::Controller::BUTTON_A:
                CCLOG("BUTTON_A");
                if (_currentTarget &&
                    _currentTarget->getOnSelectCallback())
                {
                    _currentTarget->onSelect();
                }
                
                break;
            case cocos2d::Controller::BUTTON_B:
                CCLOG("BUTTON_B");
                break;
            case cocos2d::Controller::BUTTON_C:
                CCLOG("BUTTON_C");
                break;
            case cocos2d::Controller::BUTTON_DPAD_CENTER:
                CCLOG("BUTTON_DPAD_CENTER");
                break;
            case cocos2d::Controller::BUTTON_DPAD_DOWN:
                CCLOG("BUTTON_DPAD_DOWN");
                break;
            case cocos2d::Controller::BUTTON_DPAD_LEFT:
                CCLOG("BUTTON_DPAD_LEFT");
                break;
            case cocos2d::Controller::BUTTON_DPAD_RIGHT:
                CCLOG("BUTTON_DPAD_RIGHT");
                break;
            case cocos2d::Controller::BUTTON_DPAD_UP:
                CCLOG("BUTTON_DPAD_UP");
                break;
            case cocos2d::Controller::BUTTON_LEFT_SHOULDER:
                CCLOG("BUTTON_LEFT_SHOULDER");
                break;
            case cocos2d::Controller::BUTTON_LEFT_THUMBSTICK:
                CCLOG("BUTTON_LEFT_THUMBSTICK");
                break;
            case cocos2d::Controller::BUTTON_PAUSE:
                CCLOG("BUTTON_PAUSE");
                break;
            case cocos2d::Controller::BUTTON_RIGHT_SHOULDER:
                CCLOG("BUTTON_RIGHT_SHOULDER");
                break;
            case cocos2d::Controller::BUTTON_RIGHT_THUMBSTICK:
                CCLOG("BUTTON_RIGHT_THUMBSTICK");
                break;
            case cocos2d::Controller::BUTTON_SELECT:
                CCLOG("BUTTON_SELECT");
                break;
            case cocos2d::Controller::BUTTON_START:
                CCLOG("BUTTON_START");
                break;
            case cocos2d::Controller::BUTTON_X:
                CCLOG("BUTTON_X");
                break;
            case cocos2d::Controller::BUTTON_Y:
                CCLOG("BUTTON_Y");
                break;
            case cocos2d::Controller::BUTTON_Z:
                CCLOG("BUTTON_Z");
                break;
            default:
                break;
        }
    }
}




