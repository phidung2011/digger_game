//
//  LayerSelectLand.h
//  gamebase
//
//  Created by NGOCDIEP on 8/18/15.
//
//

#ifndef __gamebase__LayerSelectLand__
#define __gamebase__LayerSelectLand__

#include "LayerDisplay.h"
#include "LighterSprite.h"
#include "ui/cocosGUI.h"

class LayerSelectLand : public LayerDisplay
{
public:
    CREATE_FUNC(LayerSelectLand);
    
    void onClick(Ref *ref);
    
    static const cocos2d::Vec2 map1Pos;
    static const cocos2d::Vec2 map2Pos;
    static const cocos2d::Vec2 map3Pos;
    static const cocos2d::Vec2 map4Pos;
    static const cocos2d::Vec2 map5Pos;
    
    void onEnterTransition() override;
    void onExitTransition() override;
    
    void goNext();
    
    
    void movePointer(cocos2d::Ref* map);
    
    void targetTo(TVWidget *target) override;
private:
    TVWidget* _btnMap1;
    TVWidget* _btnMap2;
    TVWidget* _btnMap3;
    TVWidget* _btnMap4;
    TVWidget* _btnMap5;
    
    cocos2d::Sprite* _titleBar;
    cocos2d::ui::PageView* _page;
    void onScroll(cocos2d::Ref* sender, cocos2d::ui::PageView::EventType eventType);
    
    cocos2d::Vector<TVWidget*> _pages;
  
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;
    void onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event) override;
    void updateLand();
    
    bool _map1Enable;
    bool _map2Enable;
    bool _map3Enable;
    bool _map4Enable;
    bool _map5Enable;
    
protected:
    LayerSelectLand();
    virtual ~LayerSelectLand();
    
    virtual bool init() override;
    
    
};
#endif /* defined(__gamebase__LayerSelectLand__) */
