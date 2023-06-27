//
//  Game win
//  gamebase
//
//  Created by HuyPB on 7/16/15.
//
//

#include "GameWin.h"
#include <GameConfig.h>
#include "NativeUtils.h"
#include "MainGameScene.h"
#include "StartGameScene.h"
#include "AvatarConfig.h"
#include "StartGameScene.h"
#include "DataManager.h"

USING_NS_CC_WIDGET;

//#define BUTTON_SOUND "btnSound"
//#define BUTTON_MUSIC "btnMusic"
//#define BUTTON_LEVEL "btnLevel"
//#define LEVEL_STRING "level"
//#define SPEED_STRING "speed"
//#define MUSIC_STRING "music"
//#define SOUND_STRING "sound"
//#define HARD_STRING "hard"
//#define NORMAL_STRING "normal"
//#define EASILY_STRING "easily"
//#define ON_STRING "on"
//#define OFF_STRING "off"
//#define FONT_SIZE_SETTING 40
//#define BUTTON_SIZE  Size(150,35)
enum{
    shareFB =10,
    shareTT,
    playAgain,
    menuSelect,
    nextLevel
};
GameWin::GameWin()
: _labelDiamonds(nullptr)
, _labelEnemies(nullptr)
, _labelTime(nullptr)
, _labelFuel(nullptr)
{
    
}
GameWin::~GameWin()
{

}

