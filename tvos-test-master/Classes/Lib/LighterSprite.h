//
//  LighterSprite.h
//  gamebase
//
//  Created by Phi Dzung on 9/7/15.
//
//

#ifndef __gamebase__LighterSprite__
#define __gamebase__LighterSprite__

#include "cocos-widget.h"
#include "CGLProgram.h"

class LighterSprite : public cocos2d::Sprite
{
public:
    
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
//    void setDH(float value){_dH=value;}
//    float getDH()const{return _dH;}
//    void setDS(float value){_dS=value;}
//    float getDS()const{return _dS;}
    void setRate(float value){_rate=value;}
    float getRate()const{return _rate;}
    
    
    void setShader();
    static LighterSprite* create(const char *pszFileName);
    
    
protected:
    
    LighterSprite()
    : _glShaderProgram(nullptr)
    , _defaultGLProgram(nullptr)
//    , _dH(0)
//    , _dS(0)
    , _rate(0)
    {
    }
    
    virtual ~LighterSprite()
    {
        _glShaderProgram = nullptr;
        _defaultGLProgram = nullptr;
    };
    
    cocos2d::GLProgram* _defaultGLProgram;
    
    CC_SYNTHESIZE(CGLProgram*, _glShaderProgram, GLShaderProgram);
//    float _dH;
//    float _dS;
    float _rate;
    bool initWithFile(const std::string&texFileName) override;
    
};

#endif /* defined(__gamebase__LighterSprite__) */
