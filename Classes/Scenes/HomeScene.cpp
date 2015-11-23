
#include "HomeScene.h"
#include "SceneManager.h"
#include "ShopLayer.h"

static Vec2 gFoodPosition[4]= {
    Vec2(320,338),
    Vec2(320,225),
    Vec2(320,100),
    Vec2(320,90),
};
HomeScene::HomeScene()
{
    
}

HomeScene::~HomeScene()
{
    
}
bool HomeScene::init()
{
    if ( !ExtensionScene::init() )
    {
        return false;
    }
    _initData();
    
    //    bg
    Sprite* pBg = Sprite::create(localPath("bg.jpg"));
    pBg->setPosition(visibleSize*0.5);
    this->addChildToBGLayer(pBg);
    
    m_pLogo = Sprite::create(localPath("logo.png"));
    this->addChildToUILayer(m_pLogo);
    CMVisibleRect::setPositionAdapted(m_pLogo, Vec2(385-visibleSize.width, 530),kBorderNone,kBorderTop);
    
    m_pCup = Sprite::create(localPath("cup_0.png"));
    this->addChildToContentLayer(m_pCup);
    CMVisibleRect::setPositionAdapted(m_pCup, 154-visibleSize.width, 251);
    m_pCup->setLocalZOrder(10);
    
    m_pCupShadow = Sprite::create(localPath("cup_1.png"));
    this->addChildToContentLayer(m_pCupShadow);
    CMVisibleRect::setPositionAdapted(m_pCupShadow, 154, 251);

    
    m_pFork = Sprite::create(localPath("fork_1.png"));
    this->addChildToContentLayer(m_pFork);
    CMVisibleRect::setPositionAdapted(m_pFork, Vec2(217-visibleSize.width, 101));
    m_pFork->setLocalZOrder(10);
    
    m_pForkShadow = Sprite::create(localPath("fork_0.png"));
    this->addChildToContentLayer(m_pForkShadow);
    CMVisibleRect::setPositionAdapted(m_pForkShadow, Vec2(217, 101));
    
    
    m_pCupShadow->setOpacity(0);
    m_pForkShadow->setOpacity(0);
    m_pCup->runAction(Sequence::create(DelayTime::create(1),
                                       EaseBackOut::create(MoveBy::create(0.5, Vec2(visibleSize.width, 0))),
                                       DelayTime::create(0.5),
                                             CallFunc::create([=]()
                                                              {
                                                                  m_pCupShadow->runAction(FadeIn::create(0.5));
                                                                  AudioHelp::getInstance()->playEffect("start_fork.mp3");
                                                                  m_pFork->runAction(Sequence::create(Spawn::create(RotateBy::create(1, 360),
                                                                                                                    MoveBy::create(0.5, Vec2(visibleSize.width, 0)),
                                                                                                                    NULL),
                                                                                                      CallFunc::create([=]()
                                                                                                                       {
                                                                                                                           m_pForkShadow->runAction(FadeIn::create(0.5));
                                                                                                                           AudioHelp::getInstance()->playEffect("start_logo.mp3");
//                                                                                                                           m_pLogo->runAction(Spawn::create(EaseBounceOut::create(MoveBy::create(3, Vec2(visibleSize.width,0))),
//                                                                                                                                                            Sequence::create(EaseBounceOut::create(ScaleTo::create(3, 1.2)),
//                                                                                                                                                                             EaseBackOut::create(ScaleTo::create(0.5, 1)),
//                                                                                                                                                                             NULL),
//                                                                                                                                                            NULL));
                                                                                                                           m_pLogo->runAction(Sequence::create(EaseBounceOut::create(MoveBy::create(3, Vec2(visibleSize.width,0))),
                                                                                                                                                               EaseBounceOut::create(ScaleTo::create(3, 0.8)),
                                                                                                                                                               ScaleTo::create(0.5, 1),
                                                                                                                                                            NULL));
                                                                                                                           _showParticle();
                                                                                                                           m_pGameUI->showHomeUILayout();
                                                                                                                           
                                                                                                                       }),
                                                                                                      NULL));
                                                              }),
                                             NULL));
    AudioHelp::getInstance()->playBackGroundMusic("bgmusic.mp3");
    return true;
}