bool GameWin::init()
{
    if (!CPopup::init())
        return false;
    
    this->_layerId = POPUP_WIN_ID;
    this->_layerIndex = POPUP_LAYER_INDEX;
    //tao BG
    _background = CImageView::create("GUI/PlayGame/PopupLevelComplete/bg.png");
    _background->ignoreAnchorPointForPosition(true);
    _background->setPosition(VisibleRect::center() - Vec2(_background->getContentSize()/2) + Vec2(0,-40));
    this->addChild(_background);
    
    _titleBar = Sprite::create("GUI/PlayGame/PopupLevelComplete/title_bar.png");
    _titleBar->ignoreAnchorPointForPosition(true);
    _titleBar->setPosition(Vec2(_background->getContentSize()/2) + Vec2(-_titleBar->getContentSize().width/2, 126));
    _background->addChild(_titleBar,10);
    
    
    _iconDiamonds1 = Sprite::create("GUI/PlayGame/PopupLevelComplete/icon_diamond.png");
    _iconDiamonds1->ignoreAnchorPointForPosition(true);
    _iconDiamonds1->setPosition(Vec2(135,270));
    _background->addChild(_iconDiamonds1);
    
    _iconDiamonds3 = Sprite::create("GUI/PlayGame/PopupLevelComplete/icon_diamond.png");
    _iconDiamonds3->ignoreAnchorPointForPosition(true);
    _iconDiamonds3->setPosition(Vec2(175,270));
    _background->addChild(_iconDiamonds3);
    
    _iconDiamonds2 = Sprite::create("GUI/PlayGame/PopupLevelComplete/icon_diamond.png");
    _iconDiamonds2->ignoreAnchorPointForPosition(true);
    _iconDiamonds2->setPosition(Vec2(155,270));
    _background->addChild(_iconDiamonds2);
    
    _iconEnemies = Sprite::create("GUI/PlayGame/PopupLevelComplete/icon_enemies.png");
    _iconEnemies->ignoreAnchorPointForPosition(true);
    _iconEnemies->setPosition(Vec2(_iconDiamonds2->getPositionX() + _iconDiamonds2->getContentSize().width/2 - _iconEnemies->getContentSize().width/2, 220 ));
    _background->addChild(_iconEnemies);
    
    _iconClock = Sprite::create("GUI/PlayGame/PopupLevelComplete/icon_clock.png");
    _iconClock->ignoreAnchorPointForPosition(true);
    _iconClock->setPosition(Vec2(_iconDiamonds2->getPositionX() + _iconDiamonds2->getContentSize().width/2 - _iconClock->getContentSize().width/2, 170 ));
    _background->addChild(_iconClock);
    
    _iconFuel = Sprite::create("GUI/PlayGame/PopupLevelComplete/icon_fuel.png");
    _iconFuel->ignoreAnchorPointForPosition(true);
    _iconFuel->setPosition(Vec2(_iconDiamonds2->getPositionX() + _iconDiamonds2->getContentSize().width/2 - _iconFuel->getContentSize().width/2, 120 ));
    _background->addChild(_iconFuel);
    
    
    
    _labelDiamonds = CLabel::createWithTTF("", FONT_PATH_GROBOLD, 30);
    _labelDiamonds->setAnchorPoint(Vec2(0.5,0));
    _labelDiamonds->setPosition(Vec2(350,270));
    
    _labelEnemies = CLabel::createWithTTF("", FONT_PATH_GROBOLD, 30);
    _labelEnemies->setAnchorPoint(Vec2(0.5,0));
    _labelEnemies->setPosition(Vec2(350,220));
    
    _labelTime = CLabel::createWithTTF("", FONT_PATH_GROBOLD, 30);
    _labelTime->setAnchorPoint(Vec2(0.5,0));
    _labelTime->setPosition(Vec2(350,170));
    
    _labelFuel = CLabel::createWithTTF("", FONT_PATH_GROBOLD, 30);
    _labelFuel->setAnchorPoint(Vec2(0.5,0));
    _labelFuel->setPosition(Vec2(350,120));
    
    _labelTotalScore = CLabel::createWithTTF("", FONT_PATH_GROBOLD, 30);
    _labelTotalScore->setAnchorPoint(Vec2(0.5,0));
    _labelTotalScore->setPosition(Vec2(350,45));
    
    _labelTextScore = CLabel::createWithTTF("SCORE:", FONT_PATH_GROBOLD, 30);
    _labelTextScore->ignoreAnchorPointForPosition(true);
    _labelTextScore->setPosition(Vec2(_iconDiamonds2->getPositionX() + _iconDiamonds2->getContentSize().width/2, 45 ));
    _background->addChild(_labelTextScore);
    
    
    _starIcon1 = Sprite::create();
    _starIcon1->ignoreAnchorPointForPosition(true);
    _starIcon1->setPosition(Vec2(239.5 - 54,368));
    
    
    _starIcon2 = Sprite::create();
    _starIcon2->ignoreAnchorPointForPosition(true);
    _starIcon2->setPosition(Vec2(239.5,368));
    
    
    _starIcon3 = Sprite::create();
    _starIcon3->ignoreAnchorPointForPosition(true);
    _starIcon3->setPosition(Vec2(239.5 + 75,368));
    
    
    _background->addChild(_starIcon1);
    _background->addChild(_starIcon3);
    _background->addChild(_starIcon2);
    
    
    _background->addChild(_labelDiamonds);
    _background->addChild(_labelEnemies);
    _background->addChild(_labelFuel);
    _background->addChild(_labelTime);
    _background->addChild(_labelTotalScore);
    
    
    for (short i = 0; i < 4; i++)
    {
        _equalLabel[i] = CLabel::createWithTTF("x", FONT_PATH_GROBOLD, 30);
        _equalLabel[i]->ignoreAnchorPointForPosition(true);
        _equalLabel[i]->setPosition(Vec2(250, 270 - i*50));
        _background->addChild(_equalLabel[i]);
    }
    
    return true;
}

void GameWin::onClick(Ref* pSender)
{
    CButton *bt = (CButton*)pSender;
    int tag = bt->getTag();
    if (tag== shareFB) {
        //HelperUtilsInterface::ShareFBTT(1, "share fb", "", "");
        NativeUtils::shareOnFacebook("", "google.com", "",1);
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
        AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
    }
    else if (tag == shareTT)
    {
        //HelperUtilsInterface::ShareFBTT(2, "share TT", "", "");
        NativeUtils::shareOnTwitter("", "google.com", "",1);
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
        AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
    }
    else if (tag == playAgain)
    {
        TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
        
        this->setOnExitCallback([this]
        {
            int level = MainGameScene::getInstance()->getLevelMap();
            LAND land = MainGameScene::getInstance()->getLand();
            MapData data;
            auto scene = MainGameScene::create(land, level, data);
            Director::getInstance()->replaceScene(scene);
        });

    }
    else if (tag == nextLevel)
    {
        int level = MainGameScene::getInstance()->getLevelMap() + 1;
        LAND land = MainGameScene::getInstance()->getLand();
        MapData data;
        auto scene = MainGameScene::create(land, level, data);
        Director::getInstance()->replaceScene(scene);
    }
}


