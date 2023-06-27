//
//  CGLProgram.h
//  gamebase
//
//  Created by Phi Dzung on 9/7/15.
//
//

#ifndef __gamebase__CGLProgram__
#define __gamebase__CGLProgram__

#include "cocos2d.h"
class CGLProgram:public cocos2d::GLProgram
{
protected:
    CGLProgram()
    {
//        CCLOG("%s-----%p", __PRETTY_FUNCTION__, this);
    }
    virtual ~CGLProgram()
    {
//        CCLOG("%s-----%p", __PRETTY_FUNCTION__, this);
    }
    std::map<std::string,GLint> _unifoMap;
    
    bool initWithByteArrays(const GLchar *vShaderByteArray, const GLchar *fShaderByteArray);
public:
    
    static CGLProgram* createWithByteArrays(const GLchar *vShaderByteArray, const GLchar *fShaderByteArray);
    
    void attachUniform(std::string unifoName){
        _unifoMap[unifoName] = glGetUniformLocation(this->getProgram(),unifoName.c_str());
    }
    void passUnifoValue1f(std::string unifoName,GLfloat v);
    void passUnifoValue1i(std::string unifoName,GLint v);
    void passUnifoValueMatrixNfv(std::string unifoName,const GLfloat *array,int arrayLen);
    void passUnifoValueNfv(std::string unifoName,const GLfloat *array,int arrayLen);
    void passUnifoValueNfvN(std::string unifoName,const GLfloat*array,int arrayLen,int arrayCount);
    void passUnifoValueNiv(std::string unifoName,const GLint *array,int arrayLen);
    void passUnifoValueMatrixNfv(std::string unifoName,const std::vector<GLfloat>&valueList);
    void passUnifoValueNfv(std::string unifoName,const std::vector<GLfloat>&valueList);
    void passUnifoValueNiv(std::string unifoName,const std::vector<GLint>&valueList);
    
};

#endif /* defined(__gamebase__CGLProgram__) */
