//
//  LayerShopBuyCoin.cpp
//  digger
//
//  Created by Nguyễn Lê Lợi on 10/22/15.
//
//

#include "LayerShopBuyCoin.h"
#include "GameConfig.h"
#include "NativeUtils.h"


LayerShopBuyCoin::LayerShopBuyCoin()
{
    
}

LayerShopBuyCoin::~LayerShopBuyCoin()
{
    
}

bool LayerShopBuyCoin::init()
{
    if (!LayerDisplay::init())
    {
        return false;
    }
    

    
    this->_layerId = LAYER_SHOP_BUY_COIN_ID;
    this->_layerIndex = GUI_LAYER_INDEX;
    
    _background = CImageView::create("GUI/StartGame/Shop/shop_bg.png");
    _background->setPosition(VisibleRect::center());
    m_pWindow->addChild(_background);
    
    _item1 = TVWidget::create("GUI/StartGame/Shop/btn_shop_item.png");
    _item1->setTag(1);
    _item1->setPosition(Vec2(290,300));
    m_pWindow->addChild(_item1);
    
    auto img1 = Sprite::create("GUI/StartGame/Shop/item1_coin.png");
    img1->setAnchorPoint(Vec2(0.5,0));
    img1->setPosition(Vec2(290,220));
    m_pWindow->addChild(img1);
    auto price1 = CLabel::createWithTTF("500", FONT_PATH_GROBOLD, 30);
    price1->setTextColor(Color4B::BLACK);
    price1->setPosition(290,360);
    m_pWindow->addChild(price1);
    auto label1 = CLabel::createWithTTF("1$", FONT_PATH_GROBOLD, 30);
    label1->setPosition(290,185);
    label1->setTextColor(Color4B::BLACK);
    m_pWindow->addChild(label1);
    
    
    _item2 = TVWidget::create("GUI/StartGame/Shop/btn_shop_item.png");
    _item2->setTag(2);
    _item2->setPosition(Vec2(465,300));
    m_pWindow->addChild(_item2);
    
    auto img2 = Sprite::create("GUI/StartGame/Shop/item2_coin.png");
    img2->setAnchorPoint(Vec2(0.5,0));
    img2->setPosition(Vec2(465,220));
    m_pWindow->addChild(img2);
    auto price2 = CLabel::createWithTTF("1000", FONT_PATH_GROBOLD, 30);
    price2->setTextColor(Color4B::BLACK);
    price2->setPosition(465,360);
    m_pWindow->addChild(price2);
    auto label2 = CLabel::createWithTTF("2$", FONT_PATH_GROBOLD, 30);
    label2->setPosition(465,185);
    label2->setTextColor(Color4B::BLACK);
    m_pWindow->addChild(label2);
    
    _item3 = TVWidget::create("GUI/StartGame/Shop/btn_shop_item.png");
    _item3->setTag(3);
    _item3->setPosition(Vec2(640,300));
    m_pWindow->addChild(_item3);
    
    auto img3 = Sprite::create("GUI/StartGame/Shop/item3_coin.png");
    img3->setAnchorPoint(Vec2(0.5,0));
    img3->setPosition(Vec2(640,220));
    m_pWindow->addChild(img3);
    auto price3 = CLabel::createWithTTF("2000", FONT_PATH_GROBOLD, 30);
    price3->setTextColor(Color4B::BLACK);
    price3->setPosition(640,360);
    m_pWindow->addChild(price3);
    auto label3 = CLabel::createWithTTF("3$", FONT_PATH_GROBOLD, 30);
    label3->setPosition(640,185);
    label3->setTextColor(Color4B::BLACK);
    m_pWindow->addChild(label3);
    
    _item4 = TVWidget::create("GUI/StartGame/Shop/btn_shop_item.png");
    _item4->setTag(4);
    _item4->setPosition(Vec2(815,300));
    m_pWindow->addChild(_item4);
    
    auto img4 = Sprite::create("GUI/StartGame/Shop/item4_coin.png");
    img4->setAnchorPoint(Vec2(0.5,0));
    img4->setPosition(Vec2(815,220));
    m_pWindow->addChild(img4);
    auto price4 = CLabel::createWithTTF("5000", FONT_PATH_GROBOLD, 30);
    price4->setTextColor(Color4B::BLACK);
    price4->setPosition(815,360);
    m_pWindow->addChild(price4);
    auto label4 = CLabel::createWithTTF("4$", FONT_PATH_GROBOLD, 30);
    label4->setPosition(815,185);
    label4->setTextColor(Color4B::BLACK);
    m_pWindow->addChild(label4);
    
//    _item5 = TVWidget::create("GUI/StartGame/Shop/btn_shop_item.png");
//    _item5->setTag(5);
//    _item5->setPosition(Vec2(850,300));
//    m_pWindow->addChild(_item5);
//    
//    auto img5 = Sprite::create("GUI/StartGame/Shop/item5_coin.png");
//    img5->setAnchorPoint(Vec2(0.5,0));
//    img5->setPosition(Vec2(850,220));
//    m_pWindow->addChild(img5);
    
//    auto label5 = CLabel::createWithTTF("1$", FONT_PATH_GROBOLD, 30);
//    label5->setPosition(850,185);
//    label5->setTextColor(Color4B::BLACK);
//    m_pWindow->addChild(label5);
    
    this->setCurrentTarget(_item1);
    
    _item1->setOnSelectCallback([this]{
        this->onClick(_item1);
    });
    _item2->setOnSelectCallback([this]{
        this->onClick(_item2);
    });
    _item3->setOnSelectCallback([this]{
        this->onClick(_item3);
    });
    _item4->setOnSelectCallback([this]{
        this->onClick(_item4);
    });
//    _item5->setOnSelectCallback([this]{
//        this->onClick(_item5);
//    });
    
    _item1->setRightNode(_item2);
    _item2->setRightNode(_item3);
    _item3->setRightNode(_item4);
    _item2->setLeftNode(_item1);
    _item3->setLeftNode(_item2);
    _item4->setLeftNode(_item3);
    
//    _item4->setRightNode(_item5);
//    _item5->setLeftNode(_item4);
    this->addChild(m_pWindow);
    return true;
};

void LayerShopBuyCoin::onClick(cocos2d::Ref *pSender)
{
    if (pSender == nullptr)
    {
        this->setOnExitCallback(
                                [this]
                                {
                                    TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_MENU_ID);
                                    
                                });
        TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
        AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
    }
    else if (pSender == _item1)
    {
        NativeUtils::inappBilling(0);
        CCLOG("buy item 1");
    }
    else if (pSender == _item2)
    {
        NativeUtils::inappBilling(1);
        CCLOG("buy item 2");
    }
    else if (pSender == _item3)
    {
        NativeUtils::inappBilling(2);
        CCLOG("buy item 3");
    }
    else if (pSender == _item4)
    {
        NativeUtils::inappBilling(3);
        CCLOG("buy item 4");
    }
//    else if (pSender == _item5)
//    {
////        NativeUtils::inappBilling(4);
//        NativeUtils::restorePurchase();
//        CCLOG("restore");
//    }
}

void LayerShopBuyCoin::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
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
                this->onClick(nullptr);
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

void LayerShopBuyCoin::onExitTransition()
{
    this->removeFromParent();
}

void LayerShopBuyCoin::onEnterTransition()
{
    _eventDispatcher->setEnabled(true);
//    this->setCurrentTarget(_item1);
    _currentTarget->onTarget();
}