//
//  FavScene.cpp
//  FMAKER033
//
//  Created by wuguiling on 9/11/14.
//
//

#include "FavScene.h"
#include "SceneManager.h"
#include "AlumnAdapter.h"
#include "Dialog.h"

enum{
    eMenuItemTagBack,
    eMenuItemTagDelete,
    eMenuItemTagDownLoad,
};


enum{
    eAlertTagDelete,
    eAlertTagDownload,
};
static int gAlertTag = 0;
bool FavScene::init()
{
    if (!ExtensionScene::init()) {
        return false;
    }
    
//    Sprite* bgSprite = Sprite::create("shop_fav/fav0.jpg");
//    this->addChildToBGLayer(bgSprite);
//    bgSprite->setAnchorPoint(Vec2(0.5, 1));
//    bgSprite->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height-frame_size.height));
//    Menu *menu = Menu::create();
//    menu->setPosition(Vec2::ZERO);
//    menu->setZOrder(100);
//    addChildToUILayer(menu);
//    m_pMenu = menu;
    
//    m_pBackItemSprite = Utils::getMenuItemSprite("icon_common/btn_back.png", "icon_common/btn_back.png", menu, this, menu_selector(FavScene::_onMenuItemCallback));
//    m_pBackItemSprite->setAnchorPoint(Vec2(0, 0));
//    MyVisibleRect::setPosition(m_pBackItemSprite, 10, 10, eXNearestTypeLeft, eYNearestTypeBottom);
//    m_pBackItemSprite->setTag(eMenuItemTagBack);
//    
//    m_pDeleteItemSprite = Utils::getMenuItemSprite("shop_fav/btn_delete.png", "shop_fav/btn_delete.png", menu, this, menu_selector(FavScene::_onMenuItemCallback));
//    m_pDeleteItemSprite->setAnchorPoint(Vec2(0, 1));
//    MyVisibleRect::setPosition(m_pDeleteItemSprite, visibleSize.width*0.7, 600, eXNearestTypeNone, eYNearestTypeBottom);
//    m_pDeleteItemSprite->setTag(eMenuItemTagDelete);
    
//    m_pDownLoadItemSprite = Utils::getMenuItemSprite("shop_fav/btn_download.png", "shop_fav/btn_download.png", menu, this, menu_selector(FavScene::_onMenuItemCallback));
//    m_pDownLoadItemSprite->setAnchorPoint(Vec2(0, 1));
//    MyVisibleRect::setPosition(m_pDownLoadItemSprite, visibleSize.width*0.7, 220, eXNearestTypeNone, eYNearestTypeBottom);
//    m_pDownLoadItemSprite->setTag(eMenuItemTagDownLoad);
    
    m_pFlowLayer = FlowPageView::create();
    addChildToUILayer(m_pFlowLayer);
    m_pFlowLayer->setPosition(Vec2(0, 100));
    m_pFlowLayer->setContentSize(Size(visibleSize.width, visibleSize.height*0.6));
    int count = AlumnAdapter::getFavCount("tree");
    int totalcount = AlumnAdapter::getFavCount();
    for (int i = 0; i<count; i++) {
        Layout* pPage = Layout::create();
        m_pFlowLayer->addPage(pPage);
        
        string path(AlumnAdapter::getFavIconNameByID(i,"tree"));
        Sprite* item = Sprite::create(path.c_str());
        item->setPosition(Vec2(480, 300));
        pPage->addChild(item);
    }
    
    m_nCurFavTag = 0;
    if (count==0) {
//        m_pDownLoadItemSprite->setVisible(false);
//        m_pDeleteItemSprite->setVisible(false);
    }
    return true;
}

void FavScene::onEnter()
{
    ExtensionScene::onEnter();
//    AdvertiseAdapter::hideBannerAd();
    KeypadDispatchCenter::getInstance()->addDelegate(this);
}

