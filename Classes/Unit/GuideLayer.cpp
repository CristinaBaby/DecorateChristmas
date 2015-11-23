
#include "GuideLayer.h"
GuideLayer::GuideLayer()
{
    m_pGuide = nullptr;
}

GuideLayer::~GuideLayer()
{
}
bool GuideLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    return true;
}

void GuideLayer::showGuideMove(Vec2 begin,Vec2 end)
{
    if (m_pGuide) {
        m_pGuide->removeFromParent();
    }
    m_pGuide = Sprite::create("content/common/make/hand.png");
    this->addChild(m_pGuide);
    
    m_pGuide->setPosition(begin);
    m_pGuide->setVisible(true);
    m_pGuide->setAnchorPoint(Vec2(0, 0.5));
    
    m_pGuide->runAction(RepeatForever::create(Sequence::create(MoveTo::create(1, end),
                                                               DelayTime::create(0.5f),
                                                               CallFunc::create([=]()
                                                                                {
                                                                                    m_pGuide->setVisible(false);
                                                                                    m_pGuide->setPosition(begin);
                                                                                }),
                                                               DelayTime::create(3),
                                                               CallFunc::create([=]()
                                                                                {
                                                                                    m_pGuide->setVisible(true);
                                                                                }),
                                                               NULL)));

}
void GuideLayer::showGuideTapVertical(Vec2 position)
{
    if (m_pGuide) {
        m_pGuide->removeFromParent();
    }
    m_pGuide = Sprite::create("content/common/make/hand.png");
    this->addChild(m_pGuide);
    m_pGuide->setPosition(position);
    m_pGuide->setVisible(true);
    m_pGuide->setAnchorPoint(Vec2(0, 0.5));
    m_pGuide->runAction(RepeatForever::create(Sequence::create(EaseSineOut::create(MoveBy::create(1, Vec2(0, 50))),
                                                               MoveBy::create(1, Vec2(0, -50)),
                                                               EaseSineOut::create(MoveBy::create(1, Vec2(0, 50))),
                                                               MoveBy::create(1, Vec2(0, -50)),
                                                               CallFunc::create([=]()
                                                                                {
                                                                                    m_pGuide->setVisible(false);
                                                                                }),
                                                               DelayTime::create(3),
                                                               CallFunc::create([=]()
                                                                                {
                                                                                    m_pGuide->setVisible(true);
                                                                                }),
                                                               NULL)));
}
void GuideLayer::showGuideTapHorizonal(Vec2 position)
{
    if (m_pGuide) {
        m_pGuide->removeFromParent();
    }
    m_pGuide = Sprite::create("content/common/make/hand.png");
    this->addChild(m_pGuide);
    m_pGuide->setPosition(position);
    m_pGuide->setVisible(true);
    m_pGuide->setAnchorPoint(Vec2(0, 0.5));
    m_pGuide->runAction(RepeatForever::create(Sequence::create(EaseSineOut::create(MoveBy::create(1, Vec2(50, 0))),
                                                               MoveBy::create(1, Vec2(-50, 0)),
                                                               EaseSineOut::create(MoveBy::create(1, Vec2(50, 0))),
                                                               MoveBy::create(1, Vec2(-50, 0)),
                                                               CallFunc::create([=]()
                                                                                {
                                                                                    m_pGuide->setVisible(false);
                                                                                }),
                                                               DelayTime::create(3),
                                                               CallFunc::create([=]()
                                                                                {
                                                                                    m_pGuide->setVisible(true);
                                                                                }),
                                                               NULL)));
    
}
void GuideLayer::showGuideShake(Vec2 position)
{
    if (m_pGuide) {
        m_pGuide->removeFromParent();
    }
    m_pGuide = Sprite::create("content/common/make/shake.png");
    this->addChild(m_pGuide);
    m_pGuide->setPosition(position);
    m_pGuide->setVisible(true);
    
    m_pGuide->runAction(RepeatForever::create(Sequence::create(Spawn::create(EaseSineOut::create(MoveBy::create(1, Vec2(50, 0))),
                                                                             RotateTo::create(1, 10),
                                                                             NULL),
                                                               Spawn::create(MoveBy::create(1, Vec2(-100, 0)),
                                                                             RotateTo::create(1, -10),
                                                                             NULL),
                                                               Spawn::create(MoveBy::create(1, Vec2(50, 0)),
                                                                             RotateTo::create(1, 0),
                                                                             NULL),
                                                               CallFunc::create([=]()
                                                                                {
                                                                                    m_pGuide->setVisible(false);
                                                                                }),
                                                               DelayTime::create(3),
                                                               CallFunc::create([=]()
                                                                                {
                                                                                    m_pGuide->setVisible(true);
                                                                                }),
                                                               NULL)));
    
}
void GuideLayer::showGuideRotateRight(Vec2 position)
{
    if (m_pGuide) {
        m_pGuide->removeFromParent();
    }
    m_pGuide = Sprite::create("content/common/make/hand.png");
    this->addChild(m_pGuide);
    m_pGuide->setPosition(position);
    m_pGuide->setVisible(true);
    
    m_pGuide->runAction(RepeatForever::create(Sequence::create(
                                                               RotateTo::create(1, 30),
                                                               DelayTime::create(1),
                                                               RotateTo::create(1, 0),
                                                               DelayTime::create(3),
                                                               CallFunc::create([=]()
                                                                                {
                                                                                    m_pGuide->setVisible(true);
                                                                                }),
                                                               NULL)));
}
    
void GuideLayer::showGuideRotateLeft(Vec2 position)
{
    if (m_pGuide) {
        m_pGuide->removeFromParent();
    }
    m_pGuide = Sprite::create("content/common/make/hand.png");
    this->addChild(m_pGuide);
    m_pGuide->setPosition(position);
    m_pGuide->setVisible(true);
    
    m_pGuide->runAction(RepeatForever::create(Sequence::create(
                                                               RotateTo::create(1, -30),
                                                               DelayTime::create(1),
                                                               RotateTo::create(1, 0),
                                                               DelayTime::create(3),
                                                               CallFunc::create([=]()
                                                                                {
                                                                                    m_pGuide->setVisible(true);
                                                                                }),
                                                               NULL)));
}

void GuideLayer::showGuideMix(Vec2 position)
{
    if (m_pGuide) {
        m_pGuide->removeFromParent();
    }
    m_pGuide = Sprite::create("content/common/make/arrow.png");
    this->addChild(m_pGuide);
    m_pGuide->setPosition(position);
    m_pGuide->setVisible(true);
    
    m_pGuide->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.5),
                                                               DelayTime::create(2),
                                                               FadeOut::create(0.5),
                                                               DelayTime::create(5),
                                                               NULL)));
}

void GuideLayer::removeGuide()
{
    if (m_pGuide) {
        m_pGuide->removeFromParent();
    }
    m_pGuide = nullptr;
}