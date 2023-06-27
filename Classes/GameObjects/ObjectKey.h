//
//  ObjectKey.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 7/17/15.
//
//

#ifndef __gamebase__ObjectKey__
#define __gamebase__ObjectKey__

#include "TypeKey.h"

class ObjectKey : public TypeKey
{
public:
    ObjectKey();
    ObjectKey(const ObjectKey& t);
    ObjectKey(const std::string &t, int i, unsigned int idx);
    ObjectKey(const TypeKey &t, int i, unsigned int idx);
    int id;
    unsigned int index;
    
    ObjectKey& operator = (const ObjectKey&t);
    
    ObjectKey& operator = (const AnimationKey&t);
    
    bool operator == (const ObjectKey &t) const;
    
    bool operator != (const ObjectKey &t) const;
    
    
    static const ObjectKey PLAYER_KEY;
    static const ObjectKey HAMMER_KEY;
    static const ObjectKey SHIPPER_KEY;
    static const ObjectKey TANKER_KEY;
    static const ObjectKey TRACKER_KEY;
    static const ObjectKey ROLLER_KEY;
    
    static const ObjectKey BOMB_DROP_KEY;
    static const ObjectKey BOMB_FIRE_KEY;
    static const ObjectKey BOMB_SPIKE_KEY;
    static const ObjectKey BOMB_TIME_KEY;
    static const ObjectKey BOOM_BOMB_KEY;
    static const ObjectKey DIAMOND_KEY;
    
    static const ObjectKey STONE_KEY;
    static const ObjectKey BOX_GOLD_KEY;
    static const ObjectKey BOX_BOMB_DROP_KEY;
    static const ObjectKey BOX_BOMB_FIRE_KEY;
    static const ObjectKey BOX_BOMB_SPIKE_KEY;
    static const ObjectKey BOX_BOMB_TIME_KEY;
    static const ObjectKey GOLD_KEY;
    static const ObjectKey SNOW_FLAKE_KEY;
    static const ObjectKey FUEL_KEY;
    
    static const ObjectKey BOOM_CHARACTER_KEY;
    static const ObjectKey BOOM_MINE_KEY;
    static const ObjectKey BOOM_TIME_BOMB_KEY;
    
    static const ObjectKey NEXT_STAGE_DOOR_KEY;
    
    static const ObjectKey EFFECT_LAND_KEY;
    
    static const ObjectKey HP_UP_KEY;
};

namespace std {
    
    template <>
    struct hash<ObjectKey>
    {
        std::size_t operator()(const ObjectKey& k) const
        {
            using std::size_t;
            using std::hash;
            using std::string;
            
            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:
            
            return ((hash<string>()(k.type) ^
                     (hash<int>()(k.id) << 1)) >> 1);
        }
    };
    
}

#endif /* defined(__gamebase__ObjectKey__) */
