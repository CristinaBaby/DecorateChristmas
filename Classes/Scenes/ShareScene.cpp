
#include "ShareScene.h"
#include "SceneManager.h"

static std::string gPackageName[] = {
    "lemonade",
    "hotdog",
    "frenchfries",
    "snowcone",
    "churro",
    "burrito",
    "funnelcake",
    "frybread",
};
ShareScene::ShareScene()
{
    m_pTip = nullptr;
}

ShareScene::~ShareScene()
{
    
}
bool ShareScene::init()
{
    if ( !ExtensionScene::init() )
    {
        return false;
    }
    _initData();
    
    //    bg
    int bgIndex = GameDataManager::getInstance()->m_nBgIndex;
    ostringstream ostr;
    if (bgIndex<0) {
        ostr<<"content/make/dec/bg.jpg";
    }else{
        
        ostr<<"content/category/"<<"background/"<<"background"<<bgIndex<<".png";
    }
    m_pBg = Sprite::create(ostr.str());
    m_pBg->setPosition(visibleSize*0.5);
    this->addChildToBGLayer(m_pBg);
    
    m_pEatLayer = EatLayer::create();
    this->addChildToUILayer(m_pEatLayer);
    m_pEatLayer->onEatBeginCallback = CC_CALLBACK_2(ShareScene::onEatBeinCallback, this);
    m_pEatLayer->onEatEndCallback = CC_CALLBACK_1(ShareScene::onEatEndCallback, this);
    m_pEatLayer->setDrinkable(true);
    
    if (GameDataManager::getInstance()->m_nPackage==ePackageLemonade) {
        Rect rect = Rect(173, 666, 172, 210);
        rect.origin = CMVisibleRect::getPositionAdapted(rect.origin);
        m_pEatLayer->setDrinkRect(rect);
        m_pTip = Sprite::create("content/common/text_tap.png");
    }else{
        m_pEatLayer->setDrinkRect(Rect::ZERO);
        m_pTip = Sprite::create("content/common/text_tap.png");
    }
    Rect rect = Rect(visibleSize.width*0.9-130, visibleSize.height*0.7-196, 190, 270);
    rect.origin = CMVisibleRect::getPositionAdapted(rect.origin);
    m_pEatLayer->setDrinkRect(rect);
    this->addChildToUILayer(m_pTip);
    CMVisibleRect::setPositionAdapted(m_pTip, 480, 520,kBorderNone,kBorderTop);
    
    m_pDecoLayer = Layer::create();
    this->addChildToContentLayer(m_pDecoLayer);
    
    m_nNextSceneTag = eSceneTagChoosePackage;
    m_pGameUI->showShareUILayout(false);
    return true;
}

void ShareScene::onEnter()
{
    ExtensionScene::onEnter();
//    decorate界面有放大缩下功能  避免截屏到放大缩小的ui被截图下来
    
    m_pDecManager = DecorateManager::getInstance();
    m_pDecManager->showFinishedFood(m_pDecoLayer);
}

