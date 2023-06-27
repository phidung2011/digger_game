//
//  StringUtil.cpp
//  boxingapp
//
//  Created by h.hasegawa on 2014/08/15.
//
//

#include "StringUtil.h"

USING_NS_CC;

/**
 * split
 */
cocos2d::__Array* StringUtil::split(const char *$val, const char *$token)
{
    char *token = strtok(strdup($val), $token);
    auto arr = __Array::create();
    
    while (token != NULL)
    {
        arr->addObject(String::create(StringUtils::toString(token)));
        token = strtok(NULL, $token);
    }
    
    return arr;
}

/**
 * length
 */
int StringUtil::getLength(std::string $str)
{
	using namespace std;
	
    int pos;
    unsigned char lead;
    int char_size;
	int count = 0;
	
	for (pos = 0; pos < $str.size(); pos += char_size)
	{
		lead = $str[pos];
		
		if (lead < 0x80) char_size = 1;
		else if (lead < 0xE0) char_size = 2;
		else if (lead < 0xF0) char_size = 3;
        else char_size = 4;
		
		++count;
    }
	
	return count;
}

/**
 * substr
 */
std::string StringUtil::substr(std::string $str, int $maxLength)
{
	using namespace std;
	
    int pos;
    unsigned char lead;
    int char_size;
	int count = 0;
	std::string _newStr;
	
	for (pos = 0; pos < $str.size(); pos += char_size)
	{
		lead = $str[pos];
		
		if (lead < 0x80) char_size = 1;
		else if (lead < 0xE0) char_size = 2;
		else if (lead < 0xF0) char_size = 3;
        else char_size = 4;
		
		++count;
		
		_newStr.append($str.substr(pos, char_size).c_str());
		
		if (count >= $maxLength)
		{
			break;
		}
		
//		CCLOG("%d, %s", pos, $str.substr(pos, char_size).c_str());
    }
	
	return _newStr;
}