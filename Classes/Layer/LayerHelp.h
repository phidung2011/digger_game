//
//  LayerHelp.h
//  gamebase
//
//  Created by NWS on 7/23/15.
//
//

#ifndef __gamebase__LayerHelp__
#define __gamebase__LayerHelp__

#include "LayerDisplay.h"


class LayerHelp: public LayerDisplay
{
public :

    virtual void onEnterTransition() override;
    virtual void onExitTransition() override;
    
    CREATE_FUNC(LayerHelp);
private:

protected:
    void onClick(Ref* pSender);
    
    cocos2d::cocoswidget::CScrollView* _scrollDescription;
    cocos2d::cocoswidget::CScrollView* _scrollItem;
    
    virtual bool init();
    
    LayerHelp();
    ~LayerHelp();
    
    
};
#endif /* defined(__gamebase__LayerHelp__) */
