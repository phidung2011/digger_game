//
//  Setting game
//  gamebase
//
//  Created by HuyPB on 6/10/15.
//
//
/*
 effect sound
1, click button
2, click skill
3, bom nổ
4, tít tít của bom hẹn giờ
5, đá rơi
6, ăn iteam(kim cương , vàng ...)
7, âm thanh  di chuyển của nhân vật chính
8, âm thanh  di chuyển của nhân vật phụ
9, âm thanh  bắn tên lửa( đặt bom)
10, âm thanh nhân vật chính chết
11, âm thanh khi chiến thắng
12, âm thanh khi show popup 
 
background music
1, khi khởi động ở màn hình start
2, âm thanh nền cho map rừng
3, âm thanh nền cho map nước 
4, âm thanh nền cho map băng tuyết
5, âm thanh nền cho map lửa

*/
#include "SettingGame.h"
#include "GameConfig.h"
#include "StartGameScene.h"

#define LEVEL_HARD 3
#define LEVEL_NORMAL 2
#define LEVEL_EASILY 1

#define HARD_STRING "HARD"
#define NORMAL_STRING "NORMAL"
#define EASY_STRING "EASY"

SettingGame* SettingGame::_instance = NULL;
SettingGame::SettingGame()
: _currentWidget(nullptr)
{
    CCLOG("%s %d", __PRETTY_FUNCTION__, __LINE__);
    _instance = this;
}
SettingGame::~SettingGame()
{
    CCLOG("%s %d", __PRETTY_FUNCTION__, __LINE__);    
}

