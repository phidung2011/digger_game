//
//  LayerHelp.cpp
//  gamebase
//
//  Created by NWS on 7/23/15.
//
//

#include "LayerHelp.h"
#include "GameConfig.h"
#include "StartGameScene.h"
#define  SKILL1  "skill1"
#define  SKILL2  "skill2"
#define  SKILL3  "skill3"
#define  SKILL4  "skill4"
#define  SKILL5  "skill5"
#define  SKILL6  "skill6"
#define  SKILL7  "skill7"
#define  SKILL8  "skill8"
#define  SIZE_ITEM Size(100,100)
#define  FONT_SIZE_SETTING 40
#define  SIZE_SCROLL Size(300,350)
#define  SIZE_SCROLL_INFO Size(500,350)

USING_NS_CC;
USING_NS_CC_WIDGET;

LayerHelp::LayerHelp(){}
LayerHelp::~LayerHelp(){}

bool LayerHelp::init()
{
    this->_layerId = LAYER_HELP_ID;
    this->_layerIndex = GUI_LAYER_INDEX;
    
    _background = CImageView::create("GUI/StartGame/Help/bg.png");
    _background->setPosition(VisibleRect::center());
    _background->addChild(m_pWindow);
    this->addChild(_background);
    
    _scrollDescription = CScrollView::create(Size(586,140));
    _scrollDescription->setPosition(Vec2(46,221));
    _scrollDescription->ignoreAnchorPointForPosition(true);
    _scrollDescription->setBounceable(false);

    _scrollDescription->setDirection(CScrollViewDirection::eScrollViewDirectionVertical);
    
    auto _labelDescription = CLabel::createWithTTF("asd dsa h hdhsh fkd vs \n fkds fdsiksdc vksdf sdksv  hdh hds sdsh sad ashd sdkdsnsd \n  nsdkfjsdfkn asdas da asdasfasdfd \n asfsadfdad asd adsa asda dasd asfsd \n afdsf adsafafa adfsafsfds asdsaafaf sdfdsfsdfsf sdfsfsfsdf sdfsdfsfsdf sdfsdfsf", FONT_PATH_GROBOLD, 30);
    _labelDescription->setWidth(580);
    _labelDescription->setLineBreakWithoutSpace(true);
    _labelDescription->ignoreAnchorPointForPosition(true);
    
    _scrollDescription->setContainerSize(_labelDescription->getBoundingBox().size);
    
    _scrollDescription->getContainer()->addChild(_labelDescription);
    
    m_pWindow->addChild(_scrollDescription);
    
    _scrollItem = CScrollView::create(Size(586,92));
    _scrollItem->setPosition(Vec2(46,40));
    _scrollItem->ignoreAnchorPointForPosition(true);
    _scrollItem->setBounceable(false);
    
    _scrollItem->setDirection(CScrollViewDirection::eScrollViewDirectionHorizontal);
    _scrollItem->setContainerSize(Size(80*12, 80));
    for (int i = 0; i< 12; i++)
    {
        auto item = CButton::create(StringUtils::format("GUI/StartGame/Help/%d.png",i+1).c_str());
        item->setPosition(Vec2(40 + 80*(i),40));
        _scrollItem->getContainer()->addChild(item);
    }
    
    
    m_pWindow->addChild(_scrollItem);

    
    auto window = CWidgetWindow::create();
    this->addChild(window);
    CButton *btExit = CButton::create(UI_BTN_BACK);
    btExit->ignoreAnchorPointForPosition(true);
    btExit->setAnchorPoint(Vec2(0.5,0));
    btExit->setPosition(VisibleRect::leftTop() + Vec2(40, -100));
    btExit->setOnClickListener(this, ccw_click_selector(LayerHelp::onClick));
    window->addChild(btExit);
    
    return true;
}
void LayerHelp::onClick(Ref* pSender)
{
    this->setOnExitCallback([]
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
void LayerHelp::onEnterTransition()
{
    _eventDispatcher->setEnabled(true);
    
}
void LayerHelp::onExitTransition()
{
    this->removeFromParent();
}