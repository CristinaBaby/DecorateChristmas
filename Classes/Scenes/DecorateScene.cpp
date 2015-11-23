
#include "DecorateScene.h"
#include "SceneManager.h"
#include "ShopLayer.h"

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
DecorateScene::DecorateScene()
{
    m_pDecorationScrollView = nullptr;
}

DecorateScene::~DecorateScene()
{
    
}
bool DecorateScene::init()
{
    if ( !ExtensionScene::init() )
    {
        return false;
    }
    _initData();
    
    //    bg
//    m_pBg = Sprite::create(localPath("dec/bg.jpg"));
//    m_pBg->setPosition(visibleSize*0.5);
//    this->addChildToBGLayer(m_pBg);
    
    
    m_pTypeScrollView = DecTypeScrollView::createWithSize(Size(160,580));
    this->addChildToUILayer(m_pTypeScrollView);
    CMVisibleRect::setPositionAdapted(m_pTypeScrollView, 0, 30,kBorderLeft);
    m_pTypeScrollView->onItemCellSelected = CC_CALLBACK_3(DecorateScene::onTypeCallback, this);
    m_pTypeScrollView->btnPathEX = "content/category/icon/";
    m_pTypeScrollView->setLocalZOrder(10);
    m_pTypeScrollView->setDirection(DecTypeScrollView::Direction::eDirectionV);
    
    _initDefaultDecorate();
    
    m_pGameUI->showNextLayout();
    m_pGameUI->showResetLayout();
    
    m_nNextSceneTag = eSceneTagShare;
    return true;
}

#pragma mark - initData
void DecorateScene::_initData()
{
    m_nPackage = GameDataManager::getInstance()->m_nPackage;
    setExPath("content/");
    
}

