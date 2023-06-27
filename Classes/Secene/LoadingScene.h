//
//  LoadingScene.h
//  gamebase
//
//  Created by NGOCDIEP on 4/16/15.
//
//

#ifndef __gamebase__LoadingScene__
#define __gamebase__LoadingScene__
#include <SceneDisplay.h>
#include <cocos-widget.h>
class LoadingScene: public SceneDisplay
{
public:
    static LoadingScene* getInstance(){return _instance;};
    CREATE_FUNC(LoadingScene);
    

private:
    SceneDisplay* _startScene;
    virtual void onEnterTransitionDidFinish() override;
    
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
    LoadingScene();
    ~LoadingScene();
    virtual bool init() override;

    void loadData();

    static LoadingScene* _instance;
};

#endif /* defined(__gamebase__LoadingScene__) */
