//
//  LayerDisplay.cpp
//  gamebase
//
//  Created by Phi Dzung on 5/12/15.
//
//

#include "LayerDisplay.h"
#include "VisibleRect.h"
#include "CShading.h"
USING_NS_CC;
LayerDisplay::LayerDisplay()
: _background(NULL)
, _currentTarget(NULL)
, _controllerListener(NULL)
, _keybListener(NULL)
, _pTouchListener(NULL)
, _pSender(NULL)
, _layerId(INVALID_LAYER_ID)
, _layerIndex(INVALID_LAYER_INDEX)
{
    m_pWindow = cocos2d::cocoswidget::CWidgetWindow::create();
}

LayerDisplay::~LayerDisplay()
{
    if (_keybListener) _eventDispatcher->removeEventListener(_keybListener);
    if (_touchListener) _eventDispatcher->removeEventListener(_touchListener);
    if (_controllerListener) _eventDispatcher->removeEventListener(_controllerListener);
}


void LayerDisplay::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    CCLOG("key pressed: %d", keyCode);
}

bool LayerDisplay::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = touch->getLocation();
    
    CCLOG("touch began: %f, %f", location.x, location.y);
    
    return true;
}

void LayerDisplay::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = touch->getLocation();
    
//    log("touch moved: %f, %f", location.x, location.y);
    
}

void LayerDisplay::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = touch->getLocation();
    
    log("touch ended: %f, %f", location.x, location.y);
    Vec2 delta = touch->getLocation() - touch->getStartLocation();
    
    if (fabs(delta.x) > fabs(delta.y))
    {
        if (delta.x > 150)
        {
            if (_currentTarget && _currentTarget->getRightNode())
            {
                this->targetTo(_currentTarget->getRightNode());
            }
        }
        else if (delta.x < -150)
        {
            if (_currentTarget && _currentTarget->getLeftNode())
            {
                this->targetTo(_currentTarget->getLeftNode());
            }
        }
    }
    else if (fabs(delta.x) < fabs(delta.y))
    {
        if (delta.y > 150)
        {
            if (_currentTarget && _currentTarget->getTopNode())
            {
                this->targetTo(_currentTarget->getTopNode());
            }
        }
        else if (delta.y < -150)
        {
            if (_currentTarget && _currentTarget->getBotNode())
            {
                this->targetTo(_currentTarget->getBotNode());
            }
        }
    }
}

void LayerDisplay::onConnectController(cocos2d::Controller* controller, cocos2d::Event* event)
{
    log("Controller connected %s", controller->getDeviceName().c_str());
}

void LayerDisplay::onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event)
{
}

void LayerDisplay::onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
    //    log("key down: %d, float value: %f", key, controller->getKeyStatus(key).value);
    
    
    
#endif
}

