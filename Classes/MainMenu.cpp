#include "MainMenu.h"
#include "Game.h"

USING_NS_CC;

MainMenu::MainMenu()
{
	
}

MainMenu::~MainMenu()
{
    if (_keybListener) _eventDispatcher->removeEventListener(_keybListener);
    if (_touchListener) _eventDispatcher->removeEventListener(_touchListener);
    if (_controllerListener) _eventDispatcher->removeEventListener(_controllerListener);
}

bool MainMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    _tag = 1;
    
//    auto menu = Menu::create();
//    this->addChild(menu);
//    
//    for (int i = 0; i < 9; ++i)
//    {
//        Sprite* normalSprite = Sprite::create("obstacle.png");
//        normalSprite->setColor(Color3B(0, 0, 255));
//        Sprite* selectedSprite = Sprite::create("obstacle.png");
//        selectedSprite->setColor(Color3B(0, 0, 128));
//        
//        auto item = MenuItemSprite::create(normalSprite,
//                                               selectedSprite,
//                                               CC_CALLBACK_1(MainMenu::menuPlayCallback, this));
//        
//        menu->addChild(item);
//    }
//    
//    menu->alignItemsInColumns(3, 3, 3, nullptr);
    
    _keybListener = EventListenerKeyboard::create();
    _keybListener->onKeyPressed = CC_CALLBACK_2(MainMenu::onKeyPressed, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keybListener, this);
    
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
    Controller::startDiscoveryController();
#endif
    
    _controllerListener = EventListenerController::create();
    
    _controllerListener->onConnected = CC_CALLBACK_2(MainMenu::onConnectController,this);
    _controllerListener->onDisconnected = CC_CALLBACK_2(MainMenu::onDisconnectedController,this);
    _controllerListener->onKeyDown = CC_CALLBACK_3(MainMenu::onKeyDown, this);
    _controllerListener->onKeyUp = CC_CALLBACK_3(MainMenu::onKeyUp, this);
    _controllerListener->onAxisEvent = CC_CALLBACK_3(MainMenu::onAxisEvent, this);
    _controllerListener->onKeyRepeat = CC_CALLBACK_3(MainMenu::onKeyRepeat, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_controllerListener, this);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(MainMenu::handleTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainMenu::handleTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainMenu::handleTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _touchListener = listener;
    
    scheduleUpdate();
    
    return true;
}

void MainMenu::update(float delta)
{

}

void MainMenu::menuPlayCallback(Ref* sender)
{
//    Director::getInstance()->replaceScene(Game::create());
}

void MainMenu::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
//    log("key pressed: %d", keyCode);
}

bool MainMenu::handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
//    log("touch begin: %f, %f", location.x, location.y);
    
    return true;
}

void MainMenu::handleTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
    //log("touch moved: %f, %f", location.x, location.y);
}

void MainMenu::handleTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
//    log("touch ended: %f, %f", location.x, location.y);
}

void MainMenu::onConnectController(cocos2d::Controller* controller, cocos2d::Event* event)
{
    log("Controller connected %s", controller->getDeviceName().c_str());
}

void MainMenu::onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event)
{
}

void MainMenu::onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
//    log("key down: %d, float value: %f", key, controller->getKeyStatus(key).value);
    
    
    
#endif
}

void MainMenu::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    log("key up: %d", key);
    switch (key) {
        case cocos2d::Controller::BUTTON_A:
            CCLOG("BUTTON_A");
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

void MainMenu::onAxisEvent(cocos2d::Controller* controller, int axis, cocos2d::Event* event)
{
//    log("axis event: %d", axis);
}

void MainMenu::onKeyRepeat(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
//    log("key repeat: %d", key);
}