void ShareScene::onButtonCallback(Button* btn)
{
    ExtensionScene::onButtonCallback(btn);
    int tag = btn->getTag();
    if (eUIButtonTagFav==tag) {
        btn->setEnabled(false);
        RenderTexture* rt = getResultRender();
        Image* pImage = rt->newImage();
        AlumnAdapter::saveToFav(pImage,[=](){
            
        });
        pImage->autorelease();
        
//        FavoriteManager* manager = FavoriteManager::getInstace();
//        manager->setResultCallBack([=](bool ok){
//            if (ok) {                
//                Dialog* dialog=Dialog::create(Size(450,300), (void*)&MENU_TYPE_1, Dialog::DIALOG_TYPE_SINGLE);
//                dialog->setContentText("Your Food has been added to your favorites.");
//                Director::getInstance()->getRunningScene()->addChild(dialog, 9999, 9999);
//                dialog->setPosition(Director::getInstance()->getVisibleOrigin());
//                dialog->onPositiveClick = [=](void*){
//                    btn->setEnabled(true);
//                    
//                };
//            }
//        });

        
    }else if (eUIButtonTagEmail==tag){
        Image* pImage = getResultRender()->newImage();
        pImage->saveToFile(FileUtility::getStoragePath()+"shotscreen.png", false);
        pImage->autorelease();
        STSystemFunction st;
        st.sendEmailAndFilePic("Mac N' Cheese",  "<p>Check out the Mac N' Cheese I just made!  Download the app from the link below and see if you can make a better one!</p>  <p><a href=‘http://itunes.apple.com/app/id563797954’>http://itunes.apple.com/app/id563797954</a></p>", FileUtility::getStoragePath()+"shotscreen.png");
    }else if (eUIButtonTagEatAgain==tag){
        btn->setVisible(false);
        btn->setEnabled(true);
        m_pDecoLayer->removeAllChildren();
        m_pDecManager->showFinishedFood(this->m_pDecoLayer);
    }else if (eUIButtonTagNext==tag){
        m_pDecManager->reset();
    }else if (eUIButtonTagHome==tag){
        btn->setEnabled(false);
        Dialog* dialog=Dialog::create(Size(450,300), (void*)&MENU_TYPE_1, Dialog::DIALOG_TYPE_NEGATIVE);
        dialog->setContentText("Do you want to start over with a new food?");
        Director::getInstance()->getRunningScene()->addChild(dialog, 9999, 9999);
        dialog->setPosition(Director::getInstance()->getVisibleOrigin());
        dialog->onPositiveClick = [=](void*){
            btn->setEnabled(true);
            m_pDecManager->reset();

//            if (!UserDefault::getInstance() -> getBoolForKey("removeAds")){
//                AudioHelp::getInstance()->pauseBackGroundMusic();
//                AdsManager::getInstance()->setVisiable(kTypeBannerAds,false);
//                AdLoadingLayerBase::showLoading<AdsLoadingScene>(true);
//                AdLoadingLayerBase::s_currentInstance->loadingDoneCallback = [=](){
//                    AudioHelp::getInstance()->resumeBackGroundMusic();
//                    AdsManager::getInstance()->setVisiable(kTypeBannerAds,true);
//                    SceneManager::popToRootScene();
//                    SceneManager::replaceTheScene<HomeScene>();
//                };
//            }else{
                SceneManager::popToRootScene();
                SceneManager::replaceTheScene<HomeScene>();
//            }
            
        };
        dialog->onNegativeClick = [=](void*){
            btn->setEnabled(true);
            
        };
    }
}
#pragma mark - initData
void ShareScene::_initData()
{
    m_nPackage = GameDataManager::getInstance()->m_nPackage;
    setExPath("content/"+gPackageName[m_nPackage]+"/");
    
}


RenderTexture* ShareScene::getResultRender()
{
    RenderTexture* render = RenderTexture::create(visibleSize.width, visibleSize.height);
    
    render->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    m_pBGLayer->visit();
    m_pContentLayer->visit();
    render->end();
    
    Director::getInstance()->getRenderer()->render();
    
    __NotificationCenter::getInstance()->removeObserver(render, EVENT_COME_TO_BACKGROUND);
    __NotificationCenter::getInstance()->removeObserver(render, EVENT_COME_TO_FOREGROUND);

    return render;
}
void ShareScene::onEatBeinCallback(Vec2 location,bool drinkable)
{
    if (drinkable) {
        m_pDecManager->doDrink();
        AudioHelp::getInstance()->playDrinkEffect();
    }
}

void ShareScene::onEatEndCallback(Vec2 location)
{
    if (m_pTip) {
        m_pTip->runAction(Sequence::create(MoveBy::create(1, Vec2(-visibleSize.width, 0)),
                                           CallFuncN::create([=](Node* node)
                                                             {
                                                                 node->removeFromParent();
                                                             }),
                                           NULL));
        m_pTip = nullptr;
    }
    m_pDecManager->doEat(location);
    m_pDecManager->stopDrink();
    AudioHelp::getInstance()->stopDrinkEffect();
    if (m_pDecManager->finishedEat() && !m_pGameUI->eatAgainIsShow()) {
        if (GameDataManager::getInstance()->m_nPackage==ePackageLemonade) {
            m_pGameUI->showEatAgainLayout(true);
        }else{
            m_pGameUI->showEatAgainLayout();
        }
    }
}

void ShareScene::onKeyBackClicked()
{
    AudioHelp::getInstance()->playPreviousEffect();
    SceneManager::popScene();    
}