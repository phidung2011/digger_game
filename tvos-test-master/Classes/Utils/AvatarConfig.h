//
//  AvatarConfig.h
//  gamebase
//
//  Created by Phi Dzung on 5/20/15.
//
//

#ifndef gamebase_AvatarConfig_h
#define gamebase_AvatarConfig_h
//Định nghĩa cho robotcharacter(Nhân vật chính)
//Có 2 trạng thái là di chuyển (1 frame), và di chuyển (4 frame)
//Có 2 hướng di chuyển chính là trên(dưới) và trái(phải)
#define LIMIT_WIDTH  0.4// Pham vi gioi han di chuyen cho nhan vat tren man hinh device
#define LIMIT_HEIGHT  0.35// Pham vi gioi han di chuyen cho nhan vat tren man hinh device
#define TILE_SIZE 59// size tile trong tileMap(32 px)
//#include "AnimationKey.h"

enum class IDTILE
{
    DIAMOND = 5,
    DEFAULT = 0,
    SAND = 2,
    GRASS = 1,
    WALL_HARD = 3,
    WATER = 4,
    STONE = 6,
    BOMB_TIME = 7,
    BOMB_SPIKES = 8,
    BOMB_DROP = 9,
    BOOM_BOMB = 10,
    GRASS_DIAMOND = 11,
    WALL_SOFT = 12,
    BOX_GOLD = 13,
    FUEL = 14,
    BOX_BOMB_DROP = 15,
    BOX_BOMB_FIRE = 16,
    BOX_BOMB_TIME = 17,
    BOX_BOMB_SPIKE = 18,
    HP_UP = 19,
    SNOW_FLAKE = 22,
    GOLD = 23,
    NEXT_STAGE_DOOR = 31,
    CHARACTER = 32,
    PLAYER = 33,
    MARKED_PLAYER = 36,
    MARKED_CHARACTER = 35,
    MARKED_ITEM = 34,
};

typedef enum class LAND
{
    PLAIN = 1,
    VOLCANO = 2,
    DESERT = 3,
    GRASS_LAND = 4,
    SNOW_MOUTAIN = 5,
}LAND;

enum class IDCHAR
{
    PLAYER = 1,
    TRACKER = 2,
    HAMMER = 3,
    ROLLER = 4,
    SHIPPER = 5,
    TANKER = 6
};

enum class IDITEM
{
    DIAMOND = 1,
    STONE = 2,
    GOLD = 3,
    BOX_GOLD = 4,
    BOMB_FIRE = 5,
    BOMB_DROP = 6,
    BOMB_TIME = 7,
    BOMB_SPIKE = 8,
    BOOM_BOMB = 9,
    BOX_BOMB_DROP = 10,
    BOX_BOMB_FIRE = 11,
    BOX_BOMB_TIME = 12,
    BOX_BOMB_SPIKE = 13,
    HP_UP = 14,
    FUEL = 15,
    SNOW_FLAKE = 16,
    BOOM_CHARACTER = 17,
    BOOM_TIME_BOMB = 18,
    BOOM_MINE = 19,
    BOX_WOOD = 20,
    NEXT_STAGE_DOOR = 21,
};

enum class SCORE{
    DIAMOND_1 = 45,
    DIAMOND_2 = 50,
    DIAMOND_3 = 55,
    GRASS_DIAMOND = 10,
    TRACKER = 200,
    HAMMER = 155,
    ROLLER = 145,
    SHIPPER = 140,
    TANKER = 180,
    BOX_GOLD = 100,
    FUEL = 75,
    
    BONUS_ENEMIES = 30,
    BONUS_DIAMOND = 10,
    BONUS_TIME = 3,
    BONUS_FUEL = 1,
    BONUS_LIVES = 700,
    BONUS_BOMB = 30,
};


#endif
