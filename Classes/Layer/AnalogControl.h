//
//  AnalogControl.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 8/8/15.
//
//

#ifndef __gamebase__AnalogControl__
#define __gamebase__AnalogControl__

#include "cocos2d.h"
#include "WidgetMacros.h"
#include "Widget.h"
#include "WidgetProtocol.h"

NS_CC_WIDGET_BEGIN

class AnalogControl : public Node, public CWidget, public CControlableProtocol
{
public:
    AnalogControl();
    virtual ~AnalogControl();
    virtual bool init();
    virtual bool initWithFile(const char* pBaseBoard, const char* pJoystick);
    static AnalogControl* create();
    static AnalogControl* create(const char* pBaseBoard, const char* pJoystick);
    
    virtual void setContentSize(const Size& tContentSize);
    void setRadius(float fRadius);
    float getRadius() const;
    void setRelocateWithAnimation(bool bAni);
    bool isRelocateWithAnimation() const;
    
    virtual void setBaseBoardImage(const char* pFile);
    virtual void setJoystickImage(const char* pFile);
    virtual void setBaseBoardSpriteFrame(SpriteFrame* pFrame);
    virtual void setJoystickSpriteFrame(SpriteFrame* pFrame);
    virtual void setBaseBoardTexture(Texture2D *pTexture);
    virtual void setJoystickTexture(Texture2D *pTexture);
    virtual void setBaseBoardSpriteFrameName(const char* pSpriteName);
    virtual void setJoystickSpriteFrameName(const char* pSpriteName);
    
public:
    virtual CWidgetTouchModel onTouchBegan(Touch *pTouch);
    virtual void onTouchMoved(Touch *pTouch, float fDuration);
    virtual void onTouchEnded(Touch *pTouch, float fDuration);
    virtual void onTouchCancelled(Touch *pTouch, float fDuration);
    
protected:
    void relocateJoystick(bool bAni);
    virtual void onAnimateUpdate(float dt);
    void performAnimateUpdate();
    void stopAnimateUpdate();
    virtual void onExecuteEventUpdate(float dt);
    void performExecuteUpdate();
    void stopExecuteUpdate();
    
protected:
    CC_SYNTHESIZE(Sprite*, m_pBaseBoard, BaseBoard);
    CC_SYNTHESIZE(Sprite*, m_pJoystick, Joystick);
    float m_fRadius;
    
    bool m_bFollowJoystick;
    bool m_bExecuteEventUpdate;
    bool m_bAnimationUpdate;
    bool m_bRelocateWithAnimation;
    Vec2 m_tCenterPoint;
    Vec2 m_tLastPoint;
};

NS_CC_WIDGET_END
#endif /* defined(__gamebase__AnalogControl__) */
