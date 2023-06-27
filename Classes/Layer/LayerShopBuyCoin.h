//
//  LayerShopBuyCoin.h
//  digger
//
//  Created by Nguyễn Lê Lợi on 10/22/15.
//
//

#ifndef __digger__LayerShopBuyCoin__
#define __digger__LayerShopBuyCoin__

#include "LayerDisplay.h"
//#include "PluginIAP/PluginIAP.h"

class LayerShopBuyCoin : public LayerDisplay
{
public:
    LayerShopBuyCoin();
    ~LayerShopBuyCoin();
//    static LayerShopBuyCoin* create();
    CREATE_FUNC(LayerShopBuyCoin);
    virtual void onExitTransition() override;
    virtual void onEnterTransition() override;
private:
    
//    virtual void onInitialized(bool ok) override;
//    
//    virtual void onSuccess(sdkbox::Product const& p) override;
//    
//    virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;
//    
//    virtual void onCanceled(sdkbox::Product const& p) override;
//    
//    virtual void onRestored(sdkbox::Product const& p) override;
//    
//    virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;
//    
//    virtual void onProductRequestFailure(const std::string &msg) override;
//    
//    virtual void onRestoreComplete(bool ok, const std::string &msg) override;
    void onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event) override;
protected:

    virtual bool init();

    void onClick(cocos2d::Ref* pSender);
    
    
//    cocos2d::cocoswidget::CImageView* _btnBack;
    TVWidget* _item1;
    TVWidget* _item2;
    TVWidget* _item3;
    TVWidget* _item4;
    TVWidget* _item5;
    
//    std::vector<sdkbox::Product> _products;
    
};

#endif /* defined(__digger__LayerShopBuyCoin__) */