void FavScene::onExit()
{
    KeypadDispatchCenter::getInstance()->removeDelegate(this);
    ExtensionScene::onExit();
}
void FavScene::_onMenuItemCallback(cocos2d::CCMenuItemSprite *item)
{
//    m_pMenu->setEnabled(false);
//    this->scheduleOnce(schedule_selector(FavScene::_setMenuEnable), 0.3);
    int tag = item->getTag();
    switch (tag) {
        case eMenuItemTagBack:
            SceneManager::popScene();
            break;
        case eMenuItemTagDelete:
        {
            gAlertTag = eAlertTagDelete;
            
            Dialog* dialog=Dialog::create(CCSize2(406,280), (void*)&MENU_TYPE_1, Dialog::DIALOG_TYPE_NEGATIVE);
            //            dialog->setTitleText("Delete your Popsicle");
            dialog->setContentText("Are you sure you want to delete your Popsicle?");
//            dialog->setCallback(this);
            addChild(dialog, 9999, 9999);
            dialog->setPosition(Director::getInstance()->getVisibleOrigin());
        }
            break;
        case eMenuItemTagDownLoad:
        {
            gAlertTag = eAlertTagDownload;
            
            Dialog* dialog=Dialog::create(CCSize2(406,280), (void*)&MENU_TYPE_1, Dialog::DIALOG_TYPE_NEGATIVE);
            //            dialog->setTitleText("Save to Photo");
            dialog->setContentText("Do you want to add this Popsicle to your Photo?");
//            dialog->setCallback(this);
            addChild(dialog, 9999, 9999);
            dialog->setPosition(Director::getInstance()->getVisibleOrigin());
        }
            break;
            
        default:
            break;
    }
}

void FavScene::FlowPageWillScroll()
{
    if (AlumnAdapter::getFavCount()<=0) {
        return;
    }
//    m_pDownLoadItemSprite->setVisible(false);
    m_pDeleteItemSprite->setVisible(false);
}

void FavScene::FLowPageDidEndScroll(int tag)
{
    m_nCurFavTag = tag;
    if (AlumnAdapter::getFavCount()<=0) {
        return;
    }
//    m_pDownLoadItemSprite->setVisible(true);
    m_pDeleteItemSprite->setVisible(true);
    
}

void FavScene::onNegativeClick(void *)
{
    
}

void FavScene::onPositiveClick(void *)
{
    
//    CCLog("deleteFavImage  %d",m_nCurFavTag);
//    AlumnAdapter::deleteFavImage(m_nCurFavTag);
//    
//    CCArray* array = CCArray::create();
//    CCSprite* whiteBg = CCSprite::create("UI/shop_fav/photo_frame0.png");
//    int count = AlumnAdapter::getFavCount();
//    
//    CCSize imageSize = CCDirector::sharedDirector()->getVisibleSize()*0.5;
//    float xScale;
//    for (int i = 0; i<count; i++) {
//        CCNode* node = CCNode::create();
//        
//        CCSprite* whiteFrame = CCSprite::createWithTexture(whiteBg->getTexture());
//        
//        CCLog("AlumnAdapter::getFavIconNameByID(i)---%s",AlumnAdapter::getFavIconNameByID(i));
//        string path(AlumnAdapter::getFavIconNameByID(i));
//        CCSprite* item = CCSprite::create(path.c_str());
//        item->setScale(imageSize.width/item->getContentSize().width);
//        
//        xScale = (imageSize.width+30)/whiteFrame->getContentSize().width;
//        float YScale = (imageSize.height+30)/whiteFrame->getContentSize().height;
//        whiteFrame->setScaleX(xScale);
//        whiteFrame->setScaleY(YScale);
//        
//        
//        item->setPosition(whiteFrame->getContentSize()*0.5);
//        whiteFrame->setPosition(whiteFrame->getContentSize()*0.5);
//        
//        node->addChild(whiteFrame);
//        node->addChild(item);
//        node->setContentSize(whiteFrame->getContentSize());
//        
//        
//        array->addObject(node);
//    }
//    m_pFlowLayer->removeFromParent();
//    m_pFlowLayer = NULL;
//    m_pFlowLayer = FlowPageLayer::create(array, CCSize(visibleSize.width,visibleSize.height*0.7),30,0.8);
//    addChildToUILayer(m_pFlowLayer);
//    m_pFlowLayer->setFlowScale(0.5);
//    m_pFlowLayer->setPosition(Vec2(0, 100));
//    m_pFlowLayer->setFlowPageDelegate(this);
//    m_nCurFavTag = 0;
//    if (count==0) {
//        //                m_pDownLoadItemSprite->setVisible(false);
//        m_pDeleteItemSprite->setVisible(false);
//    }
}

void FavScene::onKeyBackClicked()
{
    
    CCLog("=====keyBackClicked");
    m_pMenu->setEnabled(false);
    SceneManager::popScene();
}

