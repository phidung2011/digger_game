

#include "GameSingleton.h"
#include "AppMacros.h"
#include "GameConfig.h"
USING_NS_CC;

GameSingleton * GameSingleton::_instance = NULL;

GameSingleton* GameSingleton::getInstance(void)
{
    if (!_instance)
    {
        _instance = new GameSingleton();
        _instance->init();
    }
    
    return _instance;
}

GameSingleton::GameSingleton()
{
    BGM_AUDIO_ID = -1;
    _coin = 50;
    _cachedImage = 0;
    _removeAds = 0;
    _loopSound = 0;
    isPlaying = false;
    isTouchDown = false;
    inSetting = false;
    isStartGame = false;
}

GameSingleton::~GameSingleton()
{
    _instance = NULL;
}

bool GameSingleton::init(void)
{
//    _winsize = Size::ze
    return true;
}

float GameSingleton::getScaleFixWith(){
//    float f = 1.0f;
//    
//    float fx = _winsizeCustom.width/_winsize.width;
//    float fy = _winsizeCustom.height/_winsize.height;
//    
//    f = 1 + (fx - fy);
    auto size = Director::getInstance()->getVisibleSize();
    return size.height/designResolutionSize.height;
}

float GameSingleton::getScaleFixHeight(){
    float f = 1.0f;
    
    float fx = _winsizeCustom.width/_winsize.width;
    float fy = _winsizeCustom.height/_winsize.height;
    
    f = 1 + (fy - fx);
    
    return f;
}

void GameSingleton::showTooltip(const std::string& content, cocos2d::Layer* target)
{
    cocos2d::Label* tooltip = cocos2d::Label::createWithTTF(content, FONT_PATH_GROBOLD, 32);
    tooltip->enableGlow(Color4B::BLACK);
    tooltip->enableOutline(Color4B::BLACK);
    tooltip->enableShadow();
    tooltip->setPosition(VisibleRect::center());
    target->addChild(tooltip);
    CallFunc* call = CallFunc::create([tooltip]
    {
        tooltip->removeFromParent();
    });
    tooltip->runAction(Sequence::create(DelayTime::create(1.5f),FadeOut::create(1), call , NULL));
    
    
}


