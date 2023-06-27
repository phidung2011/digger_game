//
//  ControlStick.h
//  gamebase
//
//  Created by Phi Dzung on 8/8/15.
//
//

#ifndef __gamebase__ControlStick__
#define __gamebase__ControlStick__

#include <LayerDisplay.h>
#include "AnalogControl.h"

class ControlStick : public LayerDisplay
{
public:
    ControlStick();
    ~ControlStick();
    CREATE_FUNC(ControlStick);
private:
    bool init() override;
    CC_SYNTHESIZE(cocos2d::cocoswidget::AnalogControl*, _analog, Analog);
    void onTouched(Ref* pSender, float fx, float fy);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
};

#endif /* defined(__gamebase__ControlStick__) */
