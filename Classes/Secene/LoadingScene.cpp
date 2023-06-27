//
//  LoadingScene.cpp
//  gamebase
//
//  Created by NGOCDIEP on 4/16/15.
//
//

#include "LoadingScene.h"
#include "StartGameScene.h"
#include "GameConfig.h"
#include "CShake.h"
#include "NativeUtils.h"


#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_TVOS)
#include "PlayGameSingleton.h"
#endif

LoadingScene* LoadingScene::_instance = NULL;

LoadingScene::LoadingScene() {
    _instance = this;
    
}
LoadingScene::~LoadingScene() {
    CCLOG("%s", __PRETTY_FUNCTION__);
    if (_keybListener) _eventDispatcher->removeEventListener(_keybListener);
    if (_touchListener) _eventDispatcher->removeEventListener(_touchListener);
    if (_controllerListener) _eventDispatcher->removeEventListener(_controllerListener);
}

bool LoadingScene::init()
{
    if (!SceneDisplay::init())
    {
        return false;
    }
    Sprite* _background = Sprite::create(BG_START_GAME);
    _background->setPosition(VisibleRect::center());
    _background->setScale(GameSingleton::getInstance()->getScaleFixWith());
    this->getLayerContainer()->baseLayer()->addChild(_background);
    
    
    _keybListener = EventListenerKeyboard::create();
    _keybListener->onKeyPressed = CC_CALLBACK_2(LoadingScene::onKeyPressed, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keybListener, this);
    
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
    Controller::startDiscoveryController();
#endif
    
    _controllerListener = EventListenerController::create();
    
    _controllerListener->onConnected = CC_CALLBACK_2(LoadingScene::onConnectController,this);
    _controllerListener->onDisconnected = CC_CALLBACK_2(LoadingScene::onDisconnectedController,this);
    _controllerListener->onKeyDown = CC_CALLBACK_3(LoadingScene::onKeyDown, this);
    _controllerListener->onKeyUp = CC_CALLBACK_3(LoadingScene::onKeyUp, this);
    _controllerListener->onAxisEvent = CC_CALLBACK_3(LoadingScene::onAxisEvent, this);
    _controllerListener->onKeyRepeat = CC_CALLBACK_3(LoadingScene::onKeyRepeat, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_controllerListener, this);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(LoadingScene::handleTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(LoadingScene::handleTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(LoadingScene::handleTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _touchListener = listener;
    
    return true;
}

void LoadingScene::onEnterTransitionDidFinish() {
    SceneDisplay::onEnterTransitionDidFinish();
    auto call = CallFunc::create([this] {
        this->loadData();
    });
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(3), call));
}


void LoadingScene::loadData() {
    AnimationManager::getInstance();
    DATA_MGR;
    
    
    
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->preloadBackgroundMusic(BGM_LAND1);
    SIMPLE_AUDIO->preloadBackgroundMusic(BGM_LAND2);
    SIMPLE_AUDIO->preloadBackgroundMusic(BGM_LAND3);
    SIMPLE_AUDIO->preloadBackgroundMusic(BGM_LAND4);
    SIMPLE_AUDIO->preloadBackgroundMusic(BGM_LAND5);
    SIMPLE_AUDIO->preloadBackgroundMusic(BGM_MAIN);
    
    
    SIMPLE_AUDIO->preloadEffect(EFFECT_BOMB_1);
    SIMPLE_AUDIO->preloadEffect(EFFECT_BOMB_2);
    SIMPLE_AUDIO->preloadEffect(EFFECT_BTN);
    SIMPLE_AUDIO->preloadEffect(EFFECT_CHOOSE_MAP);
    SIMPLE_AUDIO->preloadEffect(EFFECT_CHOOSE_MAP_PTR);
    SIMPLE_AUDIO->preloadEffect(EFFECT_BTN_PLAY);
    SIMPLE_AUDIO->preloadEffect(EFFECT_CART);
    SIMPLE_AUDIO->preloadEffect(EFFECT_DIG_1);
    SIMPLE_AUDIO->preloadEffect(EFFECT_DIG_2);
    SIMPLE_AUDIO->preloadEffect(EFFECT_DIG_SNOW_1);
    SIMPLE_AUDIO->preloadEffect(EFFECT_DIG_SNOW_2);
    SIMPLE_AUDIO->preloadEffect(EFFECT_GEM_1);
    SIMPLE_AUDIO->preloadEffect(EFFECT_GEM_2);
    SIMPLE_AUDIO->preloadEffect(EFFECT_GEM_3);
    SIMPLE_AUDIO->preloadEffect(EFFECT_GET_ITEM_1);
    SIMPLE_AUDIO->preloadEffect(EFFECT_GET_ITEM_2);
    SIMPLE_AUDIO->preloadEffect(EFFECT_GET_ITEM_3);
    SIMPLE_AUDIO->preloadEffect(EFFECT_GET_ITEM_4);
    SIMPLE_AUDIO->preloadEffect(EFFECT_GET_ITEM_5);
    SIMPLE_AUDIO->preloadEffect(EFFECT_GET_ITEM_6);
    SIMPLE_AUDIO->preloadEffect(EFFECT_GET_ITEM_7);
    SIMPLE_AUDIO->preloadEffect(EFFECT_MINE_1);
    SIMPLE_AUDIO->preloadEffect(EFFECT_DYNAMITE_1);
    SIMPLE_AUDIO->preloadEffect(EFFECT_DYNAMITE_2);
    SIMPLE_AUDIO->preloadEffect(EFFECT_DYNAMITE_3);
    SIMPLE_AUDIO->preloadEffect(EFFECT_ROCKET_1);
    SIMPLE_AUDIO->preloadEffect(EFFECT_ROCKET_2);
    SIMPLE_AUDIO->preloadEffect(EFFECT_DOOR);
    SIMPLE_AUDIO->preloadEffect(EFFECT_WIN);
    SIMPLE_AUDIO->preloadEffect(EFFECT_ROCK_1);
    SIMPLE_AUDIO->preloadEffect(EFFECT_ROCK_2);
    SIMPLE_AUDIO->preloadEffect(EFFECT_ROCK_3);
    SIMPLE_AUDIO->preloadEffect(EFFECT_BLOCK_MOVE);
    SIMPLE_AUDIO->preloadEffect(EFFECT_COUNT_DOWN);
    SIMPLE_AUDIO->preloadEffect(EFFECT_FAIL);
    SIMPLE_AUDIO->preloadEffect(EFFECT_PAUSE);
    SIMPLE_AUDIO->preloadEffect(EFFECT_QUIT);
    SIMPLE_AUDIO->preloadEffect(EFFECT_READY);
    SIMPLE_AUDIO->preloadEffect(EFFECT_RESTART);
#else
    
    AUDIO::preload(BGM_LAND1);
    AUDIO::preload(BGM_LAND2);
    AUDIO::preload(BGM_LAND3);
    AUDIO::preload(BGM_LAND4);
    AUDIO::preload(BGM_LAND5);
    AUDIO::preload(BGM_MAIN);
    
    AUDIO::preload(EFFECT_BOMB_1);
    AUDIO::preload(EFFECT_BOMB_2);
    AUDIO::preload(EFFECT_BTN);
    AUDIO::preload(EFFECT_CHOOSE_MAP);
    AUDIO::preload(EFFECT_CHOOSE_MAP_PTR);
    AUDIO::preload(EFFECT_BTN_PLAY);
    AUDIO::preload(EFFECT_CART);
    AUDIO::preload(EFFECT_DIG_1);
    AUDIO::preload(EFFECT_DIG_2);
    AUDIO::preload(EFFECT_DIG_SNOW_1);
    AUDIO::preload(EFFECT_DIG_SNOW_2);
    AUDIO::preload(EFFECT_GEM_1);
    AUDIO::preload(EFFECT_GEM_2);
    AUDIO::preload(EFFECT_GEM_3);
    AUDIO::preload(EFFECT_GET_ITEM_1);
    AUDIO::preload(EFFECT_GET_ITEM_2);
    AUDIO::preload(EFFECT_GET_ITEM_3);
    AUDIO::preload(EFFECT_GET_ITEM_4);
    AUDIO::preload(EFFECT_GET_ITEM_5);
    AUDIO::preload(EFFECT_GET_ITEM_6);
    AUDIO::preload(EFFECT_GET_ITEM_7);
    AUDIO::preload(EFFECT_MINE_1);
    AUDIO::preload(EFFECT_DYNAMITE_1);
    AUDIO::preload(EFFECT_DYNAMITE_2);
    AUDIO::preload(EFFECT_DYNAMITE_3);
    AUDIO::preload(EFFECT_ROCKET_1);
    AUDIO::preload(EFFECT_ROCKET_2);
    AUDIO::preload(EFFECT_DOOR);
    AUDIO::preload(EFFECT_WIN);
    AUDIO::preload(EFFECT_ROCK_1);
    AUDIO::preload(EFFECT_ROCK_2);
    AUDIO::preload(EFFECT_ROCK_3);
    AUDIO::preload(EFFECT_BLOCK_MOVE);
    AUDIO::preload(EFFECT_COUNT_DOWN);
    AUDIO::preload(EFFECT_FAIL);
    AUDIO::preload(EFFECT_PAUSE);
    AUDIO::preload(EFFECT_QUIT);
    AUDIO::preload(EFFECT_READY);
    AUDIO::preload(EFFECT_RESTART);
#endif
    
    
    //    Director::getInstance()->getTextureCache()->addImage(BG_START_GAME);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_LOGO);
    Director::getInstance()->getTextureCache()->addImage(BG_LAND2_START_GAME);
    Director::getInstance()->getTextureCache()->addImage(BG_LAND1_START_GAME);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_PLAYGAME);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_SHARE_FB);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_SHARE_TW);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_HIGHSCORE);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_SETTING);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_HELP);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_SHOP);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_EXIT);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_BAR_TITLE);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_MAP1);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_MAP2);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_MAP3);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_MAP4);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_MAP5);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_POINTER);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_SHADOW_POINTER);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_BACK);
    
    //        Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SelectLevel/img_map1.png");
    //        Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SelectLevel/img_map2.png");
    //        Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SelectLevel/img_map3.png");
    //        Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SelectLevel/img_map4.png");
    //        Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SelectLevel/img_map5.png");
    
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SelectLevel/img_pointer.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SelectLevel/img_last_pointer.png");
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_STAR);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_STAR_1);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_LOCK);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_BAR_MAIN);
    Director::getInstance()->getTextureCache()->addImage(UI_PROGRESS_BAR_FUEL);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_BAR_PLAYER);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_BAR_ENEMIES);
    Director::getInstance()->getTextureCache()->addImage(UI_IMG_BAR_DIAMONDS);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_PAUSE);
    Director::getInstance()->getTextureCache()->addImage(UI_BG_POPUP_PAUSE);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN);
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SettingGame/bg.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SettingGame/setting_btn.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SettingGame/bg_option.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SettingGame/slide_btn.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SettingGame/slide_bar.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SettingGame/img_check_box.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/SettingGame/img_check.png");
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_MINE_NORMAL);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_MINE_DISABLE);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_TIMEBOMB_NORMAL);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_TIMEBOMB_DISABLE);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_ROCKET_NORMAL);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_ROCKET_DISABLE);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_BOMB_NORMAL);
    Director::getInstance()->getTextureCache()->addImage(UI_BTN_BOMB_DISABLE);
    Director::getInstance()->getTextureCache()->addImage(UI_NUMBER_CIRCLE);
    Director::getInstance()->getTextureCache()->addImage(UI_CONTROL_BOARD);
    Director::getInstance()->getTextureCache()->addImage(UI_CONTROL_JOYSTICK);
    Director::getInstance()->getTextureCache()->addImage("GUI/PlayGame/PopupLevelComplete/icon_star_small.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/PlayGame/PopupLevelComplete/icon_star.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/PlayGame/PopupLevelComplete/icon_star_fail.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/PlayGame/PopupLevelComplete/icon_star_fail_small.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/ShopItem/btn1.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/ShopItem/btn2.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/ShopItem/btn3.png");
    Director::getInstance()->getTextureCache()->addImage("GUI/StartGame/ShopItem/btn4.png");
    //    Director::getInstance()->getTextureCache()->addImage("Maps/Land1/bg_land.png");
    //    Director::getInstance()->getTextureCache()->addImage("Maps/Land2/bg_land.png");
    //    Director::getInstance()->getTextureCache()->addImage("Maps/Land3/bg_land.png");
    //    Director::getInstance()->getTextureCache()->addImage("Maps/Land4/bg_land.png");
    //    Director::getInstance()->getTextureCache()->addImage("Maps/Land5/bg_land.png");
    
    
    
    auto scene = StartGameScene::create();
    scene->setOnEnterCallback([]{
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playBackgroundMusic(BGM_MAIN, true);
#else
        if (GameSingleton::getInstance()->BGM_AUDIO_ID != -1)
        {
            AUDIO::stop(GameSingleton::getInstance()->BGM_AUDIO_ID);
        }
        
        GameSingleton::getInstance()->BGM_AUDIO_ID = AUDIO::play2d(BGM_MAIN, true, GameSingleton::getInstance()->MUSIC*0.01, nullptr);
        
#endif
        
        
        TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_MENU_ID);
    });
    
    
    Director::getInstance()->replaceScene(scene);
}

void LoadingScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    //    log("key pressed: %d", keyCode);
}

bool LoadingScene::handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
    //    log("touch begin: %f, %f", location.x, location.y);
    
    return true;
}

void LoadingScene::handleTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
    //log("touch moved: %f, %f", location.x, location.y);
}

void LoadingScene::handleTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
    //    log("touch ended: %f, %f", location.x, location.y);
}

void LoadingScene::onConnectController(cocos2d::Controller* controller, cocos2d::Event* event)
{
    log("Controller connected %s", controller->getDeviceName().c_str());
}

void LoadingScene::onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event)
{
}

void LoadingScene::onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
    //    log("key down: %d, float value: %f", key, controller->getKeyStatus(key).value);
    
    
    
    
#endif
}

void LoadingScene::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    if (_eventDispatcher->isEnabled())
    {
        log("key up: %d", key);
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

void LoadingScene::onAxisEvent(cocos2d::Controller* controller, int axis, cocos2d::Event* event)
{
    //    log("axis event: %d", axis);
}

void LoadingScene::onKeyRepeat(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    //    log("key repeat: %d", key);
}
