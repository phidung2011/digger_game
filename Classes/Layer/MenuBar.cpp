//
//  MenuBar.cpp
//  gamebase
//
//  Created by NGOCDIEP on 7/21/15.
//
//

#include "MenuBar.h"
#include "GameConfig.h"
#include "MainGameScene.h"
#include "StartGameScene.h"
MenuBar::MenuBar()
{    
    
}
void MenuBar::pauseTime()
{
    this->unschedule(CC_SCHEDULE_SELECTOR(MenuBar::updateTime));
}
void MenuBar::resumeTime()
{
    this->schedule(CC_SCHEDULE_SELECTOR(MenuBar::updateTime), 1);
}
std::string MenuBar::convertTime(int time){
    if(time >= 0){
        int m = time / 60;
        int s = time % 60;
        
        return StringUtils::format("%02d:%02d",m,s);
    }
    return "00:00";
}
void MenuBar::updateTime(float f){
    _time--;
    if (_time <= 15)
    {
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_COUNT_DOWN);
#else
        AUDIO::play2d(EFFECT_COUNT_DOWN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
    }
    
    if (_time < 0)
    {
        this->pauseTime();
        MainGameScene::getInstance()->getPlayer()->setCurrentHp(1);
        MainGameScene::getInstance()->getPlayer()->destroy();
        return;
    }
    
    _labelTime->setString(convertTime(_time));
    
}
MenuBar::~MenuBar()
{
    this->unschedule(CC_SCHEDULE_SELECTOR(MenuBar::updateTime));
    CCLOG("%s",__PRETTY_FUNCTION__);
}

bool MenuBar::init()
{
    _time = MainGameScene::getInstance()->getPlayer()->getData().time;
    
    auto mainBar = CImageView::create(UI_IMG_BAR_MAIN);
    mainBar->setPosition(VisibleRect::top() + Vec2(0, -39.5));
    this->addChild(mainBar);
    
    _labelTime = CLabel::createWithTTF(convertTime(_time), FONT_PATH_BUBBLEGUM, 26);
    _labelTime->setPosition(Vec2(307, 37));
    _labelTime->setTextColor(Color4B::WHITE);
    mainBar->addChild(_labelTime);
    
    _labelScore = CLabel::createWithTTF("0", FONT_PATH_BUBBLEGUM, 26);
    _labelScore->setPosition(Vec2(201,34));
    _labelScore->setTextColor(Color4B::WHITE);
    mainBar->addChild(_labelScore);
    
    _progressBarFuel = CProgressBar::create(UI_PROGRESS_BAR_FUEL);
    _progressBarFuel->setPosition(Vec2(96,37));
    _progressBarFuel->setValue(MainGameScene::getInstance()->getPlayer()->getData().fuel);
    mainBar->addChild(_progressBarFuel);
    
    auto playerBar = CImageView::create(UI_IMG_BAR_PLAYER);
    playerBar->setPosition(VisibleRect::rightTop() + Vec2(-250, -39.5));
    m_pWindow->addChild(playerBar);
    
    _labelPlayerLives = CLabel::createWithTTF(StringUtils::format("%d",MainGameScene::getInstance()->getPlayer()->getCurrentHp()), FONT_PATH_GROBOLD, 30);
    _labelPlayerLives->setPosition(Vec2(47,23));
    _labelPlayerLives->setTextColor(Color4B::WHITE);
    playerBar->addChild(_labelPlayerLives);
    
    auto enemiesBar = CImageView::create(UI_IMG_BAR_ENEMIES);
    enemiesBar->setPosition(VisibleRect::leftTop() + Vec2(105, -41.5));
    this->addChild(enemiesBar);
    
    _labelEnemies = CLabel::createWithTTF(StringUtils::format("%d",MainGameScene::getInstance()->getPlayer()->getData().enemies), FONT_PATH_GROBOLD, 30);
    _labelEnemies->setPosition(Vec2(40,21));
    _labelEnemies->setTextColor(Color4B::WHITE);
    enemiesBar->addChild(_labelEnemies);
    
    auto diamondsBar = CImageView::create(UI_IMG_BAR_DIAMONDS);
    diamondsBar->setPosition(VisibleRect::leftTop() + Vec2(280, -41.5));
    this->addChild(diamondsBar);
    
    _labelDiamonds = CLabel::createWithTTF(StringUtils::format("%d",MainGameScene::getInstance()->getPlayer()->getData().diamonds), FONT_PATH_GROBOLD, 30);
    _labelDiamonds->setPosition(Vec2(40,21));
    _labelDiamonds->setTextColor(Color4B::WHITE);
    diamondsBar->addChild(_labelDiamonds);
    
//    auto btnPause = CImageView::create(UI_BTN_PAUSE);
//    btnPause->setPosition(VisibleRect::rightTop() + Vec2(-100, -42));
//    m_pWindow->addChild(btnPause);
    
    
    
    this->addChild(m_pWindow);
//    this->schedule(CC_SCHEDULE_SELECTOR(MenuBar::updateTime), 1);
    return true;
}


void MenuBar::onClick(cocos2d::Ref *pSender)
{
    MainGameScene::getInstance()->pauseGame();
    TransitionManager::getInstance()->addToSceneByCustomTransition(POPUP_PAUSE_ID);
}