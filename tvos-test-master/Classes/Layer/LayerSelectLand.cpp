//
//  LayerSelecTypeMap.cpp
//  gamebase
//
//  Created by Phi Dzung on 8/18/15.
//
//


#include "LayerSelectLand.h"
#include "GameConfig.h"
#include "StartGameScene.h"
#include "CShading.h"
#include "PointInTriangle.h"
#include "ui/cocosGUI.h"
using namespace ui;

const Vec2 LayerSelectLand::map1Pos = Vec2(772,400);
const Vec2 LayerSelectLand::map2Pos = Vec2(362,400);
const Vec2 LayerSelectLand::map3Pos = Vec2(1136/2, 640/2);
const Vec2 LayerSelectLand::map4Pos = Vec2(367,232);
const Vec2 LayerSelectLand::map5Pos = Vec2(770,240);


LayerSelectLand::LayerSelectLand()
: _map1Enable(true)
, _map2Enable(false)
, _map3Enable(false)
, _map4Enable(false)
, _map5Enable(false)
{
}

LayerSelectLand::~LayerSelectLand()
{
    _pages.clear();
}

bool LayerSelectLand::init()
{
    if (!LayerDisplay::init())
    {
        return false;
    }
    
    
    
    this->_layerId = LAYER_SELECT_LAND_ID;
    this->_layerIndex = GUI_LAYER_INDEX;
    
    _titleBar = Sprite::create(UI_IMG_BAR_TITLE);
    this->addChild(_titleBar);
    
    //    auto layout1 = ui::Layout::create();
    _btnMap1 = TVWidget::create(UI_IMG_MAP1);
    _btnMap1->setTag(0);
    //    layout1->addChild(_btnMap1);
    
    //    auto layout2 = ui::Layout::create();
    _btnMap2 = TVWidget::create(UI_IMG_MAP2);
    _btnMap2->setTag(1);
    //    layout2->addChild(_btnMap2);
    
    //    auto layout3 = ui::Layout::create();
    _btnMap3 = TVWidget::create(UI_IMG_MAP3);
    _btnMap3->setTag(2);
    //    layout3->addChild(_btnMap3);
    
    //    auto layout4 = ui::Layout::create();
    _btnMap4 = TVWidget::create(UI_IMG_MAP4);
    _btnMap4->setTag(3);
    //    layout4->addChild(_btnMap4);
    
    //    auto layout5 = ui::Layout::create();
    _btnMap5 = TVWidget::create(UI_IMG_MAP5);
    _btnMap5->setTag(4);
    //    layout5->addChild(_btnMap5);
    
    //    _page = ui::PageView::create();
    //    _page->setContentSize(VisibleRect::getVisibleRect().size);
    //    _page->setDirection(cocos2d::ui::PageView::Direction::HORIZONTAL);
    
    _btnMap1->setPosition(VisibleRect::center());
    _btnMap2->setPosition(VisibleRect::center());
    _btnMap3->setPosition(VisibleRect::center());
    _btnMap4->setPosition(VisibleRect::center());
    _btnMap5->setPosition(VisibleRect::center());
    
    //    _page->addPage(layout1);
    //    _page->addPage(layout2);
    //    _page->addPage(layout3);
    //    _page->addPage(layout4);
    //    _page->addPage(layout5);
    //    this->addChild(_page);
    
    //    _page->setTouchEnabled(false);
    //    _page->setEnabled(false);
    
    this->setCurrentTarget(_btnMap1);
    //    _page->addEventListener(CC_CALLBACK_2(LayerSelectLand::onScroll, this));
    
    //    _btnMap1->setOnTargetCallback([this]{
    //        _page->scrollToPage(_currentTarget->getTag());
    //    });
    //    _btnMap2->setOnTargetCallback([this]{
    //        _page->scrollToPage(_currentTarget->getTag());
    //    });
    //    _btnMap3->setOnTargetCallback([this]{
    //        _page->scrollToPage(_currentTarget->getTag());
    //    });
    //    _btnMap4->setOnTargetCallback([this]{
    //        _page->scrollToPage(_currentTarget->getTag());
    //    });
    //    _btnMap5->setOnTargetCallback([this]{
    //        _page->scrollToPage(_currentTarget->getTag());
    //    });
    
    _btnMap5->setOnSelectCallback([this]{
        if (_map5Enable)
        {
            this->setOnExitCallback([]
                                    {
                                        TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_LEVEL_ID, __Integer::create(5));
                                        StartGameScene::getInstance()->getFadeBackground()->runAction(FadeTo::create(0.3, 0));
                                    });
            if (GameSingleton::getInstance()->_cachedImage != 5)
            {
                Director::getInstance()->getTextureCache()->addImageAsync("GUI/StartGame/SelectLevel/img_map5.jpg", [this](Texture2D* texture){
                    this->goNext();
                });
                if (GameSingleton::getInstance()->_cachedImage > 0) {
                    Director::getInstance()->getTextureCache()->removeTextureForKey(
                                                                                    StringUtils::format("GUI/StartGame/SelectLevel/img_map%d.jpg", GameSingleton::getInstance()->_cachedImage));
                }
                
            }
            else
                this->goNext();
        }
    });
    
    
    
    _btnMap4->setOnSelectCallback([this]{
        if (_map4Enable)
        {
            this->setOnExitCallback([]
                                    {
                                        TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_LEVEL_ID, __Integer::create(4));
                                        StartGameScene::getInstance()->getFadeBackground()->runAction(FadeTo::create(0.3, 0));
                                    });
            if (GameSingleton::getInstance()->_cachedImage != 4)
            {
                Director::getInstance()->getTextureCache()->addImageAsync("GUI/StartGame/SelectLevel/img_map5.jpg", [this](Texture2D* texture){
                    this->goNext();
                });
                if (GameSingleton::getInstance()->_cachedImage > 0) {
                    Director::getInstance()->getTextureCache()->removeTextureForKey(
                                                                                    StringUtils::format("GUI/StartGame/SelectLevel/img_map%d.jpg", GameSingleton::getInstance()->_cachedImage));
                }
                
            }
            else
                this->goNext();
        }
    });
    
    _btnMap3->setOnSelectCallback([this]{
        if (_map3Enable)
        {
            this->setOnExitCallback([]
                                    {
                                        TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_LEVEL_ID, __Integer::create(3));
                                        StartGameScene::getInstance()->getFadeBackground()->runAction(FadeTo::create(0.3, 0));
                                    });
            if (GameSingleton::getInstance()->_cachedImage != 3)
            {
                Director::getInstance()->getTextureCache()->addImageAsync("GUI/StartGame/SelectLevel/img_map5.jpg", [this](Texture2D* texture){
                    this->goNext();
                });
                if (GameSingleton::getInstance()->_cachedImage > 0) {
                    Director::getInstance()->getTextureCache()->removeTextureForKey(
                                                                                    StringUtils::format("GUI/StartGame/SelectLevel/img_map%d.jpg", GameSingleton::getInstance()->_cachedImage));
                }
                
            }
            else
                this->goNext();
        }
    });
    
    _btnMap2->setOnSelectCallback([this]{
        if (_map2Enable)
        {
            this->setOnExitCallback([]
                                    {
                                        TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_LEVEL_ID, __Integer::create(2));
                                        StartGameScene::getInstance()->getFadeBackground()->runAction(FadeTo::create(0.3, 0));
                                    });
            if (GameSingleton::getInstance()->_cachedImage != 2)
            {
                Director::getInstance()->getTextureCache()->addImageAsync("GUI/StartGame/SelectLevel/img_map5.jpg", [this](Texture2D* texture){
                    this->goNext();
                });
                if (GameSingleton::getInstance()->_cachedImage > 0) {
                    Director::getInstance()->getTextureCache()->removeTextureForKey(
                                                                                    StringUtils::format("GUI/StartGame/SelectLevel/img_map%d.jpg", GameSingleton::getInstance()->_cachedImage));
                }
                
            }
            else
                this->goNext();
        }
    });
    
    
    _btnMap1->setOnSelectCallback([this]{
        if (_map1Enable)
        {
            this->setOnExitCallback([]
                                    {
                                        TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_LEVEL_ID, __Integer::create(1));
                                        StartGameScene::getInstance()->getFadeBackground()->runAction(FadeTo::create(0.3, 0));
                                    });
            if (GameSingleton::getInstance()->_cachedImage != 1)
            {
                Director::getInstance()->getTextureCache()->addImageAsync("GUI/StartGame/SelectLevel/img_map5.jpg", [this](Texture2D* texture){
                    this->goNext();
                });
                if (GameSingleton::getInstance()->_cachedImage > 0) {
                    Director::getInstance()->getTextureCache()->removeTextureForKey(
                                                                                    StringUtils::format("GUI/StartGame/SelectLevel/img_map%d.jpg", GameSingleton::getInstance()->_cachedImage));
                }
                
            }
            else
                this->goNext();
        }
    });
    
