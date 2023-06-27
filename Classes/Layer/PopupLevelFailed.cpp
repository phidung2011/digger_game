//
//  PopupLevelFailed.cpp
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 9/16/15.
//
//

#include "PopupLevelFailed.h"
#include "GameConfig.h"
#include "StartGameScene.h"
#include "MainGameScene.h"
#include "NativeUtils.h"
PopupLevelFailed::PopupLevelFailed()
{
    
}

PopupLevelFailed::~PopupLevelFailed()
{
    
}

bool PopupLevelFailed::init()
{
    if (!CPopup::init())
    {
        return false;
    }
    
    
    this->_layerId = POPUP_LEVEL_FAILED_ID;
    this->_layerIndex = POPUP_LAYER_INDEX;
    
    _background = CImageView::create(UI_BG_POPUP_PAUSE);
    _background->setPosition(VisibleRect::center());
    this->addChild(_background);
    
    
    _labelTitle = CLabel::createWithTTF("FAIL", FONT_PATH_GROBOLD, 45);
    _labelTitle->setColor(Color3B(53, 30, 95));
    _labelTitle->setTextColor(Color4B(Color3B(53, 30, 95)));
    _labelTitle->ignoreAnchorPointForPosition(true);
    _labelTitle->setPosition(Vec2(_background->getContentSize()/2) + Vec2(-_labelTitle->getContentSize().width/2, -_labelTitle->getContentSize().height/2 + 85));
    _background->addChild(_labelTitle);
    
    
    _btnRestart = TVWidget::create(UI_BTN);
    
    auto labelRestart = CLabel::createWithTTF("Try again", FONT_PATH_GROBOLD, 36);
    labelRestart->setColor(Color3B(53, 30, 95));
    labelRestart->setPosition(_btnRestart->getContentSize()/2);
    
    _btnRestart->addChild(labelRestart);
    _btnRestart->ignoreAnchorPointForPosition(true);
    _btnRestart->setPosition(Vec2(1136/2 - _btnRestart->getContentSize().width/2, 305));
    m_pWindow->addChild(_btnRestart);
    
    _btnExit = TVWidget::create(UI_BTN);
    
    auto labelExit = CLabel::createWithTTF("Back", FONT_PATH_GROBOLD, 36);
    labelExit->setColor(Color3B(53, 30, 95));
    labelExit->setPosition(_btnExit->getContentSize()/2);
    
    _btnExit->addChild(labelExit);
    _btnExit->ignoreAnchorPointForPosition(true);
    _btnExit->setPosition(Vec2(1136/2 - _btnExit->getContentSize().width/2, 207));
    m_pWindow->addChild(_btnExit);
    
    m_pWindow->setPosition(-VisibleRect::center() + _background->getContentSize()/2);
    _background->addChild(m_pWindow);
    
    
    _btnRestart->setOnSelectCallback([this]{
        this->onClick(_btnRestart);
    });
    _btnExit->setOnSelectCallback([this]{
        this->onClick(_btnExit);
    });
    _btnRestart->setBotNode(_btnExit);
    _btnExit->setTopNode(_btnRestart);
    this->setCurrentTarget(_btnRestart);
    
    
    return true;
}

void PopupLevelFailed::onEnterTransition()
{
    NativeUtils::showFullscreen();
    CPopup::onEnterTransition();
    
    for (int i = 0; i < _labelTitle->getString().length(); i++)
    {
        if (_labelTitle->getString().at(i) != ' ')
        {
            _labelTitle->getLetter(i)->setScale(0);
        }
    }
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->playEffect(EFFECT_FAIL);
#else
    AUDIO::play2d(EFFECT_FAIL, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
    _btnExit->setScale(0);
    _btnRestart->setScale(0);
    if (_pSender)
        this->setOnExitCallback(NULL);
}

void PopupLevelFailed::onExitTransition()
{
    CPopup::onExitTransition();

}

void PopupLevelFailed::popupTransition()
{
    cocos2d::Vector<Node*> tmp;
    for (int i = 0; i < _labelTitle->getString().length(); i++)
    {
        if (_labelTitle->getString().at(i) != ' ')
        {
            tmp.pushBack(_labelTitle->getLetter(i));
        }
    }
    Animator::multiPumpIn(0.02, tmp);
    
    cocos2d::Vector<Node*> temp;
    temp.pushBack(_btnRestart);
    temp.pushBack(_btnExit);
    Animator::multiPumpIn(0.1, temp);
    
    _eventDispatcher->setEnabled(false);
    
    auto call = CallFunc::create([this]{
        _eventDispatcher->setEnabled(true);
        if (_currentTarget)
            _currentTarget->onTarget();
    });
    this->runAction(Sequence::create(DelayTime::create(1),call, NULL));
}

void PopupLevelFailed::onEnter()
{
    Layer::onEnter();
}

void PopupLevelFailed::onClick(cocos2d::Ref *pSender)
{
    if (pSender == _btnRestart)
    {
        _eventDispatcher->setEnabled(false);
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_RESTART);
#else
        AUDIO::play2d(EFFECT_RESTART, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif

        this->setOnExitCallback([this]{
            
            auto level = - MainGameScene::getInstance()->getLevelMap();
            auto _level = __Integer::create(level);
            TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_SHOP_ID, _level);
        });
        TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
    }
    else if (pSender == _btnExit)
    {
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_QUIT);
#else
        AUDIO::play2d(EFFECT_QUIT, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        _eventDispatcher->setEnabled(false);
//        auto land = MainGameScene::getInstance()->getLand();
//        Director::getInstance()->getTextureCache()->addImageAsync(StringUtils::format("GUI/StartGame/SelectLevel/img_map%d.png", (int)land), [](Texture2D* texture){});
        
        Director::getInstance()->popScene();

    }
}

void PopupLevelFailed::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    if (_eventDispatcher->isEnabled())
    {
        switch (key) {
            case cocos2d::Controller::BUTTON_A:
                CCLOG("BUTTON_A");
                if (_currentTarget && _currentTarget->getOnSelectCallback())
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