bool SettingGame::init()
{
    
    if (!LayerDisplay::init())
    {
        return false;
    }
    this->_layerId = LAYER_SETTING_ID;
    this->_layerIndex = GUI_LAYER_INDEX;
    
    
    auto _backgroundWindow = CWidgetWindow::create();
    _background = CImageView::create("GUI/StartGame/SettingGame/bg.png");
    _background->addChild(_backgroundWindow);
    m_pWindow->addChild(_background);
    _background->setPosition(VisibleRect::center());
    this->addChild(m_pWindow);
    
//    _difficultBtn = CButton::create("GUI/StartGame/SettingGame/setting_btn.png");
//    _difficultBtn->setOnClickListener(this, ccw_click_selector(SettingGame::onClick));
//    _difficultBtn->setTag(1);
//    _difficultBtn->ignoreAnchorPointForPosition(true);
//    _difficultBtn->initText("Difficulty", FONT_PATH_GROBOLD, 30, Size::ZERO, Color3B(53, 30, 95));
//    _difficultBtn->setPosition(Vec2(30, _background->getContentSize().height*3/4 + 18));
    
//    auto bgDifficulty = Sprite::create("GUI/StartGame/SettingGame/bg_option.png");
//    bgDifficulty->setPosition(Vec2(_background->getContentSize().width/2 + 10, _difficultBtn->getPositionY() + _difficultBtn->getContentSize().height/2));
//    
//    _backgroundWindow->addChild(_difficultBtn,10);
//    _backgroundWindow->addChild(bgDifficulty);
    
    
    _soundBtn = CButton::create("GUI/StartGame/SettingGame/setting_btn.png");
    _soundBtn->ignoreAnchorPointForPosition(true);
    _soundBtn->initText("Sound", FONT_PATH_GROBOLD, 30, Size::ZERO, Color3B(53, 30, 95));
    _soundBtn->setPosition(Vec2(30, _background->getContentSize().height*3/4 - _soundBtn->getContentSize().height/2));
    
    auto bgSound = Sprite::create("GUI/StartGame/SettingGame/bg_option.png");
    bgSound->setOpacity(120);
    bgSound->setPosition(Vec2(_background->getContentSize().width/2 + 10, _soundBtn->getPositionY() + _soundBtn->getContentSize().height/2));
    
    _backgroundWindow->addChild(_soundBtn,10);
    _backgroundWindow->addChild(bgSound);
    
    _musicBtn = CButton::create("GUI/StartGame/SettingGame/setting_btn.png");
    _musicBtn->ignoreAnchorPointForPosition(true);
    _musicBtn->initText("Music", FONT_PATH_GROBOLD, 30, Size::ZERO, Color3B(53, 30, 95));
    _musicBtn->setPosition(Vec2(30, _background->getContentSize().height*1/4 - _musicBtn->getContentSize().height/2));
    
    auto bgMusic = Sprite::create("GUI/StartGame/SettingGame/bg_option.png");
    bgMusic->setOpacity(120);
    bgMusic->setPosition(Vec2(_background->getContentSize().width/2 + 10, _musicBtn->getPositionY() + _musicBtn->getContentSize().height/2));
    
    _backgroundWindow->addChild(_musicBtn,10);
    _backgroundWindow->addChild(bgMusic);
    
    //value difficult
//    std::string difficultStr;
//    _difficult = DATA_MGR->getGameSettingDocument()["difficult"].GetInt();
//    
//    if (_difficult == LEVEL_HARD) {
//        difficultStr = StringUtils::format("%s",HARD_STRING);
//    }
//    else if(_difficult == LEVEL_NORMAL)
//    {
//        difficultStr = StringUtils::format("%s",NORMAL_STRING);
//    }
//    else
//    {
//        difficultStr = StringUtils::format("%s",EASY_STRING);
//    }
//    
//    _diffcultLabel = CLabel::createWithTTF(difficultStr, FONT_PATH_GROBOLD, 30);
//    _diffcultLabel->setTouchEnabled(true);
//    _backgroundWindow->addChild(_diffcultLabel);
//    _diffcultLabel->setPosition(bgDifficulty->getPosition() + Vec2(75,0));
//    _diffcultLabel->setOnClickListener(this, ccw_click_selector(SettingGame::onClick));
//    _diffcultLabel->setTag(1);
    
    //value sound
    _sound = DATA_MGR->getGameSettingDocument()["sound"].GetInt();
    _soundSlider = CSlider::create("GUI/StartGame/SettingGame/slide_btn.png", "GUI/StartGame/SettingGame/slide_bar.png");
    _backgroundWindow->addChild(_soundSlider);
    _soundSlider->setAnchorPoint(Vec2(0,0.5));
    _soundSlider->setPosition(bgSound->getPosition() + Vec2(-70,0));
    _soundSlider->setValue(_sound);
//    _soundSlider->setValue(16 + viewFromValue(_sound));
//    _soundSlider->setOnValueChangedListener(this, ccw_valuechanged_selector(SettingGame::onValueChanged));
    
    
    //value music
    _music = DATA_MGR->getGameSettingDocument()["music"].GetInt();
    _musicSlider = CSlider::create("GUI/StartGame/SettingGame/slide_btn.png", "GUI/StartGame/SettingGame/slide_bar.png");
    _backgroundWindow->addChild(_musicSlider);
    _musicSlider->setPosition(bgMusic->getPosition() + Vec2(-70,0));
    _musicSlider->setAnchorPoint(Vec2(0,0.5));
    _musicSlider->setValue(_music);
//    _musicSlider->setValue(16 + viewFromValue(_music));
//    _musicSlider->setOnValueChangedListener(this, ccw_valuechanged_selector(SettingGame::onValueChanged));
    
    
//    _checkBox = CCheckBox::create();
//    _control = DATA_MGR->getGameSettingDocument()["control"].GetBool();
//    _checkBox->setNormalImage("GUI/StartGame/SettingGame/img_check_box.png");
//    _checkBox->setCheckedImage("GUI/StartGame/SettingGame/img_check.png");
//    _checkBox->setChecked(_control);
//    _checkBox->setOnCheckListener(this, ccw_check_selector(SettingGame::onCheck));
//    _checkBox->ignoreAnchorPointForPosition(true);
//    _checkBox->setPosition(Vec2(30, _background->getContentSize().height/4 - _checkBox->getContentSize().height/2));
//    auto bgCheckBox = Sprite::create("GUI/StartGame/SettingGame/bg_option.png");
//    bgCheckBox->setPosition(Vec2(_background->getContentSize().width/2 + 10, _checkBox->getPositionY() + _checkBox->getContentSize().height/2));
//
//    _backgroundWindow->addChild(_checkBox,10);
//    _backgroundWindow->addChild(bgCheckBox);
//    
//    
//    _checkBoxLabel = CLabel::createWithTTF("Joystick follows finger", FONT_PATH_GROBOLD, 32);
//    _checkBoxLabel->ignoreAnchorPointForPosition(true);
//    _checkBoxLabel->setPosition(_checkBox->getPosition() + Vec2(_checkBox->getContentSize().width + 10,15));
//    _checkBoxLabel->setTouchEnabled(true);
//    _checkBoxLabel->setOnClickListener(this, ccw_click_selector(SettingGame::onClick));
//    _backgroundWindow->addChild(_checkBoxLabel,10);
    
//    _exitBtn = CImageView::create(UI_BTN_BACK);
//    _exitBtn->setTouchEnabled(true);
//    _exitBtn->ignoreAnchorPointForPosition(true);
//    _exitBtn->setAnchorPoint(Vec2(0.5,0));
//    _exitBtn->setPosition(VisibleRect::leftTop() + Vec2(40, -100));
//    _exitBtn->setOnClickListener(this, ccw_click_selector(SettingGame::onClick));
//    m_pWindow->addChild(_exitBtn);
    
    _soundSlider->setTouchEnabled(false);
    _musicSlider->setTouchEnabled(false);
    
    GameSingleton::getInstance()->SOUND = _sound;
    GameSingleton::getInstance()->MUSIC = _music;
    
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->setBackgroundMusicVolume(GameSingleton::getInstance()->MUSIC*0.01);
    SIMPLE_AUDIO->setEffectsVolume(GameSingleton::getInstance()->SOUND*0.01);
#else
    AUDIO::setVolume(GameSingleton::getInstance()->BGM_AUDIO_ID, GameSingleton::getInstance()->MUSIC*0.01);
#endif
    
    return true;
}

