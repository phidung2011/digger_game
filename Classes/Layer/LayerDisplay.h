//
//  LayerDisplay.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 5/12/15.
//
//

#ifndef __gamebase__LayerDisplay__
#define __gamebase__LayerDisplay__

#include <cocos-widget.h>
#include "LayerContainer.h"
#include "TVWidget.h"

typedef enum
{
    INVALID_LAYER_ID = -1,
    LAYER_MENU_ID = 0,
    LAYER_SELECT_LAND_ID,    
    LAYER_LEVEL_ID,
    LAYER_SETTING_ID,
    LAYER_ABOUT_ID,
    LAYER_HELP_ID,
    LAYER_SHOP_ID,
    LAYER_SHOP_BUY_COIN_ID,
    LAYER_LOADING_ID,
    
    POPUP_MAP_ID,
    POPUP_WIN_ID,
    POPUP_END_ID,
    POPUP_PAUSE_ID,
    POPUP_SHOP_ID,
    POPUP_LEVEL_FAILED_ID,
    POPUP_CONNECTION_ID,
    
}LAYER_ID;

class LayerDisplay : public cocos2d::Layer
{
public:
    CREATE_FUNC(LayerDisplay);
    
    virtual void atLayerInit(){};
    virtual void atLayerExecute(){};
    virtual void atLayerDestroy(){};
    virtual void atLayerUnInit(){};
    
    
    virtual void onExitTransition(){};
    virtual void onEnterTransition(){};
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    cocos2d::EventListenerTouchOneByOne* getPTouchListener(){return _pTouchListener;};
private:
    
    
    

    
protected:
    LayerDisplay();
    ~LayerDisplay();
    
    virtual bool init() override;
    
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) override;
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
    
    void onConnectController(cocos2d::Controller* controller, cocos2d::Event* event);
    void onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event);
    
    virtual void onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    virtual void onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    virtual void onKeyRepeat(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    
    void onAxisEvent(cocos2d::Controller* controller, int axis, cocos2d::Event* event);
    
    cocos2d::EventListenerKeyboard* _keybListener = nullptr;
    cocos2d::EventListenerTouchOneByOne* _pTouchListener = nullptr;
    cocos2d::EventListenerController* _controllerListener = nullptr;
    
    virtual void targetTo(TVWidget* target);
    cocos2d::cocoswidget::CWidgetWindow* m_pWindow;
    CC_SYNTHESIZE(LAYER_ID, _layerId, LayerId);
    CC_SYNTHESIZE(LAYER_INDEX, _layerIndex, LayerIndex);
    CC_SYNTHESIZE(cocos2d::Ref*, _pSender, Sender);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CImageView*, _background, Background);
    CC_SYNTHESIZE(TVWidget*, _currentTarget, CurrentTarget);
};

#endif /* defined(__gamebase__LayerDisplay__) */
