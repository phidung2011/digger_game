//
//  AnimationKey.h
//  gamebase
//
//  Created by Phi Dzung on 9/23/15.
//
//

#ifndef __gamebase__AnimationKey__
#define __gamebase__AnimationKey__


//#include "stdio.h"
#include "ObjectKey.h"

class AnimationKey : public ObjectKey
{
public:
    int level;
public:
    AnimationKey();
    AnimationKey(const AnimationKey& t);
    AnimationKey(const std::string &t, int i, unsigned int idx, int l);
    AnimationKey(const TypeKey& t, int i, unsigned int idx, int l);
    AnimationKey(const ObjectKey& o, int l);
    
    AnimationKey& operator = (const AnimationKey &t);
    
    bool operator == (const AnimationKey &t) const;
    
    bool operator != (const AnimationKey &t) const;
    
    static const AnimationKey PLAYER_KEY;
    static const AnimationKey HAMMER_KEY;
    static const AnimationKey SHIPPER_KEY;
    static const AnimationKey TANKER_KEY;
    static const AnimationKey TRACKER_KEY;
    static const AnimationKey ROLLER_KEY;
    
    static const AnimationKey BOMB_DROP_KEY;
    static const AnimationKey BOMB_FIRE_KEY;
    static const AnimationKey BOMB_SPIKE_KEY;
    static const AnimationKey BOMB_TIME_KEY;
    static const AnimationKey BOOM_BOMB_KEY;
    static const AnimationKey DIAMOND1_KEY;
    static const AnimationKey DIAMOND2_KEY;
    static const AnimationKey DIAMOND3_KEY;
    
    static const AnimationKey STONE_KEY;
    static const AnimationKey BOX_GOLD_KEY;
    static const AnimationKey BOX_BOMB_DROP_KEY;
    static const AnimationKey BOX_BOMB_FIRE_KEY;
    static const AnimationKey BOX_BOMB_SPIKE_KEY;
    static const AnimationKey BOX_BOMB_TIME_KEY;
    static const AnimationKey GOLD_KEY;
    static const AnimationKey SNOW_FLAKE_KEY;
    static const AnimationKey FUEL_KEY;
    
    static const AnimationKey BOOM_CHARACTER_KEY;
    static const AnimationKey BOOM_MINE_KEY;
    static const AnimationKey BOOM_TIME_BOMB_KEY;
    
    static const AnimationKey NEXT_STAGE_DOOR_KEY;
    static const AnimationKey HP_UP_KEY;
};

namespace std {
    
    template <>
    struct hash<AnimationKey>
    {
        std::size_t operator()(const AnimationKey& k) const
        {
            using std::size_t;
            using std::hash;
            using std::string;
            
            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:
            
            return ((hash<string>()(k.type) ^
                     (hash<int>()(k.id) << 1)) >> 1)
            ^ (hash<int>()(k.level) << 1);
        }
    };
    
}

#endif /* defined(__gamebase__AnimationKey__) */
