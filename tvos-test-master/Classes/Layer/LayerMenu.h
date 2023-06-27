//
//  LayerMenu.h
//
//
//  Created by HAINX on 15/7/15.
//
//

#ifndef __gamebase__LayerMenu__
#define __gamebase__LayerMenu__

#include "LayerDisplay.h"

class LayerMenu: public LayerDisplay
{
public:

    CREATE_FUNC(LayerMenu);
    
    
    void onEnterTransition() override;
    void onExitTransition() override;
private:
    void onClick(Ref* pSender);
    
    
//    cocos2d::cocoswidget::CImageView* _logoImg;
    void onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event) override;
protected:
    
    LayerMenu();
    ~LayerMenu();
    bool init() override;
    
    TVWidget* _btnPlay;
    TVWidget* _btnHighScore;
    TVWidget* _btnSetting;
//    TVWidget* _btnShareFB;
//    TVWidget* _btnShareTW;
    TVWidget* _btnShop;
};
#endif /* defined(__gamebase__LayerMenu__) */
