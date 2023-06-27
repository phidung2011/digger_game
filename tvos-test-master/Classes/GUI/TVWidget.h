//
//  TVWidget.h
//  cocos2d-x-test
//
//  Created by Phi Dzung on 12/10/15.
//
//

#ifndef TVWidget_h
#define TVWidget_h

#include "LighterSprite.h"

class TVWidget : public LighterSprite
{
public:
    CREATE_FUNC(TVWidget);
    
    static TVWidget* create(const std::string &filename);
    void setOnTargetCallback(const std::function<void()>& callback) { _onTargetCallback = callback; }
    const std::function<void()>& getOnTargetCallback() const { return _onTargetCallback; }
    void setOnUnTargetCallback(const std::function<void()>& callback) { _onUnTargetCallback = callback; }
    const std::function<void()>& getOnUnTargetCallback() const { return _onUnTargetCallback; }
    void setOnSelectCallback(const std::function<void()>& callback) { _onSelectCallback = callback; }
    const std::function<void()>& getOnSelectCallback() const { return _onSelectCallback; }
    
    virtual void onTarget();
    virtual void onSelect();
    virtual void onUnTarget();
    virtual void onEnter() override;
    
private:

protected:
    TVWidget();
    virtual ~TVWidget();
    
    std::function<void()> _onTargetCallback = NULL;
    std::function<void()> _onSelectCallback = NULL;
    std::function<void()> _onUnTargetCallback = NULL;
    
    CC_SYNTHESIZE(TVWidget*, _rightNode, RightNode);
    CC_SYNTHESIZE(TVWidget*, _leftNode, LeftNode);
    CC_SYNTHESIZE(TVWidget*, _topNode, TopNode);
    CC_SYNTHESIZE(TVWidget*, _botNode, BotNode);
};

#endif /* TVWidget_h */
