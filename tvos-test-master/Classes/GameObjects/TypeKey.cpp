//
//  TypeKey.cpp
//  gamebase
//
//  Created by Phi Dzung on 9/23/15.
//
//

#include "TypeKey.h"
#include "ObjectKey.h"
#include "AnimationKey.h"


TypeKey::TypeKey()
: type("")
{
}

TypeKey::TypeKey(const std::string &t)
: type(t)
{
    
}

TypeKey::TypeKey(const TypeKey& t)
: type(t.type)
{

}

TypeKey& TypeKey::operator=(const TypeKey &t)
{
    type = t.type;
    return *this;
}

TypeKey& TypeKey::operator=(const ObjectKey &t)
{
    type = t.type;
    return *this;
}

TypeKey& TypeKey::operator=(const AnimationKey &t)
{
    type = t.type;
    return *this;
}

bool TypeKey::operator==(const TypeKey &t) const
{
    return type.compare(t.type) == 0;
}

bool TypeKey::operator!=(const TypeKey &t) const
{
    return type.compare(t.type) != 0;
}


