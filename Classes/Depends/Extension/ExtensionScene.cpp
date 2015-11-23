
#include "ExtensionScene.h"
//#include "AdsManager.h"
#include "SceneManager.h"

ExtensionScene::ExtensionScene()
{
    m_pGuideLayer = nullptr;
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ExtensionScene::onShopItemBuy), ItemBuySuccessNotify, NULL);
}

ExtensionScene::~ExtensionScene()
{
    
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    __NotificationCenter::getInstance()->removeAllObservers(this);
}

bool ExtensionScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    m_pBGLayer = Layer::create();
    m_pBGLayer->setZOrder(0);
    this->addChild(m_pBGLayer);
    
    m_pContentLayer = Layer::create();
    m_pContentLayer->setZOrder(100);
    this->addChild(m_pContentLayer);
    
    m_pUILayer = Layer::create();
    m_pUILayer->setZOrder(200);
    this->addChild(m_pUILayer);
    
    m_pGameUI = GameUILayoutLayer::create();
    this->addChildToUILayer(m_pGameUI);
    m_pGameUI->setLocalZOrder(10);
    m_pGameUI->onButtonClicked = CC_CALLBACK_1(ExtensionScene::onButtonCallback, this);
//    m_pGameUI->showNextLayout();
    return true;
}

void ExtensionScene::onEnter()
{
    Layer::onEnter();
    
    if (!UserDefault::getInstance()->getBoolForKey("removeAds")){
//        AdsManager::getInstance()->showAds(kTypeBannerAds);
    }
}

void ExtensionScene::onExit()
{
    Layer::onExit();
}


void ExtensionScene::onButtonCallback(Button* btn)
{
    int tag = btn->getTag();

    
    if (eUIButtonTagBack==tag){
        AudioHelp::getInstance()->playPreviousEffect();
        SceneManager::popScene();
    }else if (eUIButtonTagFav==tag){
        
    }else if (eUIButtonTagNext==tag) {
        AudioHelp::getInstance()->stopLoopEffect();
        
        AudioHelp::getInstance()->stopFryEffect();
        AudioHelp::getInstance()->playNextEffect();
        switch (m_nNextSceneTag) {
            case eSceneTagDecorate:
                SceneManager::replaceTheScene<DecorateScene>();
                break;
            case eSceneTagShare:
            {
//                if (!UserDefault::getInstance() -> getBoolForKey("removeAds")){
//                    AudioHelp::getInstance()->pauseBackGroundMusic();
//                    AdsManager::getInstance()->setVisiable(kTypeBannerAds,false);
//                    AdLoadingLayerBase::showLoading<AdsLoadingScene>(true);
//                    AdLoadingLayerBase::s_currentInstance->loadingDoneCallback = [=](){
//                        AudioHelp::getInstance()->resumeBackGroundMusic();
//                        AdsManager::getInstance()->setVisiable(kTypeBannerAds,true);
//                        SceneManager::pushTheScene<ShareScene>();
//                    };
//                }else{
                    SceneManager::pushTheScene<ShareScene>();
//                }
            }
                break;
            default:
                break;
        }
    }
}


// 添加一个Node到背景层
void ExtensionScene::addChildToBGLayer(Node* child)
{
    m_pBGLayer->addChild(child);
}

// 添加一个Node到UI层
void ExtensionScene::addChildToUILayer(Node* child)
{
    m_pUILayer->addChild(child);
}

// 添加一个Node到内容层
void ExtensionScene::addChildToContentLayer(Node* child)
{
    m_pContentLayer->addChild(child);
}



DragNode* ExtensionScene::_createDrageNode(std::string path,bool enable)
{
    DragNode* pTool = DragNode::create(path);
    pTool->setLimitRect(Rect(0, 90, visibleSize.width, visibleSize.height));
    pTool->setTouchEnabled(enable);
    pTool->dragNodeTouchBegin = CC_CALLBACK_2(ExtensionScene::dragNodeTouchBegin, this);
    pTool->dragNodeTouchMoved = CC_CALLBACK_2(ExtensionScene::dragNodeTouchMoved, this);
    pTool->dragNodeTouchEnded = CC_CALLBACK_2(ExtensionScene::dragNodeTouchEnded, this);
    pTool->dragNodeClicked = CC_CALLBACK_2(ExtensionScene::dragNodeClicked, this);
    return pTool;
    
}
