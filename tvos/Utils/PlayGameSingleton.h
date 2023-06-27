//
//  ControllerSingleLeaderboard.h
//  GooglePlayGameServices
//
//  Created by NSS on 4/7/14.
//
//




#ifndef __PLAY_GAME_SINGLETON_H__
#define __PLAY_GAME_SINGLETON_H__


class PlayGameSingleton {
public:
    static PlayGameSingleton* sharedInstance();
    ~PlayGameSingleton();
    PlayGameSingleton();
    
    static PlayGameSingleton* _instance;
    int _login;
    int _coins;
    
    void showSingleLeaderboard(const char* leaderBoardID);
    void restorePurchase();
    void showLeaderboards();
    bool isPurchased();
    
    void submitScore(long score, const char* leaderBoardID);
    
    void showAchievements();
    void finishGameCenter();
    
    void revealAchievement(const char* achievementID);
    void unlockAchievement(const char* achievementID);
    void incrementAchievement(int numSteps, const char* achievementID);
    void incrementPercentageAchievement(float percentage, const char* achievementID);
    
    void authenticate();
    void signOut();
    void trySilentAuthentication();
    bool isSignedIn();
    
    bool isOnline();
    bool isShowAd();
    void initAdView();
    void showBanner();
    void hideBanner();
    void showInterstitial();
    void inappBilling(int index);
    
    void rateApp();
    
    void loadAd();
    
    void shareOnFacebook(long score, int level, int obstacles);
    void shareOnFacebook(char* msg, char* url, char* image);
    void shareOnTwitter(char* msg, char* url, char* image);
    
    
    void userLogin();
    void updateDataString(const char* key, const char* data);
    void updateDataInt(const char* key, int data);
    int getDataInt(const char* key);
    std::string getDataString(const char* key);
    void showAlertConnection();
    
    void reload();
private:
    void* rootController;
};

#endif