void DecorateScene::_initDefaultDecorate()
{
    DecorateManager* pDecManager = DecorateManager::getInstance();
    
    if (m_nPackage==0) {
        pDecManager->initWithParent(this->m_pContentLayer, eDecorateTypeFood);
        pDecManager->addDecoration(Sprite::create(localPath("dec/bowl.png")), eDecorationLayerFoodBack,"bowl",Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
        pDecManager->addDecoration(Sprite::create(localPath("dec/macaroni.png")), eDecorationLayerFood,"",visibleSize*0.5);
        
        m_pTypeScrollView->loadType(ConfigManager::getInstance()->getDecorateType("tree"));
    }
    
}

void DecorateScene::_reset()
{
    DecorateManager::getInstance()->reset();
    _initDefaultDecorate();
    m_pBg->setTexture(Sprite::create(localPath("dec/bg.jpg"))->getTexture());
    GameDataManager::getInstance()->m_nBgIndex = -1;
}

void DecorateScene::onButtonCallback(Button* btn)
{
    ExtensionScene::onButtonCallback(btn);
    int tag = btn->getTag();
    
    if (eUIButtonTagNext==tag){
//        if (m_pTypeScrollView->getPercent()>=100) {
//        }else{
//            m_pTypeScrollView->scrollToNext();
//        }
        
    }else if (eUIButtonTagBack==tag){
//        m_pTypeScrollView->scrollToPre();
        
    }else if (eUIButtonTagReset==tag){
        btn->setEnabled(false);
        Dialog* dialog=Dialog::create(Size(450,300), (void*)&MENU_TYPE_1, Dialog::DIALOG_TYPE_NEGATIVE);
        dialog->setContentText("Are you sure you want to reset your food?");
        Director::getInstance()->getRunningScene()->addChild(dialog, 9999, 9999);
        dialog->setPosition(Director::getInstance()->getVisibleOrigin());
        dialog->onPositiveClick = [=](void*){
            btn->setEnabled(true);
            _reset();
        };
        dialog->onNegativeClick = [=](void*){
            btn->setEnabled(true);
            
        };
    }
    
}
void DecorateScene::onTypeCallback(int index,std::string typeName,bool selected)
{
    m_sCurTypeStr = string(typeName);
    AudioHelp::getInstance()->playSelectedEffect();
    if (selected) {
        std::stringstream ostr;
        ostr.str("");
        ostr<<"content/category/"<<m_sCurTypeStr<<"_icon/";
        if (!m_pDecorationScrollView) {
            m_pDecorationScrollView = ItemScrollView::createWithSize(Size(145, 560));
            this->addChildToUILayer(m_pDecorationScrollView);
            
            m_pDecorationScrollView->decorationData = ConfigManager::getInstance()->getDecorateFile(m_sCurTypeStr);
            m_pDecorationScrollView->onItemCellSelected = CC_CALLBACK_2(DecorateScene::onDecorationCallback, this);
        }else{
            m_pDecorationScrollView->decorationData = ConfigManager::getInstance()->getDecorateFile(m_sCurTypeStr);
        }
        m_pDecorationScrollView->stopAllActions();
        CMVisibleRect::setPositionAdapted(m_pDecorationScrollView, 135-visibleSize.width/2, 40,kBorderLeft);
        m_pDecorationScrollView->runAction(EaseBackIn::create(MoveBy::create(0.5, Vec2(visibleSize.width/2, 0))));
        m_pDecorationScrollView->btnPathEX = ostr.str();
        m_pDecorationScrollView->bgPath = "content/category/icon/bg2.png";
        m_pDecorationScrollView->reloadData();
    }else{
        if (m_pDecorationScrollView) {
            m_pDecorationScrollView->removeFromParent();
            m_pDecorationScrollView = nullptr;
        }
    }
}
void DecorateScene::onDecorationCallback(int index,DecorateConfigData decData)
{
    m_pTypeScrollView->setNormal();
    if (m_pDecorationScrollView) {
        m_pDecorationScrollView->removeFromParent();
        m_pDecorationScrollView = nullptr;
    }
    if (!gNoneIap) {
        if (index>=decData.freeCount+decData.beginIndex && !(index<decData.totalCount+decData.beginIndex && index>=decData.holidayIndex && decData.holidayIndex>=0 && decData.holidayCount==0)){
            //        SceneManager::pushTheScene<ShopScene>();
            
            ShopLayer* pLayer = ShopLayer::create();
            this->addChildToUILayer(pLayer);
            pLayer->setLocalZOrder(100);
            pLayer->shopDismissed = [=]()
            {
                if (!UserDefault::getInstance()->getBoolForKey("removeAds")){
//                    AdsManager::getInstance()->setVisiable(kTypeBannerAds, true);
                    
                }
            };
            return;
        }
    }
    AudioHelp::getInstance()->playSelectedEffect();
    std::stringstream ostr;
    ostr<<"content/category/"<<m_sCurTypeStr<<"/"<<index<<".png";
    
    if (std::strcmp(m_sCurTypeStr.c_str(), "background")==0){
        std::stringstream ostr;
        ostr<<"content/category/"<<m_sCurTypeStr<<"/"<<index<<".png";
        m_pBg->setTexture(ostr.str());
        GameDataManager::getInstance()->m_nBgIndex = index;
        return;
    }
    
    
    ParticleSystemQuad* pParticle = ParticleSystemQuad::create("particle/cleanend.plist");
    this->addChildToUILayer(pParticle);
    
    if (std::strcmp(m_sCurTypeStr.c_str(), "bowl")==0) {
        Sprite* unit = Sprite::create(ostr.str());
        DecorateManager::getInstance()->addDecoration(unit, eDecorationLayerFoodBack,decData.single?m_sCurTypeStr:"",Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
        pParticle->setPosition(unit->getPosition());
    }else if (std::strcmp(m_sCurTypeStr.c_str(), "drink")==0) {
        Sprite* unit = Sprite::create(ostr.str());
        DecorateManager::getInstance()->addDecoration(Sprite::create("content/category/drink/cup1.png"), eDecorationLayerDrinkBack,"cupBack",Vec2(visibleSize.width*0.9, visibleSize.height*0.7));
        DecorateManager::getInstance()->addDecoration(unit, eDecorationLayerDrink,decData.single?m_sCurTypeStr:"",Vec2(visibleSize.width*0.9, visibleSize.height*0.7));
        DecorateManager::getInstance()->addDecoration(Sprite::create("content/category/drink/cup0.png"), eDecorationLayerDrinkFront,"cupFront",Vec2(visibleSize.width*0.9, visibleSize.height*0.7));
        pParticle->setPosition(unit->getPosition());
    }else{
        if (decData.zoomable||decData.rotatable) {
            if (decData.eatable) {
                FillMaterialModel* unit = FillMaterialModel::create(ostr.str());
                DecorateManager::getInstance()->addDecoration(unit, eDecorationLayerAllFront,decData.single?m_sCurTypeStr:"",visibleSize*0.5);
                pParticle->setPosition(unit->getPosition());
            }else{
                FillMaterialModel* unit = FillMaterialModel::create(ostr.str());
                DecorateManager::getInstance()->addDecoration(unit, eDecorationLayerFoodFront,decData.single?m_sCurTypeStr:"",visibleSize*0.5);
                pParticle->setPosition(unit->getPosition());
            }
        }else{
            if (decData.eatable) {
                Sprite* unit = Sprite::create(ostr.str());
                DecorateManager::getInstance()->addDecoration(unit, eDecorationLayerAllFront,decData.single?m_sCurTypeStr:"",visibleSize*0.5);
                pParticle->setPosition(unit->getPosition());
            }else{
                Sprite* unit = Sprite::create(ostr.str());
                DecorateManager::getInstance()->addDecoration(unit, eDecorationLayerAllFront,decData.single?m_sCurTypeStr:"",visibleSize*0.5);
                pParticle->setPosition(unit->getPosition());
            }
        }
    }
    
}