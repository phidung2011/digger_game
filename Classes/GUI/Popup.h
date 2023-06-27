//
//  CPopup.h
//  gamebase
//
//  Created by NGOCDIEP on 5/4/15.
//
//

#ifndef __gamebase__CPopup__
#define __gamebase__CPopup__

#include "LayerDisplay.h"

class CPopup : public LayerDisplay
{
public:

    CREATE_FUNC(CPopup);
    
private:

    
    
    
protected:
    CPopup();
    ~CPopup();
    virtual bool init() override;
    
    virtual void onExitTransition() override;
        virtual void onEnterTransition() override;
//    virtual void onEnter() override;
    
    virtual void popupTransition(){};
    
//    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    CC_SYNTHESIZE(cocos2d::cocoswidget::CImageView*, _image, Image);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CButton*, _okButton, OkButton);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CButton*, _cancelButton, CancelButton);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CButton*, _closeButton, CloseButton);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CLabel*, _title, Title);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CLabel*, _text, Text);

};

#endif /* defined(__gamebase__CPopup__) */
