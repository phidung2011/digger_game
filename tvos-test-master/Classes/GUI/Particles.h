//
//  Particles.h
//  gamebase
//
//  Created by Phi Dzung on 7/30/15.
//
//

#ifndef __gamebase__Particles__
#define __gamebase__Particles__

#include "cocos2d.h"
//! @brief An snow particle system
class CParticles : public cocos2d::ParticleSystemQuad
{
public:
//    static CParticles* create();
//    static CParticles* createWithTotalParticles(int numberOfParticles);
    static CParticles* create(const std::string &plistFile)
    {
        CParticles *ret = new (std::nothrow) CParticles();
        if (ret && ret->initWithFile(plistFile))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return ret;
    };
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    CParticles(){CCLOG("%s",__PRETTY_FUNCTION__);}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CParticles(){CCLOG("%s",__PRETTY_FUNCTION__);}
    

    
private:
//    CC_DISALLOW_COPY_AND_ASSIGN(CParticles);
};
#endif /* defined(__gamebase__Particles__) */
