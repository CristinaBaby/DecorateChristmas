
#include "DecTypeScrollView.h"



DecTypeScrollView::DecTypeScrollView()
{
    m_pCurTypeBtn = nullptr;
    onItemCellSelected = nullptr;
}

DecTypeScrollView::~DecTypeScrollView()
{
    
}
DecTypeScrollView* DecTypeScrollView::createWithSize(cocos2d::Size size)
{
    auto pRet = new DecTypeScrollView();
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

bool DecTypeScrollView::init(Size size)
{
    if ( !Layer::init() )
    {
        return false;
    };
    m_eDirection = Direction::eDirectionH;
    decTypeData.init();
    
    onItemCellSelected = nullptr;
    m_nPercent = 0;
    m_pBoard = Sprite::create("content/category/icon/board0.png");
    this->addChild(m_pBoard);
    CMVisibleRect::setPositionAdapted(m_pBoard, m_pBoard->getContentSize().width*0.4, visibleSize.height/2);
    
    m_pScrollView = ExpandScrollView::create();
    this->addChild(m_pScrollView);
    m_pScrollView->setPosition(Vec2(0, 5));
    m_pScrollView->setContentSize(size);
    m_pScrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
    return true;
}

void DecTypeScrollView::loadType(std::vector<DecorateTypeConfigData> vec)
{
    m_DecTypeVector = vec;
    int i = 0;
    float deltX = 0;
    float deltY = 0;
    float margin = 0;
    for (auto it = vec.begin(); it!=vec.end(); ++it) {
        Button* pBtn = Button::create(btnPathEX+it->decIconName+".png",btnPathEX+it->decIconName+".png");
        m_pScrollView->getInnerContainer()->addChild(pBtn);
        
        deltX = pBtn->getContentSize().width;
        deltY = pBtn->getContentSize().height;
        if (m_eDirection==Direction::eDirectionH) {
            pBtn->setPosition(Vec2(deltX*0.5+(deltX+10)*i, deltY/2));
        }else{
            pBtn->setPosition(Vec2(deltX/2+20,deltY*0.7+(deltY*1.3)*(vec.size()-i-1)));
        }
        pBtn->setTag(i);
        pBtn->addTouchEventListener(CC_CALLBACK_2(DecTypeScrollView::_itemSelected, this));
        i++;
    }
    if (m_eDirection==Direction::eDirectionH) {
        m_pScrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
        m_pScrollView->setInnerContainerSize(Size(deltX*0.5+(deltX+10)*m_DecTypeVector.size(), deltY));
        CMVisibleRect::setPositionAdapted(m_pBoard, m_pBoard->getContentSize().width*0.4, visibleSize.height*0.5);
    }else{
        m_pScrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
        m_pScrollView->setInnerContainerSize(Size(deltX,deltY*0.1+(deltY*1.3)*m_DecTypeVector.size()));
        CMVisibleRect::setPositionAdapted(m_pBoard, m_pBoard->getContentSize().width*0.2,m_pScrollView->getContentSize().height/2);
        m_pBoard->setPosition(Vec2( m_pBoard->getContentSize().width*0.2, m_pScrollView->getContentSize().height/2));
    }
}
void DecTypeScrollView::scrollToNext()
{
    int percent = getPercent();
    if (percent>100) {
        percent = 100;
    }
    m_pScrollView->scrollToPercentHorizontal(percent, 1, true);
    m_nPercent = percent;
}

void DecTypeScrollView::scrollToPre()
{
    float offsetX = m_pScrollView->getInnerContainerSize().width*m_nPercent/100;
    float percent = (offsetX-m_pScrollView->getContentSize().width)*100/m_pScrollView->getInnerContainerSize().width;
    if (percent<100) {
        percent = 0;
    }
    m_pScrollView->scrollToPercentHorizontal(percent, 1, true);
    m_nPercent = percent;
    
}

int DecTypeScrollView::getPercent()
{
    float offsetX = -m_pScrollView->getInnerContainer()->getPositionX();
    m_nPercent = (offsetX+m_pScrollView->getContentSize().width)*100/m_pScrollView->getInnerContainerSize().width;
    return m_nPercent;
}

void DecTypeScrollView::_itemSelected(Ref* ref,Widget::TouchEventType type)
{
    if (type==Widget::TouchEventType::ENDED) {
        Button* btn = (Button*)ref;
        int tag = btn->getTag();
        DecorateTypeConfigData data = m_DecTypeVector.at(tag);
        if (btn==m_pCurTypeBtn) {
            btn->loadTextureNormal(btnPathEX+data.decIconName+".png");
            onItemCellSelected(tag,data.decTypeName,false);
            m_pCurTypeBtn = nullptr;
        }else{
            if (m_pCurTypeBtn) {
                int tag = m_pCurTypeBtn->getTag();
                DecorateTypeConfigData data = m_DecTypeVector.at(tag);
                m_pCurTypeBtn->loadTextureNormal(btnPathEX+data.decIconName+".png");
            }
            if (btn) {
                btn->loadTextureNormal(btnPathEX+data.decIconName+"_h.png");
            }
            m_pCurTypeBtn = btn;
            if(onItemCellSelected){
                onItemCellSelected(tag,data.decTypeName,true);
            }
        }
    }
}

