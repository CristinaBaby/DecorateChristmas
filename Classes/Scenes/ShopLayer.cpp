
#include "ShopLayer.h"
#include "SceneManager.h"


ShopLayer::ShopLayer()
{
    m_InnerPosition = Vec2::ZERO;
    m_bIsScrolling = false;
    shopDismissed = nullptr;
    m_nPercent = 0;
}

ShopLayer::~ShopLayer()
{
    
}
bool ShopLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    _initData();
    
    LayerColor* color = LayerColor::create(Color4B(0, 0, 0, 160));
    this->addChild(color);
    
    //    bg
    Sprite* pBg = Sprite::create(localPath("bg.png"));
    pBg->setPosition(visibleSize*0.5);
    this->addChild(pBg);
    
    Sprite* pLogo = Sprite::create(localPath("logo.png"));
    CMVisibleRect::setPositionAdapted(pLogo, 480, 580+visibleSize.height);
    this->addChild(pLogo);
    
    Button* pCloseBtn = Button::create(localPath("btn_close.png"));
    pCloseBtn->addTouchEventListener([=](Ref* ref,Widget::TouchEventType type){
        if (type==Widget::TouchEventType::ENDED) {
            pCloseBtn->setEnabled(false);
            _dismiss();
        }
    });
    this->addChild(pCloseBtn);
    CMVisibleRect::setPositionAdapted(pCloseBtn, 850, 570);
    
    Button* pRestoreBtn = Button::create(localPath("btn_restore.png"));
    pRestoreBtn->addTouchEventListener([=](Ref* ref,Widget::TouchEventType type){
        if (type==Widget::TouchEventType::ENDED) {
            ShopAdapter::getInstance()->requestRestore();
        }
    });
    this->addChild(pRestoreBtn);
    CMVisibleRect::setPositionAdapted(pRestoreBtn, 480, 120);
    
    Button* pNextBtn = Button::create(localPath("btn_next.png"));
    pNextBtn->addTouchEventListener([=](Ref* ref,Widget::TouchEventType type){
        if (type==Widget::TouchEventType::ENDED) {
            int percent = getPercent();
            if (percent>100) {
                percent = 0;
            }
            m_pScrollView->scrollToPercentHorizontal(percent, 1, true);
            m_nPercent = percent;
        }
    });
    
    pBg->addChild(pNextBtn);
    pNextBtn->setPosition(Vec2(780, 220));
    
    Button* pPreBtn = Button::create(localPath("btn_back.png"));
    pPreBtn->addTouchEventListener([=](Ref* ref,Widget::TouchEventType type){
        if (type==Widget::TouchEventType::ENDED) {
            float offsetX = m_pScrollView->getInnerContainerSize().width*m_nPercent/100;
            float percent = (offsetX-m_pScrollView->getContentSize().width)*100/m_pScrollView->getInnerContainerSize().width;
            if (percent<100) {
                percent = 0;
            }
            m_pScrollView->scrollToPercentHorizontal(percent, 1, true);
            m_nPercent = percent;
        }
    });
    pBg->addChild(pPreBtn);
    pPreBtn->setPosition(Vec2(70, 220));
    
    m_pScrollView = ExpandScrollView::create();
    pBg->addChild(m_pScrollView);
    m_pScrollView->setContentSize(Size(pBg->getContentSize().width-190, pBg->getContentSize().width-200));
    m_pScrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
    m_pScrollView->setPosition(Vec2(90, 50));
    int count = ConfigManager::getInstance()->getIapDataVector().size();
    Rect visibleRect = m_pScrollView->getBoundingBox();
    visibleRect.origin = m_pScrollView->getParent()->convertToWorldSpace(visibleRect.origin);
    
    for (int i = 0; i<count; i++) {
        IAPConfigData data = ConfigManager::getInstance()->getIapData(i);
        IAPItem* pItem = IAPItem::create();
        pItem->initWithName(localPath(data.iconName), localPath("btn_buy.png"));
        m_pScrollView->addChild(pItem);
        pItem->setPosition(Vec2(115+225*i, 190));
        pItem->setTag(i);
        pItem->visibleWorldRect = visibleRect;
        if (i==0) {
            Sprite* pSprite = Sprite::create("content/shop/bg_bestdeal_food.png");
            pItem->addChild(pSprite);
            pSprite->setPosition(Vec2(0, 50));
            pSprite->runAction(RepeatForever::create(Sequence::create(EaseBounceOut::create(ScaleTo::create(0.5, 1.1)),
                                                                      ScaleTo::create(0.3, 1),
                                                                      DelayTime::create(0.5), NULL)));
            
            Sprite* pNoads = Sprite::create("content/shop/noads.png");
            pItem->addChild(pNoads);
            pNoads->setPosition(Vec2(70, 120));
            
            ParticleSystemQuad* pParticle = ParticleSystemQuad::create("particle/dress.plist");
            pItem->addChild(pParticle);
            pParticle->setPosition(Vec2::ZERO);
            
        }
        pItem->setTag(i);
        pItem->onItemClicked = CC_CALLBACK_1(ShopLayer::onItemClicked, this);
        m_ItemVector.pushBack(pItem);
    }
    m_pScrollView->setInnerContainerSize(Size(115+225*count, m_pScrollView->getContentSize().height));

    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch *pTouch, Event *pEvent){
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    _showScrollBottom();
    pLogo->runAction(EaseBackOut::create(MoveBy::create(0.5, Vec2(0, -visibleSize.height))));
    pBg->runAction(Sequence::create(DelayTime::create(0.5),
                                    ScaleTo::create(0.1, 1,0.9),
                                    EaseBackIn::create(ScaleTo::create(0.2,1)),
                                    CallFunc::create([=]()
                                                     {
                                                         
                                                     }),
                                    NULL));
    return true;
}

void ShopLayer::onEnter()
{
    Layer::onEnter();
    
    if (!UserDefault::getInstance()->getBoolForKey("removeAds")){
//        AdsManager::getInstance()->setVisiable(kTypeBannerAds, false);
        
    }
}

int ShopLayer::getPercent()
{
    float offsetX = -m_pScrollView->getInnerContainer()->getPositionX();
    m_nPercent = (offsetX+m_pScrollView->getContentSize().width)*100/m_pScrollView->getInnerContainerSize().width;
    return m_nPercent;
}

#pragma mark - initData
void ShopLayer::_initData()
{
    
    setExPath("content/shop/");
}

void ShopLayer::_showScrollBottom()
{
    m_pScrollView->scrollToPercentHorizontal(100, 2, true);
    this->runAction(Sequence::create(DelayTime::create(2.2),
                                     CallFunc::create([=]()
                                                      {
                                                          m_pScrollView->scrollToPercentHorizontal(0, 1, true);
                                                      }),
                                     NULL));
}

void ShopLayer::_showScrollBottomBack()
{
//    m_pPageView->scrollToTop(1, true);
//    m_pPageView->scrollToPage(0);
}

void ShopLayer::_dismiss()
{
    if (shopDismissed) {
        shopDismissed();
    }
    this->removeFromParent();
}
void ShopLayer::onItemClicked(int index)
{
//    if (m_pPageView->isScrolled()) {
//        return;
//    }
    if (m_pScrollView->isScrolled()) {
        return;
    }
    ShopAdapter::getInstance()->requestBuyItem(ConfigManager::getInstance()->getIapData(index).iapId);
}