void HomeScene::onEnter()
{
    ExtensionScene::onEnter();
    
//    if (!UserDefault::getInstance()->getBoolForKey("removeAds")){
//        AdsManager::getInstance()->removeAds(kTypeBannerAds);
//        
//    }
}
void HomeScene::onButtonCallback(Button* btn)
{
    int tag = btn->getTag();
    btn->setEnabled(false);
    this->runAction(Sequence::create(DelayTime::create(0.3),
                                     CallFunc::create([=]()
                                                      {
                                                          btn->setEnabled(true);
                                                      }),
                                     NULL));
    switch (tag) {
        case eUIButtonTagHomeStart:
        {
            AudioHelp::getInstance()->playStartEffect();
//            if (!UserDefault::getInstance() -> getBoolForKey("removeAds")){
//                AudioHelp::getInstance()->pauseBackGroundMusic();
//                AdsManager::getInstance()->setVisiable(kTypeBannerAds,false);
//                AdLoadingLayerBase::showLoading<AdsLoadingScene>(true);
//                AdLoadingLayerBase::s_currentInstance->loadingDoneCallback = [=](){
//                    AudioHelp::getInstance()->resumeBackGroundMusic();
//                    AdsManager::getInstance()->setVisiable(kTypeBannerAds,true);
//                    SceneManager::replaceTheScene<CookScene>();
//                };
//            }else{
                SceneManager::replaceTheScene<DecorateScene>();
//            }
        }
            break;
        case eUIButtonTagHomeRestore:
        {
            ShopAdapter::getInstance()->requestRestore();
        }
            break;
        case eUIButtonTagHomeFav:
        {
//            SceneManager::pushTheScene<FavoriteLayer>();
        }
            break;
        case eUIButtonTagHomeMore:
        {
            STSystemFunction st;
            st.showMoreGame();
        }
            break;
        case eUIButtonTagHomeShop:
        {
            ShopLayer* pLayer = ShopLayer::create();
            this->addChildToUILayer(pLayer);
            pLayer->setLocalZOrder(100);
        }
            break;
            
        default:
            break;
    }
}

#pragma mark - initData
void HomeScene::_initData()
{
    setExPath("content/start/");
    
}

void HomeScene::_showParticle()
{
    ParticleSystemQuad* pParticle = ParticleSystemQuad::create("particle/dress.plist");
    this->addChildToContentLayer(pParticle);
    pParticle->setLocalZOrder(5);
    pParticle->setPosition(Vec2(0, visibleSize.height*0.8));
    
    AudioHelp::getInstance()->playEffect("particles_sparkle.mp3");
    pParticle->runAction(RepeatForever::create(Sequence::create(Spawn::create(MoveBy::create(10, Vec2(visibleSize.width+100, 0)),
                                                                              Sequence::create(EaseBackOut::create(MoveBy::create(1, Vec2(0, 30))),
                                                                                               DelayTime::create(1),
                                                                                               EaseBackOut::create(MoveBy::create(2, Vec2(0, -60))),
                                                                                               DelayTime::create(1),
                                                                                               EaseBackOut::create(MoveBy::create(2, Vec2(0, 60))),
                                                                                               DelayTime::create(1),
                                                                                               EaseBackOut::create( MoveBy::create(1, Vec2(0, -30))),
                                                                                               NULL),
                                                                              NULL),
                                                                DelayTime::create(2),
                                                                CallFunc::create([=]()
                                                                                 {
                                                                                     pParticle->setPosition(Vec2(0, visibleSize.height*0.8));
                                                                                     AudioHelp::getInstance()->playEffect("particles_sparkle.mp3");
                                                                                 }),
                                                                NULL)));
    
}

void HomeScene::onKeyBackClicked()
{
    if (Director::getInstance()->getRunningScene()->getChildByTag(9999)) {
        Director::getInstance()->getRunningScene()->getChildByTag(9999)->removeFromParent();
        return;
    }
    Dialog* dialog=Dialog::create(CCSize2(600,330), (void*)&MENU_TYPE_1, Dialog::DIALOG_TYPE_NEGATIVE);
    dialog->setContentText("Are you sure you want to quit the game?");
    Director::getInstance()->getRunningScene()->addChild(dialog, 9999, 9999);
    dialog->setPosition(Director::getInstance()->getVisibleOrigin());
    dialog->onPositiveClick = [=](void*){
        STSystemFunction st;
        st.endAnalytics();
        Director::getInstance()->end();
    };
    
}