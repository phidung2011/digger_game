//
//  LayerSelectLevel.cpp
//  gamebase
//
//  Created by HuyPB on 6/10/15.
//
//

#include "LayerSelectLevel.h"
#include "GameConfig.h"
#include "MainGameScene.h"
#include "StartGameScene.h"

LayerSelectLevel* LayerSelectLevel::_instance = NULL;

LayerSelectLevel::LayerSelectLevel() {
    //	CCLOG("%s %d", __PRETTY_FUNCTION__, __LINE__);
    _instance = this;
}
LayerSelectLevel::~LayerSelectLevel() {
    //	CCLOG("%s %d", __PRETTY_FUNCTION__, __LINE__);
}
bool LayerSelectLevel::init()
{
    if (!LayerDisplay::init())
    {
        return false;
    }
    
    _lastLevel = 22;
    //    auto listener = EventListenerTouchOneByOne::create();
    //    listener->onTouchBegan = CC_CALLBACK_2(LayerSelectLevel::onTouchBegan, this);
    //    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->_layerId = LAYER_LEVEL_ID;
    this->_layerIndex = BASE_LAYER_INDEX;
    
    //    CButton* addBtn = CButton::create(UI_BTN_HELP);
    //    addBtn->setTag(99);
    //    addBtn->setOnClickListener(this, ccw_click_selector(LayerSelectLevel::addVec));
    //    addBtn->setPosition(VisibleRect::rightBottom() + Vec2(-100,100));
    //    m_pWindow->addChild(addBtn,99);
    //
    //    CButton* writeBtn = CButton::create(UI_BTN_HIGHSCORE);
    //    writeBtn->setTag(100);
    //    writeBtn->setOnClickListener(this, ccw_click_selector(LayerSelectLevel::saveVec));
    //    writeBtn->setPosition(VisibleRect::rightBottom() + Vec2(-200,100));
    //    m_pWindow->addChild(writeBtn,99);
    
    //    _doc.SetArray();
    
    
    this->addChild(m_pWindow);
    
    return true;
}

//void LayerSelectLevel::addVec()
//{
//
//    rapidjson::Document::AllocatorType& allocator = _doc.GetAllocator();
//
//    rapidjson::Value obj = rapidjson::Value(rapidjson::kObjectType);
//
//    obj.AddMember("x", (int)_lastPoint.x, allocator);
//    obj.AddMember("y", (int)_lastPoint.y, allocator);
//
//    auto sp = Sprite::create(UI_BTN_SETTING);
//    sp->setAnchorPoint(Vec2(0.5,0));
//    sp->setPosition(_lastPoint);
//    _scrollView->getContainer()->addChild(sp,99);
//
//
//    _doc.PushBack(obj, allocator);
//
//    CCLOG("size --- %d", _doc.Size());
//}
//
//void LayerSelectLevel::saveVec()
//{
//    DATA_MGR->writeToJsonFile(FileUtils::getInstance()->getWritablePath() + "mapdata.json", _doc);
//
//}
//
//bool LayerSelectLevel::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
//{
//    auto btn1 = m_pWindow->getChildByTag(99);
//    auto btn2 = m_pWindow->getChildByTag(100);
//    auto pos = touch->getLocation();
//    if (!btn1->getBoundingBox().containsPoint(pos) && !btn2->getBoundingBox().containsPoint(pos))
//    {
//        auto actualPos = pos + Vec2(_scrollView->getContainer()->getPosition().x,-_scrollView->getContainer()->getPosition().y);
//
//        _lastPoint = actualPos;
//
//        CCLOG("%f----%f", actualPos.x, actualPos.y);
//    }
//
//
//    return true;
//}
void LayerSelectLevel::chooseLevelClick(cocos2d::Ref *pSender) {
    CButton* bt = (CButton*) pSender;
    
    auto tag = bt->getTag();
    __Integer* level = __Integer::create(tag);
    
    TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_SHOP_ID, level);
    
    
    
    
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
    AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
}

void LayerSelectLevel::onClick(cocos2d::Ref *pSender) {
    this->setOnExitCallback(
                            [this]
                            {
                                TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_SELECT_LAND_ID);
                            });
    TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
    StartGameScene::getInstance()->getFadeBackground()->runAction(FadeTo::create(0.3, 255));
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->playEffect(EFFECT_BTN);
#else
    AUDIO::play2d(EFFECT_BTN, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
}

