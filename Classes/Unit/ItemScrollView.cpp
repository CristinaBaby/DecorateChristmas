
#include "ItemScrollView.h"

ItemCell* ItemCell::create(const std::string bgPath,const std::string bgHighlight,const std::string btn,const std::string lock)
{
    
    auto pRet = new ItemCell();
    if (pRet && pRet->init(bgPath,bgHighlight,btn,lock))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool ItemCell::init(const std::string bgPath,const std::string bgHighlight,const std::string btn,const std::string lock)
{
    if (!Node::init() )
    {
        return false;
    };
    m_pBg = nullptr;
    onItemCellSelected = nullptr;
    m_pLock = nullptr;
    
    m_sBgPath = bgPath;
    m_sBgHighlightPath = bgHighlight;
    
    if (std::strcmp(m_sBgPath.c_str(), "")) {
        m_pBg = Sprite::create(bgPath);
        if (m_pBg) {
            this->addChild(m_pBg);
        }
    }
    if (std::strcmp(m_sBgHighlightPath.c_str(), "")) {
        m_pBgHeighlight = Sprite::create(m_sBgHighlightPath);
        if (m_pBgHeighlight) {
            this->addChild(m_pBgHeighlight);
            m_pBgHeighlight->setVisible(false);
        }
    }
    m_pBtn = Button::create(btn,btn,btn);
    m_pBtn->setPressedActionEnabled(false);
    this->addChild(m_pBtn);
    
    if (std::strcmp(lock.c_str(), "")) {
        m_pLock = Sprite::create(lock);
        if (m_pLock) {
            this->addChild(m_pLock);
            m_pLock->setPosition(Vec2(m_pBtn->getContentSize().width/2-40, -m_pBtn->getContentSize().width/2+40));
        }
    }
    m_pBtn->setTouchEnabled(false);
    this->setContentSize(m_pBtn->getContentSize());
//    m_pBtn->addTouchEventListener([=](Ref* ref,Widget::TouchEventType type){
//        if (type==Widget::TouchEventType::ENDED){
//            m_pBtn->setTouchEnabled(false);
////            this->setSelected(true);
//            if (onItemCellSelected) {
//                this->onItemCellSelected(this);
//            }
//        }
//    });
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    listener->onTouchBegan = [=](Touch* pTouch, Event* event)
    {
        Vec2 point = pTouch->getLocation();
        point = this->convertToNodeSpace(point);
        Rect rect = m_pBtn->getBoundingBox();
        if (!rect.containsPoint(point)) {
            return false;
        }
        log("contain");
        return true;
    };
    listener->onTouchEnded = [=](Touch*, Event*)
    {
        if (onItemCellSelected) {
            this->onItemCellSelected(this);
        }
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//    m_pBtn->setTouchEnabled(false);
    
    return true;
}

void ItemCell::setSelected(bool selected)
{
    if (selected) {
//        m_pBtn->setTouchEnabled(false);
        
        if (m_pBg) {
            m_pBg->setVisible(false);
        }
        if (m_pBgHeighlight) {
            m_pBgHeighlight->setVisible(true);
        }
    }else {
//        m_pBtn->setTouchEnabled(true);
        
        if (m_pBg) {
            m_pBg->setVisible(true);
        }
        if (m_pBgHeighlight) {
            m_pBgHeighlight->setVisible(false);
        }
        
    }
}



ItemScrollView::ItemScrollView()
{
    
}

ItemScrollView::~ItemScrollView()
{
    
}
ItemScrollView* ItemScrollView::createWithSize(cocos2d::Size size)
{
    auto pRet = new ItemScrollView();
    if (pRet && pRet->init(size))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool ItemScrollView::init(Size size)
{
    if ( !Layer::init() )
    {
        return false;
    };
    decorationData.init();
    indexOffset = 0;
    lockFreeCount = 0;
    levelFreeCount  = 0;
    colNum = 1;
    m_pCurCell = nullptr;
    onItemCellSelected = nullptr;
    
    Sprite* m_pBoard = Sprite::create("content/category/icon/board1.png");
    this->addChild(m_pBoard);
//    CMVisibleRect::setPositionAdapted(m_pBoard, m_pBoard->getContentSize().width*0.6, size.height/2);
    m_pBoard->setPosition(Vec2( m_pBoard->getContentSize().width*0.6, size.height/2));
    
    m_pTableView = TableView::create(this, size);
    m_pTableView->setColor(Color3B(200, 200, 200));
    this->addChild(m_pTableView);
    m_pTableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
    m_pTableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    m_pTableView->setDelegate(this);
    m_pTableView->setSwallowsTouches(true);
    
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* pTouch, Event* event)
    {
        return true;
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}


TableViewCell* ItemScrollView::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildrenWithCleanup(true);
    log("idx = %zd",idx);
    int index = idx*colNum;
//    if (idx>=decorationData.freeCount+levelFreeCount && idx<decorationData.freeCount+decorationData.levelCount) {
//        lockName = "Cocos/ui/studio_ui/pubilc/lmg_lock_level.png";
//    }else if (idx>=decorationData.freeCount+decorationData.levelCount+lockFreeCount){
//        lockName = "Cocos/ui/studio_ui/pubilc/img_lock_normal.png";
//    }
    for (int i = 0; i<colNum; i++) {
        if (index+i>=decorationData.totalCount) {
            break;
        }
        std::stringstream ostr;
        ostr<<btnPathEX<<index+i+decorationData.beginIndex<<".png";
        string lockName = "content/common/lock.png";
        if (index+i<decorationData.freeCount) {
            lockName="";
        }else if (index+i<decorationData.totalCount+decorationData.beginIndex && index+i>=decorationData.holidayIndex && decorationData.holidayIndex>=0 && decorationData.holidayCount==0){
            lockName="";            
        }
        if (gNoneIap){
            lockName="";
        }
        ItemCell* item = ItemCell::create(bgPath, bgHighlightPath, std::string(ostr.str()),lockName);
        item->setTag(index+i+decorationData.beginIndex);
        cell->addChild(item);
        item->onItemCellSelected = CC_CALLBACK_1(ItemScrollView::_itemSelected, this);
        item->setPosition(Vec2(90+155*i, 60));
    }
    return cell;
    
}

ssize_t ItemScrollView::numberOfCellsInTableView(TableView *table)
{
    return (decorationData.totalCount+colNum)/colNum;
}

void ItemScrollView::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("=====");
//    int index = cell->getTag();
//    if (cell==m_pCurCell) {
//        
//    }else{
//        if (m_pCurCell) {
//            ItemCell* item = (ItemCell*)m_pCurCell->getChildByTag(0);
//            if (item) {
//                item->setSelected(false);
//            }
//        }
//        m_pCurCell = cell;
//        ItemCell* item = (ItemCell*)m_pCurCell->getChildByTag(0);
//        if (item) {
//            item->setSelected(true);
//        }
//        if(this->onItemCellSelected){
//            this->onItemCellSelected(index);
//        }
//    }
}

void ItemScrollView::scrollToNext()
{
    Vec2 offset = m_pTableView->getContentOffset();
    if (offset.x-500>-m_pTableView->getContentSize().width) {
        m_pTableView->setContentOffset(Vec2(offset.x-500, 0),0.2);
    }else{
        m_pTableView->setContentOffset(Vec2(500-m_pTableView->getContentSize().width, 0),0.2);
    }
}

void ItemScrollView::scrollToPre()
{
    Vec2 offset = m_pTableView->getContentOffset();
    if (offset.x+500<0) {
        m_pTableView->setContentOffset(Vec2(offset.x+500, 0),0.2);
    }else{
        m_pTableView->setContentOffset(Vec2::ZERO,0.2);
    }
    
}
void ItemScrollView::_itemSelected(ItemCell* cell)
{
    if (m_pTableView->isTouchMoved()) {
        return;
    }
    Rect rect = m_pTableView->boundingBox();
    rect.origin = m_pTableView->getParent()->convertToWorldSpace(rect.origin);
    Vec2 pointTop = cell->getParent()->convertToWorldSpace(Vec2(cell->getContentSize().width*0.5, cell->getContentSize().height*0.5));
    Vec2 pointDown = cell->getParent()->convertToWorldSpace(Vec2(cell->getContentSize().width*0.5, cell->getContentSize().height*0.5));
    if (!rect.containsPoint(pointTop) && !rect.containsPoint(pointDown)) {
        log("touch no in scrollview");
        return;
    }
    if(onItemCellSelected){
        onItemCellSelected(cell->getTag(),DecorateConfigData::copy(decorationData));
    }
}

