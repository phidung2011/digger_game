//
//  TypeKey.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 9/23/15.
//
//

#ifndef __gamebase__TypeKey__
#define __gamebase__TypeKey__

#include "cocos2d.h"

class ObjectKey;
class AnimationKey;


class TypeKey
{
public:
    TypeKey(const std::string &t);
    TypeKey(const TypeKey& t);
    TypeKey();
    
    std::string type;
    
    TypeKey& operator = (const TypeKey&t);
    
    TypeKey& operator = (const ObjectKey&t);
    
    TypeKey& operator = (const AnimationKey&t);
    
    bool operator == (const TypeKey &t) const;
    
    bool operator != (const TypeKey &t) const;
};

#endif /* defined(__gamebase__TypeKey__) */
