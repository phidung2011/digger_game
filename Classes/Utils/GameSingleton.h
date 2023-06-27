#ifndef __GameSingleton_H__
#define __GameSingleton_H__

#include "cocos2d.h"

typedef enum class GameState{
    sStartGame,
    sCreateUserMaster,
    sCreateUserDevice,
    sLoadUserMasterFromCreate,
    sLoadUserMaster,
    sLoadUserDevice,
    sLoadStar,
    sLoadCoin,
    sUpdateStar,
    sUpdateCoin,
    sLoginSucceed,
    sUpdateRemoveAds,
}GameState;

class GameSingleton
{
public:
    GameSingleton();
	 ~GameSingleton();
    
    virtual bool init();
    
	static GameSingleton * getInstance(void);
    int BGM_AUDIO_ID;
    int SOUND;
    int MUSIC;
    cocos2d::Size _winsize;
    cocos2d::Size _winsizeCustom;
    void showTooltip(const std::string& content, cocos2d::Layer* target);
    
    int _coin;
    int _removeAds;
    
    int _loopSound;
    
    int _cachedImage;
    
    float getScaleFixWith();
    float getScaleFixHeight();
    bool isStartGame;
    bool isPlaying;
    
    bool isTouchDown;
    bool inSetting;
protected:
    static GameSingleton* _instance;
    
    CC_SYNTHESIZE(GameState, _currentState, CurrentState);
};

#endif // __LOADING_SCENE_H__
