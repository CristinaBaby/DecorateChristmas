
#include "GameUILayoutLayer.h"
#include "Heads.h"

GameUILayoutLayer::GameUILayoutLayer()
{
    m_pHomeStart = nullptr;
    m_pHomeRestore = nullptr;
    m_pHomeMore = nullptr;
    m_pHomeFav = nullptr;
    m_pHomeShop = nullptr;
    
    m_pNext = nullptr;
    m_pBack = nullptr;
    m_pReset = nullptr;
    
    m_pFav = nullptr;
    m_pEmail = nullptr;
    m_pHome = nullptr;
    m_pEatAgain = nullptr;
    
    onButtonClicked = nullptr;
}

GameUILayoutLayer::~GameUILayoutLayer()
{
    
}
bool GameUILayoutLayer::init()
{
    if ( !Node::init() )
    {
        return false;
    }

    return true;
}

void GameUILayoutLayer::showHomeUILayout(bool animate)
{
    if (!m_pHomeMore) {
        m_pHomeMore = _createButton("content/start/btn_more.png");
        this->addChild(m_pHomeMore);
    }
    if (!m_pHomeShop) {
        m_pHomeShop = _createButton("content/start/btn_shop.png");
        this->addChild(m_pHomeShop);
    }
    if (!m_pHomeStart) {
        m_pHomeStart = _createButton("content/start/home_btn_play.png");
        this->addChild(m_pHomeStart);
    }
    
    m_pHomeStart->setTag(eUIButtonTagHomeStart);
    m_pHomeMore->setTag(eUIButtonTagHomeMore);
    m_pHomeShop->setTag(eUIButtonTagHomeShop);
    
    if (gNoneIap) {
        m_pHomeShop->setEnabled(false);
        m_pHomeShop->setVisible(false);
    }
    if (!animate) {
        CMVisibleRect::setPositionAdapted(m_pHomeMore, 894, 48,kBorderRight,kBorderBottom);
        CMVisibleRect::setPositionAdapted(m_pHomeShop, 794, 48,kBorderRight,kBorderBottom);
        CMVisibleRect::setPositionAdapted(m_pHomeStart, 444, 300);
    }else{
        CMVisibleRect::setPositionAdapted(m_pHomeMore, 894, 48,kBorderRight,kBorderBottom);
        CMVisibleRect::setPositionAdapted(m_pHomeShop, 794, 48,kBorderRight,kBorderBottom);
        CMVisibleRect::setPositionAdapted(m_pHomeStart, 444, 300);

        m_pHomeStart->setEnabled(false);
        m_pHomeMore->setEnabled(false);
        m_pHomeShop->setEnabled(false);
        
        m_pHomeMore->setOpacity(0);
        m_pHomeShop->setOpacity(0);
        
        _showHomeButtonAnimation(m_pHomeMore,0.5,1.2);
        if (!gNoneIap) {
            _showHomeButtonAnimation(m_pHomeShop,0.5,1.5);
        }
        
        m_pHomeStart->runAction(Sequence::create(DelayTime::create(2),
                                                 ScaleTo::create(0.5, 1),
                                                 CallFunc::create([=]()
                                                                  {
                                                                      m_pHomeStart->setEnabled(true);
                                                                      m_pHomeStart->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5, 1),
                                                                                                                                     DelayTime::create(0.5),
                                                                                                                                     EaseBackOut::create(ScaleTo::create(0.5, 1.2)),
                                                                                                                                     NULL)));
                                                                  }),
                                            NULL));
    }
}

void GameUILayoutLayer::showMakeUILayout(bool animate)
{
    showNextLayout(animate);
    showBackLayout(animate);
}

void GameUILayoutLayer::showNextLayout(bool animate)
{
    if (!m_pNext) {
        m_pNext = _createButton("content/common/btn_next.png");
        this->addChild(m_pNext);
    }
    m_pNext->setVisible(true);
    m_pNext->setEnabled(true);
    
    m_pNext->setTag(eUIButtonTagNext);
    
    m_pNext->stopAllActions();
    m_pNext->setRotation(0);
    
    if (!animate) {
        CMVisibleRect::setPositionAdapted(m_pNext, 900, 580,kBorderRight,kBorderTop);
    }else{
        CMVisibleRect::setPositionAdapted(m_pNext, 900, 580,kBorderRight,kBorderTop);
        m_pNext->runAction(RepeatForever::create(Sequence::create(EaseBounceIn::create(ScaleTo::create(0.5, 1.1)),
                                                                  ScaleTo::create(0.5, 1),
                                                                  DelayTime::create(2),
                                                                  NULL)));
    }
    
}

