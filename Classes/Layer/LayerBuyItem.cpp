//
//  LayerBuyItem.cpp
//  digger
//
//  Created by Nguyễn Lê Lợi on 10/27/15.
//
//

#include "LayerBuyItem.h"
#include "GameConfig.h"
#include "StartGameScene.h"
#include "LayerSelectLevel.h"
#include "AvatarConfig.h"
#include "MainGameScene.h"
#include "NativeUtils.h"
bool LayerBuyItem::init()
{
    if (!CPopup::init())
    {
        return false;
    }
    this->_layerId = LAYER_SHOP_ID;
    this->_layerIndex = POPUP_LAYER_INDEX;
    _level = 0;
    _tmpCoin = GameSingleton::getInstance()->_coin;
    
    fixedBuyPackage = MapData(3,3,3,3,3,3,3,3);
    
    this->addChild(m_pWindow);
    
    _background = CImageView::create("GUI/StartGame/ShopItem/bg.png");
    _background->setPosition(VisibleRect::center());
    m_pWindow->addChild(_background);
    
    auto newWindow = CWidgetWindow::create();
    _background->addChild(newWindow);
    
    auto titleBar = Sprite::create("GUI/StartGame/ShopItem/bar_title.png");
    titleBar->ignoreAnchorPointForPosition(true);
    titleBar->setPosition(Vec2(_background->getContentSize().width/2, _background->getContentSize().height) - Vec2(titleBar->getContentSize()/2));
    _background->addChild(titleBar);
    
    auto coinIcon = Sprite::create("GUI/StartGame/ShopItem/bg_coin.png");
    coinIcon->ignoreAnchorPointForPosition(true);
    coinIcon->setPosition(Vec2(60,380));
    _background->addChild(coinIcon);
    
    auto bg1 = Sprite::create("GUI/StartGame/ShopItem/bg_fade.png");
    bg1->ignoreAnchorPointForPosition(true);
    bg1->setPosition(Vec2(64,130));
    _background->addChild(bg1);
    auto bg2 = Sprite::create("GUI/StartGame/ShopItem/bg_fade.png");
    bg2->ignoreAnchorPointForPosition(true);
    bg2->setPosition(Vec2(397,130));
    _background->addChild(bg2);
    
    _item1 = Sprite::create("GUI/StartGame/ShopItem/bg_map_item.png");
    _item1->setPosition(Vec2(100,275));
    _background->addChild(_item1);
    
    auto diamond = Sprite::create("GUI/StartGame/ShopItem/icon_diamond.png");
    diamond->ignoreAnchorPointForPosition(true);
    diamond->setPosition(Vec2(-22,-2));
    _item1->addChild(diamond);
    
    _item2 = Sprite::create("GUI/StartGame/ShopItem/bg_map_item.png");
    _item2->setPosition(Vec2(100,215));
    _background->addChild(_item2);
    
    auto tanker = Sprite::create("GUI/StartGame/ShopItem/icon_tanker.png");
    tanker->ignoreAnchorPointForPosition(true);
    tanker->setPosition(Vec2(-20,-4));
    _item2->addChild(tanker);
    
    _item3 = Sprite::create("GUI/StartGame/ShopItem/bg_map_item.png");
    _item3->setPosition(Vec2(100,155));
    _background->addChild(_item3);
    
    auto roller = Sprite::create("GUI/StartGame/ShopItem/icon_roller.png");
    roller->ignoreAnchorPointForPosition(true);
    roller->setPosition(Vec2(-22,-4));
    _item3->addChild(roller);
    
    _item4 = Sprite::create("GUI/StartGame/ShopItem/bg_map_item.png");
    _item4->setPosition(Vec2(245,275));
    _background->addChild(_item4);
    
    auto shipper = Sprite::create("GUI/StartGame/ShopItem/icon_shipper.png");
    shipper->ignoreAnchorPointForPosition(true);
    shipper->setPosition(Vec2(70,-5));
    _item4->addChild(shipper);
    
    _item5 = Sprite::create("GUI/StartGame/ShopItem/bg_map_item.png");
    _item5->setPosition(Vec2(245,215));
    _background->addChild(_item5);
    
    auto hammer = Sprite::create("GUI/StartGame/ShopItem/icon_hammer.png");
    hammer->ignoreAnchorPointForPosition(true);
    hammer->setPosition(Vec2(65,-5));
    _item5->addChild(hammer);
    
    _item6 = Sprite::create("GUI/StartGame/ShopItem/bg_map_item.png");
    _item6->setPosition(Vec2(245,155));
    _background->addChild(_item6);
    
    auto tracker = Sprite::create("GUI/StartGame/ShopItem/icon_tracker.png");
    tracker->ignoreAnchorPointForPosition(true);
    tracker->setPosition(Vec2(51,-5));
    _item6->addChild(tracker);
    
    _item1->ignoreAnchorPointForPosition(true);
    _item2->ignoreAnchorPointForPosition(true);
    _item3->ignoreAnchorPointForPosition(true);
    _item4->ignoreAnchorPointForPosition(true);
    _item5->ignoreAnchorPointForPosition(true);
    _item6->ignoreAnchorPointForPosition(true);
    
    _btn1 = TVWidget::create("GUI/StartGame/ShopItem/btn1.png");
    _btn1->ignoreAnchorPointForPosition(true);
    _btn1->setPosition(Vec2(30,30));
    _btn1->setOnSelectCallback([this]{
        this->onClick(_btn1);
    });
    newWindow->addChild(_btn1);
    
    auto label1 = Label::createWithTTF("50", FONT_PATH_GROBOLD, 24);
    label1->setColor(Color3B::YELLOW);
    label1->enableGlow(Color4B::BLACK);
    label1->setAnchorPoint(Vec2(1,0.5));
    label1->setAlignment(cocos2d::TextHAlignment::RIGHT);
    label1->setPosition(Vec2(130,31));
    _btn1->addChild(label1);
    
    _btn2 = TVWidget::create("GUI/StartGame/ShopItem/btn2.png");
    _btn2->ignoreAnchorPointForPosition(true);
    _btn2->setPosition(Vec2(210,30));
    _btn2->setOnSelectCallback([this]{
        this->onClick(_btn2);
    });
    newWindow->addChild(_btn2);
    
    auto label2 = Label::createWithTTF("75", FONT_PATH_GROBOLD, 24);
    label2->setColor(Color3B::YELLOW);
    label2->enableGlow(Color4B::BLACK);
    label2->setAnchorPoint(Vec2(1,0.5));
    label2->setAlignment(cocos2d::TextHAlignment::RIGHT);
    label2->setPosition(Vec2(130,31));
    _btn2->addChild(label2);
    
    _btn3 = TVWidget::create("GUI/StartGame/ShopItem/btn3.png");
    _btn3->ignoreAnchorPointForPosition(true);
    _btn3->setPosition(Vec2(390,30));
    _btn3->setOnSelectCallback([this]{
        this->onClick(_btn3);
    });
    newWindow->addChild(_btn3);
    
    auto label3 = Label::createWithTTF("100", FONT_PATH_GROBOLD, 24);
    label3->setColor(Color3B::YELLOW);
    label3->enableGlow(Color4B::BLACK);
    label3->setAnchorPoint(Vec2(1,0.5));
    label3->setAlignment(cocos2d::TextHAlignment::RIGHT);
    label3->setPosition(Vec2(130,31));
    _btn3->addChild(label3);
    
    _btn4 = TVWidget::create("GUI/StartGame/ShopItem/btn4.png");
    _btn4->ignoreAnchorPointForPosition(true);
    _btn4->setPosition(Vec2(570,30));
    _btn4->setOnSelectCallback([this]{
        this->onClick(_btn4);
    });
    newWindow->addChild(_btn4);
    
    auto label4 = Label::createWithTTF("150", FONT_PATH_GROBOLD, 24);
    label4->setColor(Color3B::YELLOW);
    label4->enableGlow(Color4B::BLACK);
    label4->setAnchorPoint(Vec2(1,0.5));
    label4->setAlignment(cocos2d::TextHAlignment::RIGHT);
    label4->setPosition(Vec2(130,31));
    _btn4->addChild(label4);
    
    _weapon1 = Sprite::create("GUI/StartGame/ShopItem/bg_weapon_item.png");
    _weapon2 = Sprite::create("GUI/StartGame/ShopItem/bg_weapon_item.png");
    _weapon3 = Sprite::create("GUI/StartGame/ShopItem/bg_weapon_item.png");
    _weapon4 = Sprite::create("GUI/StartGame/ShopItem/bg_weapon_item.png");
    
    _background->addChild(_weapon1);
    _background->addChild(_weapon2);
    _background->addChild(_weapon3);
    _background->addChild(_weapon4);
    
    _weapon1->setPosition(Vec2(500,275));
    _weapon2->setPosition(Vec2(500,185));
    _weapon3->setPosition(Vec2(610,275));
    _weapon4->setPosition(Vec2(610,185));
    
    auto weaponIcon1 = Sprite::create("GUI/StartGame/ShopItem/bg_circle_weapon_item.png");
    weaponIcon1->ignoreAnchorPointForPosition(true);
    weaponIcon1->setPosition(Vec2(-45,-12));
    _weapon1->addChild(weaponIcon1);
    
    auto weaponIcon2 = Sprite::create("GUI/StartGame/ShopItem/bg_circle_weapon_item.png");
    weaponIcon2->ignoreAnchorPointForPosition(true);
    weaponIcon2->setPosition(Vec2(-45,-12));
    _weapon2->addChild(weaponIcon2);
    
    auto weaponIcon3 = Sprite::create("GUI/StartGame/ShopItem/bg_circle_weapon_item.png");
    weaponIcon3->ignoreAnchorPointForPosition(true);
    weaponIcon3->setPosition(Vec2(65,-12));
    _weapon3->addChild(weaponIcon3);
    
    auto weaponIcon4 = Sprite::create("GUI/StartGame/ShopItem/bg_circle_weapon_item.png");
    weaponIcon4->ignoreAnchorPointForPosition(true);
    weaponIcon4->setPosition(Vec2(65,-12));
    _weapon4->addChild(weaponIcon4);
    
    auto rocket = Sprite::create("GUI/StartGame/ShopItem/icon_rocket.png");
    rocket->setPosition(Vec2(weaponIcon1->getContentSize()/2));
    weaponIcon1->addChild(rocket);
    
    auto mine = Sprite::create("GUI/StartGame/ShopItem/icon_mine.png");
    mine->setPosition(Vec2(weaponIcon2->getContentSize()/2));
    weaponIcon2->addChild(mine);
    
    auto bomb = Sprite::create("GUI/StartGame/ShopItem/icon_bomb.png");
    bomb->setPosition(Vec2(weaponIcon3->getContentSize()/2) + Vec2(0,8));
    weaponIcon3->addChild(bomb);
    
    auto timeBomb = Sprite::create("GUI/StartGame/ShopItem/icon_bomb_time.png");
    timeBomb->setPosition(Vec2(weaponIcon4->getContentSize()/2));
    weaponIcon4->addChild(timeBomb);
    
    
    
    //labels
    _titleLabel = Label::createWithTTF("10", FONT_PATH_GROBOLD, 30);
    _titleLabel->setTextColor(Color4B(Color3B(90,28,5)));
    _titleLabel->ignoreAnchorPointForPosition(true);
    _titleLabel->setAlignment(cocos2d::TextHAlignment::LEFT);
    _titleLabel->setPosition(Vec2(208,17));
    titleBar->addChild(_titleLabel);
    
    log(" -------- %d", GameSingleton::getInstance()->_coin);
    
    _coinLabel = Label::createWithTTF(StringUtils::format("%d", _tmpCoin), FONT_PATH_GROBOLD, 26);
    _coinLabel->setPosition(Vec2(105,coinIcon->getContentSize().height/2 - 3));
    coinIcon->addChild(_coinLabel);
    
    _itemMapLabel1 = Label::createWithTTF("10", FONT_PATH_GROBOLD, 24);
    _itemMapLabel1->setPosition(Vec2(83,17));
    _item1->addChild(_itemMapLabel1);
    
    _itemMapLabel2 = Label::createWithTTF("10", FONT_PATH_GROBOLD, 24);
    _itemMapLabel2->setPosition(Vec2(83,17));
    _item2->addChild(_itemMapLabel2);
    
    _itemMapLabel3 = Label::createWithTTF("10", FONT_PATH_GROBOLD, 24);
    _itemMapLabel3->setPosition(Vec2(83,17));
    _item3->addChild(_itemMapLabel3);
    
    _itemMapLabel4 = Label::createWithTTF("10", FONT_PATH_GROBOLD, 24);
    _itemMapLabel4->setPosition(Vec2(29,17));
    _item4->addChild(_itemMapLabel4);
    
    _itemMapLabel5 = Label::createWithTTF("10", FONT_PATH_GROBOLD, 24);
    _itemMapLabel5->setPosition(Vec2(29,17));
    _item5->addChild(_itemMapLabel5);
    
    _itemMapLabel6 = Label::createWithTTF("10", FONT_PATH_GROBOLD, 24);
    _itemMapLabel6->setPosition(Vec2(29,17));
    _item6->addChild(_itemMapLabel6);
    
    _itemMapLabel1->setTextColor(Color4B(Color3B(65, 68, 66)));
    _itemMapLabel2->setTextColor(Color4B(Color3B(65, 68, 66)));
    _itemMapLabel3->setTextColor(Color4B(Color3B(65, 68, 66)));
    _itemMapLabel4->setTextColor(Color4B(Color3B(65, 68, 66)));
    _itemMapLabel5->setTextColor(Color4B(Color3B(65, 68, 66)));
    _itemMapLabel6->setTextColor(Color4B(Color3B(65, 68, 66)));
    
    _itemFreeLabel1 = Label::createWithTTF("10", FONT_PATH_GROBOLD, 24);
    _itemFreeLabel1->setPosition(Vec2(62,20));
    _itemFreeLabel1->setAnchorPoint(Vec2(1,0.5));
    _itemFreeLabel1->setAlignment(cocos2d::TextHAlignment::RIGHT);
    _weapon1->addChild(_itemFreeLabel1);
    
    _itemFreeLabel2 = Label::createWithTTF("10", FONT_PATH_GROBOLD, 24);
    _itemFreeLabel2->setAnchorPoint(Vec2(1,0.5));
    _itemFreeLabel2->setPosition(Vec2(62,20));
    _itemFreeLabel2->setAlignment(cocos2d::TextHAlignment::RIGHT);
    _weapon2->addChild(_itemFreeLabel2);
    
    _itemFreeLabel3 = Label::createWithTTF("10", FONT_PATH_GROBOLD, 24);
    _itemFreeLabel3->setAnchorPoint(Vec2(0,0.5));
    _itemFreeLabel3->setPosition(Vec2(18,20));
    _itemFreeLabel3->setAlignment(cocos2d::TextHAlignment::LEFT);
    _weapon3->addChild(_itemFreeLabel3);
    
    _itemFreeLabel4 = Label::createWithTTF("10", FONT_PATH_GROBOLD, 24);
    _itemFreeLabel4->setAnchorPoint(Vec2(0,0.5));
    _itemFreeLabel4->setPosition(Vec2(18,20));
    _itemFreeLabel4->setAlignment(cocos2d::TextHAlignment::LEFT);
    _weapon4->addChild(_itemFreeLabel4);
    
    _itemBuyLabel1 = Label::createWithTTF("1", FONT_PATH_BUBBLEGUM, 20);
    _itemBuyLabel2 = Label::createWithTTF("1", FONT_PATH_BUBBLEGUM, 20);
    _itemBuyLabel3 = Label::createWithTTF("1", FONT_PATH_BUBBLEGUM, 20);
    _itemBuyLabel4 = Label::createWithTTF("1", FONT_PATH_BUBBLEGUM, 20);
    
    _itemBuyLabel1->setPosition(Vec2(20,47));
    _btn1->addChild(_itemBuyLabel1);
    
    _itemBuyLabel2->setPosition(Vec2(20,47));
    _btn2->addChild(_itemBuyLabel2);
    
    _itemBuyLabel3->setPosition(Vec2(20,47));
    _btn3->addChild(_itemBuyLabel3);
    
    _itemBuyLabel4->setPosition(Vec2(20,47));
    _btn4->addChild(_itemBuyLabel4);
    
    _btnPlay = TVWidget::create("GUI/StartGame/ShopItem/btn_play.png");
    _btnPlay->setPosition(Vec2(_background->getContentSize().width/2, - 20));
    _btnPlay->setOnSelectCallback([this]{
        this->onClick(_btnPlay);
    });
    newWindow->addChild(_btnPlay);
    
    this->setCurrentTarget(_btnPlay);
    
    auto bgInfo = Sprite::create("GUI/StartGame/ShopItem/bg_info.png");
    bgInfo->ignoreAnchorPointForPosition(true);
    bgInfo->setPosition(Vec2(bg2->getPosition().x + bg2->getContentSize().width - bgInfo->getContentSize().width, 360));
    _background->addChild(bgInfo);
    
    auto missionLabel = Label::createWithTTF("Mission", FONT_PATH_GROBOLD, 20);
    missionLabel->setPosition(Vec2(4,28));
    missionLabel->ignoreAnchorPointForPosition(true);
    missionLabel->enableOutline(Color4B(Color3B(53, 30, 95)),10);
    missionLabel->enableShadow();
    missionLabel->enableGlow(Color4B(Color3B(53, 30, 95)));
    bgInfo->addChild(missionLabel);
    
    auto mapInfoLabel = Label::createWithTTF("Map Information", FONT_PATH_GROBOLD, 20);
    mapInfoLabel->setPosition(Vec2(0,bg1->getContentSize().height));
    mapInfoLabel->ignoreAnchorPointForPosition(true);
    mapInfoLabel->enableOutline(Color4B(Color3B(53, 30, 95)),10);
    mapInfoLabel->enableShadow();
    mapInfoLabel->enableGlow(Color4B(Color3B(53, 30, 95)));
    bg1->addChild(mapInfoLabel);
    
    auto freeItemLabel = Label::createWithTTF("Free weapon", FONT_PATH_GROBOLD, 20);
    freeItemLabel->setPosition(Vec2(0,bg2->getContentSize().height));
    freeItemLabel->ignoreAnchorPointForPosition(true);
    freeItemLabel->enableOutline(Color4B(Color3B(53, 30, 95)),10);
    freeItemLabel->enableShadow();
    freeItemLabel->enableGlow(Color4B(Color3B(53, 30, 95)));
    bg2->addChild(freeItemLabel);
    
    auto buyLabel = Label::createWithTTF("Buy Weapon", FONT_PATH_GROBOLD, 20);
    buyLabel->setPosition(Vec2(0,_btn1->getContentSize().height));
    buyLabel->ignoreAnchorPointForPosition(true);
    buyLabel->enableOutline(Color4B(Color3B(53, 30, 95)),10);
    buyLabel->enableShadow();
    buyLabel->enableGlow(Color4B(Color3B(53, 30, 95)));
    _btn1->addChild(buyLabel);
    
    auto _iconDiamonds2 = Sprite::create("GUI/PlayGame/PopupLevelComplete/icon_diamond.png");
    //    _iconDiamonds2->ignoreAnchorPointForPosition(true);
    _iconDiamonds2->setPosition(Vec2(110,37));
    //    _iconDiamonds2->setScale(0.8);
    bgInfo->addChild(_iconDiamonds2);
    
    
    auto _iconEnemies = Sprite::create("GUI/PlayGame/PopupLevelComplete/icon_enemies.png");
    //    _iconEnemies->ignoreAnchorPointForPosition(true);
    _iconEnemies->setPosition(Vec2(220,35));
    _iconEnemies->setScale(0.75);
    bgInfo->addChild(_iconEnemies);
    
    auto _iconClock = Sprite::create("GUI/PlayGame/PopupLevelComplete/icon_clock.png");
    //    _iconClock->ignoreAnchorPointForPosition(true);
    _iconClock->setPosition(Vec2(310,35));
    _iconClock->setScale(0.75);
    bgInfo->addChild(_iconClock);
    
    _labelDiamond = Label::createWithTTF("5", FONT_PATH_GROBOLD , 20);
    _labelDiamond->setPosition(Vec2(140,35));
    _labelDiamond->setAnchorPoint(Vec2(0,0.5));
    _labelDiamond->setAlignment(cocos2d::TextHAlignment::LEFT);
    bgInfo->addChild(_labelDiamond);
    
    _labelEnemies = Label::createWithTTF("5", FONT_PATH_GROBOLD, 20);
    _labelEnemies->setAnchorPoint(Vec2(0,0.5));
    _labelEnemies->setPosition(Vec2(250,35));
    _labelEnemies->setAlignment(cocos2d::TextHAlignment::LEFT);
    bgInfo->addChild(_labelEnemies);
    
    _labelTime = Label::createWithTTF("5", FONT_PATH_GROBOLD, 20);
    _labelTime->setAnchorPoint(Vec2(0,0.5));
    _labelTime->setAlignment(cocos2d::TextHAlignment::LEFT);
    _labelTime->setPosition(Vec2(340,35));
    bgInfo->addChild(_labelTime);
    
    _btn1->setRightNode(_btn2);
    _btn2->setLeftNode(_btn1);
    _btn2->setRightNode(_btn3);
    _btn3->setLeftNode(_btn2);
    _btn3->setRightNode(_btn4);
    _btn4->setLeftNode(_btn3);
    
    _btn1->setBotNode(_btnPlay);
    _btn2->setBotNode(_btnPlay);
    _btn3->setBotNode(_btnPlay);
    _btn4->setBotNode(_btnPlay);
    
    _btnPlay->setTopNode(_btn2);
    
    _btn1->setOnTargetCallback([this]{
        _btn1->setZOrder(99);
    });
    _btn2->setOnTargetCallback([this]{
        _btn2->setZOrder(99);
    });
    _btn3->setOnTargetCallback([this]{
        _btn3->setZOrder(99);
    });
    _btn4->setOnTargetCallback([this]{
        _btn4->setZOrder(99);
    });
    
    _btn1->setOnUnTargetCallback([this]{
        _btn1->setZOrder(0);
    });
    _btn2->setOnUnTargetCallback([this]{
        _btn2->setZOrder(0);
    });
    _btn3->setOnUnTargetCallback([this]{
        _btn3->setZOrder(0);
    });
    _btn4->setOnUnTargetCallback([this]{
        _btn4->setZOrder(0);
    });
    updateBuy();
    
    return true;
}


