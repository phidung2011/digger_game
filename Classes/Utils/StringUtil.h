//
//  StringUtil.h
//  boxingapp
//
//  Created by h.hasegawa on 2014/08/15.
//
//

#ifndef __boxingapp__StringUtil__
#define __boxingapp__StringUtil__

#include "cocos2d.h"

class StringUtil
{
private:
    StringUtil();
    ~StringUtil();
    
public:
    static cocos2d::__Array* split(const char *$val, const char *$token);
	static int getLength(std::string $str);
	static std::string substr(std::string $str, int $maxLength);
};

#endif /* defined(__boxingapp__StringUtil__) */
