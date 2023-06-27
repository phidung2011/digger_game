//
//  AnalogControl.cpp
//  gamebase
//
//  Created by Phi Dzung on 8/8/15.
//
//

#include "AnalogControl.h"
#include "VisibleRect.h"
#include "GameConfig.h"
#include <cmath>

#define MOVE_DELAY 0.0f
#define PARAM_PRE 10

static cocos2d::Vec2 rootPosition;

NS_CC_WIDGET_BEGIN

AnalogControl::AnalogControl()
: m_pBaseBoard(NULL)
, m_pJoystick(NULL)
, m_fRadius(100.0f)
, m_tCenterPoint(Vec2::ZERO)
, m_bRelocateWithAnimation(true)
, m_bAnimationUpdate(false)
, m_bExecuteEventUpdate(false)
, m_tLastPoint(Vec2::ZERO)
, m_bFollowJoystick(DATA_MGR->getGameSettingDocument()["control"].GetBool())
{
    setThisObject(this);
    
}

AnalogControl::~AnalogControl()
{
    this->stopExecuteUpdate();
}

AnalogControl* AnalogControl::create()
{
    AnalogControl* pRet = new AnalogControl();
    if( pRet && pRet->init() )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

AnalogControl* AnalogControl::create(const char* pBaseBoard, const char* pJoystick)
{
    AnalogControl* pRet = new AnalogControl();
    if( pRet && pRet->initWithFile(pBaseBoard, pJoystick) )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void AnalogControl::setRadius(float fRadius)
{
    m_fRadius = fRadius;
}

float AnalogControl::getRadius() const
{
    return m_fRadius;
}

void AnalogControl::setRelocateWithAnimation(bool bAni)
{
    m_bRelocateWithAnimation = bAni;
}

bool AnalogControl::isRelocateWithAnimation() const
{
    return m_bRelocateWithAnimation;
}

bool AnalogControl::init()
{
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    
    setAnchorPoint(Vec2::ZERO);
    setContentSize(CONTROL_RECT.size);
    m_tCenterPoint = Vec2(125,100);
    rootPosition = m_tCenterPoint;
    return true;
}

bool AnalogControl::initWithFile(const char* pBaseBoard, const char* pJoystick)
{
    if( init() )
    {
        if( pBaseBoard && pJoystick && strlen(pBaseBoard) && strlen(pJoystick) )
        {
            setBaseBoardImage(pBaseBoard);
            setJoystickImage(pJoystick);
        }
        return true;
    }
    return false;
}

void AnalogControl::relocateJoystick(bool bAni)
{
    if( bAni )
    {
        Sequence* pSequence = Sequence::create(
                                               MoveTo::create(MOVE_DELAY, m_tCenterPoint),
                                               CallFunc::create(std::bind(&AnalogControl::stopAnimateUpdate,this)),
                                               NULL);
        m_pJoystick->runAction(pSequence);
        performAnimateUpdate();
    }
    else
    {
        m_pJoystick->setPosition(m_tCenterPoint);
    }
}

void AnalogControl::onAnimateUpdate(float dt)
{
    
}

void AnalogControl::performAnimateUpdate()
{
    if( !m_bAnimationUpdate )
    {
        m_bAnimationUpdate = true;
    }
}

void AnalogControl::stopAnimateUpdate()
{
    if( m_bAnimationUpdate )
    {
        if( m_pJoystick )
        {
            m_pJoystick->stopAllActions();
        }
        m_bAnimationUpdate = false;
        stopExecuteUpdate();
    }
}

void AnalogControl::onExecuteEventUpdate(float dt)
{
    if( m_pJoystick )
    {
        Vec2 tOffset = m_pJoystick->getPosition() - m_tCenterPoint;
        executeControlHandler(this, tOffset.x / PARAM_PRE, tOffset.y / PARAM_PRE);
    }
    else
    {
        Vec2 tOffset = m_tLastPoint - m_tCenterPoint;
        executeControlHandler(this, tOffset.x / PARAM_PRE, tOffset.y / PARAM_PRE);
    }
}

void AnalogControl::performExecuteUpdate()
{
    if( !m_bExecuteEventUpdate )
    {
        schedule(schedule_selector(AnalogControl::onExecuteEventUpdate));
        m_bExecuteEventUpdate = true;
    }
}

void AnalogControl::stopExecuteUpdate()
{
    if( m_bExecuteEventUpdate )
    {
        unschedule(schedule_selector(AnalogControl::onExecuteEventUpdate));
        m_bExecuteEventUpdate = false;
    }
}

CWidgetTouchModel AnalogControl::onTouchBegan(Touch *pTouch)
{
    stopAnimateUpdate();
    
    
    Vec2 tPoint = convertToNodeSpace(pTouch->getLocation());
    tPoint.x = tPoint.x * 0.55f;
    tPoint.y = tPoint.y * 0.77f;
    
    if( m_pJoystick )
    {
//        this->setOpacity(166);
        m_pJoystick->setPosition(tPoint);
        m_pBaseBoard->setPosition(tPoint);
        m_tCenterPoint = tPoint;
        auto parent = dynamic_cast<CWidgetWindow*>(this->getParent());
        parent->setTouchArea(m_pBaseBoard->getBoundingBox());
        if( m_pJoystick->getBoundingBox().containsPoint(tPoint) )
        {
            performExecuteUpdate();
            return eWidgetTouchSustained;
        }
    }
    else
    {
        m_tLastPoint = tPoint;
        performExecuteUpdate();
        return eWidgetTouchSustained;
    }
    return eWidgetTouchNone;
}

void AnalogControl::onTouchMoved(Touch *pTouch, float fDuration)
{
    if( m_pJoystick )
    {
        // i don't wanna let u understand this
        Vec2 touchPoint = convertToNodeSpace(pTouch->getLocation());
        touchPoint.x = touchPoint.x * 0.55f;
        touchPoint.y = touchPoint.y * 0.77f;
        Vec2 delta = touchPoint - m_tCenterPoint;
        float fD = delta.getLength();
        if (fD < m_fRadius)
            m_pJoystick->setPosition(touchPoint);
        else
        {
            if (m_bFollowJoystick)
            {
                m_pJoystick->setPosition(touchPoint);
                float rate = (fD - m_fRadius)/fD;
                Vec2 dxy = delta*rate;
                m_tCenterPoint += dxy;
                m_pBaseBoard->setPosition(m_pBaseBoard->getPosition() + dxy);
            }
            else
            {
                m_pJoystick->setPosition(Vec2(
                                              ((touchPoint.x - m_tCenterPoint.x) / fD) * m_fRadius + m_tCenterPoint.x,
                                              ((touchPoint.y - m_tCenterPoint.y) / fD) * m_fRadius + m_tCenterPoint.y
                                              ));
                
            }
        }
    }
    else
    {
        Vec2 tA = convertToNodeSpace(pTouch->getLocation());
        Vec2 tN = m_tCenterPoint-tA;
        float fD = sqrtf(tN.x*tN.x+tN.y*tN.y);
        fD < m_fRadius ? m_tLastPoint = tA : m_tLastPoint = (Vec2(
                                                                  ((tA.x - m_tCenterPoint.x) / fD) * m_fRadius + m_tCenterPoint.x,
                                                                  ((tA.y - m_tCenterPoint.y) / fD) * m_fRadius + m_tCenterPoint.y
                                                                  )
                                                             );
    }
}

void AnalogControl::onTouchEnded(Touch *pTouch, float fDuration)
{
    if( m_pJoystick )
    {
        this->setOpacity(0);
        m_pJoystick->setPosition(rootPosition);
        m_pBaseBoard->setPosition(rootPosition);
        m_tCenterPoint = rootPosition;
        auto parent = dynamic_cast<CWidgetWindow*>(this->getParent());
        parent->setTouchArea(CONTROL_RECT);
        if( !m_bRelocateWithAnimation )
        {
            stopExecuteUpdate();
        }
        relocateJoystick(m_bRelocateWithAnimation);
    }
    else
    {
        stopExecuteUpdate();
    }
}

void AnalogControl::onTouchCancelled(Touch *pTouch, float fDuration)
{
    onTouchEnded(pTouch, fDuration);
}

void AnalogControl::setContentSize(const Size& tContentSize)
{
    Node::setContentSize(tContentSize);
    
    if( m_pBaseBoard )
    {
        m_pBaseBoard->setPosition(m_tCenterPoint);
    }
    
    if( m_pJoystick )
    {
        m_pJoystick->setPosition(m_tCenterPoint);
    }
}

void AnalogControl::setBaseBoardImage(const char* pFile)
{
    if( pFile && strlen(pFile) )
    {
        Texture2D* pTexture = Director::getInstance()->getTextureCache()->addImage(pFile);
        setBaseBoardTexture(pTexture);
    }
}

void AnalogControl::setJoystickImage(const char* pFile)
{
    if( pFile && strlen(pFile) )
    {
        Texture2D* pTexture = Director::getInstance()->getTextureCache()->addImage(pFile);
        setJoystickTexture(pTexture);
    }
}

void AnalogControl::setBaseBoardSpriteFrame(SpriteFrame* pFrame)
{
    if( pFrame )
    {
        if( m_pBaseBoard )
        {
            m_pBaseBoard->setSpriteFrame(pFrame);
        }
        else
        {
            m_pBaseBoard = Sprite::createWithSpriteFrame(pFrame);
            addChild(m_pBaseBoard);
        }
        m_pBaseBoard->setPosition(m_tCenterPoint);
    }
}

void AnalogControl::setJoystickSpriteFrame(SpriteFrame* pFrame)
{
    if( pFrame )
    {
        if( m_pJoystick )
        {
            m_pJoystick->setSpriteFrame(pFrame);
        }
        else
        {
            m_pJoystick = Sprite::createWithSpriteFrame(pFrame);
            addChild(m_pJoystick, 1);
        }
        m_pJoystick->setPosition(m_tCenterPoint);
    }
}

void AnalogControl::setBaseBoardTexture(Texture2D *pTexture)
{
    if( pTexture )
    {
        if( m_pBaseBoard )
        {
            m_pBaseBoard->setTexture(pTexture);
            
            Rect tRect = Rect::ZERO;
            tRect.size = pTexture->getContentSize();
            m_pBaseBoard->setTextureRect(tRect);
        }
        else
        {
            m_pBaseBoard = Sprite::createWithTexture(pTexture);
            addChild(m_pBaseBoard);
        }
        m_pBaseBoard->setPosition(m_tCenterPoint);
    }
}

void AnalogControl::setJoystickTexture(Texture2D *pTexture)
{
    if( pTexture )
    {
        if( m_pJoystick )
        {
            m_pJoystick->setTexture(pTexture);
            
            Rect tRect = Rect::ZERO;
            tRect.size = pTexture->getContentSize();
            m_pJoystick->setTextureRect(tRect);
        }
        else
        {
            m_pJoystick = Sprite::createWithTexture(pTexture);
            addChild(m_pJoystick, 1);
        }
        m_pJoystick->setPosition(m_tCenterPoint);
    }
}

void AnalogControl::setBaseBoardSpriteFrameName(const char* pSpriteName)
{
    SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pSpriteName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pSpriteName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    return setBaseBoardSpriteFrame(pFrame);
}

void AnalogControl::setJoystickSpriteFrameName(const char* pSpriteName)
{
    SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pSpriteName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pSpriteName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    return setJoystickSpriteFrame(pFrame);
}



NS_CC_WIDGET_END
