//
//  LayerSelectLevel.cpp
//  gamebase
//
//  Created by HuyPB on 6/10/15.
//
//


#ifndef __gamebase__LayerSelectLevel__
#define __gamebase__LayerSelectLevel__

#include "LayerDisplay.h"
#include "DataManager.h"

class LayerSelectLevel: public LayerDisplay
{
public:

    CREATE_FUNC(LayerSelectLevel);
    
    static LayerSelectLevel* getInstance(){return _instance;};
private:
    void onClick(cocos2d::Ref* pSender);
    void chooseLevelClick(cocos2d::Ref *pSender);
    
    void onEnterTransition() override;
    void onExitTransition() override;
    
    void onEnter() override;
    
    static LayerSelectLevel* _instance;
    int _lastLevel;
//    void addVec();
//    void saveVec();
    virtual void onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event) override;
    
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
    bool isTouch;
protected:
    LayerSelectLevel();
    ~LayerSelectLevel();
    bool init() override;
    
//    cocos2d::Vec2 _lastPoint;
//    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
//    rapidjson::Document _doc;
    cocos2d::cocoswidget::CScrollView* _scrollView;
    
    CC_SYNTHESIZE(int, _land, Land);
};
#endif /* defined(__gamebase__LayerSelectLevel__) */
