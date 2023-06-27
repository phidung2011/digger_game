//
//  PopupEnd.h
//  gamebase
//
//  Created by Phi Dzung on 7/23/15.
//
//

#ifndef __gamebase__PopupPause__
#define __gamebase__PopupPause__

#include "Popup.h"

class PopupPause: public CPopup
{
public:

    CREATE_FUNC(PopupPause);
    
    
    
    void onExitTransition() override;
    
    void popupTransition() override;
    void onEnterTransition() override;
    bool _isRestartGame;
    void onEnter() override;
private:
    
    void onKeyUp(cocos2d::Controller *controller, int key, cocos2d::Event *event);
protected:
    
    PopupPause();
    ~PopupPause();
    TVWidget* _btnRestart;
    TVWidget* _btnExit;
    
    void onClick(Ref* pSender);
    bool init() override;
    cocos2d::cocoswidget::CLabel* _labelTitle;
};

#endif /* defined(__gamebase__PopupEnd__) */