void LayerSelectLevel::onEnterTransition() {
    int value = 0;
//    _currentTarget = nullptr;
    if (_pSender) {
        value = dynamic_cast<__Integer *>(_pSender)->getValue();
        if (value >= 1)
        {
            _land = value;
            GameSingleton::getInstance()->_cachedImage = _land;
        }
        
        _pSender->release();
        _pSender = nullptr;
    }
    
    _eventDispatcher->setEnabled(false);
    
    _scrollView = CScrollView::create(VisibleRect::getVisibleRect().size);
    _scrollView->ignoreAnchorPointForPosition(true);
    _background = CImageView::create(StringUtils::format("GUI/StartGame/SelectLevel/img_map%d.jpg", _land).c_str());
    _background->setAnchorPoint(Vec2(0, 0));
    _scrollView->setBounceable(false);
    _scrollView->setContainerSize(_background->getBoundingBox().size);
    _scrollView->setDirection(CScrollViewDirection::eScrollViewDirectionVertical); //scroll theo chieu ngang
    _scrollView->getContainer()->addChild(_background);
    _scrollView->setTouchEnabled(false);
    _scrollView->setEnabled(false);
    
    //	_scrollView->getContainer()->setScale(GameSingleton::getInstance()->getScaleFixWith());
    //  _scrollView->setOnScrollingListener(this, ccw_scrolling_selector(LayerSelectLevel::onSCVScrolling));
    
    m_pWindow->addChild(_scrollView);
    std::vector<Vec2> arr = DataManager::getInstance()->getPositionAtLevel(_land);
    
    auto call =
    CallFunc::create(
                     [this, value, arr]
                     {
                         cocos2d::Vector<TVWidget*> widgetList;
                         
                         cocos2d::Vector<Node*> temp;
                         
                         TVWidget* tempNode = NULL;
                         long size = arr.size();
                         std::vector<Vec2>::iterator it;
                         //        int i = 1;
                         int next_level = 0;
                         
                         bool nextLevelAnim = false;
                         for(int i = 0; i < size; i++)
                         {
                             TVWidget* level = NULL;
                             bool check = false;
                             if (i != size - 1) {
                                 level = TVWidget::create("GUI/StartGame/SelectLevel/img_pointer.png");
                             }
                             else
                             {
                                 level = TVWidget::create("GUI/StartGame/SelectLevel/img_last_pointer.png");
                             }
                             if (tempNode)
                             {
                                 level->setBotNode(tempNode);
                                 tempNode->setTopNode(level);
                             }
                             tempNode = level;
                             
                             widgetList.pushBack(level);
                             
                             
                             
                             level->ignoreAnchorPointForPosition(true);
                             if (value < 0 && i + 1 == -1*value)
                             {
                                 
                                 if (_lastLevel == -1*value)
                                 {
                                     check = true;
                                 }
                                 else
                                     temp.pushBack(level);
                                 
                             }
                             else
                                 temp.pushBack(level);
                             int totalStar = DataManager::getInstance()->getStar( _land, i + 1);
                             if (totalStar > 0 || next_level == 0)
                             {
                                 //								level->initText(StringUtils::format("%d",i+1), FONT_PATH_GROBOLD, 28, Size::ZERO, Color3B::WHITE);
                                 //                                level->getLabel()->setPosition(level->getLabel()->getPosition() + Vec2(0,-10));
                                 
                                 auto label = CLabel::createWithTTF(StringUtils::format("%d",i+1), FONT_PATH_GROBOLD, 28, Size::ZERO);
                                 label->setTag(99);
                                 label->setPosition(Vec2(level->getContentSize()/2) + Vec2(0,-15));
                                 level->addChild(label);
                                 level->setTag(i+1);
                                 level->setOnSelectCallback([level,this]{
                                     this->chooseLevelClick(level);
                                 });
                                 level->setOnTargetCallback([this, level]{
                                     _scrollView->setContentOffsetEaseIn(Vec2(0,-level->getPosition().y + winSize.height/2), 0.3, 0.1);
                                 });
                                 level->setOnUnTargetCallback([level]{
                                 });

                                 if(totalStar > 0)
                                 {
                                     cocos2d::Vector<cocos2d::Node*> tmp;
                                     for(int j = 0; j< 3; j++)
                                     {
                                         CImageView* img;
                                         if(j < totalStar)
                                             img = CImageView::create(UI_IMG_STAR);
                                         else
                                             img = CImageView::create(UI_IMG_STAR_1);
                                         
                                         
                                         int subPos = 0;
                                         if(j == 0 || j == 2)
                                             subPos = -6;
                                         img->setPosition(Vec2(j*25 + 60, 110 + subPos));
                                         
                                         if(j == 0)
                                             img->setRotation(-30);
                                         else if(j == 2)
                                             img->setRotation(30);
                                         img->setTag(j+1);
                                         level->addChild(img);
                                         
                                         if (check)
                                         {
                                             img->setScale(0);
                                             tmp.pushBack(img);
                                         }
                                     }
                                     if (check && !tmp.empty())
                                     {
                                         auto call = CallFunc::create([tmp,this]{
                                             Animator::multiPumpIn(0.2, tmp);
                                             
                                         });
                                         _eventDispatcher->setEnabled(false);
                                         auto seq = Sequence::create(Animator::mark(level, 0.1*i), Animator::turning(level), call, NULL);
                                         level->runAction(seq);
                                         
                                     }
                                     
                                     
                                 }
                                 else
                                 {
                                     next_level = 1;
                                     _lastLevel = i + 1;
                                 }
                                 
                                 if (nextLevelAnim)
                                 {
                                     auto lock = CImageView::create(UI_IMG_LOCK);
                                     lock->setPosition(Vec2(level->getContentSize()/2) + Vec2(0,-9));
                                     level->addChild(lock,99);
                                     
                                     label->setOpacity(0);
                                     _eventDispatcher->setEnabled(false);
                                     auto call = CallFunc::create([this, level, label]{
                                         label->runAction(Animator::mark(label));
                                     });
                                     
                                     auto seq = Sequence::create(Animator::fadeOut(lock,0.1*i + 2), call, NULL);
                                     
                                     lock->runAction(seq);
                                 }
                             }
                             else
                             {
                                 auto lock = CImageView::create(UI_IMG_LOCK);
                                 lock->setPosition(Vec2(level->getContentSize()/2) + Vec2(0,-9));
                                 level->addChild(lock);
                             }
                             
                             level->setAnchorPoint(Vec2(0.5,0));
                             level->setPosition(arr.at(i) - Vec2(level->getContentSize().width/2, 0));
                             _scrollView->getContainer()->addChild(level);
                             if (check)
                             {
                                 nextLevelAnim = true;
                             }
                         }
                         
                         if (value < 0)
                         {
                             float time = 0.05*(-value);
                             _scrollView->setContentOffsetEaseIn(Vec2(0,-arr.at(-value -1).y + winSize.height/2), time, 0.5);
                             auto target = widgetList.at(-value - 1);
                             this->setCurrentTarget(target);
                             this->runAction(Sequence::create(DelayTime::create(time),CallFunc::create([this,target]{
                                 _eventDispatcher->setEnabled(true);
                                 isTouch = true;
                                 target->onTarget();
                             }), NULL));
                             
                         }
                         else if (value >= 0)
                         {
                             float time = 0.05*_lastLevel;
                             _scrollView->setContentOffsetEaseIn(Vec2(0,-arr.at(_lastLevel - 1).y + winSize.height/2), time, 0.5);
                             auto target = widgetList.at(_lastLevel - 1);
                             this->setCurrentTarget(target);
                             this->runAction(Sequence::create(DelayTime::create(time),CallFunc::create([this,target]{
                                 _eventDispatcher->setEnabled(true);
                                 isTouch = true;
                                 target->onTarget();
                             }), NULL));
                         }
                         
                         
                         Animator::multiPumpIn(0.05, temp);
                         
//                         if (_currentTarget == nullptr)
//                             _currentTarget = widgetList.at(0);
                     });
    
    
    //    if (StartGameScene::getInstance()->getFadeBackground()->getOpacity() == 90)
    //    {
    
    auto call2 = CallFunc::create([this]{_currentTarget->onTarget();});
    
    auto seq = Sequence::create(DelayTime::create(0.5), call, DelayTime::create(0.5), call2, NULL);
    this->runAction(seq);
    isTouch = false;
    //    }
}

