//
//  SkillItem.h
//  gamebase
//
//  Created by NGOCDIEP on 6/24/15.
//
//

#ifndef __gamebase__SkillItem__
#define __gamebase__SkillItem__

#include "cocos-widget.h"

class SkillItem : public cocos2d::cocoswidget::CButton
{
public:
    static SkillItem* create(const char* pNormal, const char* pSelected = NULL, const char* pDisabled = NULL);
private:
protected:
    SkillItem();
    ~SkillItem();
    
    bool initWithFile(const char *pNormal, const char *pSelected, const char *pDisabled);
    
    CC_SYNTHESIZE(cocos2d::cocoswidget::CButton*, _textAmount, TextAmount);
    CC_SYNTHESIZE(SkillItem*, _nextItem, NextItem);
    
};
#endif /* defined(__gamebase__SkillItem__) */
