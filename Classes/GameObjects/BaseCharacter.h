//
//  BaseCharacter.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 7/1/15.
//
//

#ifndef __gamebase__BaseCharacter__
#define __gamebase__BaseCharacter__

#include "BaseBomb.h"
#include "CGLProgram.h"
//#include "FreezedSprite.h"


class BaseCharacter : public BaseBomb
{
public:
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    
    void setShader();
    void move(int dir, State state) override;
    CREATE_FUNC(BaseCharacter);
    
    int dirSkill;
    virtual bool isFirable();
    bool isMovable(int dir) override;
    void flip(int dir);
    bool worldUpdate() override;
    void onDestroyObject() override;
    bool destroy() override;
    
    bool updateTile(cocos2d::Vec2 nextPos) override;
    void setRate(float value){_rate=value;}
    float getRate()const{return _rate;}
//    void animUpdate(unsigned int currentLoop) override {};
private:

    int stateToAnimation(State state) const override;
    
protected:
    BaseCharacter();
    ~BaseCharacter();
    
    virtual int getMove(){ return INVALID_TAG;};
    
    CC_SYNTHESIZE(int, _maxHp, MaxHp);
    CC_SYNTHESIZE(int, _currentHp, CurrentHp);
    
    cocos2d::GLProgram* _defaultGLProgram;
    
    float _rate;
    
    CC_SYNTHESIZE(CGLProgram*, _glShaderProgram, GLShaderProgram);
    //    float _dH;
    //    float _dS;
    bool init() override;
};

#endif /* defined(__gamebase__BaseCharacter__) */
