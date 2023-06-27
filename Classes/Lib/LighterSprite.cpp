//
//  LighterSprite.cpp
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 9/7/15.
//
//

#include "LighterSprite.h"
USING_NS_CC;

LighterSprite* LighterSprite::create(const char *pszFileName)
{
    LighterSprite *pobSprite = new LighterSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

bool LighterSprite::initWithFile(const std::string&texFileName)
{
    
    //init this CCSprite
    if (!Sprite::initWithFile(texFileName))
    {
        return false;
    }
    //blendfunc
//    glEnable(GL_BLEND);
    BlendFunc blendFunc={GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};
    this->setBlendFunc(blendFunc);
    setShader();
    return true ;
}
void LighterSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (_glShaderProgram)
    {
        _glShaderProgram->use();
        glUniform1f(glGetUniformLocation(_glShaderProgram->getProgram(), "rate"), _rate);
        glUniform1f(glGetUniformLocation(_glShaderProgram->getProgram(), "u_opacity"), this->getDisplayedOpacity());
        
#if CC_USE_CULLING
        // Don't do calculate the culling if the transform was not updated
        auto visitingCamera = Camera::getVisitingCamera();
        auto defaultCamera = Camera::getDefaultCamera();
        if (visitingCamera == defaultCamera) {
            _insideBounds = ((flags & FLAGS_TRANSFORM_DIRTY)|| visitingCamera->isViewProjectionUpdated()) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
        }
        else
        {
            _insideBounds = renderer->checkVisibility(transform, _contentSize);
        }
        
        if(_insideBounds)
#endif
        {
            _trianglesCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, _polyInfo.triangles, transform, flags);
            renderer->addCommand(&_trianglesCommand);
        }
    }
    else
        Sprite::draw(renderer, transform, flags);
    
}
void LighterSprite::setShader()
{
    
    //create and set shader program
    {
        GLchar * fragSource = (GLchar*) String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("Shaders/LighterShader.fsh").c_str())->getCString();
        _glShaderProgram = CGLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource);
        
        
        //check gl error
        _defaultGLProgram = this->getGLProgram();
        this->setGLProgram(_glShaderProgram);
        
        CHECK_GL_ERROR_DEBUG();
    }
    //check gl error
    CHECK_GL_ERROR_DEBUG();
}
