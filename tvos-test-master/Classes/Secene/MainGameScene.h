//
//  MainGameScene.h
//  gamebase
//
//  Created by Phi Dzung on 4/14/15.
//
//

#ifndef __gamebase__MainGameScene__
#define __gamebase__MainGameScene__

#include "TileMap.h"
#include "Player.h"
#include "SceneDisplay.h"
#include "MenuBar.h"
#include "SkillLayer.h"
#include "ControlStick.h"

enum class LAND;


class MainGameScene : public SceneDisplay
{
public:
    MainGameScene();
    ~MainGameScene();
    
    static MainGameScene * getInstance(){return _instance;};
    
    static MainGameScene* create(LAND land, int level, MapData bonusPackage);
    static MainGameScene* create();
    
    void update(float f) override;
    void addObject(DataObject *dt, int zOrder = 0);
//    void addEffect(DataObject *dt, int zOrder = 0);
    
    void setGameOver();
    void setGameWin();
    void pauseGame();
    void resumeGame();
    void shake();
    void openTheDoor();
    void effectUpdate();
    
    cocos2d::Vector<DataObject*>* getObjectPool(){return _objectPool;};
    cocos2d::Vector<DataObject*>& getReleasePool(){return _releasePool;};
    cocos2d::Vector<DataObject*>& getEffectPool(){return _effectPool;};
    
//    DataObject* getObjectAt(cocos2d::Vec2 pos);
    bool GAME_DONE;
    
    bool CLEAR_STAGE;
    bool SHOW_NEXT_STAGE_DOOR;
    bool GAME_OVER;
    
    MapData& getBonusPackage(){return _bonusPackage;};
    
private:
    static MainGameScene* _instance;

protected:
    void setViewPoint(cocos2d::Vec2 playerPos);
    
    //base loop has 4 updates below
    void inputUpdate();
    void worldUpdate();
    void cleanUp();
    
    bool _isShaking;
    cocos2d::Sprite* _mapBackground;

    MapData _bonusPackage;
    CC_SYNTHESIZE(LAND, _land, Land);
    
    
    
    cocos2d::Vector<DataObject*>* _objectPool;
    cocos2d::Vector<DataObject*> _effectPool;
    cocos2d::Vector<DataObject*> _releasePool;
    
    void createPlayer();
    void createTileMap();
    void createObject();
    void createKey();
    
    void updateUIEffect();
    bool isFading;
    void setBackgroundPosition();
    
    bool init(LAND land, int level, MapData bonusPackage);
    
    CC_SYNTHESIZE(MenuBar*, _menuBar, MenuBar);
    CC_SYNTHESIZE(TileMap*, _tileMap, TileMap);
    CC_SYNTHESIZE(Player*, _player, Player);
    CC_SYNTHESIZE(unsigned int, _currentMainLoop, CurrentMainLoop);
    CC_SYNTHESIZE(int, _levelMap, LevelMap);
    CC_SYNTHESIZE(SkillLayer*, _skillLayer, SkillLayer);
    CC_SYNTHESIZE(ControlStick*, _control, Control);
    
};


#endif /* defined(__gamebase__MainGameScene__) */
