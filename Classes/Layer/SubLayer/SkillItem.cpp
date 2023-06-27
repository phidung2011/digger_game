//
//  SkillItem.cpp
//  gamebase
//
//  Created by NGOCDIEP on 6/24/15.
//
//

#include "SkillItem.h"
#include "Constants.h"
#include "MainGameScene.h"
USING_NS_CC;
USING_NS_CC_WIDGET;

SkillItem::SkillItem()
: _textAmount(NULL)
{
    
}

SkillItem::~SkillItem()
{
    
}

SkillItem* SkillItem::create(const char* pNormal, const char* pSelected, const char* pDisabled)
{
    SkillItem* pRet = new SkillItem();
    if( pRet && pRet->initWithFile(pNormal, pSelected, pDisabled) )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool SkillItem::initWithFile(const char *pNormal, const char *pSelected, const char *pDisabled)
{
    if (!CButton::initWithFile(pNormal, pSelected, pDisabled))
    {
        return false;
    }
    
    _textAmount = CButton::create(UI_NUMBER_CIRCLE);
    _textAmount->initText("", "fonts/arial.ttf", 24, Size::ZERO, Color3B::BLACK);
    _textAmount->getLabel()->setTextColor(Color4B::BLACK);
    _textAmount->setPosition(Vec2(20, this->getContentSize().height * 0.5));
    this->addChild(_textAmount);
    return true;
}
