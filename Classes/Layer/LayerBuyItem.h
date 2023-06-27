//
//  LayerBuyItem.h
//  digger
//
//  Created by Nguyễn Lê Lợi on 10/27/15.
//
//

#ifndef __digger__LayerBuyItem__
#define __digger__LayerBuyItem__

#include "Popup.h"
#include "DataManager.h"
class LayerBuyItem : public CPopup
{
public:
    CREATE_FUNC(LayerBuyItem);
    
    void onExitTransition() override;
    void onEnterTransition() override;
    void popupTransition() override;
    
    void updateBuy();
private:
    
    void onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event) override;
    void onKeyUp(cocos2d::Controller *controller, int key, cocos2d::Event *event) override;
protected:
    LayerBuyItem(){};
    ~LayerBuyItem(){};
    
    bool init() override;
    void onClick(cocos2d::Ref* pSender);
    
    int _level;
    int _tmpCoin;
    
    TVWidget* _btnPlay;
    
    cocos2d::Sprite* _item1;
    cocos2d::Sprite* _item2;
    cocos2d::Sprite* _item3;
    cocos2d::Sprite* _item4;
    cocos2d::Sprite* _item5;
    cocos2d::Sprite* _item6;
    
    cocos2d::Sprite* _weapon1;
    cocos2d::Sprite* _weapon2;
    cocos2d::Sprite* _weapon3;
    cocos2d::Sprite* _weapon4;
    
    TVWidget* _btn1;
    TVWidget* _btn2;
    TVWidget* _btn3;
    TVWidget* _btn4;
    
    cocos2d::Label* _titleLabel;
    
    cocos2d::Label* _coinLabel;
    
    cocos2d::Label* _itemMapLabel1;
    cocos2d::Label* _itemMapLabel2;
    cocos2d::Label* _itemMapLabel3;
    cocos2d::Label* _itemMapLabel4;
    cocos2d::Label* _itemMapLabel5;
    cocos2d::Label* _itemMapLabel6;
    
    cocos2d::Label* _itemFreeLabel1;
    cocos2d::Label* _itemFreeLabel2;
    cocos2d::Label* _itemFreeLabel3;
    cocos2d::Label* _itemFreeLabel4;
    
    cocos2d::Label* _itemBuyLabel1;
    cocos2d::Label* _itemBuyLabel2;
    cocos2d::Label* _itemBuyLabel3;
    cocos2d::Label* _itemBuyLabel4;
    
    cocos2d::Label* _labelDiamond;
    cocos2d::Label* _labelEnemies;
    cocos2d::Label* _labelTime;
    
    MapData bonusPackage;
    MapData fixedBuyPackage;
    MapData data;
    
};


#endif /* defined(__digger__LayerBuyItem__) */
