//
//  AnimationKey.cpp
//  gamebase
//
//  Created by Phi Dzung on 9/23/15.
//
//

#include "AnimationKey.h"
#include "AvatarConfig.h"

AnimationKey::AnimationKey()
: ObjectKey("",0,0)
, level(0)
{
    
}

AnimationKey::AnimationKey(const TypeKey& t, int i, unsigned int idx, int l)
: ObjectKey(t,i,idx)
, level(l)
{
    
}

AnimationKey::AnimationKey(const std::string &t, int i, unsigned int idx, int l)
: ObjectKey(t,i,idx)
, level(l)
{
    
}

AnimationKey::AnimationKey(const ObjectKey& o, int l)
: ObjectKey(o)
, level(l)
{
    
}

AnimationKey::AnimationKey(const AnimationKey& t)
: ObjectKey(t.type, t.id, t.index)
, level(t.level)
{
    
}

const ObjectKey ObjectKey::PLAYER_KEY = ObjectKey("CHAR",(int)IDCHAR::PLAYER, -1);


const ObjectKey ObjectKey::BOMB_DROP_KEY = ObjectKey("ITEM",(int)IDITEM::BOMB_DROP, 0);
const ObjectKey ObjectKey::BOMB_FIRE_KEY = ObjectKey("ITEM",(int)IDITEM::BOMB_FIRE, 1);
const ObjectKey ObjectKey::BOMB_SPIKE_KEY = ObjectKey("ITEM",(int)IDITEM::BOMB_SPIKE, 2);
const ObjectKey ObjectKey::BOMB_TIME_KEY = ObjectKey("ITEM",(int)IDITEM::BOMB_TIME, 3);
const ObjectKey ObjectKey::BOOM_BOMB_KEY = ObjectKey("ITEM",(int)IDITEM::BOOM_BOMB, 4);
const ObjectKey ObjectKey::DIAMOND_KEY = ObjectKey("ITEM",(int)IDITEM::DIAMOND, 5);

const ObjectKey ObjectKey::STONE_KEY = ObjectKey("ITEM",(int)IDITEM::STONE, 6);
const ObjectKey ObjectKey::BOX_GOLD_KEY = ObjectKey("ITEM",(int)IDITEM::BOX_GOLD, 7);
const ObjectKey ObjectKey::BOX_BOMB_DROP_KEY = ObjectKey("ITEM",(int)IDITEM::BOX_BOMB_DROP, 8);
const ObjectKey ObjectKey::BOX_BOMB_FIRE_KEY = ObjectKey("ITEM",(int)IDITEM::BOX_BOMB_FIRE, 9);
const ObjectKey ObjectKey::BOX_BOMB_SPIKE_KEY = ObjectKey("ITEM",(int)IDITEM::BOX_BOMB_SPIKE, 10);
const ObjectKey ObjectKey::BOX_BOMB_TIME_KEY = ObjectKey("ITEM",(int)IDITEM::BOX_BOMB_TIME, 11);
const ObjectKey ObjectKey::GOLD_KEY = ObjectKey("ITEM",(int)IDITEM::GOLD, 12);
const ObjectKey ObjectKey::SNOW_FLAKE_KEY = ObjectKey("ITEM",(int)IDITEM::SNOW_FLAKE, 13);
const ObjectKey ObjectKey::FUEL_KEY = ObjectKey("ITEM",(int)IDITEM::FUEL, 14);

const ObjectKey ObjectKey::HAMMER_KEY = ObjectKey("CHAR",(int)IDCHAR::HAMMER, 15);
const ObjectKey ObjectKey::SHIPPER_KEY = ObjectKey("CHAR",(int)IDCHAR::SHIPPER, 16);
const ObjectKey ObjectKey::TANKER_KEY = ObjectKey("CHAR",(int)IDCHAR::TANKER, 17);
const ObjectKey ObjectKey::TRACKER_KEY = ObjectKey("CHAR",(int)IDCHAR::TRACKER, 18);
const ObjectKey ObjectKey::ROLLER_KEY = ObjectKey("CHAR",(int)IDCHAR::ROLLER, 19);

const ObjectKey ObjectKey::BOOM_CHARACTER_KEY = ObjectKey("ITEM",(int)IDITEM::BOOM_CHARACTER, 20);
const ObjectKey ObjectKey::BOOM_MINE_KEY = ObjectKey("ITEM",(int)IDITEM::BOOM_MINE, 21);
const ObjectKey ObjectKey::BOOM_TIME_BOMB_KEY = ObjectKey("ITEM",(int)IDITEM::BOOM_TIME_BOMB, 22);

const ObjectKey ObjectKey::NEXT_STAGE_DOOR_KEY = ObjectKey("ITEM",(int)IDITEM::NEXT_STAGE_DOOR, 23);

