//
//  MainGameScene.cpp
//  gamebase
//
//  Created by Phi Dzung on 4/14/15.
//
//

#include "MainGameScene.h"
#include "StartGameScene.h"
#include "GameConfig.h"
#include "GameWin.h"
#include "MenuBar.h"
#include "AvatarConfig.h"
#include "PopupPause.h"
#include "Utils.h"
#include "PlayGameConstants.h"
#include "NativeUtils.h"
#include "ControlStick.h"
#include "CShake.h"
#include "BaseItem.h"
#include "PopupLevelFailed.h"
#include "LayerBuyItem.h"
#include "renderer/CCGLProgramStateCache.h"

//static int asd = 40;
MainGameScene* MainGameScene::_instance = NULL;

MainGameScene::~MainGameScene()
{
    
//    GLProgramCache::getInstance()->reloadDefaultGLPrograms();
    
    for (int i = 0; i < 25; i++)
    {
        if (!_objectPool[i].empty())
        {
            _objectPool[i].clear();
        }
    }
    delete [] _objectPool;
    
    
    _objectPool = nullptr;
    
    if (!_effectPool.empty())
    {
        _effectPool.clear();
    }
    
    if (!_releasePool.empty())
    {
        _releasePool.clear();
    }
    delete _tileMap;
    GLProgramStateCache::getInstance()->removeAllGLProgramState();
    Director::getInstance()->getTextureCache()->removeTextureForKey(StringUtils::format("Maps/Land%d/bg_land.jpg",(int)_land));
    CCLOG("%s",__PRETTY_FUNCTION__);
}

MainGameScene::MainGameScene()
: _isShaking(false)
, GAME_DONE(true)
, _currentMainLoop(0)
, isFading(false)
, CLEAR_STAGE(false)
, SHOW_NEXT_STAGE_DOOR(false)
, GAME_OVER(false)
{
    AnimationManager::getInstance();
    DATA_MGR;
    _instance = this;
//    asd++;
}

