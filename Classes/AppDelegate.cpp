#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SceneManager.h"
#include "Heads.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    CMVisibleRect::setupVisibleRect(960, 640);
    visibleSize = Director::getInstance()->getVisibleSize();

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

//    // create a scene. it's an autorelease object
    
    ConfigManager::getInstance()->loadFile("config/config.plist");
//    IAPManager初始化要放在ConfigManager后面
    GameDataManager::getInstance()->setup(); //要放在ConfigManager后面
    ConfigManager::getInstance()->restoreDecorateConfigData();
    
//    AdsManager::getInstance()->preloadAllAds();
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    gNoneIap = false;
#else
    gNoneIap = true;
#endif
    
//    GameDataManager::getInstance()->m_nPackage = ePackageHotdog;
    SceneManager::replaceTheScene<DecorateScene>(0);
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
    if (!UserDefault::getInstance() -> getBoolForKey("removeAds")){
//        AudioHelp::getInstance()->pauseBackGroundMusic();
//        AdsManager::getInstance()->setVisiable(kTypeBannerAds,false);
//        AdLoadingLayerBase::showLoading<AdsLoadingScene>(false);
//        AdLoadingLayerBase::s_currentInstance->loadingDoneCallback = [=](){
//            AdsManager::getInstance()->setVisiable(kTypeBannerAds,true);
//            AudioHelp::getInstance()->resumeBackGroundMusic();
//        };
    }
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
