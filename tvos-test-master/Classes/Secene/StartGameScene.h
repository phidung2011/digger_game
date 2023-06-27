//
//  StartGameScene.h
//  gamebase
//
//  Created by Phi Dzung on 4/16/15.
//
//
#pragma once
//#ifndef __gamebase__StartGameScene__
//#define __gamebase__StartGameScene__


#include <SceneDisplay.h>
#include "../../cocos2d/cocos/ui/UIWebView.h"


class StartGameScene : public SceneDisplay
{
public:

    CREATE_FUNC(StartGameScene);
    static StartGameScene* getInstance(){return _instance;};
    void updateFromServer(float delta);
    void reload();
    virtual void onEnter() override;
private:
    DISALLOW_COPY_AND_ASSIGN(StartGameScene);
    bool init() override;
    static StartGameScene* _instance;
    
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    bool handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void handleTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void handleTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void onConnectController(cocos2d::Controller* controller, cocos2d::Event* event);
    void onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event);
    
    void onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    void onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    void onKeyRepeat(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    
    void onAxisEvent(cocos2d::Controller* controller, int axis, cocos2d::Event* event);
    
    cocos2d::EventListenerKeyboard* _keybListener = nullptr;
    cocos2d::EventListener* _touchListener = nullptr;
    cocos2d::EventListenerController* _controllerListener = nullptr;
protected:
    StartGameScene();
    virtual ~StartGameScene();
    
    CC_SYNTHESIZE(cocos2d::Sprite*, _background, Background);
    CC_SYNTHESIZE(cocos2d::LayerColor*, _fadeBackground, FadeBackground);
    
    CC_SYNTHESIZE(cocos2d::Sprite*, _logoImg, LogoImage);
    CC_SYNTHESIZE(cocos2d::Sprite*, _land1Img, Land1Image);
    CC_SYNTHESIZE(cocos2d::Sprite*, _land2Img, Land2Image);
};
//#endif /* defined(__gamebase__StartGameScene__) */
