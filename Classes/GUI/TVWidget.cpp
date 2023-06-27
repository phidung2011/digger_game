//
//  TVWidget.cpp
//  cocos2d-x-test
//
//  Created by Nguyễn Lê Lợi on 12/10/15.
//
//

#include "TVWidget.h"
#include "CShading.h"
USING_NS_CC;


TVWidget::TVWidget()
: _onSelectCallback(NULL)
, _onTargetCallback(NULL)
, _onUnTargetCallback(NULL)
, _leftNode(NULL)
, _rightNode(NULL)
, _botNode(NULL)
, _topNode(NULL)
{
    this->setOpacity(177);
//    this->setOnEnterCallback([this]{
//        this->setOpacity(177);
//        Action* repeat = NULL;
//        repeat = this->getActionByTag(99);
//        if (repeat)
//        {
//            this->setRate(0);
//            this->stopAction(repeat);
//        }
//    });
}

TVWidget::~TVWidget()
{
    
}

TVWidget* TVWidget::create(const std::string &filename)
{
    TVWidget *pobSprite = new TVWidget();
    if (pobSprite && pobSprite->initWithFile(filename))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void TVWidget::onTarget()
{
    if (_onTargetCallback)
    {
        _onTargetCallback();
    }
    
    if (!this->getActionByTag(99))
    {
        this->setRate(0);
        auto shade = CShading::create(0.15f, 0.6);
        auto seq = Sequence::create(shade, shade->reverse(), NULL);
        
        
        auto repeat = RepeatForever::create(seq);
        repeat->setTag(99);
        //    auto spaw = Spawn::create(scale, repeat, NULL);
        this->runAction(repeat);
    }
    auto scale = FadeTo::create(0.1, 255);
    this->runAction(scale);
}

void TVWidget::onUnTarget()
{
    if (_onUnTargetCallback)
    {
        _onUnTargetCallback();
    }
    Action* repeat = NULL;
    repeat = this->getActionByTag(99);
    if (repeat)
    {
        this->stopAction(repeat);
    }
    this->setRate(0);
    this->runAction(FadeTo::create(0.1, 177));
}

void TVWidget::onSelect()
{
//    Action* repeat = NULL;
//    repeat = this->getActionByTag(99);
//    if (repeat)
//    {
//        this->stopAction(repeat);
//    }
//    this->setRate(0);
//    this->runAction(FadeTo::create(0.1, 177));
    
    if (_onSelectCallback)
    {
        _onSelectCallback();
    }
 
}

void TVWidget::onEnter()
{
    LighterSprite::onEnter();
    this->setOnEnterCallback([this]{
        this->setOpacity(177);
        Action* repeat = NULL;
        repeat = this->getActionByTag(99);
        if (repeat)
        {
            this->setRate(0);
            this->stopAction(repeat);
        }
    });
}