MainGameScene* MainGameScene::create(LAND land, int level, MapData bonusPackage)
{
    MainGameScene *pRet = new MainGameScene();
    if (pRet && pRet->init(land, level, bonusPackage))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
MainGameScene* MainGameScene::create()
{
    MapData data;
    MainGameScene *pRet = new MainGameScene();
    if (pRet && pRet->init(LAND::DESERT, 1, data))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool MainGameScene::init(LAND land, int level, MapData bonusPackage)
{
    if (!SceneDisplay::init())
    {
        return false;
    }

//	std::string st = NativeUtils::getDataString("dataInfo");
    
    _land = land;
    _levelMap = level;
    _bonusPackage = bonusPackage;
    
    this->insertLayer(POPUP_WIN_ID, GameWin::create());
    this->insertLayer(POPUP_PAUSE_ID, PopupPause::create());
    this->insertLayer(POPUP_LEVEL_FAILED_ID, PopupLevelFailed::create());
    this->insertLayer(LAYER_SHOP_ID, LayerBuyItem::create());
    
    
    
    //create map background
    _mapBackground = Sprite::create(StringUtils::format("Maps/Land%d/bg_land.jpg",(int)_land));
    _mapBackground->setAnchorPoint(Vec2(0,0));
    this->addChild(_mapBackground,-1);
    //-----------------
    
    
    
    //-----------------
    createKey();
    createTileMap();
    createPlayer();
    createObject();
    
    //tinh lai postion mapbackground
    
    Vec2 pos = getLayerContainer()->baseLayer()->getPosition();
    
//    _dtPos = Vec2(x + pos.x - (int)pos.x, y + pos.y - (int)pos.y);
    
//    _mapBackground->setPosition(_mapBackground->getPosition() + _dtPos);
    
    int dX = abs((int)(pos.x)) % TILE_SIZE;
    int dY = abs((int)(pos.y)) % TILE_SIZE;
    
    
    _mapBackground->setPosition(-Vec2(dX,dY));
    
    
//    for (int i = 0; i < ((int)_tileMap->_tileMapSize.width / 1136.0f) + 1; i++)
//    {
//        CImageView* imgV = CImageView::create(BG_PLAY_LAND_2);
//        imgV->setAnchorPoint(Vec2::ZERO);
//        imgV->setPosition(Vec2(i * 1136, _tileMap->_tileMapSize.height - TILE_SIZE - 12));
//        this->getLayerContainer()->gameLayer()->addChild(imgV,55);
//    }
    


    
    //Create Menu Bar
    _menuBar = MenuBar::create();
    this->getLayerContainer()->guiLayer()->addChild(_menuBar);
    
    _control = ControlStick::create();
    this->getLayerContainer()->guiLayer()->addChild(_control);
    
    //Create Layer Skill
    _skillLayer = SkillLayer::create();
    this->getLayerContainer()->guiLayer()->addChild(_skillLayer);
    
//    /// display for tester
//    CLabel* levelLabel = CLabel::createWithTTF(StringUtils::format("%d",level), FONT_PATH_PIXELERIS, FONT_SIZE);
//    levelLabel->setAnchorPoint(Vec2(1,0.5));
//    levelLabel->setTextColor(Color4B::BLUE);
//    levelLabel->setPosition(VisibleRect::rightBottom() + Vec2(-50,20));
//    this->getLayerContainer()->loadingLayer()->addChild(levelLabel);
//    
//    CLabel* oneStarLabel = CLabel::createWithTTF(StringUtils::format("1 sao: %d",_tileMap->getEasyTimePlay()), "Arial", 30);
//    oneStarLabel->setAnchorPoint(Vec2(1,0.5));
//    oneStarLabel->setTextColor(Color4B::BLACK);
//    oneStarLabel->setPosition(VisibleRect::rightBottom() + Vec2(-50,45));
//    this->getLayerContainer()->loadingLayer()->addChild(oneStarLabel);
//    
//    CLabel* twoStarLabel = CLabel::createWithTTF(StringUtils::format("2 sao: %d",_tileMap->getNormalTimePlay()), "Arial", 30);
//    twoStarLabel->setAnchorPoint(Vec2(1,0.5));
//    twoStarLabel->setTextColor(Color4B::BLACK);
//    twoStarLabel->setPosition(VisibleRect::rightBottom() + Vec2(-50,70));
//    this->getLayerContainer()->loadingLayer()->addChild(twoStarLabel);
//    
//    CLabel* threeStarLabel = CLabel::createWithTTF(StringUtils::format("3 sao: %d",_tileMap->getHardTimePlay()), "Arial", 30);
//    threeStarLabel->setAnchorPoint(Vec2(1,0.5));
//    threeStarLabel->setTextColor(Color4B::BLACK);
//    threeStarLabel->setPosition(VisibleRect::rightBottom() + Vec2(-50,95));
//    this->getLayerContainer()->loadingLayer()->addChild(threeStarLabel);
    
    
    _eventDispatcher->setEnabled(false);
    
    this->getControl()->getAnalog()->setEnabled(false);
    
    this->setOnEnterCallback([this]()
    {

        
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playBackgroundMusic(StringUtils::format(BGM_LAND, (int)_land).c_str(), true);
#else
        if (GameSingleton::getInstance()->BGM_AUDIO_ID != -1)
        {
            AUDIO::stop(GameSingleton::getInstance()->BGM_AUDIO_ID);
            GameSingleton::getInstance()->BGM_AUDIO_ID = -1;
        }
        
        GameSingleton::getInstance()->BGM_AUDIO_ID = AUDIO::play2d(StringUtils::format(BGM_LAND, (int)_land).c_str(), true, GameSingleton::getInstance()->MUSIC*0.01, nullptr);
        
#endif
        
        
        auto callTrans = CallFunc::create([this]
        {
            auto readyLabel = CLabel::createWithTTF("READY", FONT_PATH_GROBOLD, 50);
            readyLabel->setPosition(Vec2(-VisibleRect::center().x, VisibleRect::center().y));
            this->getLayerContainer()->loadingLayer()->addChild(readyLabel);
            
            readyLabel->enableOutline(Color4B(Color3B(53, 30, 95)),10);
            readyLabel->enableShadow();
            readyLabel->enableGlow(Color4B(Color3B(53, 30, 95)));
            
            auto call = CallFunc::create([this]
                                         {
                                             this->getControl()->getAnalog()->setEnabled(true);
                                             _eventDispatcher->setEnabled(true);
                                             GAME_DONE = false;
                                             _menuBar->resumeTime();
                                         });
#if (USE_SIMPLE_AUDIO_ENGINE)
            SIMPLE_AUDIO->playEffect(EFFECT_READY);
#else
            AUDIO::play2d(EFFECT_READY, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif

            readyLabel->runAction(Sequence::create(
                                                   MoveTo::create(0.3, VisibleRect::center()),
                                                   DelayTime::create(0.7),
                                                   EaseBackIn::create(MoveTo::create(0.7, VisibleRect::center() + VisibleRect::rightBottom())),
                                                   call,
                                                   NULL));

        });
        this->runAction(Sequence::create(FadeTo::create(0.1, 0),
                                                    callTrans,
                                                    NULL));
        
        
        
    });
    
    
    this->schedule(CC_SCHEDULE_SELECTOR(MainGameScene::update));

    GameSingleton::getInstance()->isPlaying = true;

    
    
   
    
    return true;
}


void MainGameScene::setBackgroundPosition()
{
    if (_mapBackground->getPositionX() <= -TILE_SIZE*2 + EX ||
        _mapBackground->getPositionX() >= -EX)
    {
        _mapBackground->setPositionX(-TILE_SIZE);
    }
    if (_mapBackground->getPositionY() <= -TILE_SIZE*2 +EX ||
        _mapBackground->getPositionY() >= -EX)
    {
        _mapBackground->setPositionY(-TILE_SIZE);
    }
}


void MainGameScene::update(float f)
{
    SceneDisplay::update(f);
    if (!GAME_DONE)
    {
//        if (_player->getActionPool().empty() && _currentMainLoop >= 17)
//        {
//            _player->executeControl(dt_right);
//        }
//        if (_currentMainLoop == 84)
//        {
////            CCLOG("-----------------%d",84);
//            this->getSkillLayer()->SkillBomDrop();
//            
//        }
//        if (_currentMainLoop == 120) {
//            this->unschedule(schedule_selector(MainGameScene::update));
//            this->schedule(CC_SCHEDULE_SELECTOR(MainGameScene::update),0.5);
//        }
        
        //input update
        this->inputUpdate();
        
        //world update logic
        this->worldUpdate();
        
        //update effect object
        this->effectUpdate();
        
        //clean up object
        this->cleanUp();
        
        //set view point camera
        if (_player->getDelta() != Vec2::ZERO)
        {
            this->setViewPoint(_player->getPosition());
            this->setBackgroundPosition();
            
            updateUIEffect();
        }
        
        
        if (SHOW_NEXT_STAGE_DOOR && !CLEAR_STAGE)
        {
            this->openTheDoor();
        }
        if (GameSingleton::getInstance()->_loopSound > 0)
        {
            GameSingleton::getInstance()->_loopSound--;
        }
        _currentMainLoop++;
    }
}


void MainGameScene::inputUpdate()
{
    if (!_player->isDead)
        _player->update(_currentMainLoop);
    for (int i = 0; i < 25; i++)
    {
//        for (auto obj : _objectPool[i]) {
//            if (obj)
//                obj->update(_currentMainLoop);
//        }
        
//        for (auto itr = _objectPool[i].begin(); itr != _objectPool[i].end(); ) {
//            if ((*itr)->update(_currentMainLoop)) {
//                itr = _objectPool[i].erase(itr);
//            }
//            else
//                itr++;
//        }

        
        for (int j = 0; j < _objectPool[i].size();)
        {
            auto obj = _objectPool[i].at(j);
            if (!obj->isValid())
            {
                if (obj->update(_currentMainLoop))
                {
                    _objectPool[i].erase(j);
                }
                else
                {
                    j++;
                }
            }
            else
                _objectPool[i].erase(j);
        }
    }
}

//game logic
void MainGameScene::worldUpdate()
{
    if (!_player->isDead)
        _player->worldUpdate();
    for (auto i = 0; i < 25; i++)
    {
//        for (auto itr = _objectPool[i].begin(); itr != _objectPool[i].end();) {
//            if ((*itr)->worldUpdate()) {
//                itr = _objectPool[i].erase(itr);
//            }
//            else
//                itr++;
//        }
        

        for (int j = 0; j < _objectPool[i].size();)
        {
            auto obj = _objectPool[i].at(j);
            if (!obj->isValid())
            {
                if (obj->worldUpdate())
                {
                    _objectPool[i].erase(j);
                }
                else
                {
                    j++;
                }
            }
            else
                _objectPool[i].erase(j);
        }
    }
}


void MainGameScene::pauseGame()
{
    GameSingleton::getInstance()->isPlaying = false;
    GAME_DONE = true;
    this->getMenuBar()->pauseTime();
    this->getControl()->getAnalog()->onTouchCancelled(nullptr, 0.0);
//    CCLOG("cached info----- %s", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}
void MainGameScene::resumeGame()
{
    GameSingleton::getInstance()->isPlaying = true;
    GAME_DONE = false;
    this->getMenuBar()->resumeTime();
}
void MainGameScene::setGameOver()
{
    if (!GAME_OVER) {
        auto call = CallFunc::create([this]
                                     {
                                         this->pauseGame();
                                         auto ref = Node::create();
                                         TransitionManager::getInstance()->addToSceneByCustomTransition(POPUP_LEVEL_FAILED_ID, ref);
                                     });
        this->runAction(Sequence::create(DelayTime::create(3),call,NULL));
        GAME_OVER = true;
        GameSingleton::getInstance()->isPlaying = false;
    }
}

void MainGameScene::openTheDoor()
{
    Vec2 p = Vec2::ZERO;
    int dir = _player->dirSkill;
    auto matrixPos = ConvertUtils::convertCDMaptoMatrix(_player->getBackPosition(), _tileMap->_tileSize, _tileMap->_tileMapSizeMatrix);
    int tileNext = -1;
    switch (dir)
    {
        case dt_right:
            p = matrixPos + Vec2(-1,0);
            tileNext = _tileMap->getIdTile(p);
            break;
        case dt_left:
            p = matrixPos + Vec2(1,0);
            tileNext = _tileMap->getIdTile(p);
            break;
        case dt_top:
            p = matrixPos + Vec2(0,1);
            tileNext = _tileMap->getIdTile(p);
            break;
        case dt_bot:
            p = matrixPos + Vec2(0,-1);
            tileNext = _tileMap->getIdTile(p);
            break;
    }
    if((IDTILE)tileNext == IDTILE::DEFAULT)
    {
        auto mapPos = ConvertUtils::convertCDMatrixtoMap(p, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
        auto door = BaseItem::createWithKey(ObjectKey::NEXT_STAGE_DOOR_KEY, (int)IDTILE::NEXT_STAGE_DOOR);
        door->setOnAnimationFinishCallback([door](int animId)
        {
            if (animId == 0)
            {
                door->playAnim(1);
            }
        });
        door->setPosition(mapPos);
        door->loadToMap();
        
#if (USE_SIMPLE_AUDIO_ENGINE)
        SIMPLE_AUDIO->playEffect(EFFECT_DOOR);
#else
        AUDIO::play2d(EFFECT_DOOR, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
        MainGameScene::getInstance()->addObject(door);
        MainGameScene::getInstance()->CLEAR_STAGE = true;
    }
    
}

void MainGameScene::setGameWin()
{
    GameSingleton::getInstance()->isPlaying = false;
    auto call = CallFunc::create([this]
                                 {
                                     this->pauseGame();
                                     _player->getBonusScore().time = _menuBar->getTime();
                                     _player->getBonusScore().fuel = _menuBar->getProgressBarFuel()->getValue();
                                     
                                     auto arr = __Array::create(__Integer::create(_player->getBonusScore().diamonds),
                                                              __Integer::create(_player->getBonusScore().enemies),
                                                              __Integer::create(_player->getBonusScore().time),
                                                              __Integer::create(_player->getBonusScore().fuel),
                                                              NULL);
                                     
                                     TransitionManager::getInstance()->addToSceneByCustomTransition(POPUP_WIN_ID, arr);
                                 });
    this->runAction(Sequence::create(DelayTime::create(0.3),call,NULL));

}

void MainGameScene::shake()
{
    if (!_isShaking)
    {
        auto shake = CShake::create(0.3f, 2);
        auto call = CallFunc::create([this]()
        {
            _isShaking = false;
        });
        auto seq = Sequence::create(shake,call, NULL);
        this->runAction(seq);
        _isShaking = true;
    }
}

void MainGameScene::createObject()
{
    for (auto i = 0; i < 25; i++)
    {
        for (auto&obj : _objectPool[i])
        {
            this->getLayerContainer()->gameLayer()->addChild(obj);
//            if(obj->getKey().type == "CHAR")
//            {
//                dynamic_cast<TiledObject*>(obj)->loadToMap();
//            }
        }
    }
}
void MainGameScene::addObject(DataObject *dt, int zOrder)
{
    this->getLayerContainer()->gameLayer()->addChild(dt,zOrder);
    _objectPool[dt->getKey().index].pushBack(dt);
}

//void MainGameScene::addEffect(DataObject *dt, int zOrder)
//{
//    this->getLayerContainer()->effectLayer()->addChild(dt,zOrder);
//    _objectPool.at(dt->getKey()).pushBack(dt);
//}
void MainGameScene::createTileMap()
{
    _tileMap = new TileMap((int)_land, _levelMap);
    this->getLayerContainer()->baseLayer()->addChild(_tileMap->_tileMap);
    
    _tileMap->addItem();
    _tileMap->addObject();
//    
//    auto data = DATA_MGR->getMapDataAtLevel(_levelMap);
//    
//    int newWeight = _tileMap->getWeight() + data.enemies*WEIGHT_CHARACTER_TO_KILL + data.diamonds*WEIGHT_DIAMOND_TO_COLLECT + _tileMap->_tileMapSizeMatrix.width*_tileMap->_tileMapSizeMatrix.height*WEIGHT_MAP_SIZE;
//    
//    
//    int twoStar = newWeight/25;
//    _tileMap->setWeight(newWeight);
//    _tileMap->setEasyTimePlay(twoStar*1.25f);
//    _tileMap->setHardTimePlay(twoStar*0.75f);
    
}

void MainGameScene::createPlayer()
{
    _player = Player::create();
    this->getLayerContainer()->gameLayer()->addChild(_player,1);
    _player->setPosition(_tileMap->_posPlayer);
    _tileMap->setIdTile(_player->getMatrixPos(), (int)IDTILE::PLAYER);
    
    this->getLayerContainer()->baseLayer()->setPosition(VisibleRect::center() - _player->getPosition());
    this->getLayerContainer()->gameLayer()->setPosition(VisibleRect::center() - _player->getPosition());
    this->getLayerContainer()->effectLayer()->setPosition(VisibleRect::center() - _player->getPosition());
    
    _tileMap->setNormalTimePlay(_player->getData().time);

    
    Size mapSize = this->getTileMap()->_tileMapSize;
    
    if (_tileMap->_posPlayer.x < winSize.width * 0.5)
    {
        this->getLayerContainer()->baseLayer()->setPositionX(0);
        this->getLayerContainer()->gameLayer()->setPositionX(0);
        this->getLayerContainer()->effectLayer()->setPositionX(0);
    }
    if (_tileMap->_posPlayer.y < winSize.height * 0.5)
    {
        this->getLayerContainer()->baseLayer()->setPositionY(0);
        this->getLayerContainer()->gameLayer()->setPositionY(0);
        this->getLayerContainer()->effectLayer()->setPositionY(0);
    }
    if (_tileMap->_posPlayer.x > mapSize.width - winSize.width * 0.5)
    {
        this->getLayerContainer()->baseLayer()->setPositionX(winSize.width - mapSize.width);
        this->getLayerContainer()->gameLayer()->setPositionX(winSize.width - mapSize.width);
        this->getLayerContainer()->effectLayer()->setPositionX(winSize.width - mapSize.width);
    }
    if (_tileMap->_posPlayer.y > mapSize.height - winSize.height * 0.5)
    {
        this->getLayerContainer()->baseLayer()->setPositionY(winSize.height - mapSize.height);
        this->getLayerContainer()->gameLayer()->setPositionY(winSize.height - mapSize.height);
        this->getLayerContainer()->effectLayer()->setPositionY(winSize.height - mapSize.height);
    }
}

void MainGameScene::setViewPoint(cocos2d::Vec2 playerPos)
{
    Vec2 devicePos = ConvertUtils::convertMapToDevice(playerPos, this->getLayerContainer()->baseLayer()->getPosition()); // toạ độ của player trên device
    
    Size mapSize = this->getTileMap()->_tileMapSize;
    Size tileSize = this->getTileMap()->_tileSize;
    
    
    if (playerPos.x + _player->getDelta().x - winSize.width * LIMIT_WIDTH <= 0 ||
        playerPos.x + _player->getDelta().x + winSize.width * LIMIT_WIDTH >= mapSize.width)
    {
        
    }
    else
    {
        if ((devicePos.x + _player->getDelta().x < winSize.width * LIMIT_WIDTH && _player->getDelta().x < 0) ||
            (devicePos.x + _player->getDelta().x > winSize.width * (1 - LIMIT_WIDTH) && _player->getDelta().x > 0))
        {
            this->getLayerContainer()->baseLayer()->setPositionX(this->getLayerContainer()->baseLayer()->getPositionX() - _player->getDelta().x);
            this->getLayerContainer()->gameLayer()->setPositionX(this->getLayerContainer()->gameLayer()->getPositionX() - _player->getDelta().x);
            this->getLayerContainer()->effectLayer()->setPositionX(this->getLayerContainer()->effectLayer()->getPositionX() - _player->getDelta().x);
            this->_mapBackground->setPositionX(this->_mapBackground->getPositionX() - _player->getDelta().x);
        }
    }
    
    if (playerPos.y + _player->getDelta().y - winSize.height * LIMIT_HEIGHT <= 0 ||
        playerPos.y + _player->getDelta().y + winSize.height * LIMIT_HEIGHT >= mapSize.height)
    {
        
    }
    else
    {
        if ((devicePos.y + _player->getDelta().y < winSize.height * LIMIT_HEIGHT && _player->getDelta().y < 0) ||
            (devicePos.y + _player->getDelta().y > winSize.height * (1 - LIMIT_HEIGHT) && _player->getDelta().y > 0))
        {
            this->getLayerContainer()->baseLayer()->setPositionY(this->getLayerContainer()->baseLayer()->getPositionY() - _player->getDelta().y);
            this->getLayerContainer()->gameLayer()->setPositionY(this->getLayerContainer()->gameLayer()->getPositionY() - _player->getDelta().y);
            this->getLayerContainer()->effectLayer()->setPositionY(this->getLayerContainer()->effectLayer()->getPositionY() - _player->getDelta().y);
            this->_mapBackground->setPositionY(this->_mapBackground->getPositionY() - _player->getDelta().y);
        }
    }
}

void MainGameScene::updateUIEffect()
{
    auto playerPos = ConvertUtils::convertMapToDevice(_player->getPosition(), this->getLayerContainer()->gameLayer()->getPosition());
    if (playerPos.x > 950)
    {
        if (!isFading)
        {
            auto fade = FadeTo::create(0.3, 100);
            _skillLayer->getBtnBombDrop()->runAction(fade);
            _skillLayer->getBtnBombFire()->runAction(fade->clone());
            _skillLayer->getBtnBombSpike()->runAction(fade->clone());
            _skillLayer->getBtnBombTime()->runAction(fade->clone());
            isFading = true;
        }
    }
    else
    {
        if (isFading)
        {
            auto fade = FadeTo::create(0.3, 255);
            auto call = CallFunc::create([this]{
                isFading = false;
            });
            _skillLayer->getBtnBombDrop()->runAction(Sequence::create(fade, call, NULL));
            _skillLayer->getBtnBombFire()->runAction(fade->clone());
            _skillLayer->getBtnBombSpike()->runAction(fade->clone());
            _skillLayer->getBtnBombTime()->runAction(fade->clone());
        }
    }
}



//DataObject* MainGameScene::getObjectAt(cocos2d::Vec2 pos)
//{
//    if (_objectPool.empty())
//    {
//        return nullptr;
//    }
//    for (auto& pool : _objectPool)
//    {
//        for (auto&object : pool.second)
//        {
//            if (object && ConvertUtils::convertCDMaptoMatrix(dynamic_cast<TiledObject*>(object)->getFrontPosition(), _tileMap->_tileSize, _tileMap->_tileMapSizeMatrix) == pos)
//            {
//                return object;
//            }
//        }
//    }
//    return nullptr;
//}

void MainGameScene::effectUpdate()
{
    if (!_effectPool.empty())
    {
        for (auto i = 0; i < _effectPool.size(); i++)
        {
            _effectPool.at(i)->animUpdate(_currentMainLoop);
        }
    }
}


void MainGameScene::cleanUp()
{
    if (!_releasePool.empty())
    {
        _releasePool.clear();
    }
    
}

void MainGameScene::createKey()
{
    _objectPool = new cocos2d::Vector<DataObject*>[25];
    // set all value to 0
    
    
//    cocos2d::Vector<DataObject*> HAMMERS;
//    cocos2d::Vector<DataObject*> SHIPPERS;
//    cocos2d::Vector<DataObject*> TANKERS;
//    cocos2d::Vector<DataObject*> TRACKERS;
//    cocos2d::Vector<DataObject*> ROLLERS;
//    
//    cocos2d::Vector<DataObject*> BOMB_DROPS;
//    cocos2d::Vector<DataObject*> BOMB_FIRES;
//    cocos2d::Vector<DataObject*> BOMB_SPIKES;
//    cocos2d::Vector<DataObject*> BOMB_TIMES;
//    
//    cocos2d::Vector<DataObject*> BOOM_BOMBS;
//    cocos2d::Vector<DataObject*> BOOM_CHARACTERS;
//    cocos2d::Vector<DataObject*> BOOM_MINES;
//    cocos2d::Vector<DataObject*> BOOM_TIME_BOMBS;
//    
//    cocos2d::Vector<DataObject*> DIAMONDS;
//    
//    cocos2d::Vector<DataObject*> STONES;
//    cocos2d::Vector<DataObject*> BOX_GOLDS;
//    cocos2d::Vector<DataObject*> BOX_BOMB_DROPS;
//    cocos2d::Vector<DataObject*> BOX_BOMB_FIRES;
//    cocos2d::Vector<DataObject*> BOX_BOMB_SPIKES;
//    cocos2d::Vector<DataObject*> BOX_BOMB_TIMES;
//    cocos2d::Vector<DataObject*> GOLDS;
//    cocos2d::Vector<DataObject*> SNOWS;
//    cocos2d::Vector<DataObject*> FUELS;
//    cocos2d::Vector<DataObject*> NEXT_STAGE_DOORS;
//    cocos2d::Vector<DataObject*> EFFECT_LAND;
//    cocos2d::Vector<DataObject*> HP_UP;
//    
//    
//    _objectPool.insert(std::make_pair(ObjectKey::HAMMER_KEY, HAMMERS));
//    _objectPool.insert(std::make_pair(ObjectKey::SHIPPER_KEY, SHIPPERS));
//    _objectPool.insert(std::make_pair(ObjectKey::TANKER_KEY, TANKERS));
//    _objectPool.insert(std::make_pair(ObjectKey::TRACKER_KEY, TRACKERS));
//    _objectPool.insert(std::make_pair(ObjectKey::ROLLER_KEY, ROLLERS));
//    _objectPool.insert(std::make_pair(ObjectKey::BOMB_DROP_KEY, BOMB_DROPS));
//    _objectPool.insert(std::make_pair(ObjectKey::BOMB_FIRE_KEY, BOMB_FIRES));
//    _objectPool.insert(std::make_pair(ObjectKey::BOMB_SPIKE_KEY, BOMB_SPIKES));
//    _objectPool.insert(std::make_pair(ObjectKey::BOMB_TIME_KEY, BOMB_TIMES));
//    
//    _objectPool.insert(std::make_pair(ObjectKey::BOOM_BOMB_KEY, BOOM_BOMBS));
//    _objectPool.insert(std::make_pair(ObjectKey::BOOM_CHARACTER_KEY, BOOM_CHARACTERS));
//    _objectPool.insert(std::make_pair(ObjectKey::BOOM_MINE_KEY, BOOM_MINES));
//    _objectPool.insert(std::make_pair(ObjectKey::BOOM_TIME_BOMB_KEY, BOOM_TIME_BOMBS));
//    
//    _objectPool.insert(std::make_pair(ObjectKey::DIAMOND_KEY, DIAMONDS));
//    _objectPool.insert(std::make_pair(ObjectKey::STONE_KEY, STONES));
//    _objectPool.insert(std::make_pair(ObjectKey::BOX_GOLD_KEY, BOX_GOLDS));
//    _objectPool.insert(std::make_pair(ObjectKey::BOX_BOMB_DROP_KEY, BOX_BOMB_DROPS));
//    _objectPool.insert(std::make_pair(ObjectKey::BOX_BOMB_FIRE_KEY, BOX_BOMB_FIRES));
//    _objectPool.insert(std::make_pair(ObjectKey::BOX_BOMB_SPIKE_KEY, BOX_BOMB_SPIKES));
//    _objectPool.insert(std::make_pair(ObjectKey::BOX_BOMB_TIME_KEY, BOX_BOMB_TIMES));
//    _objectPool.insert(std::make_pair(ObjectKey::GOLD_KEY, GOLDS));
//    _objectPool.insert(std::make_pair(ObjectKey::SNOW_FLAKE_KEY, SNOWS));
//    _objectPool.insert(std::make_pair(ObjectKey::FUEL_KEY, FUELS));
//    _objectPool.insert(std::make_pair(ObjectKey::NEXT_STAGE_DOOR_KEY, NEXT_STAGE_DOORS));
//    _objectPool.insert(std::make_pair(ObjectKey::EFFECT_LAND_KEY, EFFECT_LAND));
//    _objectPool.insert(std::make_pair(ObjectKey::HP_UP_KEY, HP_UP));
    
    
//    for (auto i = 0; i < 25; i++)
//    {
//        cocos2d::Vector<DataObject*> temp;
//        
//        _objectPool[i] = temp;
//    }
}