const ObjectKey ObjectKey::HP_UP_KEY = ObjectKey("ITEM",14, 24);

const ObjectKey ObjectKey::EFFECT_LAND_KEY = ObjectKey("EFFECT",1, 0);


const AnimationKey AnimationKey::PLAYER_KEY = AnimationKey(ObjectKey::PLAYER_KEY,1);
const AnimationKey AnimationKey::HAMMER_KEY = AnimationKey(ObjectKey::HAMMER_KEY,1);
const AnimationKey AnimationKey::SHIPPER_KEY = AnimationKey(ObjectKey::SHIPPER_KEY,1);
const AnimationKey AnimationKey::TANKER_KEY = AnimationKey(ObjectKey::TANKER_KEY,1);
const AnimationKey AnimationKey::TRACKER_KEY = AnimationKey(ObjectKey::TRACKER_KEY,1);
const AnimationKey AnimationKey::ROLLER_KEY = AnimationKey(ObjectKey::ROLLER_KEY,1);

const AnimationKey AnimationKey::BOMB_DROP_KEY = AnimationKey(ObjectKey::BOMB_DROP_KEY,1);
const AnimationKey AnimationKey::BOMB_FIRE_KEY = AnimationKey(ObjectKey::BOMB_FIRE_KEY,1);
const AnimationKey AnimationKey::BOMB_SPIKE_KEY = AnimationKey(ObjectKey::BOMB_SPIKE_KEY,1);
const AnimationKey AnimationKey::BOMB_TIME_KEY = AnimationKey(ObjectKey::BOMB_TIME_KEY,1);
const AnimationKey AnimationKey::BOOM_BOMB_KEY = AnimationKey(ObjectKey::BOOM_BOMB_KEY,1);
const AnimationKey AnimationKey::DIAMOND1_KEY = AnimationKey(ObjectKey::DIAMOND_KEY,1);
const AnimationKey AnimationKey::DIAMOND2_KEY = AnimationKey(ObjectKey::DIAMOND_KEY,2);
const AnimationKey AnimationKey::DIAMOND3_KEY = AnimationKey(ObjectKey::DIAMOND_KEY,3);

const AnimationKey AnimationKey::STONE_KEY = AnimationKey(ObjectKey::STONE_KEY,1);
const AnimationKey AnimationKey::BOX_GOLD_KEY = AnimationKey(ObjectKey::BOX_GOLD_KEY,1);
const AnimationKey AnimationKey::BOX_BOMB_DROP_KEY = AnimationKey(ObjectKey::BOX_BOMB_DROP_KEY,1);
const AnimationKey AnimationKey::BOX_BOMB_FIRE_KEY = AnimationKey(ObjectKey::BOX_BOMB_FIRE_KEY,1);
const AnimationKey AnimationKey::BOX_BOMB_SPIKE_KEY = AnimationKey(ObjectKey::BOX_BOMB_SPIKE_KEY,1);
const AnimationKey AnimationKey::BOX_BOMB_TIME_KEY = AnimationKey(ObjectKey::BOX_BOMB_TIME_KEY,1);
const AnimationKey AnimationKey::GOLD_KEY = AnimationKey(ObjectKey::GOLD_KEY,1);
const AnimationKey AnimationKey::SNOW_FLAKE_KEY = AnimationKey(ObjectKey::SNOW_FLAKE_KEY,1);
const AnimationKey AnimationKey::FUEL_KEY = AnimationKey(ObjectKey::FUEL_KEY,1);

const AnimationKey AnimationKey::BOOM_CHARACTER_KEY = AnimationKey(ObjectKey::BOOM_CHARACTER_KEY,1);
const AnimationKey AnimationKey::BOOM_MINE_KEY = AnimationKey(ObjectKey::BOOM_MINE_KEY,1);
const AnimationKey AnimationKey::BOOM_TIME_BOMB_KEY = AnimationKey(ObjectKey::BOOM_TIME_BOMB_KEY,1);

const AnimationKey AnimationKey::NEXT_STAGE_DOOR_KEY = AnimationKey(ObjectKey::NEXT_STAGE_DOOR_KEY, 1);

const AnimationKey AnimationKey::HP_UP_KEY = AnimationKey(ObjectKey::HP_UP_KEY, 1);

AnimationKey& AnimationKey::operator = (const AnimationKey &t)
{
    type = t.type;
    id = t.id;
    level = t.level;
    index = t.index;
    return *this;
}

bool AnimationKey::operator == (const AnimationKey &t) const
{
    return (type == t.type && id == t.id && level == t.level);
}

bool AnimationKey::operator != (const AnimationKey &t) const
{
    return (type != t.type || id != t.id || level != t.level);
}