void LayerSelectLevel::onEnter() {
    Layer::onEnter();
}

void LayerSelectLevel::onExitTransition() {
    _eventDispatcher->setEnabled(false);
    
    //	auto fadeIn = FadeTo::create(0.5, 255);
    auto call = CallFunc::create([this] {
        _scrollView->removeFromParent();
        this->removeFromParent();
        //        _eventDispatcher->setEnabled(true);
    });
    auto seq = Sequence::create(DelayTime::create(0.3), call, NULL);
    this->runAction(seq);
}

void LayerSelectLevel::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    if (_eventDispatcher->isEnabled() && isTouch)
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
                    TransitionManager::getInstance()->addToSceneByCustomTransition(LAYER_SELECT_LAND_ID);
                });
                
                TransitionManager::getInstance()->removeFromSceneByCustomTransition(this->getLayerId());
                StartGameScene::getInstance()->getFadeBackground()->runAction(FadeTo::create(0.3, 255));
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


void LayerSelectLevel::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = touch->getLocation();
    
    log("touch ended: %f, %f", location.x, location.y);
    Vec2 delta = touch->getLocation() - touch->getStartLocation();
    
    if (fabs(delta.x) > fabs(delta.y))
    {
        if (delta.x > 150)
        {
            if (_currentTarget && _currentTarget->getRightNode() && _currentTarget->getRightNode()->getOnSelectCallback())
            {
                this->targetTo(_currentTarget->getRightNode());
            }
        }
        else if (delta.x < -150)
        {
            if (_currentTarget && _currentTarget->getLeftNode() && _currentTarget->getLeftNode()->getOnSelectCallback())
            {
                this->targetTo(_currentTarget->getLeftNode());
            }
        }
    }
    else if (fabs(delta.x) < fabs(delta.y))
    {
        if (delta.y > 150)
        {
            if (_currentTarget && _currentTarget->getTopNode() && _currentTarget->getTopNode()->getOnSelectCallback())
            {
                this->targetTo(_currentTarget->getTopNode());
            }
        }
        else if (delta.y < -150)
        {
            if (_currentTarget && _currentTarget->getBotNode() && _currentTarget->getBotNode()->getOnSelectCallback())
            {
                this->targetTo(_currentTarget->getBotNode());
            }
        }
    }
}

