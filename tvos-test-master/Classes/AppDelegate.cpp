#include "AppDelegate.h"

#include "LoadingScene.h"
#include "AppMacros.h"
#include "GameConfig.h"
#include "NativeUtils.h"
#include "MainMenu.h"
#include "StartGameScene.h"

USING_NS_CC;

//static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
//static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
//static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
//static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("tvapp", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("tvapp");
#endif
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    Size frameSize = glview->getFrameSize();
    
    register_all_packages();
    
    ZipUtils::setPvrEncryptionKey(0x8cb60bfc,
                                  0x8192ce0b,
                                  0xfe9cc710,
                                  0xe3f96492);
    
    
    GameSingleton::getInstance()->_winsize = director->getVisibleSize();
    //    dictionary
    glview->setDesignResolutionSize(designResolutionSize.width,
                                    designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
    
    GameSingleton::getInstance()->_winsizeCustom = designResolutionSize;
    
    std::vector < std::string > searchPath;
    searchPath.push_back("res");
    // set searching path
    FileUtils::getInstance()->setSearchPaths(searchPath);
    
    // create a scene. it's an autorelease object
    auto scene = LoadingScene::create();
    
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}