//void SettingGame::onCheck()
//{
//    _control = !_control;
//}
void SettingGame::onClick(cocos2d::Ref *pSender)
{
//    if (pSender == _checkBoxLabel)
//    {
//        _checkBox->setChecked(!_control);
//    }
//    else if (pSender == _difficultBtn || pSender == _diffcultLabel)
//    {
//        if (_difficult == 1) {
//            _diffcultLabel->setString(NORMAL_STRING);
//            _difficult = 2;
//        }
//        else if(_difficult == 2)
//        {
//            _diffcultLabel->setString(HARD_STRING);
//            _difficult = 3;
//        }
//        else if (_difficult == 3)
//        {
//            _diffcultLabel->setString(EASY_STRING);
//            _difficult = 1;
//        }
//    }
    {
        
        DATA_MGR->getGameSettingDocument()["control"].SetBool(_control);
//        DATA_MGR->getGameSettingDocument()["difficult"].SetInt(_difficult);
        DATA_MGR->getGameSettingDocument()["sound"].SetInt(_sound);
        DATA_MGR->getGameSettingDocument()["music"].SetInt(_music);
        DATA_MGR->saveGameSetting();
        TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
        TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_MENU_ID);
        
        GameSingleton::getInstance()->SOUND = _sound;
        GameSingleton::getInstance()->MUSIC = _music;
        
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->setBackgroundMusicVolume(GameSingleton::getInstance()->MUSIC*0.01);
        SIMPLE_AUDIO->setEffectsVolume(GameSingleton::getInstance()->SOUND*0.01);
#else
        AUDIO::setVolume(GameSingleton::getInstance()->BGM_AUDIO_ID, GameSingleton::getInstance()->MUSIC*0.01);
#endif
        
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
        AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
    }
}
//void SettingGame::onValueChanged(Ref* pSender, int nValue)
//{
//    auto sender = (CSlider*)pSender;
//    
//    if (sender == _soundSlider)
//    {
//        int s = sender->getValue();
//        if (s < 16)
//        {
//            sender->setValue(16);
//        }
//        _sound =  viewFromValue(sender->getValue() - 16);
//    }
//    else
//    {
//        int m = sender->getValue();
//        if (m < 16)
//        {
//            sender->setValue(16);
//        }
//        _music =  viewFromValue(sender->getValue()-16);
//    }
//    
//    GameSingleton::getInstance()->SOUND = _sound;
//    GameSingleton::getInstance()->MUSIC = _music;
//
//#if (USE_SIMPLE_AUDIO_ENGINE)
//    SIMPLE_AUDIO->setBackgroundMusicVolume(GameSingleton::getInstance()->MUSIC*0.01);
//    SIMPLE_AUDIO->setEffectsVolume(GameSingleton::getInstance()->SOUND*0.01);
//#else
//    AUDIO::setVolume(GameSingleton::getInstance()->BGM_AUDIO_ID, GameSingleton::getInstance()->MUSIC*0.01);
//#endif
//}

//int SettingGame::viewFromValue(int value)
//{
//    return value*((float)100/84);
//}