void LayerBuyItem::onClick(cocos2d::Ref *pSender)
{
    if(pSender == _btnPlay)
    {
        if (_level >= 0) {
            auto layerLevel = LayerSelectLevel::getInstance();
            
            TransitionManager::getInstance()->removeFromSceneByCustomTransition(LAYER_LEVEL_ID);
            TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
            StartGameScene::getInstance()->runAction(FadeTo::create(0.3, 255));
            layerLevel->setOnExitCallback([this]
                                          {
                                              
                                              StartGameScene::getInstance()->setOnEnterCallback([this]{
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
                                                  
                                                  TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_LEVEL_ID, __Integer::create(-_level));
                                              });
                                              
                                              GameSingleton::getInstance()->_coin = _tmpCoin;
                                              log("coin ------  %d", GameSingleton::getInstance()->_coin);
                                              
                                              GameSingleton::getInstance()->setCurrentState(GameState::sUpdateCoin);
                                              
                                              NativeUtils::updateData(USER_COIN, GameSingleton::getInstance()->_coin);
                                              
                                              auto scene = MainGameScene::create((LAND)LayerSelectLevel::getInstance()->getLand(), _level, bonusPackage);
                                              Director::getInstance()->pushScene(scene);
                                          });
            
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_BTN_PLAY);
#else
            AUDIO::play2d(EFFECT_BTN_PLAY, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        }
        else {
            
            auto land = MainGameScene::getInstance()->getLand();
            GameSingleton::getInstance()->_coin = _tmpCoin;
            log("coin ------  %d", GameSingleton::getInstance()->_coin);
            
            GameSingleton::getInstance()->setCurrentState(GameState::sUpdateCoin);
            NativeUtils::updateData(USER_COIN, GameSingleton::getInstance()->_coin);
            
            auto scene = MainGameScene::create(land, -_level, bonusPackage);
            Director::getInstance()->replaceScene(scene);
            
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_BTN_PLAY);
#else
            AUDIO::play2d(EFFECT_BTN_PLAY, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        }
    }
    else if (pSender == _btn4)
    {
        if (fixedBuyPackage.rockets > 0 && _tmpCoin >= ROCKET_PRICE)
        {
            bonusPackage.rockets++;
            fixedBuyPackage.rockets--;
            _tmpCoin -= ROCKET_PRICE;
            updateBuy();
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
            AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        }
        
    }
    else if (pSender == _btn2)
    {
        if (fixedBuyPackage.bombs > 0 && _tmpCoin >= BOMB_PRICE)
        {
            bonusPackage.bombs++;
            fixedBuyPackage.bombs--;
            _tmpCoin -= BOMB_PRICE;
            updateBuy();
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
            AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        }
        
        
    }
    else if (pSender == _btn1)
    {
        if (fixedBuyPackage.mines > 0 && _tmpCoin >= MINE_PRICE)
        {
            bonusPackage.mines++;
            fixedBuyPackage.mines--;
            _tmpCoin -= MINE_PRICE;
            updateBuy();
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
            AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        }
    }
    else if (pSender == _btn3)
    {
        if (fixedBuyPackage.time_bombs > 0 && _tmpCoin >= TIMEBOMB_PRICE)
        {
            bonusPackage.time_bombs++;
            fixedBuyPackage.time_bombs--;
            _tmpCoin -= TIMEBOMB_PRICE;
            updateBuy();
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
            AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        }
    }
}