//    if (_map2Enable)
//    {
//        _btnMap1->setRightNode(_btnMap2);
//        _btnMap3->setLeftNode(_btnMap2);
//    }
//    
//    if (_map3Enable)
//    {
//        _btnMap2->setRightNode(_btnMap3);
//        _btnMap4->setLeftNode(_btnMap3);
//    }
//    
//    if (_map4Enable)
//    {
//        _btnMap3->setRightNode(_btnMap4);
//        _btnMap5->setLeftNode(_btnMap4);
//    }
//    
//    if (_map5Enable)
//    {
//        _btnMap4->setRightNode(_btnMap5);
//        _btnMap1->setLeftNode(_btnMap5);
//    }
//    
//    _btnMap5->setRightNode(_btnMap1);
//    _btnMap2->setLeftNode(_btnMap1);
    
    updateLand();
    
    
    
    _pages.pushBack(_btnMap1);
    _pages.pushBack(_btnMap2);
    _pages.pushBack(_btnMap3);
    _pages.pushBack(_btnMap4);
    _pages.pushBack(_btnMap5);
    
    this->addChild(_currentTarget);
    return true;
}
void LayerSelectLand::updateLand()
{
    if (_map2Enable)
    {
        _btnMap1->setRightNode(_btnMap2);
        _btnMap3->setLeftNode(_btnMap2);
    }
    else
    {
        _btnMap1->setRightNode(NULL);
        _btnMap3->setLeftNode(NULL);
    }
    
    if (_map3Enable)
    {
        _btnMap2->setRightNode(_btnMap3);
        _btnMap4->setLeftNode(_btnMap3);
    }
    else
    {
        _btnMap2->setRightNode(NULL);
        _btnMap4->setLeftNode(NULL);
    }
    
    if (_map4Enable)
    {
        _btnMap3->setRightNode(_btnMap4);
        _btnMap5->setLeftNode(_btnMap4);
    }
    else
    {
        _btnMap3->setRightNode(NULL);
        _btnMap5->setLeftNode(NULL);
    }
    
    if (_map5Enable)
    {
        _btnMap4->setRightNode(_btnMap5);
        _btnMap1->setLeftNode(_btnMap5);
    }
    else
    {
        _btnMap4->setRightNode(NULL);
        _btnMap1->setLeftNode(NULL);
    }
    
    _btnMap5->setRightNode(_btnMap1);
    _btnMap2->setLeftNode(_btnMap1);
}

