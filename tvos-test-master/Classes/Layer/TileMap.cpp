//
//  TileMap.cpp
//  bomberman
//
//  Created by Phi Dzung on 3/5/15.
//
//

#include "TileMap.h"
#include "GameConfig.h"
#include "AvatarConfig.h"
#include <Diamond.h>
#include <MainGameScene.h>
#include <Stone.h>
#include <BomSpikes.h>
#include <BumBum.h>
#include <BomDrop.h>
#include <BomTime.h>
#include <CarShipper.h>
#include <Hammer.h>
#include <Tanker.h>
#include <Tracker.h>
#include <Roller.h>
#include <BoxGold.h>
#include <BaseItem.h>

USING_NS_CC;

TileMap::TileMap(int land, int level)
: _weight(0)
{
    std::string str = StringUtils::format("res/Maps/Land%d/map_%d_en.tmx", land, level);
    _tileMap = TMXTiledMap::create(str);
    _layerBackground = _tileMap->getLayer("BackGround");
    _tileSize = _tileMap->getTileSize();
    _tileMapSizeMatrix = _tileMap->getMapSize();
    _tileMapSize = Size(_tileMap->getMapSize().width * _tileSize.width,
                        _tileMap->getMapSize().height * _tileSize.height);
    
    //get Postion player
    TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("RobotCharacter");
    auto player = objectGroup->getObject("Player");
    int x = player["x"].asInt();
    int y = player["y"].asInt();
    
    auto posMatrix = ConvertUtils::convertCDMaptoMatrix(Vec2(x,y), _tileSize, _tileMapSizeMatrix);
    _posPlayer = ConvertUtils::convertCDMatrixtoMap(posMatrix, _tileSize, _tileMapSizeMatrix);
    
    _totalScoreFull = 0;
    _totalScoreFull += (int)SCORE::BONUS_FUEL * 100;
    _totalScoreFull += (int)SCORE::BONUS_LIVES * 3;
    
    //add Background
    CImageView* imgV = CImageView::create(StringUtils::format("GUI/PlayGame/background_land_%d.png",land).c_str());
    imgV->setAnchorPoint(Vec2::ZERO);
    imgV->setPosition(Vec2(0, _tileMapSize.height - _tileSize.height - 12));
    MainGameScene::getInstance()->getLayerContainer()->gameLayer()->addChild(imgV,100);
    if(_tileMapSize.width > 1136){
        //add Background 1
        CImageView* imgV1 = CImageView::create(StringUtils::format("GUI/PlayGame/background_land_%d.png",land).c_str());
        imgV1->setAnchorPoint(Vec2::ZERO);
        imgV1->setPosition(Vec2(1136, _tileMapSize.height - _tileSize.height - 12));
        MainGameScene::getInstance()->getLayerContainer()->gameLayer()->addChild(imgV1,100);
    }
    
    _tileMapSize.height = _tileMapSize.height + _tileSize.height * 2;
    
}

TileMap::~TileMap()
{
    _tileMap = NULL;
    _layerBackground = NULL;
}

