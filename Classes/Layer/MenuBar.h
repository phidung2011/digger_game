//
//  MenuBar.h
//  gamebase
//
//  Created by NGOCDIEP on 7/21/15.
//
//

#ifndef __gamebase__MenuBar__
#define __gamebase__MenuBar__


#include <LayerDisplay.h>


class MenuBar: public LayerDisplay
{
public:

    CREATE_FUNC(MenuBar);
    

    void pauseTime();
    void resumeTime();
    void onClick(Ref* pSender);
private:
    virtual bool init();
    
    
    cocos2d::Label* _labelTime;
    
    void updateTime(float f);
    std::string convertTime(int time);
    
public:
    MenuBar();
    ~MenuBar();
    CC_SYNTHESIZE(cocos2d::cocoswidget::CLabel*, _labelScore, LabelScore);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CLabel*, _labelEnemies, LabelEnemies);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CLabel*, _labelDiamonds, LabelDiamonds);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CLabel*, _labelPlayerLives, LabelPlayerLives);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CProgressBar*, _progressBarFuel, ProgressBarFuel);
    CC_SYNTHESIZE(int, _time, Time);
};

#endif /* defined(__gamebase__MenuBar__) */
