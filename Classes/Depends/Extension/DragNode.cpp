
#include "DragNode.h"

bool DragNode::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    m_bMovable = true;
    return true;
}

DragNode* DragNode::create(const std::string name)
{
    DragNode* node = new DragNode();
    if (node && node->init(name))
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_RELEASE(node);
    return NULL;
}

DragNode* DragNode::createWithSpriteFrameName(const std::string name)
{
    DragNode* node = new DragNode();
    if (node && node->initWithSpriteFrameName(name))
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_RELEASE(node);
    return NULL;
}

DragNode* DragNode::create(cocos2d::Texture2D *texture)
{
    DragNode* node = new DragNode();
    if (node && node->initWithTexture(texture))
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_RELEASE(node);
    return NULL;
}


bool DragNode::init(const std::string name)
{
    if (!Node::init()) {
        return false;
    }
    m_pSprite = Sprite::create(name);
    this->addChild(m_pSprite);
    m_cActionPoint = m_pSprite->getAnchorPointInPoints();
    this->setContentSize(m_pSprite->getContentSize());
    return true;
}
bool DragNode::initWithSpriteFrameName(const std::string name)
{
    if (!Node::init()) {
        return false;
    }
    m_pSprite = Sprite::createWithSpriteFrameName(name);
    this->addChild(m_pSprite);
    m_cActionPoint = m_pSprite->getAnchorPointInPoints();
    this->setContentSize(m_pSprite->getContentSize());
    return true;
}

bool DragNode::initWithTexture(cocos2d::Texture2D *texture)
{
    if (!Node::init()) {
        return false;
    }
    m_pSprite = Sprite::createWithTexture(texture);
    this->addChild(m_pSprite);
    m_cActionPoint = m_pSprite->getAnchorPointInPoints();
    this->setContentSize(m_pSprite->getContentSize());
    
    
    return true;
}
void DragNode::onEnter()
{
    Node::onEnter();
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(DragNode::ccTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(DragNode::ccTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(DragNode::ccTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(DragNode::ccTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    m_pListener = listener;
}

void DragNode::onExit()
{
    Node::onExit();
}

void DragNode::setTouchEnabled(bool var)
{
    m_bTouchEnable = var;
//    if (!m_bTouchEnable) {
//        if (m_pListener) {
//            _eventDispatcher->removeEventListener(m_pListener);
//            m_pListener = nullptr;
//        }
//    }else{
//        EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
//        listener->setSwallowTouches(true);
//        listener->onTouchBegan = CC_CALLBACK_2(DragNode::ccTouchBegan, this);
//        listener->onTouchMoved = CC_CALLBACK_2(DragNode::ccTouchMoved, this);
//        listener->onTouchEnded = CC_CALLBACK_2(DragNode::ccTouchEnded, this);
//        listener->onTouchCancelled = CC_CALLBACK_2(DragNode::ccTouchCancelled, this);
//        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//        m_pListener = listener;
//    }
}

bool DragNode::getTouchEnabled()
{
    return m_bTouchEnable;
}

void DragNode::setMovable(bool var)
{
    m_bMovable = var;
}

bool DragNode::getMovable()
{
    return m_bMovable;
}

void DragNode::setTouchPriority(int var)
{
    m_nTouchPriority = var;
}

int DragNode::getTouchPriority()
{
    return m_nTouchPriority;
}

void DragNode::setActionPoint(cocos2d::Point var)
{
    m_cActionPoint = var;
}

Point DragNode::getActionPoint()
{
    return m_cActionPoint;
}

void DragNode::setLimitRect(cocos2d::Rect var)
{
    m_cLimitRect = var;
}

Rect DragNode::getLimitRect()
{
    return m_cLimitRect;
}

Point DragNode::getOrgPosition()
{
    return m_cOrgPosition;
}

void DragNode::setOrgPosition(cocos2d::Point var)
{
    m_cOrgPosition = var;
}

void DragNode::setOrgPositionDefault()
{
    m_cOrgPosition = this->getPosition();
}
Point DragNode::getWorldSpaceActionPoint()
{
//    Point leftBottomPoint = Vec2(Vec2(this->getContentSize().width*m_pSprite->getAnchorPoint().x*getScaleX(), this->getContentSize().height*m_pSprite->getAnchorPoint().y)*getScaleY(),this->getPosition());
//    Point point = Vec2(-Vec2(m_cActionPoint.x*getScaleX(), m_cActionPoint.y*getScaleY()), leftBottomPoint);
//    point = this->getParent()->convertToWorldSpace(point);
    Point point = m_pSprite->convertToWorldSpace(m_cActionPoint);
    log("====%f,%f===",point.x,point.y);
    log("====%f,%f===",point.x,point.y);
    return point;
}

Sprite* DragNode::getDragSprite(){
    return m_pSprite;
}
void DragNode::setDragSprite(Sprite* sprite){
    if (m_pSprite) {
        m_pSprite->removeFromParent();
    }
    m_pSprite = sprite;
    this->addChild(m_pSprite);
    this->setContentSize(sprite->getContentSize());
}
bool DragNode::ccTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (!m_bTouchEnable) {
        return false;
    }
    m_bIsMoved = false;
    Point location = pTouch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    Point point = this->getParent()->convertToWorldSpace(this->getPosition());
    log("====%f,%f",getContentSize().width,getContentSize().height);
    Rect rect = Rect(point.x-this->getContentSize().width*m_pSprite->getAnchorPoint().x*getScaleX(), point.y-this->getContentSize().height*m_pSprite->getAnchorPoint().y*getScaleY(), this->getContentSize().width*getScaleX(), this->getContentSize().height*getScaleY());
    
    if (!rect.containsPoint(location)) {
        log("dont contain");
        return false;
    }
    log("contain");
    if (dragNodeTouchBegin) {
        dragNodeTouchBegin(this,getWorldSpaceActionPoint());
    }
    return true;
}

void DragNode::ccTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    
    if (!m_bTouchEnable) {
        return;
    }
    if (!m_bMovable) {
        return;
    }
    //    m_bIsMoved = true;
    Point newPt = Vec2(-this->getPosition(), pTouch->getDelta());
    Point offset = pTouch->getDelta();
    Point newPtWold  = this->getParent()->convertToWorldSpace(newPt);
    if (fabs(offset.x)>5||fabs(offset.y)>5) {
        m_bIsMoved = true;
    }
    if (m_cLimitRect.equals(Rect::ZERO)) {
        this->setPosition(newPt);
        m_cOffset = offset;
        if (dragNodeTouchMoved && !ignoreMoving) {
            dragNodeTouchMoved(this, getWorldSpaceActionPoint());
        }
    }else if(m_cLimitRect.containsPoint(newPtWold)){
        this->setPosition(newPt);
        m_cOffset = offset;
        if (dragNodeTouchMoved && !ignoreMoving) {
            dragNodeTouchMoved(this, getWorldSpaceActionPoint());
        }
    }else{
    }
}

void DragNode::ccTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    Point location = pTouch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    if (m_bIsMoved) {
        log("=========dragNodeMoveEnd ===");
        if (dragNodeTouchEnded) {
            dragNodeTouchEnded(this, getWorldSpaceActionPoint());
        }
    }else{
        log("=========dragNodeClicked ===");
        
        if (dragNodeClicked) {
            dragNodeClicked(this, getWorldSpaceActionPoint());
        }
    }
}

void DragNode::ccTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    ccTouchEnded(pTouch, pEvent);
}

