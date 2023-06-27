//
//  SkillLayer.cpp
//  gamebase
//
//  Created by Phi Dzung on 6/24/15.
//
//

#include "SkillLayer.h"
#include "AvatarConfig.h"
#include "GameConfig.h"
#include "MainGameScene.h"
#include "BomSpikes.h"
#include "BomTime.h"
#include "BomDrop.h"
#include "BomFire.h"


SkillLayer::SkillLayer()
{
    _player = MainGameScene::getInstance()->getPlayer();
}
SkillLayer::~SkillLayer()
{
    
}
bool SkillLayer::init()
{
    if (!LayerDisplay::init())
    {
        return false;
    }
    _pTouchListener->setSwallowTouches(false);
    //    this->_layerId = LAYER_MENU_ID;
    //    this->_layerIndex = GUI_LAYER_INDEX;
    //    auto btSkill = SkillItem::createSkill(UI_ITEM_SKILL, "", UI_ITEM_UNSELECT,Size(108,108));
    //    btSkill->setOnClickListener(this, ccw_click_selector(SkillLayer::onClick));
    //    btSkill->setTag(10);
    //    btSkill->setPosition(Vec2(-80, 80));
    
    _btnBombSpike = SkillItem::create(UI_BTN_MINE_NORMAL, UI_BTN_MINE_NORMAL, UI_BTN_MINE_DISABLE);
//    _btnBombSpike->setOnClickListener(this, ccw_click_selector(SkillLayer::SkillBomSpikes));
    _btnBombSpike->setAnchorPoint(Vec2(1,0.5));
    _btnBombSpike->setPosition(Vec2(winSize.width, 100));
    
    _btnBombTime = SkillItem::create(UI_BTN_TIMEBOMB_NORMAL, UI_BTN_TIMEBOMB_NORMAL, UI_BTN_TIMEBOMB_DISABLE);
//    _btnBombTime->setOnClickListener(this, ccw_click_selector(SkillLayer::SkillBomTime));
    _btnBombTime->setAnchorPoint(Vec2(1,0.5));
    _btnBombTime->setPosition(Vec2(winSize.width, 220));
    
    _btnBombFire = SkillItem::create(UI_BTN_ROCKET_NORMAL, UI_BTN_ROCKET_NORMAL, UI_BTN_ROCKET_DISABLE);
//    _btnBombFire->setOnClickListener(this, ccw_click_selector(SkillLayer::SkillFire));
    _btnBombFire->setAnchorPoint(Vec2(1,0.5));
    _btnBombFire->setPosition(Vec2(winSize.width, 340));
    
    _btnBombDrop = SkillItem::create(UI_BTN_BOMB_NORMAL, UI_BTN_BOMB_NORMAL, UI_BTN_BOMB_DISABLE);
//    _btnBombDrop->setOnClickListener(this, ccw_click_selector(SkillLayer::SkillBomDrop));
    _btnBombDrop->setAnchorPoint(Vec2(1,0.5));
    _btnBombDrop->setPosition(Vec2(winSize.width, 460));
    
    _btnBombDrop->setNextItem(_btnBombFire);
    _btnBombFire->setNextItem(_btnBombTime);
    _btnBombTime->setNextItem(_btnBombSpike);
    _btnBombSpike->setNextItem(_btnBombDrop);
    
    this->setTargetItem(_btnBombDrop);
    updateSkill();
    if (!_targetItem->isEnabled() && _targetItem == _btnBombDrop)
        _btnBombDrop->setScale(1.2);
    else if (_targetItem->isEnabled())
        _targetItem->setScale(1.2);
    
    onTargetItem();
    
    m_pWindow->addChild(_btnBombSpike);
    m_pWindow->addChild(_btnBombTime);
    m_pWindow->addChild(_btnBombDrop);
    m_pWindow->addChild(_btnBombFire);
    //    m_pWindow->addChild(_btnSnowFlake);
    this->addChild(m_pWindow);
    //Add Child bgLayer
    return true;
}

