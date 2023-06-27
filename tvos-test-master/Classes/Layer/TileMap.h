//
//  TileMap.h
//  bomberman
//
//  Created by Phi Dzung on 3/5/15.
//
//

#ifndef __bomberman__TileMap__
#define __bomberman__TileMap__

#include "cocos2d.h"
#include "DataManager.h"
#include "ObjectKey.h"
//#include "AvatarConfig.h"

#define WEIGHT_STONE 3
#define WEIGHT_MAP_SIZE 3
#define WEIGHT_WALL_HARD 4
#define WEIGHT_MINE 10
#define WEIGHT_BOMB -6
#define WEIGHT_WALL_SOFT 3
#define WEIGHT_BOX_GOLD 1
#define WEIGHT_BOX_BOMB -10
#define WEIGHT_SNOW -10
#define WEIGHT_CHARACTER_ON_MAP 25
#define WEIGHT_CHARACTER_TO_KILL 50
#define WEIGHT_DIAMOND_TO_COLLECT 20

class TileMap
{
public:
    TileMap(int land, int level);
    ~TileMap();
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _layerBackground;
    cocos2d::Size _tileSize;
    cocos2d::Size _tileMapSize;
    cocos2d::Size _tileMapSizeMatrix;
    cocos2d::Vec2 _posPlayer;
    
    void removeTileInMap(cocos2d::Vec2 pos);
    bool checkPathPlayer(cocos2d::Vec2 pos);
    int getIdTile(cocos2d::Vec2 pos);
    void setIdTile(cocos2d::Vec2 pos, int id);
    
    CC_SYNTHESIZE(int, _weight, Weight);
    CC_SYNTHESIZE(int, _hardTimePlay, HardTimePlay);
    CC_SYNTHESIZE(int, _normalTime, NormalTimePlay);
    CC_SYNTHESIZE(int, _easyTimePlay, EasyTimePlay);
    CC_SYNTHESIZE(int, _totalScoreFull, TotalScoreFull);
    
    MapData data;
    void addItem();
    void addObject();
    
private:

protected:
};
#endif /* defined(__bomberman__TileMap__) */
