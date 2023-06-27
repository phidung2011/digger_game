//
//  DataManager.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 4/14/15.
//
//

#ifndef __menhera__DataManager__
#define __menhera__DataManager__

#include "cocos2d.h"
#define DATA_MGR DataManager::getInstance()

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

class MapData
{
public:
    MapData()
    : bombs(0)
    , time_bombs(0)
    , rockets(0)
    , mines(0)
    , diamonds(0)
    , fuel(0)
    , enemies(0)
    , time(0)
    {};
    
    MapData(int diamond, int fu, int enemy, int time_play, int bomb, int time_bomb, int rocket, int mine)
    : diamonds(diamond)
    , fuel(fu)
    , enemies(enemy)
    , time(time_play)
    , bombs(bomb)
    , time_bombs(time_bomb)
    , rockets(rocket)
    , mines(mine)
    {};
    
    int diamonds;
    float fuel;
    int enemies;
    int time;
    
    int bombs;
    int time_bombs;
    int rockets;
    int mines;
    
    
    MapData& operator = (const MapData &other)
    {
        diamonds = other.diamonds;
        fuel = other.fuel;
        enemies = other.enemies;
        time = other.time;
        bombs = other.bombs;
        time_bombs = other.time_bombs;
        rockets = other.rockets;
        mines = other.mines;
        return *this;
    };
    
    MapData operator + (const MapData& other) const
    {
        return MapData(this->diamonds + other.diamonds,
                       this->fuel + other.fuel,
                       this->enemies + other.enemies,
                       this->time + other.time,
                       this->bombs + other.bombs,
                       this->time_bombs + other.time_bombs,
                       this->rockets + other.rockets,
                       this->mines + other.mines);
    }
    
    MapData operator - (const MapData& other) const
    {
        return MapData(this->diamonds - other.diamonds,
                       this->fuel - other.fuel,
                       this->enemies - other.enemies,
                       this->time - other.time,
                       this->bombs - other.bombs,
                       this->time_bombs - other.time_bombs,
                       this->rockets - other.rockets,
                       this->mines - other.mines);
    }
    
    
};


class Inventory
{
public:
    Inventory()
    : bombs(0)
    , mines(0)
    , time_bombs(0)
    , rockets(0)
    , coins(0)
    , snow_flakes(0)
    , switch_bombs(0)
    {
    };
    
    Inventory(int bomb, int mine, int time_bomb, int rocket, int coin, int snow_flake, int switch_bomb)
    : bombs(bomb)
    , mines(mine)
    , time_bombs(time_bomb)
    , rockets(rocket)
    , coins(coin)
    , snow_flakes(snow_flake)
    , switch_bombs(switch_bomb)
    {
    };
    
    int bombs;
    int mines;
    int time_bombs;
    int switch_bombs;
    int rockets;
    int coins;
    int snow_flakes;
    
    void setValue(int bomb, int mine, int time_bomb, int rocket, int coin, int snow_flake, int switch_bomb)
    {
        bombs = bomb;
        mines = mine;
        time_bombs = time_bomb;
        rockets = rocket;
        coins = coin;
        snow_flakes = snow_flake;
        switch_bombs = switch_bomb;
    };
    
    Inventory& operator = (const Inventory& other)
    {
        this->setValue(other.bombs, other.mines, other.time_bombs, other.rockets, other.coins, other.snow_flakes, other.switch_bombs);
        return *this;
    };
    
    Inventory operator + (const Inventory& other) const
    {
        return Inventory(this->bombs + other.bombs,
                         this->mines + other.mines,
                         this->time_bombs + other.time_bombs,
                         this->rockets + other.rockets,
                         this->coins + other.coins,
                         this->snow_flakes + other.snow_flakes,
                         this->switch_bombs + other.switch_bombs);
    }
    
    Inventory operator - (const Inventory& other) const
    {
        return Inventory(this->bombs - other.bombs,
                         this->mines - other.mines,
                         this->time_bombs - other.time_bombs,
                         this->rockets - other.rockets,
                         this->coins - other.coins,
                         this->snow_flakes - other.snow_flakes,
                         this->switch_bombs - other.switch_bombs);
    }
    
    
    
};

class DataManager
{
public:
    DataManager();
    ~DataManager();
    static DataManager* getInstance();
    
    bool writeToJsonFile(std::string filePath, rapidjson::Document& document);
    
    Inventory getInventory();
    MapData getMapDataAtLevel(int land, int level);
    std::vector<cocos2d::Vec2> getPositionAtLevel(int land);
    
    void saveGameSetting();
    
    rapidjson::Document& getGameSettingDocument(){return _gameSettingDoc;};
    rapidjson::Document& getPositionLevelDocument(){return _positionLevelDoc;};
    rapidjson::Document& getMapDataDocument(){return _mapDataDoc;};
    rapidjson::Document& getLevelsClearedDocument(){return _levelsClearedDoc;};
    rapidjson::Document& getGameInfoDocument(){return _levelsClearedDoc;};
    rapidjson::Document& getInventoryDocument(){return _inventory;};
    rapidjson::Document& getAchievementDocument(){return _achievement;};

    rapidjson::Document _mapDataDoc;
    rapidjson::Document _positionLevelDoc;
    rapidjson::Document _gameSettingDoc;
    rapidjson::Document _dataStar;
    rapidjson::Document _levelsClearedDoc;
    rapidjson::Document _gameInfo;
    rapidjson::Document _inventory;
    rapidjson::Document _achievement;
    
    int _totalStar;
    
    rapidjson::Document loadMapData(int land);
    rapidjson::Document loadLevelPositionData(int land);
    void loadGameSetting();
    void loadLevelsCleared();
    void loadGameInfo();
    void loadInventory();
    void loadAchievement();
    
    
    void loadStar();
    void updateStar(int land, int level, int star);
    int getStar(int land, int level);
    static DataManager* _instance;
};

#endif /* defined(__menhera__DataManager__) */
