//
//  SkillLayer.h
//  gamebase
//
//  Created by Phi Dzung on 6/24/15.
//
//

#ifndef __gamebase__SkillLayer__
#define __gamebase__SkillLayer__

#include "Player.h"

#include "LayerDisplay.h"
#include "SkillItem.h"

class SkillLayer: public LayerDisplay
{
public:

    CREATE_FUNC(SkillLayer);
    void SkillBomDrop();
    void onTargetItem();
private:
    
    virtual void onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event) override;
    virtual void onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event) override;
    bool init() override;
    Player* _player;
    CC_SYNTHESIZE(SkillItem*, _btnBombDrop, BtnBombDrop);
    CC_SYNTHESIZE(SkillItem*, _btnBombFire, BtnBombFire);
    CC_SYNTHESIZE(SkillItem*, _btnBombSpike, BtnBombSpike);
    CC_SYNTHESIZE(SkillItem*, _btnBombTime, BtnBombTime);
//    CC_SYNTHESIZE(SkillItem*, _btnSnowFlake, BtnSnowFlake);
    CC_SYNTHESIZE(SkillItem*, _targetItem, TargetItem);

    
    void SkillBomTime();
    void SkillBomSpikes();
    
    void SkillFire();
    void SkillFreeze();
    void updateSkill();
protected:
    SkillLayer();
    ~SkillLayer();
};
#endif /* defined(__gamebase__SkillLayer__) */
