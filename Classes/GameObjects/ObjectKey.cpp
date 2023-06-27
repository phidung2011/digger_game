//
//  ObjectKey.cpp
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 7/17/15.
//
//

#include "ObjectKey.h"
#include "AnimationKey.h"

ObjectKey::ObjectKey()
: TypeKey("")
, id(0)
, index(-1)
{
    
}

ObjectKey::ObjectKey(const std::string &t, int i, unsigned int idx)
: TypeKey(t)
, id(i)
, index(idx)
{
    
}

ObjectKey::ObjectKey(const TypeKey &t, int i, unsigned int idx)
: TypeKey(t)
, id(i)
, index(idx)
{
    
}

ObjectKey::ObjectKey(const ObjectKey& t)
: TypeKey(t.type)
, id(t.id)
, index(t.index)
{
    
}

ObjectKey& ObjectKey::operator=(const ObjectKey &t)
{
    type = t.type;
    id = t.id;
    index = t.index;
    return *this;
}

ObjectKey& ObjectKey::operator=(const AnimationKey &t)
{
    type = t.type;
    id = t.id;
    index = t.index;
    return *this;
}

bool ObjectKey::operator==(const ObjectKey &t) const
{
    return index == t.index;
}

bool ObjectKey::operator!=(const ObjectKey &t) const
{
    return index != t.index;
}