void TileMap::addItem()
{
    for (int i = 0; i < _tileMapSizeMatrix.width; i++)
    {
        for (int j = 0; j < _tileMapSizeMatrix.height; j++)
        {
            switch ((IDTILE)this->getIdTile(Vec2(i,j)))
            {
                case IDTILE::WALL_HARD:
                    _weight += WEIGHT_WALL_HARD;
                    break;
                case IDTILE::WALL_SOFT:
                    _weight += WEIGHT_WALL_SOFT;
                    break;
                case IDTILE::DIAMOND:
                {
                    int level = j%3 + 1;
                    auto diamond = Diamond::createWithLevel(level);
                    diamond->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::DIAMOND_KEY.index].pushBack(diamond);
                    data.diamonds++;
                    if (level == 1)
                    {
                        _totalScoreFull += (int)SCORE::DIAMOND_1;
                    }
                    else if (level == 2)
                    {
                        _totalScoreFull += (int)SCORE::DIAMOND_2;
                    }
                    else
                    {
                        _totalScoreFull += (int)SCORE::DIAMOND_3;
                    }
                    
                    _totalScoreFull += (int)SCORE::BONUS_DIAMOND;
                }
                    break;
                case IDTILE::GRASS_DIAMOND:
                {
                    _totalScoreFull += (int)SCORE::GRASS_DIAMOND;
                }
                    break;
                case IDTILE::STONE:
                {
                    _weight += WEIGHT_STONE;
                    auto stone = Stone::create();
                    stone->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::STONE_KEY.index].pushBack(stone);
                }
                    break;
                case IDTILE::BOMB_SPIKES:
                {
                    _weight += WEIGHT_MINE;
                    auto spikes = BomSpikes::create();
                    spikes->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOMB_SPIKE_KEY.index].pushBack(spikes);
                }
                    break;
                case IDTILE::BOMB_DROP:
                {
                    _weight += WEIGHT_BOMB;
                    auto drop = BomDrop::create();
                    drop->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOMB_DROP_KEY.index].pushBack(drop);
                }
                    break;
                case IDTILE::BOMB_TIME:
                {
                    auto time = BomTime::create();
                    time->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOMB_TIME_KEY.index].pushBack(time);
                }
                    break;
                case IDTILE::BOX_GOLD:
                {
                    _weight += WEIGHT_BOX_GOLD;
                    auto gold = BoxGold::create();
                    gold->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOX_GOLD_KEY.index].pushBack(gold);
                    _totalScoreFull += (int)SCORE::BOX_GOLD;
                }
                    break;
                case IDTILE::BOX_BOMB_DROP:
                {
                    _weight += WEIGHT_BOX_BOMB;
                    auto boxBomb = BaseItem::createWithKey(ObjectKey::BOX_BOMB_DROP_KEY, (int)IDTILE::BOX_BOMB_DROP);
                    boxBomb->setCleanEffect();
                    boxBomb->setOnAnimationFinishCallback([boxBomb](int animId)
                                                          {
                                                              if (animId == 1)
                                                              {
                                                                  boxBomb->cleanByEffect();
                                                              }
                                                          });
                    boxBomb->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOX_BOMB_DROP_KEY.index].pushBack(boxBomb);
                    _totalScoreFull += (int)SCORE::BONUS_BOMB*3;
                }
                    break;
                case IDTILE::BOX_BOMB_FIRE:
                {
                    _weight += WEIGHT_BOX_BOMB;
                    auto boxBomb = BaseItem::createWithKey(ObjectKey::BOX_BOMB_FIRE_KEY, (int)IDTILE::BOX_BOMB_FIRE);
                    boxBomb->setCleanEffect();
                    boxBomb->setOnAnimationFinishCallback([boxBomb](int animId)
                                                          {
                                                              if (animId == 1)
                                                              {
                                                                  boxBomb->cleanByEffect();
                                                              }
                                                          });
                    boxBomb->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOX_BOMB_FIRE_KEY.index].pushBack(boxBomb);
                    _totalScoreFull += (int)SCORE::BONUS_BOMB*3;
                }
                    break;
                case IDTILE::BOX_BOMB_TIME:
                {
                    _weight += WEIGHT_BOX_BOMB;
                    auto boxBomb = BaseItem::createWithKey(ObjectKey::BOX_BOMB_TIME_KEY, (int)IDTILE::BOX_BOMB_TIME);
                    boxBomb->setCleanEffect();
                    boxBomb->setOnAnimationFinishCallback([boxBomb](int animId)
                                                          {
                                                              if (animId == 1)
                                                              {
                                                                  boxBomb->cleanByEffect();
                                                              }
                                                          });
                    boxBomb->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOX_BOMB_TIME_KEY.index].pushBack(boxBomb);
                    _totalScoreFull += (int)SCORE::BONUS_BOMB*3;
                }
                    break;
                case IDTILE::BOX_BOMB_SPIKE:
                {
                    _weight += WEIGHT_BOX_BOMB;
                    auto boxBomb = BaseItem::createWithKey(ObjectKey::BOX_BOMB_SPIKE_KEY, (int)IDTILE::BOX_BOMB_SPIKE);
                    boxBomb->setCleanEffect();
                    boxBomb->setOnAnimationFinishCallback([boxBomb](int animId)
                                                       {
                                                           if (animId == 1)
                                                           {
                                                               boxBomb->cleanByEffect();
                                                           }
                                                       });
                    boxBomb->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::BOX_BOMB_SPIKE_KEY.index].pushBack(boxBomb);
                    _totalScoreFull += (int)SCORE::BONUS_BOMB*3;
                }
                    break;
                case IDTILE::SNOW_FLAKE:
                {
                    _weight += WEIGHT_SNOW;
                    auto snow = BaseItem::createWithKey(ObjectKey::SNOW_FLAKE_KEY, (int)IDTILE::SNOW_FLAKE);
                    snow->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::SNOW_FLAKE_KEY.index].pushBack(snow);
                }
                    break;
                case IDTILE::FUEL:
                {
                    auto fuel = BaseItem::createWithKey(ObjectKey::FUEL_KEY, (int)IDTILE::FUEL);
                    fuel->setCleanEffect();
                    fuel->setOnAnimationFinishCallback([fuel](int animId)
                    {
                        if (animId == 1)
                        {
                            fuel->cleanByEffect();
                        }
                    });
                    fuel->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::FUEL_KEY.index].pushBack(fuel);
                    _totalScoreFull += (int)SCORE::FUEL;
                }
                    break;
                case IDTILE::HP_UP:
                {
                    auto hp = BaseItem::createWithKey(ObjectKey::HP_UP_KEY, (int)IDTILE::HP_UP);
                    hp->setPosition(ConvertUtils::convertCDMatrixtoMap(Vec2(i,j), _tileSize, _tileMapSizeMatrix));
                    MainGameScene::getInstance()->getObjectPool()[ObjectKey::HP_UP_KEY.index].pushBack(hp);
//                    _totalScoreFull += (int)SCORE::BONUS_LIVES;
                }
                    break;
            }
        }
    }
}