void LayerBuyItem::updateBuy()
{
    if (fixedBuyPackage.time_bombs > 0 && _tmpCoin >= TIMEBOMB_PRICE)
    {
        _btn3->initWithFile("GUI/StartGame/ShopItem/btn3.png");
    }
    else
    {
        _btn3->initWithFile("GUI/StartGame/ShopItem/btn3_disable.png");
    }
    
    if (fixedBuyPackage.mines > 0 && _tmpCoin >= MINE_PRICE)
    {
        _btn1->initWithFile("GUI/StartGame/ShopItem/btn1.png");
    }
    else
    {
        _btn1->initWithFile("GUI/StartGame/ShopItem/btn1_disable.png");
    }
    
    if (fixedBuyPackage.bombs > 0 && _tmpCoin >= BOMB_PRICE)
    {
        _btn2->initWithFile("GUI/StartGame/ShopItem/btn2.png");
    }
    else
    {
        _btn2->initWithFile("GUI/StartGame/ShopItem/btn2_disable.png");
    }
    
    if (fixedBuyPackage.rockets > 0 && _tmpCoin >= ROCKET_PRICE)
    {
        _btn4->initWithFile("GUI/StartGame/ShopItem/btn4.png");
    }
    else
    {
        _btn4->initWithFile("GUI/StartGame/ShopItem/btn4_disable.png");
    }
    
    _itemBuyLabel1->setString(StringUtils::format("%d", fixedBuyPackage.rockets));
    _itemBuyLabel2->setString(StringUtils::format("%d", fixedBuyPackage.bombs));
    _itemBuyLabel3->setString(StringUtils::format("%d", fixedBuyPackage.mines));
    _itemBuyLabel4->setString(StringUtils::format("%d", fixedBuyPackage.time_bombs));
    _coinLabel->setString(StringUtils::format("%d",_tmpCoin));
    
    if (bonusPackage.rockets > 0)
    {
        _itemFreeLabel1->setScale(0.8);
        _itemFreeLabel1->setString(StringUtils::format("%d+%d", data.rockets, bonusPackage.rockets));
    }
    else
        _itemFreeLabel1->setScale(1);
    if (bonusPackage.bombs > 0)
    {
        _itemFreeLabel3->setScale(0.8);
        _itemFreeLabel3->setString(StringUtils::format("%d+%d", data.bombs, bonusPackage.bombs));
    }
    else
        _itemFreeLabel3->setScale(1);
    if (bonusPackage.mines > 0)
    {
        _itemFreeLabel2->setScale(0.8);
        _itemFreeLabel2->setString(StringUtils::format("%d+%d", data.mines, bonusPackage.mines));
    }
    else
        _itemFreeLabel2->setScale(1);
    if (bonusPackage.time_bombs > 0)
    {
        _itemFreeLabel4->setScale(0.8);
        _itemFreeLabel4->setString(StringUtils::format("%d+%d", data.time_bombs, bonusPackage.time_bombs));
    }
    else
        _itemFreeLabel4->setScale(1);
}


