////
////  AdView.m
////  BTEndlessTunnel
////
////  Created by NSS on 4/8/14.
////
////
//
//#import "AdView.h"
//#import "Constants.h"
//#import "cocos2d.h"
//
//@implementation AdView
//
//
//- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
//{
//    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
//    if (self) {
//        
//    }
//    return self;
//}
//
//- (void)viewDidLoad
//{
//    [super viewDidLoad];
//    
//    _isShowAd = NO;
////    self.mopubView = [MPInterstitialAdController interstitialAdControllerForAdUnitId:@"ce112ea3e9704b78a0529b904ea58e6e"];
////    [self.mopubView setTesting:true];
////    [self.mopubView setDelegate:self];
//    
//    
////    [self cacheInterstitial];
//    
////    STAStartAppSDK* sdk = [STAStartAppSDK sharedInstance];
////    sdk.appID = @"209612738";
//    
////    [Chartboost startWithAppId:@"560d06e743150f2ccc15ec4f" appSignature:@"13c9099dadcde4061dda421d2dfa202f39d955fb" delegate:self];
////    [Chartboost setAutoCacheAds:YES];
//    
//
////    [RevMobAds startSessionWithAppID:@"561ba0327f9b975c7aad1d80" andDelegate:self];
//    
////    _banner = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
////    _banner.adUnitID = [NSString stringWithUTF8String:MY_IOS_BANNER_ID];
////    _banner.rootViewController = self;
////    _banner.adSize = kGADAdSizeSmartBannerLandscape;
////    _banner.translatesAutoresizingMaskIntoConstraints = YES;
////    
////    GADRequest* request = [GADRequest request];
////    _banner.backgroundColor = [UIColor redColor];
////    request.testDevices = @[
////                            kGADSimulatorID
////                            ];
////    [_banner loadRequest:request];
////    
////    
////    [self.view addSubview:_banner];
////    
////    
////    [self.view addConstraint:[NSLayoutConstraint constraintWithItem:_banner attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self.view attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0]];
//    
//    
////    _interstitial = [self createAndLoadInterstitial];
//    
//    [self cacheInterstitial];
////    [self loadFullscreen];
//}
//
//- (void)didReceiveMemoryWarning
//{
//    [super didReceiveMemoryWarning];
//    // Dispose of any resources that can be recreated.
//}
//
//- (void)dealloc
//{
////    _banner = nil;
////    _interstitial = nil;
////    self.mopubView.delegate = nil;
//    [super dealloc];
//}
//
//- (void)hide
//{
////    [_banner removeFromSuperview];
//}
//
//- (void)show
//{
////    [self.view addSubview:_banner];
//}
//
//- (void)present
//{
////    [_interstitial presentFromRootViewController:self];
//}
//
//
//- (void)cacheInterstitial {
////    if (![Chartboost hasInterstitial:CBLocationHomeScreen])
////    {
////        [Chartboost cacheInterstitial:CBLocationHomeScreen];
////    }
//
////    if (![self.mopubView ready]) {
////        [self.mopubView loadAd];
////    }
//    
//
//}
//
////- (void)didFailToLoadInterstitial:(CBLocation)location
////                        withError:(CBLoadError)error
////{
////    [self cacheInterstitial];
////}
//
//- (void)loadFullscreen {
////    if (self.fullscreen) {
////        [self.fullscreen release];
////        self.fullscreen = nil;
////    }
//
////    self.fullscreen = [[RevMobAds session] fullscreen];
////    self.fullscreen.delegate = self;
////    [self.fullscreen loadAd];
//}
//
//- (void)showPreLoadedFullscreen{
////    if (self.fullscreen) [self.fullscreen showAd];
//}
//
//- (void)presentChartBoost
//{
////    if ([self.mopubView ready]) {
////        [self.mopubView showFromViewController:self];
////        _isShowAd = YES;
////    }
////    else
////    {
////        [self cacheInterstitial];
////    }
////    
//
//}
//
//- (BOOL)isShowAd
//{
//    return _isShowAd;
//}
//
////- (void)didDismissInterstitial:(CBLocation)location
////{
////    [self cacheInterstitial];
////}
////
////
////
////- (void)didCloseInterstitial:(CBLocation)location
////{
////    [self cacheInterstitial];
////    cocos2d::Director::getInstance()->startAnimation();
////}
//
////- (GADInterstitial *)createAndLoadInterstitial
////{
////    GADInterstitial *newAd = [[GADInterstitial alloc] initWithAdUnitID:[NSString stringWithUTF8String:MY_IOS_INTERSTITIAL_ID]];
////    newAd.delegate = self;
////    [newAd loadRequest:[GADRequest request]];
////    return newAd;
////}
////
////
////- (void)interstitialDidDismissScreen:(GADInterstitial *)interstitial
////{
////    self.interstitial = [self createAndLoadInterstitial];
////}
//
//
////#pragma mark - Navigation
////
////// In a storyboard-based application, you will often want to do a little preparation before navigation
////- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
////{
//////     Get the new view controller using [segue destinationViewController].
//////     Pass the selected object to the new view controller.
////}
//
//#pragma mark - RevMobAdsDelegate methods
//
//
///////Session Listeners/////
//- (void)revmobSessionIsStarted {
//    NSLog(@"[RevMob Sample App] Session started with delegate.");
//    //    [self basicUsageShowFullscreen];
//}
//
//- (void)revmobSessionNotStarted:(NSError *)error {
//    NSLog(@"[RevMob Sample App] Session not started again: %@", error);
//}
//
//
///////Ad Listeners/////
//- (void)revmobAdDidReceive {
//    NSLog(@"[RevMob Sample App] Ad loaded.");
//}
//
//- (void)revmobAdDidFailWithError:(NSError *)error {
//    NSLog(@"[RevMob Sample App] Ad failed: %@", error);
////    [self loadFullscreen];
//}
//
//- (void)revmobAdDisplayed {
//    NSLog(@"[RevMob Sample App] Ad displayed.");
//    
//}
//
//- (void)revmobUserClosedTheAd {
//    NSLog(@"[RevMob Sample App] User clicked in the close button.");
////    [[[RevMobAds session] fullscreen] release];
////    [self loadFullscreen];
//    
//}
//
//- (void)revmobUserClickedInTheAd {
//    NSLog(@"[RevMob Sample App] User clicked in the Ad.");
//}
//
//#pragma mark - <MPInterstitialAdControllerDelegate>
//
////- (void)interstitialDidLoadAd:(MPInterstitialAdController *)interstitial
////{
////    
////}
////
////- (void)interstitialDidFailToLoadAd:(MPInterstitialAdController *)interstitial
////{
//////    [self cacheInterstitial];
////}
////
////- (void)interstitialDidExpire:(MPInterstitialAdController *)interstitial
////{
////    [self cacheInterstitial];
////}
////
////- (void)interstitialWillAppear:(MPInterstitialAdController *)interstitial
////{
////    cocos2d::Director::getInstance()->stopAnimation();
////}
////
////- (void)interstitialDidAppear:(MPInterstitialAdController *)interstitial
////{
////
////}
////
////- (void)interstitialWillDisappear:(MPInterstitialAdController *)interstitial
////{
////    
////}
////
////- (void)interstitialDidDisappear:(MPInterstitialAdController *)interstitial
////{
////    [self cacheInterstitial];
////    cocos2d::Director::getInstance()->startAnimation();
////}
////
////- (void)interstitialDidReceiveTapEvent:(MPInterstitialAdController *)interstitial
////{
////
////}
////
////- (void)didDismissInterstitial:(CBLocation)location
////{
////    [self cacheInterstitial];
////    cocos2d::Director::getInstance()->startAnimation();
////    _isShowAd = NO;
////}
////
////- (void)didCacheInterstitial:(CBLocation)location
////{
////    NSLog(@"did cache interstitial");
////}
////
//
//@end