void LayerSelectLand::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    if (_eventDispatcher->isEnabled())
    {
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
        //    log("key down: %d, float value: %f", key, controller->getKeyStatus(key).value);
        
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
                this->setOnExitCallback([]{
                    TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_MENU_ID);
                });
                
                TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
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
        
        
#endif
    }
}


int asdas = 0;
void LayerSelectLand::onScroll(cocos2d::Ref *sender, cocos2d::ui::PageView::EventType eventType)
{
    if (eventType == cocos2d::ui::PageView::EventType::TURNING)
        CCLOG("Turn page --- %d",asdas);
    
    
    //    auto layout = _page->getCurrentFocusedWidget();
    //    this->targetTo((TVWidget*)layout->getChildByTag(_page->getCurPageIndex()));
    
    
    
    asdas++;
}

void LayerSelectLand::targetTo(TVWidget *target)
{
    _eventDispatcher->setEnabled(false);
    TVWidget* removeNode = _currentTarget;
    
    bool isLeft = (target == removeNode->getLeftNode());
    
    _currentTarget->onUnTarget();
    this->setCurrentTarget(target);
    
    
    this->addChild(target);
    
    MoveBy* move = NULL;
    if (isLeft)
    {
        target->setPosition(Vec2(-VisibleRect::getVisibleRect().size.width/2,VisibleRect::getVisibleRect().size.height/2));
        move = MoveBy::create(0.1, Vec2(VisibleRect::getVisibleRect().size.width,0));
    }
    else
    {
        target->setPosition(Vec2(VisibleRect::getVisibleRect().size.width*1.5,VisibleRect::getVisibleRect().size.height/2));
        move = MoveBy::create(0.1, -Vec2(VisibleRect::getVisibleRect().size.width,0));
    }
    
    removeNode->runAction(Sequence::createWithTwoActions(move, CallFunc::create([this,removeNode,target]{
        
        CCLOG("---value : %p",removeNode);
        removeNode->stopAllActions();
        removeNode->setScale(1);
        removeNode->removeFromParent();
        _eventDispatcher->setEnabled(true);
        target->onTarget();
    })));
    target->runAction(move->clone());
    
}



