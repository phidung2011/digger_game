//
//  Setting game
//  gamebase
//
//  Created by HuyPB on 6/10/15.
//
//

#ifndef __gamebase__SettingGame__
#define __gamebase__SettingGame__

#include <LayerDisplay.h>
#include <cocos-widget.h>

class SettingGame: public LayerDisplay
{
public:

    CREATE_FUNC(SettingGame);
    static SettingGame* getInstance(){return _instance;};
    void up();
    void down();
    void right();
    void left();
private:
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) override;
    static SettingGame* _instance;
    void onKeyUp(cocos2d::Controller *controller, int key, cocos2d::Event *event) override;
protected:
    SettingGame();
    ~SettingGame();
    
    int _sound;
    int _music;
//    int _difficult;
    bool _control;
    
    virtual bool init();
    
//    cocos2d::cocoswidget::CButton* _difficultBtn;
    cocos2d::cocoswidget::CButton* _musicBtn;
    cocos2d::cocoswidget::CButton* _soundBtn;
    
//    cocos2d::cocoswidget::CLabel* _diffcultLabel;
    cocos2d::cocoswidget::CSlider* _soundSlider;
    cocos2d::cocoswidget::CSlider* _musicSlider;
//    cocos2d::cocoswidget::CCheckBox* _checkBox;
//    cocos2d::cocoswidget::CLabel* _checkBoxLabel;
//    cocos2d::cocoswidget::CImageView* _exitBtn;
    
    
    void onClick(Ref* pSender);
//    void onCheck();
//    void onValueChanged(Ref* pSender, int nValue);
    virtual void onEnterTransition() override;
    virtual void onExitTransition() override;
    
//    int viewFromValue(int value);
    
    CC_SYNTHESIZE(cocos2d::cocoswidget::CSlider*, _currentWidget, CurrentWidget);
};
#endif /* defined(__gamebase__LayerSelectLevel__) */
