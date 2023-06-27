//
//  StartGameScene.cpp
//  gamebase
//
//  Created by NGOCDIEP on 4/16/15.
//
//

#include "StartGameScene.h"
#include "LayerSelectLevel.h"
#include "MainGameScene.h"
#include "SettingGame.h"
#include "GameConfig.h"
#include "LayerMenu.h"
#include "LayerHelp.h"
#include "LayerSelectLand.h"
#include "LayerLoading.h"
#include "NativeUtils.h"
#include "ConnectionError.h"
#include "LayerShopBuyCoin.h"
#include "LayerBuyItem.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_TVOS)
#include "PlayGameSingleton.h"
#endif

StartGameScene* StartGameScene::_instance = NULL;

StartGameScene::StartGameScene() {
    _instance = this;
}
StartGameScene::~StartGameScene() {
    CCLOG("%s", __PRETTY_FUNCTION__);
    if (_keybListener) _eventDispatcher->removeEventListener(_keybListener);
    if (_touchListener) _eventDispatcher->removeEventListener(_touchListener);
    if (_controllerListener) _eventDispatcher->removeEventListener(_controllerListener);
}

bool StartGameScene::init() {
    if (!SceneDisplay::init()) {
        return false;
    }
    
    this->insertLayer(LAYER_MENU_ID, LayerMenu::create());
    this->insertLayer(LAYER_SELECT_LAND_ID, LayerSelectLand::create());
    this->insertLayer(LAYER_LEVEL_ID, LayerSelectLevel::create());
    
    this->insertLayer(LAYER_SETTING_ID, SettingGame::create());
    //	this->insertLayer(LAYER_HELP_ID, LayerHelp::create());
    this->insertLayer(LAYER_LOADING_ID, LayerLoading::create());
    this->insertLayer(LAYER_SHOP_BUY_COIN_ID, LayerShopBuyCoin::create());
    this->insertLayer(LAYER_SHOP_ID, LayerBuyItem::create());
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    this->insertLayer(POPUP_CONNECTION_ID, ConnectionError::create());
#endif
    
    
    _background = Sprite::create(BG_START_GAME);
    _background->setPosition(VisibleRect::center());
    //	auto size = Director::getInstance()->getVisibleSize();
    
    _background->setScale(GameSingleton::getInstance()->getScaleFixWith());
    this->getLayerContainer()->baseLayer()->addChild(_background);
    
    _logoImg = Sprite::create(UI_IMG_LOGO);
    _logoImg->ignoreAnchorPointForPosition(true);
    _logoImg->setPosition(Vec2(627, 430));
    this->getLayerContainer()->baseLayer()->addChild(_logoImg);
    
    _land2Img = Sprite::create(BG_LAND2_START_GAME);
    _land2Img->setAnchorPoint(Vec2::UNIT_X);
    _land2Img->setPosition(VisibleRect::rightBottom());
    this->getLayerContainer()->baseLayer()->addChild(_land2Img);
    
    _land1Img = Sprite::create(BG_LAND1_START_GAME);
    _land1Img->setAnchorPoint(Vec2(0.5, 0));
    _land1Img->setPosition(VisibleRect::bottom());
    this->getLayerContainer()->baseLayer()->addChild(_land1Img);
    
    _fadeBackground = LayerColor::create(Color4B(Color3B(254, 252, 248)));
    _fadeBackground->setOpacity(0);
    this->getLayerContainer()->baseLayer()->addChild(_fadeBackground, 10);
    
    _eventDispatcher->setEnabled(false);
    auto call = CallFunc::create([this] {
        this->reload();
    });
    
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.3), call));
    
    
    
    
    _keybListener = EventListenerKeyboard::create();
    _keybListener->onKeyPressed = CC_CALLBACK_2(StartGameScene::onKeyPressed, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keybListener, this);
    
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
    Controller::startDiscoveryController();
#endif
    
    //    _controllerListener = EventListenerController::create();
    //
    //    _controllerListener->onConnected = CC_CALLBACK_2(StartGameScene::onConnectController,this);
    //    _controllerListener->onDisconnected = CC_CALLBACK_2(StartGameScene::onDisconnectedController,this);
    //    _controllerListener->onKeyDown = CC_CALLBACK_3(StartGameScene::onKeyDown, this);
    //    _controllerListener->onKeyUp = CC_CALLBACK_3(StartGameScene::onKeyUp, this);
    //    _controllerListener->onAxisEvent = CC_CALLBACK_3(StartGameScene::onAxisEvent, this);
    //    _controllerListener->onKeyRepeat = CC_CALLBACK_3(StartGameScene::onKeyRepeat, this);
    //
    //    _eventDispatcher->addEventListenerWithSceneGraphPriority(_controllerListener, this);
    //
    //    auto listener = EventListenerTouchOneByOne::create();
    //    listener->setSwallowTouches(true);
    //
    //    listener->onTouchBegan = CC_CALLBACK_2(StartGameScene::handleTouchBegan, this);
    //    listener->onTouchMoved = CC_CALLBACK_2(StartGameScene::handleTouchMoved, this);
    //    listener->onTouchEnded = CC_CALLBACK_2(StartGameScene::handleTouchEnded, this);
    //
    //    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //    _touchListener = listener;
    //
    //    scheduleUpdate();
    return true;
}

void StartGameScene::onEnter()
{
    SceneDisplay::onEnter();
    
}

void StartGameScene::reload()
{
    NativeUtils::userLogin();
    this->schedule(schedule_selector(StartGameScene::updateFromServer), 3.0);
//        TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_LOADING_ID);
}

void StartGameScene::updateFromServer(float delta) {
    
    int rs = PlayGameSingleton::sharedInstance()->_login;
    if (rs == 1) {
        //Load data from server
        DataManager::getInstance()->loadStar();
        GameSingleton::getInstance()->_coin = NativeUtils::getDataInt(USER_COIN);
        //		TransitionManager::getInstance()->removeFromSceneByCustomTransition(LAYER_LOADING_ID);
        
        _eventDispatcher->setEnabled(true);
        this->unschedule(schedule_selector(StartGameScene::updateFromServer));
    } else if (rs == -1) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        TransitionManager::getInstance()->addToSceneByCustomTransition(POPUP_CONNECTION_ID);
        TransitionManager::getInstance()->removeFromSceneByCustomTransition(LAYER_LOADING_ID);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_TVOS)
        NativeUtils::showAlertConnection();
#endif
    }
}

void StartGameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    log("key pressed: %d", keyCode);
}

bool StartGameScene::handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
    //    log("touch begin: %f, %f", location.x, location.y);
    
    return true;
}

void StartGameScene::handleTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
    log("touch moved: %f, %f", location.x, location.y);
}

void StartGameScene::handleTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
    //    log("touch ended: %f, %f", location.x, location.y);
}

void StartGameScene::onConnectController(cocos2d::Controller* controller, cocos2d::Event* event)
{
    log("Controller connected %s", controller->getDeviceName().c_str());
}

void StartGameScene::onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event)
{
}

void StartGameScene::onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
}

void StartGameScene::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    if (_eventDispatcher->isEnabled())
    {
        CCLOG("key up: %d", key);
        switch (key) {
            case cocos2d::Controller::BUTTON_A:
                CCLOG("BUTTON_A");
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

void StartGameScene::onAxisEvent(cocos2d::Controller* controller, int axis, cocos2d::Event* event)
{
    //    log("axis event: %d", axis);
}

void StartGameScene::onKeyRepeat(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    //    log("key repeat: %d", key);
}


