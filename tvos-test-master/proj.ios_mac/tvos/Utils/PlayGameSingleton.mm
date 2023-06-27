//
//  ControllerSingleLeaderboard.m
//  GooglePlayGameServices
//
//  Created by NSS on 4/7/14.
//
//

#import "PlayGameSingleton.h"
#import "AdView.h"
#import "Globals.h"
#import "GCHelper.h"
#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>
//#import <Social/Social.h>
#import "cocos2d.h"
#import "AppController.h"
#import "RootViewController.h"
#include "ParseUtils.h"
#include "StartGameScene.h"
#include "AudioEngine.h"
#import "IAPRequestListItem.h"
#import "Contants_iOS.h"

#define APP_ID 864587748 //id from iTunesConnect

using namespace cocos2d;

// A function for parsing URL parameters returned by the Feed Dialog.
//NSDictionary* parseURLParams(NSString* query)
//{
//    NSArray *pairs = [query componentsSeparatedByString:@"&"];
//    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
//    for (NSString *pair in pairs) {
//        NSArray *kv = [pair componentsSeparatedByString:@"="];
//        NSString *val =
//        [kv[1] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
//        params[kv[0]] = val;
//    }
//    return params;
//}

#pragma mark - Declare Views
//AdView* adView = 0;

#pragma mark - Destructor and Constructor
PlayGameSingleton::~PlayGameSingleton()
{
    rootController = nullptr;
//    adView = nullptr;
}

PlayGameSingleton::PlayGameSingleton()
: rootController(nullptr)
{
    _login = 0;
    UIWindow *window =  [[UIApplication sharedApplication] keyWindow];
    
    if(!rootController)
        rootController = window.rootViewController;
}

void PlayGameSingleton::restorePurchase()
{
    [[IAPRequestListItem getInstance] restorePurchase];
}

bool PlayGameSingleton::isPurchased()
{
    return [[IAPRequestListItem getInstance] isPurchased];
}


#pragma mark - Singleton

PlayGameSingleton* PlayGameSingleton::_instance = NULL;

PlayGameSingleton* PlayGameSingleton::sharedInstance() {
    if (!_instance) {
        [[IAPRequestListItem getInstance] registerIAPHelper];
        NSArray *arrs = @[INAPP_ITEM1, INAPP_ITEM2, INAPP_ITEM3, INAPP_ITEM4, INAPP_ITEM5];
        
        [[IAPRequestListItem getInstance] requestGetListOfItemPurchase:arrs];
        _instance = new PlayGameSingleton();
    }
    return _instance;
}


#pragma mark - Single Leaderboard
void PlayGameSingleton::showSingleLeaderboard(const char* leaderBoardID)
{    
    if(!isSignedIn())
        authenticate();
    
//    cocos2d::experimental::AudioEngine::pauseAll();
    Director::getInstance()->stopAnimation();
    NSString* name = [NSString stringWithUTF8String:leaderBoardID];
    [[GCHelper sharedInstance] showLeaderboard:name];
}


#pragma mark - Leaderboards Picker
void PlayGameSingleton::showLeaderboards()
{
    
    if(!isSignedIn())
    {
        authenticate();
        return;
    }
    
    Director::getInstance()->stopAnimation();
    [[GCHelper sharedInstance] showLeaderboard:nil];
}


#pragma mark - Submit score
void PlayGameSingleton::submitScore(long score, const char *leaderBoardID)
{
    
    if(!isSignedIn())
        return;

    NSString* name = [NSString stringWithUTF8String:leaderBoardID];
    [[GCHelper sharedInstance] submitScore: score forCategory:name];
    
}

#pragma mark - Achievements
void PlayGameSingleton::showAchievements()
{
    
    if(!isSignedIn())
    {
        authenticate();
        return;
    }
    
    Director::getInstance()->stopAnimation();
    [[GCHelper sharedInstance] showAchievements];
}


#pragma mark - Manage achievements
void PlayGameSingleton::revealAchievement(const char *achievementID)
{
    if(!isSignedIn())
        return;
}

void PlayGameSingleton::unlockAchievement(const char *achievementID)
{
    if(!isSignedIn())
        return;
    
    if(strlen(achievementID) == 0)
        return;
    
    NSString* name = [NSString stringWithUTF8String:achievementID];
    [[GCHelper sharedInstance] reportAchievementIdentifier:name percentComplete:100];
    
}

void PlayGameSingleton::finishGameCenter()
{
    cocos2d::experimental::AudioEngine::resumeAll();
    Director::getInstance()->startAnimation();
}

void PlayGameSingleton::incrementPercentageAchievement(float percentage, const char *achievementID)
{
    if(!isSignedIn())
        return;
    
    if(strlen(achievementID) == 0)
        return;
    
    NSString* name = [NSString stringWithUTF8String:achievementID];
    [[GCHelper sharedInstance] reportAchievementIdentifier:name percentComplete:percentage];
}