void SettingGame::onEnterTransition()
{
    _eventDispatcher->setEnabled(true);
    
    _currentWidget = _soundSlider;
    _currentWidget->setOpacity(255);
    _musicSlider->setOpacity(177);
    
    GameSingleton::getInstance()->inSetting = true;
}
void SettingGame::onExitTransition()
{
    this->removeFromParent();
    GameSingleton::getInstance()->inSetting = false;
}

void SettingGame::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = touch->getLocation();
    
    log("touch ended: %f, %f", location.x, location.y);
    Vec2 delta = touch->getLocation() - touch->getStartLocation();
    
//    if (fabs(delta.x) > fabs(delta.y))
//    {
//        if (delta.x > 150)
//        {
//            if (_currentTarget && _currentTarget->getRightNode())
//            {
//                this->targetTo(_currentTarget->getRightNode());
//            }
//        }
//        else if (delta.x < -150)
//        {
//            if (_currentTarget && _currentTarget->getLeftNode())
//            {
//                this->targetTo(_currentTarget->getLeftNode());
//            }
//        }
//    }
    if (fabs(delta.x) < fabs(delta.y))
    {
        if (delta.y > 150)
        {
            
        }
        else if (delta.y < -150)
        {
            
        }
    }
}
void SettingGame::left()
{
    if (_currentWidget->getValue() <= 10)
    {
        _currentWidget->setValue(0);
    }
    else
    {
        _currentWidget->setValue(_currentWidget->getValue() - 10);
    }
    _sound = _soundSlider->getValue();
    _music = _musicSlider->getValue();
    GameSingleton::getInstance()->SOUND = _sound;
    GameSingleton::getInstance()->MUSIC = _music;
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->setBackgroundMusicVolume(GameSingleton::getInstance()->MUSIC*0.01);
    SIMPLE_AUDIO->setEffectsVolume(GameSingleton::getInstance()->SOUND*0.01);
#else
    AUDIO::setVolume(GameSingleton::getInstance()->BGM_AUDIO_ID, GameSingleton::getInstance()->MUSIC*0.01);
#endif
}

void SettingGame::right()
{
    if (_currentWidget->getValue() >= 90)
    {
        _currentWidget->setValue(100);
    }
    else
    {
        _currentWidget->setValue(_currentWidget->getValue() + 10);
    }
    
    _sound = _soundSlider->getValue();
    _music = _musicSlider->getValue();
    GameSingleton::getInstance()->SOUND = _sound;
    GameSingleton::getInstance()->MUSIC = _music;
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->setBackgroundMusicVolume(GameSingleton::getInstance()->MUSIC*0.01);
    SIMPLE_AUDIO->setEffectsVolume(GameSingleton::getInstance()->SOUND*0.01);
#else
    AUDIO::setVolume(GameSingleton::getInstance()->BGM_AUDIO_ID, GameSingleton::getInstance()->MUSIC*0.01);
#endif

    
}

void SettingGame::up()
{
    if (_currentWidget && _currentWidget == _musicSlider)
    {
        auto scale = FadeTo::create(0.1, 255);
        _soundSlider->runAction(scale);
        _musicSlider->runAction(FadeTo::create(0.1, 177));
        _currentWidget = _soundSlider;
    }
}

void SettingGame::down()
{
    if (_currentWidget && _currentWidget == _soundSlider)
    {
        
        auto scale = FadeTo::create(0.1, 255);
        _musicSlider->runAction(scale);
        _soundSlider->runAction(FadeTo::create(0.1, 177));
        _currentWidget = _musicSlider;
    }
}

void SettingGame::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = touch->getLocation();
    
    log("touch ended: %f, %f", location.x, location.y);
    Vec2 delta = touch->getLocation() - touch->getPreviousLocation();
    
    //    if (fabs(delta.x) > fabs(delta.y))
    //    {
    //        if (delta.x > 150)
    //        {
    //            if (_currentTarget && _currentTarget->getRightNode())
    //            {
    //                this->targetTo(_currentTarget->getRightNode());
    //            }
    //        }
    //        else if (delta.x < -150)
    //        {
    //            if (_currentTarget && _currentTarget->getLeftNode())
    //            {
    //                this->targetTo(_currentTarget->getLeftNode());
    //            }
    //        }
    //    }
    
    

}

void SettingGame::onKeyUp(cocos2d::Controller *controller, int key, cocos2d::Event *event)
{
    if (_eventDispatcher->isEnabled())
    {
        switch (key) {
            case cocos2d::Controller::BUTTON_A:
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
                this->onClick(nullptr);
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