void GameWin::setStar()
{
}

void GameWin::onEnterTransition()
{
    
    NativeUtils::showFullscreen();
    CPopup::onEnterTransition();
    StartGameScene::getInstance()->getDictionary().at(LAYER_LEVEL_ID)->setTag(1);
    
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->playEffect(EFFECT_WIN);
#else
    AUDIO::play2d(EFFECT_WIN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif

    if (_pSender)
    {
        auto arr = (__Array*)_pSender;
        _diamonds = dynamic_cast<__Integer*>(arr->getObjectAtIndex(0))->getValue();
        _enemies = dynamic_cast<__Integer*>(arr->getObjectAtIndex(1))->getValue();
        _time = dynamic_cast<__Integer*>(arr->getObjectAtIndex(2))->getValue();
        _fuel = dynamic_cast<__Integer*>(arr->getObjectAtIndex(3))->getValue();
        _pSender->release();
    }
    
    int scoreDiamonds = _diamonds * (int)SCORE::BONUS_DIAMOND;
    int scoreEnemies = _enemies * (int)SCORE::BONUS_ENEMIES;
    int scoreTime = _time * (int)SCORE::BONUS_TIME;
    int scoreFuel = _fuel * (int)SCORE::BONUS_FUEL;
    
    auto data = MainGameScene::getInstance()->getPlayer()->getData();
    
    int scoreBomb = (data.mines + data.bombs + data.rockets + data.time_bombs)* (int)SCORE::BONUS_BOMB;
    int scoreLives = MainGameScene::getInstance()->getPlayer()->getCurrentHp()* (int)SCORE::BONUS_LIVES;
    
    std::string diamonds = StringUtils::format("%d",_diamonds);
    std::string enemy = StringUtils::format("%d",_enemies);
    std::string time = StringUtils::format("%d",_time);
    std::string fuel = StringUtils::format("%d",_fuel);
    
    _labelDiamonds->setString(diamonds);
    _labelEnemies->setString(enemy);
    _labelTime->setString(time);
    _labelFuel->setString(fuel);
    
    MainGameScene::getInstance()->getPlayer()->_totalScore += scoreDiamonds + scoreEnemies + scoreTime + scoreFuel + scoreBomb + scoreLives;
    
    _labelTotalScore->setString(StringUtils::format("%d", MainGameScene::getInstance()->getPlayer()->_totalScore));
    
    
    CCLOG("-------- score: %d", MainGameScene::getInstance()->getPlayer()->_totalScore);
    //tinh so sao nhan duoc
    
    _star = 0;
    
    if(MainGameScene::getInstance()->getPlayer()->_totalScore >= (MainGameScene::getInstance()->getTileMap()->getTotalScoreFull()) * 0.8){
        

        _star = 3;
    }else if(MainGameScene::getInstance()->getPlayer()->_totalScore >= (MainGameScene::getInstance()->getTileMap()->getTotalScoreFull()) * 0.55){
        

        _star = 2;
    }else{

        _star = 1;
    }
    
    int lives = MainGameScene::getInstance()->getPlayer()->getCurrentHp();
    if (lives < _star)
    {
        _star = lives;
    }
    
    switch (_star) {
        case 3:
            _starIcon1->setTexture("GUI/PlayGame/PopupLevelComplete/icon_star_small.png");
            _starIcon2->setTexture("GUI/PlayGame/PopupLevelComplete/icon_star.png");
            _starIcon3->setTexture("GUI/PlayGame/PopupLevelComplete/icon_star_small.png");
            break;
        case 2:
            _starIcon1->setTexture("GUI/PlayGame/PopupLevelComplete/icon_star_small.png");
            _starIcon2->setTexture("GUI/PlayGame/PopupLevelComplete/icon_star.png");
            _starIcon3->setTexture("GUI/PlayGame/PopupLevelComplete/icon_star_fail_small.png");
            break;
        case 1:
            _starIcon1->setTexture("GUI/PlayGame/PopupLevelComplete/icon_star_small.png");
            _starIcon2->setTexture("GUI/PlayGame/PopupLevelComplete/icon_star_fail.png");
            _starIcon3->setTexture("GUI/PlayGame/PopupLevelComplete/icon_star_fail_small.png");
            break;
        default:
            break;
    }
    
    DataManager::getInstance()->updateStar((int)MainGameScene::getInstance()->getLand(), MainGameScene::getInstance()->getLevelMap(), _star);
    
    cocos2d::Vector<cocos2d::Node*> temp;
    temp.pushBack(_iconDiamonds1);
    temp.pushBack(_iconDiamonds2);
    temp.pushBack(_iconDiamonds3);
    
    temp.pushBack(_iconEnemies);
    temp.pushBack(_iconClock);
    temp.pushBack(_iconFuel);
    
    cocos2d::Vector<cocos2d::Node*> temp2;
    
    temp2.pushBack(_equalLabel[0]);
    temp2.pushBack(_labelDiamonds);
    
    temp2.pushBack(_equalLabel[1]);
    temp2.pushBack(_labelEnemies);
    
    
    temp2.pushBack(_equalLabel[2]);
    temp2.pushBack(_labelTime);
    
    
    temp2.pushBack(_equalLabel[3]);
    temp2.pushBack(_labelFuel);
    
    temp2.pushBack(_labelTextScore);
    temp2.pushBack(_labelTotalScore);
    
    Animator::multiPumpIn(0.09, temp);
    Animator::multiJumpIn(0.04, temp2);
    
    cocos2d::Vector<cocos2d::Node*> tmp;
    tmp.pushBack(_starIcon1);
    tmp.pushBack(_starIcon2);
    tmp.pushBack(_starIcon3);
    Animator::multiPumpIn(0.3, tmp, 0.5);
    
    
}

void GameWin::popupTransition()
{
}

std::string GameWin::reformatText(std::string text){
    
    if(text.length() > 0){
        text[0] = '\t';
        for (int i = 1; i< text.length(); i++) {
            if(text[i] == '0' && text[i - 1] == '\t')
                text[i] = '\t';
        }
    }
    return text;
}

void GameWin::onExitTransition()
{
    CPopup::onExitTransition();
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->playEffect(EFFECT_QUIT);
#else
    AUDIO::play2d(EFFECT_QUIT, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
    _eventDispatcher->setEnabled(false);
    auto levelValue = (int)MainGameScene::getInstance()->getLevelMap();
//    auto land = (int)MainGameScene::getInstance()->getLand();
//    
//    bool anim = false;
//    
//    int totalStar = DataManager::getInstance()->getStar( land, levelValue);
    
    
    
    StartGameScene::getInstance()->setOnEnterCallback([levelValue]{
        
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playBackgroundMusic(BGM_MAIN, true);
#else
        if (GameSingleton::getInstance()->BGM_AUDIO_ID != -1)
        {
            AUDIO::stop(GameSingleton::getInstance()->BGM_AUDIO_ID);
            GameSingleton::getInstance()->BGM_AUDIO_ID = -1;
        }
        
        
        GameSingleton::getInstance()->BGM_AUDIO_ID = AUDIO::play2d(BGM_MAIN, true, GameSingleton::getInstance()->MUSIC*0.01, nullptr);
#endif

        
        auto sender = __Integer::create(-levelValue);
        TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_LEVEL_ID, sender);
        Director::getInstance()->getEventDispatcher()->setEnabled(false);
    });
    
//    auto land = MainGameScene::getInstance()->getLand();
//    Director::getInstance()->getTextureCache()->addImageAsync(StringUtils::format("GUI/StartGame/SelectLevel/img_map%d.jpg", (int)land), [](Texture2D* texture){});
    Director::getInstance()->popScene();

    

}

void GameWin::onKeyUp(cocos2d::Controller *controller, int key, cocos2d::Event *event)
{
    if (_eventDispatcher->isEnabled())
    {
        onExitTransition();
    }
}
