//
//  CGLProgram.cpp
//  gamebase
//
//  Created by Phi Dzung on 9/7/15.
//
//

#include "CGLProgram.h"

CGLProgram* CGLProgram::createWithByteArrays(const GLchar *vShaderByteArray, const GLchar *fShaderByteArray)
{
    auto ret = new (std::nothrow) CGLProgram();
    if(ret && ret->initWithByteArrays(vShaderByteArray, fShaderByteArray)) {
        ret->link();
        ret->updateUniforms();
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CGLProgram::initWithByteArrays(const GLchar *vShaderByteArray, const GLchar *fShaderByteArray)
{
    if (!GLProgram::initWithByteArrays(vShaderByteArray, fShaderByteArray))
    {
        return false;
    }
    
    return true;
}


void CGLProgram::passUnifoValue1f(std::string unifoName,GLfloat v){
    glUniform1f(_unifoMap[unifoName],v);
}
void CGLProgram::passUnifoValue1i(std::string unifoName,GLint v){
    glUniform1i(_unifoMap[unifoName],v);
}
void CGLProgram::passUnifoValueMatrixNfv(std::string unifoName,const GLfloat *array,int arrayLen){
    assert(arrayLen==4||arrayLen==9||arrayLen==16);
    switch (arrayLen) {
        case 4:
            glUniformMatrix2fv(_unifoMap[unifoName],1,GL_FALSE,array);
            break;
        case 9:
            glUniformMatrix3fv(_unifoMap[unifoName],1,GL_FALSE,array);
            break;
        case 16:
            glUniformMatrix4fv(_unifoMap[unifoName],1,GL_FALSE,array);
            break;
        default:
            assert(false);
            break;
    }
    
}
void CGLProgram::passUnifoValueNfv(std::string unifoName,const GLfloat*array,int arrayLen){
    assert(arrayLen>=1&&arrayLen<=4);
    switch (arrayLen) {
        case 1:
            glUniform1fv(_unifoMap[unifoName],1,array);
            break;
        case 2:
            glUniform2fv(_unifoMap[unifoName],1,array);
            break;
        case 3:
            glUniform3fv(_unifoMap[unifoName],1,array);
            break;
        case 4:
            glUniform4fv(_unifoMap[unifoName],1,array);
            break;
        default:
            assert(false);
            break;
    }
    
}
void CGLProgram::passUnifoValueNfvN(std::string unifoName,const GLfloat*array,int arrayLen,int arrayCount){
    assert(arrayLen>=1&&arrayLen<=4);
    switch (arrayLen) {
        case 1:
            glUniform1fv(_unifoMap[unifoName],arrayCount,array);
            break;
        case 2:
            glUniform2fv(_unifoMap[unifoName],arrayCount,array);
            break;
        case 3:
            glUniform3fv(_unifoMap[unifoName],arrayCount,array);
            break;
        case 4:
            glUniform4fv(_unifoMap[unifoName],arrayCount,array);
            break;
        default:
            assert(false);
            break;
    }
    
}
void CGLProgram::passUnifoValueNiv(std::string unifoName,const GLint*array,int arrayLen){
    assert(arrayLen>=1&&arrayLen<=4);
    switch (arrayLen) {
        case 1:
            glUniform1iv(_unifoMap[unifoName],1,array);
            break;
        case 2:
            glUniform2iv(_unifoMap[unifoName],1,array);
            break;
        case 3:
            glUniform3iv(_unifoMap[unifoName],1,array);
            break;
        case 4:
            glUniform4iv(_unifoMap[unifoName],1,array);
            break;
        default:
            assert(false);
            break;
    }
    
}
void CGLProgram::passUnifoValueMatrixNfv(std::string unifoName,const std::vector<GLfloat>&valueList){
    passUnifoValueMatrixNfv(unifoName, &valueList.front(), (int)valueList.size());
}
void CGLProgram::passUnifoValueNfv(std::string unifoName,const std::vector<GLfloat>&valueList){
    passUnifoValueNfv(unifoName, &valueList.front(), (int)valueList.size());
}
void CGLProgram::passUnifoValueNiv(std::string unifoName,const std::vector<GLint>&valueList){
    passUnifoValueNiv(unifoName, &valueList.front(), (int)valueList.size());
}