void PlayGameSingleton::incrementAchievement(int numSteps, const char *achievementID)
{
    if(!isSignedIn())
        return;
}

#pragma mark - Login configuration
void PlayGameSingleton::trySilentAuthentication()
{
}

void PlayGameSingleton::authenticate()
{
    [[GCHelper sharedInstance] authenticateLocalUser];
}

bool PlayGameSingleton::isSignedIn()
{
    return user_data_id != "";
}


void PlayGameSingleton::signOut()
{
    if(isSignedIn())
    {

    }
}

#pragma mark - Advertisement
void PlayGameSingleton::initAdView()
{
//    if(!adView && rootController)
//    {
//        adView = [[AdView alloc] init];
//        [((UIViewController *) rootController).view addSubview: adView.view];
//    }
}

bool PlayGameSingleton::isOnline()
{
    return [((RootViewController *) rootController).internetReachability currentReachabilityStatus] > NetworkStatus::NotReachable;
}


void PlayGameSingleton::showBanner()
{
//    [adView show];
}

void PlayGameSingleton::hideBanner()
{
//    [adView hide];
}

void PlayGameSingleton::showInterstitial()
{
//    [adView presentChartBoost];
}

void PlayGameSingleton::userLogin(){
    [ParseUtils userLogin];
}

void PlayGameSingleton::updateDataInt(const char *key, int data){
    NSString *strKey = [NSString stringWithCString:key encoding:NSUTF8StringEncoding];
    [ParseUtils updateDataInt:strKey :data];
}

void PlayGameSingleton::updateDataString(const char *key, const char *data){
    NSString *strKey = [NSString stringWithCString:key encoding:NSUTF8StringEncoding];
    NSString *strData = [NSString stringWithCString:data encoding:NSUTF8StringEncoding];
    [ParseUtils updateDataString:strKey :strData];
    
}

int PlayGameSingleton::getDataInt(const char *key){
    NSString *strKey = [NSString stringWithCString:key encoding:NSUTF8StringEncoding];
    return (int)[ParseUtils getDataInt:strKey];
}

std::string PlayGameSingleton::getDataString(const char *key){
    NSString *strKey = [NSString stringWithCString:key encoding:NSUTF8StringEncoding];
    NSString* str = [ParseUtils getDataString:strKey];
    
    if(str != nil){
        std::string rs = [str cStringUsingEncoding:[NSString defaultCStringEncoding]];
        return rs;
    }else{
        std::string st = "a";
        return st;
    }
}

void PlayGameSingleton::inappBilling(int index){
    [[IAPRequestListItem getInstance] buyItem:index];
    switch (index) {
        case 0:
            _coins = 500;
            break;
        case 1:
            _coins = 1000;
            break;
        case 2:
            _coins = 2000;
            break;
        case 3:
            _coins = 5000;
            break;
        case 4:
            _coins = -1;
            break;
        default:
            _coins = 0;
    }
}


void PlayGameSingleton::rateApp()
{
    NSString *reviewURL = [NSString stringWithFormat:@"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%d", APP_ID];
    
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:reviewURL]];
    
}
void PlayGameSingleton::shareOnTwitter(char* msg, char* url, char* image)
{
//    AppController *appController = (AppController*) [UIApplication sharedApplication].delegate;
//    
//    NSString *strMessage = [NSString stringWithCString:msg encoding:NSUTF8StringEncoding];
//    NSString *strUrl = [NSString stringWithCString:url encoding:NSUTF8StringEncoding];
//    NSString *strImg = [NSString stringWithCString:image encoding:NSUTF8StringEncoding];
//    
//    [appController.viewController postTwitter:strMessage :strUrl :strImg];
}
void PlayGameSingleton::shareOnFacebook(char* msg, char* url, char* image)
{
//    AppController *appController = (AppController*) [UIApplication sharedApplication].delegate;
//    
//    NSString *strMessage = [NSString stringWithCString:msg encoding:NSUTF8StringEncoding];
//    NSString *strUrl = [NSString stringWithCString:url encoding:NSUTF8StringEncoding];
//    NSString *strImg = [NSString stringWithCString:image encoding:NSUTF8StringEncoding];
//    
//    [appController.viewController postFacebook:strMessage :strUrl :strImg];
}

void PlayGameSingleton::showAlertConnection()
{
    AppController *appController = (AppController*) [UIApplication sharedApplication].delegate;
    [appController.viewController showAlertConnection];
}

void PlayGameSingleton::reload()
{
    if (StartGameScene::getInstance())
    {
        StartGameScene::getInstance()->reload();
    }
}

void PlayGameSingleton::loadAd()
{
//    [adView cacheInterstitial];
}

void PlayGameSingleton::shareOnFacebook(long score, int level, int obstacles)
{
    
}

bool PlayGameSingleton::isShowAd()
{
//    return [adView isShowAd];
}
