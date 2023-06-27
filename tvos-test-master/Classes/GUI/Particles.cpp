//
//  Particles.cpp
//  gamebase
//
//  Created by Phi Dzung on 7/30/15.
//
//
#include "Particles.h"
#include "base/firePngData.h"
#include "renderer/CCTextureCache.h"
#include "cocos2d.h"

USING_NS_CC;

//static Texture2D* getDefaultTexture(std::string path)
//{
//    Texture2D* texture = nullptr;
//    Image* image = nullptr;
//    do
//    {
//        bool ret = false;
//        const std::string key = "/__firePngData";
//        texture = Director::getInstance()->getTextureCache()->getTextureForKey(key);
//        CC_BREAK_IF(texture != nullptr);
//        
//        image = new (std::nothrow) Image();
//        CC_BREAK_IF(nullptr == image);
//        if(path == "")
//            ret = image->initWithImageData(__firePngData, sizeof(__firePngData));
//        else
//            ret = image->initWithImageFile(path);
//        CC_BREAK_IF(!ret);
//        
//        texture = Director::getInstance()->getTextureCache()->addImage(image, key);
//    } while (0);
//    
//    CC_SAFE_RELEASE(image);
//    
//    return texture;
//}
//
//
//CParticles* CParticles::create()
//{
//    CParticles* ret = new (std::nothrow) CParticles();
//    if (ret && ret->init())
//    {
//        ret->autorelease();
//    }
//    else
//    {
//        CC_SAFE_DELETE(ret);
//    }
//    return ret;
//}
//
//CParticles* CParticles::createWithTotalParticles(int numberOfParticles)
//{
//    CParticles* ret = new (std::nothrow) CParticles();
//    if (ret && ret->initWithTotalParticles(numberOfParticles))
//    {
//        ret->autorelease();
//    }
//    else
//    {
//        CC_SAFE_DELETE(ret);
//    }
//    return ret;
//}
//
//bool CParticles::initWithTotalParticles(int numberOfParticles)
//{
//    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
//    {
//        this->setDuration(-1);
//        
//        // gravity
//        this->setGravity(Vec2::ZERO);
//        
//        // angle
//        this->setAngle(90);
//        this->setAngleVar(360);
//        
//        // speed of particles
//        this->setSpeed(160);
//        this->setSpeedVar(20);
//        
//        // radial
//        this->setRadialAccel(-120);
//        this->setRadialAccelVar(0);
//        
//        // tagential
//        this->setTangentialAccel(30);
//        this->setTangentialAccelVar(0);
//        
//        // emitter position
//        this->setPosition( Vec2(160,240) );
//        this->setPosVar(Vec2::ZERO);
//        
//        // life of particles
//        this->setLife(4);
//        this->setLifeVar(1);
//        
//        // spin of particles
//        this->setStartSpin(0);
//        this->setStartSizeVar(0);
//        this->setEndSpin(0);
//        this->setEndSpinVar(0);
//        
//        // color of particles
//        Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
//        this->setStartColor(startColor);
//        
//        Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
//        this->setStartColorVar(startColorVar);
//        
//        Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
//        this->setEndColor(endColor);
//        
//        Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);
//        this->setEndColorVar(endColorVar);
//        
//        // size, in pixels
//        this->setStartSize(80.0f);
//        this->setStartSizeVar(40.0f);
//        this->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);
//        
//        // emits per second
//        this->setEmissionRate(this->getTotalParticles()/this->getLife());
//       
//        Texture2D* texture = getDefaultTexture("UI/ParticleBatchNode.png");
////        Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("ParticleBatchNode.png");
//        if (texture != nullptr)
//        {
//            setTexture(texture);
//        }
//        
//        // additive
//        this->setBlendAdditive(false);
//        return true;
//    }
//    return false;
//}