void LayerSelectLand::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 location = touch->getLocation();
    
    log("touch ended: %f, %f", location.x, location.y);
    Vec2 delta = touch->getLocation() - touch->getStartLocation();
    
    if (fabs(delta.x) > fabs(delta.y))
    {
        if (delta.x > 150)
        {
            if (_currentTarget && _currentTarget->getLeftNode())
            {
                this->targetTo(_currentTarget->getLeftNode());
            }
        }
        else if (delta.x < -150)
        {
            if (_currentTarget && _currentTarget->getRightNode())
            {
                this->targetTo(_currentTarget->getRightNode());
            }
        }
    }
    //    else if (fabs(delta.x) < fabs(delta.y))
    //    {
    //        if (delta.y > 150)
    //        {
    //            if (_currentTarget && _currentTarget->getTopNode())
    //            {
    //                this->targetTo(_currentTarget->getTopNode());
    //            }
    //        }
    //        else if (delta.y < -150)
    //        {
    //            if (_currentTarget && _currentTarget->getBotNode())
    //            {
    //                this->targetTo(_currentTarget->getBotNode());
    //            }
    //        }
    //    }
    
}

void LayerSelectLand::onExitTransition()
{
    _titleBar->runAction(MoveTo::create(0.7, VisibleRect::top() + Vec2(0,200)));
    auto fade = FadeOut::create(0.3);
    _currentTarget->runAction(fade);
    _eventDispatcher->setEnabled(false);
    this->runAction(Sequence::create(DelayTime::create(1),CallFunc::create([this]{this->removeFromParent();}), NULL));
    
}
void LayerSelectLand::onEnterTransition()
{
    int starMap2 = DataManager::getInstance()->getStar( 1, 22);
    if (starMap2 > 0)
    {
        _map2Enable = true;
    }
    else
    {
        _map2Enable = false;
    }
    int starMap3 = DataManager::getInstance()->getStar( 2, 22);
    if (starMap3 > 0)
    {
        _map3Enable = true;
    }
    else
    {
        _map3Enable = false;
    }
    int starMap4 = DataManager::getInstance()->getStar( 3, 22);
    if (starMap4 > 0)
    {
        _map4Enable = true;
    }
    else
    {
        _map4Enable = false;
    }
    int starMap5 = DataManager::getInstance()->getStar( 4, 22);
    if (starMap5 > 0)
    {
        _map5Enable = true;
    }
    else
    {
        _map5Enable = false;
    }
    
    updateLand();
    StartGameScene::getInstance()->getFadeBackground()->runAction(FadeTo::create(0.3, 90));
    //    Animator::mark(this->_currentTarget);
    this->_currentTarget->setPosition(Vec2(VisibleRect::getVisibleRect().size.width/2, -VisibleRect::getVisibleRect().size.height/2));
    
    this->_currentTarget->runAction(MoveTo::create(0.3, VisibleRect::center()));
    _eventDispatcher->setEnabled(false);
    _titleBar->setPosition(VisibleRect::top() + Vec2(0,200));
    _titleBar->runAction(MoveTo::create(0.7, VisibleRect::top() + Vec2(0,-70)));
    this->runAction(Sequence::create(DelayTime::create(1),CallFunc::create([this]{_eventDispatcher->setEnabled(true);}), NULL));
}
void LayerSelectLand::onClick(cocos2d::Ref *ref)
{
    
}

void LayerSelectLand::goNext()
{
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
    
#endif
    TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
    StartGameScene::getInstance()->getFadeBackground()->runAction(Sequence::create(FadeTo::create(0.3, 255), NULL));
}

void LayerSelectLand::movePointer(cocos2d::Ref* map)
{
    
}