void GameUILayoutLayer::showBackLayout(bool animate)
{
    if (!m_pBack) {
        m_pBack = _createButton("content/common/btn_back.png");
        this->addChild(m_pBack);
    }
    
    m_pBack->setVisible(true);
    m_pBack->setEnabled(true);
    m_pBack->setTag(eUIButtonTagBack);
    
    m_pBack->stopAllActions();
    m_pBack->setRotation(0);
    
    if (!animate) {
        CMVisibleRect::setPositionAdapted(m_pBack, 58, 580,kBorderLeft,kBorderTop);
    }else{
        CMVisibleRect::setPositionAdapted(m_pBack, 58, 580,kBorderLeft,kBorderTop);
        m_pBack->runAction(RepeatForever::create(Sequence::create(EaseBounceIn::create(ScaleTo::create(0.5, 1.1)),
                                                                  ScaleTo::create(0.5, 1),
                                                                  DelayTime::create(2),
                                                                  NULL)));
    }
    
}

void GameUILayoutLayer::showResetLayout(bool animate)
{
    if (!m_pReset) {
        m_pReset = _createButton("content/common/btn_reset.png");
        this->addChild(m_pReset);
    }
    m_pReset->setVisible(true);
    m_pReset->setEnabled(true);
    
    m_pReset->setTag(eUIButtonTagReset);
    
    m_pReset->stopAllActions();
    m_pReset->setRotation(0);
    
    if (!animate) {
        CMVisibleRect::setPositionAdapted(m_pReset, 900, 476,kBorderRight,kBorderTop);
    }else{
        CMVisibleRect::setPositionAdapted(m_pReset, 900, 476,kBorderRight,kBorderTop);
        m_pReset->runAction(RepeatForever::create(Sequence::create(EaseBounceIn::create(JumpBy::create(3, Vec2::ZERO, 10, 1)),
                                                                  DelayTime::create(5),
                                                                  NULL)));
    }
    
}

void GameUILayoutLayer::showEatAgainLayout(bool isDrink,bool animate)
{
    if (!m_pEatAgain) {
        if (isDrink) {
            m_pEatAgain = _createButton("content/common/btn_again0.png");
        }else{
            m_pEatAgain = _createButton("content/common/btn_again0.png");
        }
        this->addChild(m_pEatAgain);
    }
    
    m_pEatAgain->setVisible(true);
    m_pEatAgain->setEnabled(true);
    m_pEatAgain->setTag(eUIButtonTagEatAgain);
    
    m_pEatAgain->stopAllActions();
    m_pEatAgain->setRotation(0);
    
    if (!animate) {
        CMVisibleRect::setPositionAdapted(m_pEatAgain, 480, 320);
    }else{
        CMVisibleRect::setPositionAdapted(m_pEatAgain, 480, 320);
        m_pEatAgain->runAction(RepeatForever::create(Sequence::create(EaseBounceIn::create(ScaleTo::create(1, 1.1)),
                                                                      DelayTime::create(1),
                                                                      ScaleTo::create(1, 1),
                                                                      NULL)));
    }
    
}


void GameUILayoutLayer::showDecorateUILayout(bool animate)
{
    
}

void GameUILayoutLayer::showShareUILayout(bool animate)
{
    if (!m_pFav) {
        m_pFav = _createButton("content/common/btn_fav.png");
        this->addChild(m_pFav);
    }
//    if (!m_pEmail) {
//        m_pEmail = _createButton("content/common/icon/public_btn_email.png");
//        this->addChild(m_pEmail);
//    }
    if (!m_pHome) {
        m_pHome = _createButton("content/common/btn_home.png");
        this->addChild(m_pHome);
    }
    CMVisibleRect::setPositionAdapted(m_pFav, 900, 480,kBorderRight,kBorderTop);
//    CMVisibleRect::setPositionAdapted(m_pEmail, 320, 160,kBorderNone,kBorderBottom);
    CMVisibleRect::setPositionAdapted(m_pHome, 900, 580,kBorderRight,kBorderTop);

    m_pFav->setTag(eUIButtonTagFav);
//    m_pEmail->setTag(eUIButtonTagEmail);
    m_pHome->setTag(eUIButtonTagHome);
    
//    showNextLayout(false);
    showBackLayout(false);
}

void GameUILayoutLayer::_showHomeButtonAnimation(cocos2d::ui::Button *pButton,float duration,float delay)
{
    pButton->runAction(Sequence::create(DelayTime::create(delay),
                                        EaseBounceOut::create(FadeIn::create(duration)),
                                        CallFunc::create([=]()
                                                        {
                                                            pButton->setEnabled(true);
                                                        }),
                                        NULL));
}

void GameUILayoutLayer::_onButtonCallback(Ref* ref,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        if (onButtonClicked) {
            onButtonClicked((Button*)ref);
        }
    }
}

Button* GameUILayoutLayer::_createButton(std::string path)
{
    Button* pBtn = Button::create();
    pBtn->loadTextures(path, path, path);
    pBtn->addTouchEventListener(CC_CALLBACK_2(GameUILayoutLayer::_onButtonCallback, this));
    return pBtn;
}