void LayerBuyItem::onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
}

void LayerBuyItem::onKeyUp(cocos2d::Controller *controller, int key, cocos2d::Event *event)
{
    CCLOG("--------------%d", _eventDispatcher->isEnabled());
    
    CCLOG("-----btn1: %d",_btn1->getOpacity());
    CCLOG("-----btn2: %d",_btn2->getOpacity());
    CCLOG("-----btn3: %d",_btn3->getOpacity());
    CCLOG("-----btn4: %d",_btn4->getOpacity());
    CCLOG("-----btnPlay: %d",_btnPlay->getOpacity());
    
    if (_eventDispatcher->isEnabled())
    {
        
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
        log("key up: %d, float value: %f", key, controller->getKeyStatus(key).value);
        
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
                TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
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
        
        
#endif
    }
    
}

void LayerBuyItem::onEnterTransition()
{
    
    CPopup::onEnterTransition();
    _eventDispatcher->setEnabled(false);
    if (_pSender)
    {
        _level = dynamic_cast<__Integer*>(_pSender)->getValue();
        
        CC_SAFE_RELEASE(_pSender);
    }
    fixedBuyPackage = MapData(3,3,3,3,3,3,3,3);
    bonusPackage = MapData();
    
    _tmpCoin = GameSingleton::getInstance()->_coin;
    
    if (_level >= 0)
    {
        data = DATA_MGR->getMapDataAtLevel((int)LayerSelectLevel::getInstance()->getLand(), _level);
    }
    else
    {
        data = DATA_MGR->getMapDataAtLevel((int)MainGameScene::getInstance()->getLand(), -_level);
    }
    
    _titleLabel->setString(StringUtils::format("%d",abs(_level)));
    auto land = LayerSelectLevel::getInstance()->getLand();
    
    std::string str = StringUtils::format("res/Maps/Land%d/map_%d_en.tmx", land, abs(_level));
    
    auto map = TMXTiledMap::create(str);
    
    auto background = map->getLayer("BackGround");
    
    auto size = background->getLayerSize();
    
    int diamond = 0;
    int shipper = 0;
    int tanker = 0;
    int hammer = 0;
    int roller = 0;
    int tracker = 0;
    
    
    
    for (int i = 0; i < size.width; i++) {
        for (int j = 0; j < size.height; j++) {
            switch ((IDTILE)background->getTileGIDAt(Vec2(i,j)))
            {
                case IDTILE::DIAMOND:
                    diamond++;
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    TMXObjectGroup *objectGroup1 = map->getObjectGroup("EnemyCharacter");
    auto enemyArr = objectGroup1->getObjects();
    
    ValueVector::const_iterator i;
    for (i = enemyArr.begin(); i< enemyArr.end(); i++)
    {
        std::string  str_name = (*i).asValueMap().at("name").asString();
        if(str_name.compare("Shipper") == 0)
        {
            shipper++;
        }
        
        if(str_name.compare("Hammer") == 0)
        {
            hammer++;
        }
        
        if(str_name.compare("Tanker") == 0)
        {
            tanker++;
        }
        
        if(str_name.compare("Tracker") == 0)
        {
            tracker++;
        }
        
        if(str_name.compare("Roller") == 0)
        {
            roller++;
        }
    }
    
    _itemMapLabel1->setString(StringUtils::format("%d",diamond));
    _itemMapLabel2->setString(StringUtils::format("%d",tanker));
    _itemMapLabel3->setString(StringUtils::format("%d",roller));
    _itemMapLabel4->setString(StringUtils::format("%d",shipper));
    _itemMapLabel5->setString(StringUtils::format("%d",hammer));
    _itemMapLabel6->setString(StringUtils::format("%d",tracker));
    
    _itemFreeLabel1->setString(StringUtils::format("%d",data.rockets));
    _itemFreeLabel2->setString(StringUtils::format("%d",data.mines));
    _itemFreeLabel3->setString(StringUtils::format("%d",data.bombs));
    _itemFreeLabel4->setString(StringUtils::format("%d",data.time_bombs));
    _labelDiamond->setString(StringUtils::format("%d",data.diamonds));
    _labelEnemies->setString(StringUtils::format("%d",data.enemies));
    
    std::string timeStr;
    if(data.time >= 0){
        int m = data.time / 60;
        int s = data.time % 60;
        
        timeStr = StringUtils::format("%dm%ds",m,s);
    }
    else timeStr = "0m0s";
    
    _labelTime->setString(timeStr);
    
    updateBuy();
    
    
    
    cocos2d::Vector<cocos2d::Node*> temp;
    cocos2d::Vector<cocos2d::Node*> temp2;
    temp.pushBack(_item1);
    temp2.pushBack(_item4);
    temp.pushBack(_item2);
    temp2.pushBack(_item5);
    temp.pushBack(_item3);
    temp2.pushBack(_item6);
    
    cocos2d::Vector<cocos2d::Node*> tmp;
    cocos2d::Vector<cocos2d::Node*> tmp2;
    tmp.pushBack(_weapon1);
    tmp2.pushBack(_weapon3);
    tmp.pushBack(_weapon2);
    tmp2.pushBack(_weapon4);
    
    cocos2d::Vector<cocos2d::Node*> tp;
    tp.pushBack(_btn1);
    tp.pushBack(_btn2);
    tp.pushBack(_btn3);
    tp.pushBack(_btn4);
    
    //    cocos2d::Vector<cocos2d::Node*> labels;
    //
    //    labels.pushBack(_labelDiamond);
    //    labels.pushBack(_labelEnemies);
    //    labels.pushBack(_labelTime);
    
    Animator::multiPumpIn(0.13, temp,0.4);
    Animator::multiPumpIn(0.13, temp2,0.4);
    Animator::multiPumpIn(0.17, tmp,0.4);
    Animator::multiPumpIn(0.17, tmp2,0.4);
    Animator::multiPumpIn(0.05, tp,0.4);
    //    Animator::multiPumpIn(0.05, labels,0.5);
    this->runAction(Sequence::create(DelayTime::create(1),CallFunc::create([this]{
        //        this->setCurrentTarget(_btnPlay);
        //        _btnPlay->onTarget();
        _eventDispatcher->setEnabled(true);
    }), NULL));
}

void LayerBuyItem::popupTransition()
{
    //    _eventDispatcher->setEnabled(true);
}



void LayerBuyItem::onExitTransition()
{
    CPopup::onExitTransition();
    if (_level < 0) {
        this->setOnExitCallback([]{
            auto ref = Node::create();
            if (!MainGameScene::getInstance()->GAME_OVER)
                TransitionManager::getInstance()->addToSceneByCustomTransition(POPUP_PAUSE_ID, ref);
            else
                TransitionManager::getInstance()->addToSceneByCustomTransition(POPUP_LEVEL_FAILED_ID, ref);
        });
    }
    else
    {
        this->setOnExitCallback(NULL);
    }
}