void SkillLayer::SkillBomTime()
{
    if (_player->getData().time_bombs > 0)
    {
        Vec2 p = Point::ZERO;
        int dir = MainGameScene::getInstance()->getPlayer()->dirSkill;
        auto matrixPos = ConvertUtils::convertCDMaptoMatrix(_player->getFrontPosition(), MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
        int tileNext = -1;
        switch (dir) {
            case dt_right:
                p = matrixPos + Vec2(1,0);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_left:
                p = matrixPos + Vec2(-1,0);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_top:
                p = matrixPos + Vec2(0,-1);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_bot:
                p = matrixPos + Vec2(0,1);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
        }
        if((IDTILE)tileNext == IDTILE::DEFAULT || (IDTILE)tileNext == IDTILE::GRASS || (IDTILE)tileNext == IDTILE::GRASS_DIAMOND)
        {
            auto mapPos = ConvertUtils::convertCDMatrixtoMap(p, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
            BomTime* bom = BomTime::create();
            bom->setPosition(mapPos);
            bom->loadToMap();
            MainGameScene::getInstance()->addObject(bom);
            _player->getData().time_bombs--;
            updateSkill();
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_DYNAMITE_1);
#else
            AUDIO::play2d(EFFECT_DYNAMITE_1, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        }
    }
}
void SkillLayer::SkillBomSpikes()
{
    if (_player->getData().mines > 0)
    {
        Vec2 p = Point::ZERO;
        int dir = MainGameScene::getInstance()->getPlayer()->dirSkill;
        auto matrixPos = ConvertUtils::convertCDMaptoMatrix(_player->getBackPosition(), MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
        int tileNext = -1;
        switch (dir)
        {
            case dt_right:
                p = matrixPos + Vec2(-1,0);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_left:
                p = matrixPos + Vec2(1,0);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_top:
                p = matrixPos + Vec2(0,1);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_bot:
                p = matrixPos + Vec2(0,-1);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
        }
        if((IDTILE)tileNext == IDTILE::DEFAULT || (IDTILE)tileNext == IDTILE::GRASS || (IDTILE)tileNext == IDTILE::GRASS_DIAMOND)
        {
            auto mapPos = ConvertUtils::convertCDMatrixtoMap(p, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
            BomSpikes* bom = BomSpikes::create();
            bom->setPosition(mapPos);
            bom->loadToMap();
            MainGameScene::getInstance()->addObject(bom);
            _player->getData().mines--;
            updateSkill();
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_MINE_1);
#else
            AUDIO::play2d(EFFECT_MINE_1, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        }
    }
}
void SkillLayer::SkillBomDrop()
{
    if (_player->getData().bombs > 0)
    {
        Vec2 p = Point::ZERO;
        int dir = MainGameScene::getInstance()->getPlayer()->dirSkill;
        auto matrixPos = ConvertUtils::convertCDMaptoMatrix(_player->getFrontPosition(), MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
        int tileNext = -1;
        switch (dir) {
            case dt_right:
                p = matrixPos + Vec2(1,0);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_left:
                p = matrixPos + Vec2(-1,0);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_top:
                p = matrixPos + Vec2(0,-1);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_bot:
                p = matrixPos + Vec2(0,1);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
        }
        if((IDTILE)tileNext == IDTILE::DEFAULT || (IDTILE)tileNext == IDTILE::GRASS || (IDTILE)tileNext == IDTILE::GRASS_DIAMOND)
        {
            auto mapPos = ConvertUtils::convertCDMatrixtoMap(p, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
            BomDrop* bom = BomDrop::create();
            bom->setPosition(mapPos);
            bom->loadToMap();
            MainGameScene::getInstance()->addObject(bom);
            _player->getData().bombs--;
            updateSkill();
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_BOMB_1);
#else
            AUDIO::play2d(EFFECT_BOMB_1, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        }
    }
    
}

void SkillLayer::SkillFire()
{
    if (_player->getData().rockets > 0) {
        Vec2 p = Point::ZERO;
        int dir = MainGameScene::getInstance()->getPlayer()->dirSkill;
        auto matrixPos = ConvertUtils::convertCDMaptoMatrix(_player->getFrontPosition(), MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
        int tileNext = -1;
        switch (dir)
        {
            case dt_right:
                p = matrixPos + Vec2(1,0);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_left:
                p = matrixPos + Vec2(-1,0);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_top:
                p = matrixPos + Vec2(0,-1);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
            case dt_bot:
                p = matrixPos + Vec2(0,1);
                tileNext = MainGameScene::getInstance()->getTileMap()->getIdTile(p);
                break;
        }
        if (MainGameScene::getInstance()->getPlayer()->isFirable())
        {
            auto mapPos = ConvertUtils::convertCDMatrixtoMap(p, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
            BomFire* bom = BomFire::createWithDir(dir);
            bom->setOwner(MainGameScene::getInstance()->getPlayer());
            
            bom->setPosition(mapPos);
            MainGameScene::getInstance()->addObject(bom);
            _player->getData().rockets--;
            updateSkill();
            
        }
    }
}

void SkillLayer::onTargetItem()
{
    if (!_btnBombDrop->isEnabled() && !_btnBombFire->isEnabled() && !_btnBombSpike->isEnabled() && !_btnBombTime->isEnabled())
        return;
    
    SkillItem* temp = _targetItem->getNextItem();
    
    while (!temp->isEnabled()) {
        temp = temp->getNextItem();
    }
    
    if (_targetItem != temp)
    {
        _targetItem->runAction(ScaleTo::create(0.1, 1));
        _targetItem = temp;
        _targetItem->runAction(ScaleTo::create(0.1, 1.2));
    }
}

void SkillLayer::updateSkill(){
    if (_player->getData().mines > 0)
    {
        _btnBombSpike->setEnabled(true);
    }
    else
        _btnBombSpike->setEnabled(false);
    _btnBombSpike->getTextAmount()->getLabel()->setString(StringUtils::format("%d",_player->getData().mines));
    
    if (_player->getData().time_bombs > 0)
    {
        _btnBombTime->setEnabled(true);
    }
    else
        _btnBombTime->setEnabled(false);
    _btnBombTime->getTextAmount()->getLabel()->setString(StringUtils::format("%d",_player->getData().time_bombs));
    
    if (_player->getData().rockets > 0)
    {
        _btnBombFire->setEnabled(true);
    }
    else
        _btnBombFire->setEnabled(false);
    _btnBombFire->getTextAmount()->getLabel()->setString(StringUtils::format("%d",_player->getData().rockets));
    
    if (_player->getData().bombs > 0)
    {
        _btnBombDrop->setEnabled(true);
    }
    else
        _btnBombDrop->setEnabled(false);
    _btnBombDrop->getTextAmount()->getLabel()->setString(StringUtils::format("%d",_player->getData().bombs));
    
    if (!_targetItem->isEnabled())
        onTargetItem();
}

void SkillLayer::SkillFreeze()
{
}
void SkillLayer::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    
}
void SkillLayer::onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    if (_eventDispatcher->isEnabled() && !MainGameScene::getInstance()->GAME_DONE)
    {
        switch (key) {
            case cocos2d::Controller::BUTTON_A:
//                CCLOG("BUTTON_A");
//                if (_currentTarget) {
//                    _currentTarget->onSelect();
//                }
//                else
//                {
//                    CCLOG("target widget not setup yet");
//                }
                
                if (_targetItem == _btnBombDrop)
                    this->SkillBomDrop();
                else if (_targetItem == _btnBombFire)
                    this->SkillFire();
                else if (_targetItem == _btnBombSpike)
                    this->SkillBomSpikes();
                else if (_targetItem == _btnBombTime)
                    this->SkillBomTime();
                break;
            case cocos2d::Controller::BUTTON_B:
//                CCLOG("BUTTON_B");
                break;
            case cocos2d::Controller::BUTTON_C:
//                CCLOG("BUTTON_C");
                break;
            case cocos2d::Controller::BUTTON_DPAD_CENTER:
//                CCLOG("BUTTON_DPAD_CENTER");
                break;
            case cocos2d::Controller::BUTTON_DPAD_DOWN:
//                CCLOG("BUTTON_DPAD_DOWN");
                break;
            case cocos2d::Controller::BUTTON_DPAD_LEFT:
//                CCLOG("BUTTON_DPAD_LEFT");
                break;
            case cocos2d::Controller::BUTTON_DPAD_RIGHT:
//                CCLOG("BUTTON_DPAD_RIGHT");
                break;
            case cocos2d::Controller::BUTTON_DPAD_UP:
//                CCLOG("BUTTON_DPAD_UP");
                break;
            case cocos2d::Controller::BUTTON_LEFT_SHOULDER:
                CCLOG("BUTTON_LEFT_SHOULDER");
                break;
            case cocos2d::Controller::BUTTON_LEFT_THUMBSTICK:
                CCLOG("BUTTON_LEFT_THUMBSTICK");
                break;
            case cocos2d::Controller::BUTTON_PAUSE:
//                CCLOG("BUTTON_PAUSE");
                MainGameScene::getInstance()->getMenuBar()->onClick(nullptr);
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
//                CCLOG("BUTTON_X");
                
                
                this->onTargetItem();
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



