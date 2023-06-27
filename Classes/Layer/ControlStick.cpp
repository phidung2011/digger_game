//
//  ControlStick.cpp
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 8/8/15.
//
//

#include "ControlStick.h"
#include "GameConfig.h"
#include "MainGameScene.h"
ControlStick::ControlStick()
{
    
}
ControlStick::~ControlStick()
{
    
}

bool ControlStick::init()
{
//    auto _listener = EventListenerTouchOneByOne::create();
//    _listener->onTouchBegan = CC_CALLBACK_2(ControlStick::onTouchBegan, this);
//    _listener->onTouchMoved = CC_CALLBACK_2(ControlStick::onTouchMoved, this);
//    _listener->onTouchEnded = CC_CALLBACK_2(ControlStick::onTouchEnded, this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
    
    _analog = AnalogControl::create(UI_CONTROL_BOARD, UI_CONTROL_JOYSTICK);
    _analog->setRadius(_analog->getBaseBoard()->getBoundingBox().size.width*0.5);
    _analog->setOnControlListener(this, ccw_control_selector(ControlStick::onTouched));
    _analog->setOpacity(0);
    m_pWindow->addChild(_analog);
    m_pWindow->setTouchArea(CONTROL_RECT);
    m_pWindow->setTouchAreaEnabled(true);
//    m_pWindow->setMultiTouchEnabled(true);
    this->addChild(m_pWindow);
    
    return true;
}

void ControlStick::onTouched(Ref* pSender, float fx, float fy)
{
    if (!MainGameScene::getInstance()->GAME_DONE && !GameSingleton::getInstance()->isTouchDown)
    {
        int flag = INVALID_TAG;
        auto pos = Vec2(fx, fy);
        float angle = pos.getAngle();
        float angle2 = CC_RADIANS_TO_DEGREES(angle);
        float length = pos.getLength();
        
        if (length > 3)
        {
            if (angle2 > -45 && angle2< 45)
            {
                flag = dt_top;
            }
            else if(angle2 > 45 && angle2< 135)
            {
                flag = dt_left;
            }
            else if((angle2 > 135 && angle2< 180 )|| (angle2 > -180 && angle2 < -135))
            {
                flag = dt_bot;
            }
            if (angle2 < -45 && angle2> -135)
            {
                flag = dt_right;
            }
        }
        
        if (flag != INVALID_TAG)
        {
            MainGameScene::getInstance()->getPlayer()->executeControl(flag);
        }
    }
}

bool ControlStick::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}

void ControlStick::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if (MainGameScene::getInstance()->getPlayer()->getActionPool().empty())
    {
        Vec2 delta = touch->getLocation() - touch->getStartLocation();
        if (delta.getLength() > 150.0f)
        {
            float angle = delta.getAngle();
            
            if (angle >= - PI_NUMBER*0.25f && angle < PI_NUMBER*0.25f)
            {
                MainGameScene::getInstance()->getPlayer()->flip(dt_right);
                MainGameScene::getInstance()->getPlayer()->dirSkill = dt_right;
            }
            else if (angle >= PI_NUMBER*0.25f && angle < PI_NUMBER*0.75f)
            {
                MainGameScene::getInstance()->getPlayer()->flip(dt_top);
                MainGameScene::getInstance()->getPlayer()->dirSkill = dt_top;
            }
            else if (angle < - PI_NUMBER*0.25f && angle >= - PI_NUMBER*0.75f)
            {
                MainGameScene::getInstance()->getPlayer()->flip(dt_bot);
                MainGameScene::getInstance()->getPlayer()->dirSkill = dt_bot;
            }
            else if ((angle >= PI_NUMBER*0.75f && angle <= PI_NUMBER) || (angle < - PI_NUMBER*0.75f && angle >= - PI_NUMBER))
            {
                MainGameScene::getInstance()->getPlayer()->flip(dt_left);
                MainGameScene::getInstance()->getPlayer()->dirSkill = dt_left;
            }
        }
    }
}


void ControlStick::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}

void ControlStick::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}

