#include "MakeEatLayer.h"
#include "Heads.h"

bool MakeEatLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    m_nAlphaPercent = 100;
    m_nCurPercent = 0;
    return true;
}

void MakeEatLayer::onEnter()
{
    Layer::onEnter();
    
}

void MakeEatLayer::doEat(Vec2 point)
{
    if (m_pRenderTexture&&m_pShapeSprite) {
        m_pShapeSprite->setBlendFunc({GL_ZERO,GL_ONE_MINUS_SRC_ALPHA});
        point = m_pRenderTexture->convertToNodeSpace(point);
        point = Vec2(point.x+m_pRenderTexture->getSprite()->getContentSize().width*0.5, point.y+m_pRenderTexture->getSprite()->getContentSize().height*0.5);
        m_pShapeSprite->setPosition(point);
        m_pRenderTexture->begin();
        m_pShapeSprite->visit();
        m_pRenderTexture->end();
        Director::getInstance()->getRenderer()->render();
        
        __NotificationCenter::getInstance()->removeObserver(m_pRenderTexture, EVENT_COME_TO_BACKGROUND);
        __NotificationCenter::getInstance()->removeObserver(m_pRenderTexture, EVENT_COME_TO_FOREGROUND);

        
        if (m_pDelegate&& m_pFunc) {
            (m_pDelegate->*m_pFunc)();
        }
        m_nCurPercent = m_pRenderTexture->getPercentageTransparent();
        
//        AudioHelp::getInstance()->playEffect("basic/eat.mp3");
//        ParticleSystemQuad* pParticle = ParticleSystemQuad::create("particle/biting.plist");
//        this->addChild(pParticle);
//        pParticle->setPosition(point);
    }
    
}
