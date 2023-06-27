//
//  ConnectionError.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 10/8/15.
//
//

#ifndef __gamebase__ConnectionError__
#define __gamebase__ConnectionError__

#include "Popup.h"

class ConnectionError: public CPopup
{
public:
    
    CREATE_FUNC(ConnectionError);
    
    
    
    void onExitTransition() override;
    
    void popupTransition() override;
    void onEnterTransition() override;
private:
    
protected:
    
    ConnectionError();
    ~ConnectionError();
    cocos2d::cocoswidget::CButton* _btnTryAgain;
    
    void onClick(Ref* pSender);
    bool init() override;
    cocos2d::cocoswidget::CLabel* _labelTitle;
};

#endif /* defined(__gamebase__ConnectionError__) */
