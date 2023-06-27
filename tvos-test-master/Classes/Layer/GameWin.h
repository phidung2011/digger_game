//
//  Game win
//  gamebase
//
//  Created by HuyPB on 7/16/15.
//
//

#ifndef __gamebase__GameWin__
#define __gamebase__GameWin__

#include "Popup.h"

class GameWin: public CPopup
{
public:

    CREATE_FUNC(GameWin);
    

    
private:
    
    void onEnterTransition() override;
    void onExitTransition() override;
    void popupTransition() override;
    void onClick(cocos2d::Ref* pSender);
    std::string reformatText(std::string text);
    void setStar();
    
    int _time;
    int _enemies;
    int _diamonds;
    int _fuel;
    int _star;
    
    virtual void onKeyUp(cocos2d::Controller *controller, int key, cocos2d::Event *event) override;
    
protected:
    GameWin();
    ~GameWin();
    
    bool init() override;
    
    cocos2d::Sprite* _bgScoreBig;
    cocos2d::Sprite* _bgScoreSmall;
    cocos2d::Sprite* _iconDiamonds1;
    cocos2d::Sprite* _iconDiamonds2;
    cocos2d::Sprite* _iconDiamonds3;
    cocos2d::Sprite* _iconEnemies;
    cocos2d::Sprite* _iconClock;
    cocos2d::Sprite* _iconFuel;
    cocos2d::Sprite* _bgFade;
    cocos2d::Sprite* _titleBar;
    cocos2d::Sprite* _starIcon1;
    cocos2d::Sprite* _starIcon2;
    cocos2d::Sprite* _starIcon3;
    cocos2d::cocoswidget::CLabel* _equalLabel[4];
    cocos2d::cocoswidget::CLabel* _labelTextScore;
    
    CC_SYNTHESIZE(cocos2d::cocoswidget::CLabel*, _labelTotalScore, LabelTotalScore);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CLabel*, _labelDiamonds, LabelDiamonds);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CLabel*, _labelEnemies, LabelEnemies);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CLabel*, _labelTime, LabelTime);
    CC_SYNTHESIZE(cocos2d::cocoswidget::CLabel*, _labelFuel, LabelFuel);
    

};
#endif /* defined(__gamebase__LayerSelectLevel__) */