void LayerDisplay::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    if (_eventDispatcher->isEnabled())
    {
        switch (key) {
            case cocos2d::Controller::BUTTON_A:
                CCLOG("BUTTON_A");
                if (_currentTarget && _currentTarget->getOnSelectCallback())
                {
                    _currentTarget->onSelect();
                }
                
                break;
            case cocos2d::Controller::BUTTON_B:
                CCLOG("BUTTON_B");
                break;
            case cocos2d::Controller::BUTTON_C:
                CCLOG("BUTTON_C");
                break;
            case cocos2d::Controller::BUTTON_DPAD_CENTER:
                CCLOG("BUTTON_DPAD_CENTER");
                break;
            case cocos2d::Controller::BUTTON_DPAD_DOWN:
                CCLOG("BUTTON_DPAD_DOWN");
                break;
            case cocos2d::Controller::BUTTON_DPAD_LEFT:
                CCLOG("BUTTON_DPAD_LEFT");
                break;
            case cocos2d::Controller::BUTTON_DPAD_RIGHT:
                CCLOG("BUTTON_DPAD_RIGHT");
                break;
            case cocos2d::Controller::BUTTON_DPAD_UP:
                CCLOG("BUTTON_DPAD_UP");
                break;
            case cocos2d::Controller::BUTTON_LEFT_SHOULDER:
                CCLOG("BUTTON_LEFT_SHOULDER");
                break;
            case cocos2d::Controller::BUTTON_LEFT_THUMBSTICK:
                CCLOG("BUTTON_LEFT_THUMBSTICK");
                break;
            case cocos2d::Controller::BUTTON_PAUSE:
                CCLOG("BUTTON_PAUSE");
                break;
            case cocos2d::Controller::BUTTON_RIGHT_SHOULDER:
                CCLOG("BUTTON_RIGHT_SHOULDER");
                break;
            case cocos2d::Controller::BUTTON_RIGHT_THUMBSTICK:
                CCLOG("BUTTON_RIGHT_THUMBSTICK");
                break;
            case cocos2d::Controller::BUTTON_SELECT:
                CCLOG("BUTTON_SELECT");
                break;
            case cocos2d::Controller::BUTTON_START:
                CCLOG("BUTTON_START");
                break;
            case cocos2d::Controller::BUTTON_X:
                CCLOG("BUTTON_X");
                break;
            case cocos2d::Controller::BUTTON_Y:
                CCLOG("BUTTON_Y");
                break;
            case cocos2d::Controller::BUTTON_Z:
                CCLOG("BUTTON_Z");
                break;
            default:
                break;
        }
    }
}

void LayerDisplay::onAxisEvent(cocos2d::Controller* controller, int axis, cocos2d::Event* event)
{
    //    log("axis event: %d", axis);
}

void LayerDisplay::onKeyRepeat(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    //    log("key repeat: %d", key);
}

bool LayerDisplay::init()
{
    if (!Layer::init())
    {
        return false;
    }
    _controllerListener = EventListenerController::create();
    
    _controllerListener->onConnected = CC_CALLBACK_2(LayerDisplay::onConnectController,this);
    _controllerListener->onDisconnected = CC_CALLBACK_2(LayerDisplay::onDisconnectedController,this);
    _controllerListener->onKeyDown = CC_CALLBACK_3(LayerDisplay::onKeyDown, this);
    _controllerListener->onKeyUp = CC_CALLBACK_3(LayerDisplay::onKeyUp, this);
    _controllerListener->onAxisEvent = CC_CALLBACK_3(LayerDisplay::onAxisEvent, this);
    _controllerListener->onKeyRepeat = CC_CALLBACK_3(LayerDisplay::onKeyRepeat, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_controllerListener, this);
    
    _pTouchListener = EventListenerTouchOneByOne::create();
    _pTouchListener->setSwallowTouches(true);
    
    _pTouchListener->onTouchBegan = CC_CALLBACK_2(LayerDisplay::onTouchBegan, this);
    _pTouchListener->onTouchMoved = CC_CALLBACK_2(LayerDisplay::onTouchMoved, this);
    _pTouchListener->onTouchEnded = CC_CALLBACK_2(LayerDisplay::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_pTouchListener, this);
    
    //    scheduleUpdate();
    
    return true;
}

void LayerDisplay::onEnter()
{
    Layer::onEnter();
    if (_currentTarget)
        _currentTarget->onTarget();
}

void LayerDisplay::targetTo(TVWidget *target)
{
    _currentTarget->onUnTarget();
    this->setCurrentTarget(target);
    target->onTarget();
}

void LayerDisplay::onExit()
{
    cocos2d::Layer::onExit();
//    if (_currentTarget) {
//        Action* repeat = NULL;
//        repeat = _currentTarget->getActionByTag(99);
//        if (repeat)
//        {
//            _currentTarget->stopAction(repeat);
//        }
//        _currentTarget->setRate(0);
//        _currentTarget->setOpacity(177);
//    }
}
