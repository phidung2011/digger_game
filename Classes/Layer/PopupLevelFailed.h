//
//  PopupLevelFailed.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 9/16/15.
//
//

#ifndef __gamebase__PopupLevelFailed__
#define __gamebase__PopupLevelFailed__

#include "Popup.h"

class PopupLevelFailed : public CPopup
{
public:
    CREATE_FUNC(PopupLevelFailed);
    virtual void onEnter() override;
private:
    void onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event) override;
protected:
    PopupLevelFailed();
    ~PopupLevelFailed();
    
    bool init() override;
    
    void onEnterTransition() override;
    void onExitTransition() override;
    void popupTransition() override;
    
    TVWidget* _btnRestart;
    TVWidget* _btnExit;
    
    void onClick(Ref* pSender);
    
    cocos2d::cocoswidget::CLabel* _labelTitle;
    
    
};

#endif /* defined(__gamebase__PopupLevelFailed__) */