void TileMap::addObject()
{
    TMXObjectGroup *objectGroup1 = _tileMap->getObjectGroup("EnemyCharacter");
    auto enemyArr = objectGroup1->getObjects();
    
    ValueVector::const_iterator i;
    for (i = enemyArr.begin(); i< enemyArr.end(); i++)
    {
        std::string  str_name = (*i).asValueMap().at("name").asString();
        
        int x = (*i).asValueMap().at("x").asInt();
        int y = (*i).asValueMap().at("y").asInt();
        _weight += WEIGHT_CHARACTER_ON_MAP;
        if(str_name.compare("Shipper") == 0)
        {
            auto car = CarShipper::create();
            car->setShader();
            auto posMatrix = ConvertUtils::convertCDMaptoMatrix(Vec2(x,y), _tileSize, _tileMapSizeMatrix);
            car->setPosition(ConvertUtils::convertCDMatrixtoMap(posMatrix, _tileSize, _tileMapSizeMatrix));
            car->loadToMap();
            car->initDir();
            car->setRotate();
            MainGameScene::getInstance()->getObjectPool()[ObjectKey::SHIPPER_KEY.index].pushBack(car);
            _totalScoreFull += (int)SCORE::SHIPPER;
            _totalScoreFull += (int)SCORE::BONUS_ENEMIES;
        }
        
        if(str_name.compare("Hammer") == 0)
        {
            auto car = Hammer::create();
            car->setShader();
            auto posMatrix = ConvertUtils::convertCDMaptoMatrix(Vec2(x,y), _tileSize, _tileMapSizeMatrix);
            car->setPosition(ConvertUtils::convertCDMatrixtoMap(posMatrix, _tileSize, _tileMapSizeMatrix));
            car->loadToMap();
            MainGameScene::getInstance()->getObjectPool()[ObjectKey::HAMMER_KEY.index].pushBack(car);
            _totalScoreFull += (int)SCORE::HAMMER;
            _totalScoreFull += (int)SCORE::BONUS_ENEMIES;
        }
        
        if(str_name.compare("Tanker") == 0)
        {
            auto car = Tanker::create();
            car->setShader();
            auto posMatrix = ConvertUtils::convertCDMaptoMatrix(Vec2(x,y), _tileSize, _tileMapSizeMatrix);
            car->setPosition(ConvertUtils::convertCDMatrixtoMap(posMatrix, _tileSize, _tileMapSizeMatrix));
            car->loadToMap();
            MainGameScene::getInstance()->getObjectPool()[ObjectKey::TANKER_KEY.index].pushBack(car);
            _totalScoreFull += (int)SCORE::TANKER;
            _totalScoreFull += (int)SCORE::BONUS_ENEMIES;
        }
        
        if(str_name.compare("Tracker") == 0)
        {
            auto car = Tracker::create();
            car->setShader();
            auto posMatrix = ConvertUtils::convertCDMaptoMatrix(Vec2(x,y), _tileSize, _tileMapSizeMatrix);
            car->setPosition(ConvertUtils::convertCDMatrixtoMap(posMatrix, _tileSize, _tileMapSizeMatrix));
            car->loadToMap();
            MainGameScene::getInstance()->getObjectPool()[ObjectKey::TRACKER_KEY.index].pushBack(car);
            _totalScoreFull += (int)SCORE::TRACKER;
            _totalScoreFull += (int)SCORE::BONUS_ENEMIES;
        }
        
        if(str_name.compare("Roller") == 0)
        {
            auto car = Roller::create();
            car->setShader();
            auto posMatrix = ConvertUtils::convertCDMaptoMatrix(Vec2(x,y), _tileSize, _tileMapSizeMatrix);
            car->setPosition(ConvertUtils::convertCDMatrixtoMap(posMatrix, _tileSize, _tileMapSizeMatrix));
            car->loadToMap();
            MainGameScene::getInstance()->getObjectPool()[ObjectKey::ROLLER_KEY.index].pushBack(car);
            _totalScoreFull += (int)SCORE::ROLLER;
            _totalScoreFull += (int)SCORE::BONUS_ENEMIES;
        }
    }
}

void TileMap::removeTileInMap(cocos2d::Vec2 pos)
{
    if(pos.x >= 0 && pos.y >= 0 && pos.x < _tileMapSizeMatrix.width && pos.y < _tileMapSizeMatrix.height){
        _layerBackground->removeTileAt(pos);
    }
}
bool TileMap::checkPathPlayer(cocos2d::Vec2 pos)
{
    auto tile = (IDTILE)_layerBackground->getTileGIDAt(pos);
    if(tile == IDTILE::DEFAULT || tile == IDTILE::GRASS)
        return true;
    return false;
}
int TileMap::getIdTile(cocos2d::Vec2 pos){
//    CCLOG("%f  %f",pos.x, pos.y);
    if(pos.x >= 0 && pos.y >= 0 && pos.x < _tileMapSizeMatrix.width && pos.y < _tileMapSizeMatrix.height)
    {
        return _layerBackground->getTileGIDAt(pos);
    }
    return -1;
}
void TileMap::setIdTile(cocos2d::Vec2 pos, int id)
{
    _layerBackground->setTileGID(id, pos);
}
