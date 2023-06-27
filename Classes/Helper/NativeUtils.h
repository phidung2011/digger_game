//  gamebase
//
//  Created by NgocDiep on 7/8/15.
//
//
#ifndef __NATIVE_UTILS_H__
#define __NATIVE_UTILS_H__

#include "cocos2d.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JNIHelpers.h"
#endif

class NativeUtils {
public:
	/*
	 * Google play game services methods
	 */
	static bool isSignedIn();
	static bool isOnline();
    static bool isShowAd();

	static void signIn();
	static void signOut();
	static void submitScore(const char* leaderboardID, long score);
	static void unlockAchievement(const char* achievementID);
	static void incrementAchievement(const char* achievementID, int numSteps);
	static void incrementPercentageAchievement(const char *achievementID,
			float percentage);
	static void showAchievements();
	static void showLeaderboards();
	static void showLeaderboard(const char* leaderboardID);
    
    static void initAd();
    static void showAd();
    static void showFullscreen();
    static void hideAd();
    static void showInterstitial();
    static void initialGCM();
    static void rateApp();
    
    static void inappBilling(unsigned int index);
    static void pushNotification( const char* content, int time);
    
    static void showAdBuddiz();
    
    static void sendAnalytics(const char* screen);
    
    static void shareOnFacebook(long score, int level, int obstacles);
    static void shareOnTwitter(char* msg, char* url, char* image= "" , int flag = 1);
    static void shareOnFacebook(char* content, char* url = "", char* image = "" , int flag = 1);
    static void shareOnTwitter(long score, int level, int obstacles);
    static void killApp();

    static int isLoggedIn();
	static void userLogin();
	static void updateData(const char* key, int data);
	static void updateData(const char* key, const char* data);
	static int getDataInt(const char* key);
	static std::string getDataString(const char* key);

    static void showAlertConnection();
    
    static void loadAd();
    
    static void restorePurchase();
    static bool isPurchased();
	/*
	 * Ouya connection
	 */

};

#endif
